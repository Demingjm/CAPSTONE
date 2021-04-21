/**
 * Functions.c
 */

#include "../inc/functions.h"

/**
 * This file holds all of the functions for initializing the
 * player entity and camera. As well as functions for collision detection,
 * and eventually drawing textures.
 * 
 * @author Joseph Deming
 * @author Hunter Craig
 * 
 * @version 1.1.2
 */

//global variable
float speedMult = 1.0f;

/**
 * UpdatePlayer
 * ------------
 * 
 * Updates the players position in relation to environment items.
 * Collision detection is performed here, and player stats are modified here
 * as well when collision occurs with a powerup item or obstacle
 * 
 * @param player - pointer to the entity being updated
 * @param envItems - array of environment items used for collision 
 * @param envItemsLength - length of the array of environment items
 * @param deltaTime - change in time between each frame update
 * 
 * @return none - returns nothing
 */

void UpdatePlayer(Entity *player, EnvItem *map, int mapLength, float deltaTime, bool *game_state, Sound *gameSounds) {
    float horizontal = IsKeyDown(KEY_D) - IsKeyDown(KEY_A); // used to determine the direction the player is moving, if both keys are pressed then horizontal = 0 and the player won't move
    int initJumpVelocity = sqrtf(2 * GRAVITY * player->jumpHeight); // the initial y-velocity used when a player jumps

    player->speed = ((IsKeyDown(KEY_LEFT_SHIFT)) ?  DFLT_SPRNT_SPD : DFLT_SPD) * speedMult;

    //Change players velocity in respect to keys pressed, gravity, and change in time
    player->velocity.x += horizontal * player->speed * deltaTime;
    player->velocity.y += GRAVITY * deltaTime;

    // calculate the magnitude of velocity; ||V|| = sqrt(vx^2 + vy^2) 
    float velocity = sqrtf(powf(player->velocity.x, 2) + powf(player->velocity.y, 2));

    // This checks and sets velocity if the magnitude exceeds
    // the maximum velocity threshold to prevent infinite acceleration
    if (velocity > MAX_VELOCITY) {
        Vector2 temp = player->velocity;
        player->velocity = Vector2Scale(temp, (MAX_VELOCITY / velocity));
    }

    player->velocity.x /= (1 + FRICTION * deltaTime);
    player->velocity.y /= (1 + FRICTION * deltaTime);

    if (isnan(player->velocity.x)) player->velocity.x = 0;
    if (isnan(player->velocity.y)) player->velocity.y = 0;

    for (int i = 0; i < mapLength; i++) {
        if (map[i].blocking && PredictCollision(*player, map[i])) { // if this object isn't passable and collision 'will' occur then resolve it
            ResolveCollision(player, map[i], deltaTime);
        }
    }

    if (player->canJump && (IsKeyDown(KEY_W))) { 
        PlaySound(gameSounds[3]);
        player->velocity.y = -initJumpVelocity; 
        player->canJump = false; 
    } // player is trying to jump, change their velocity and play jump sound

    player->hitBox.x += player->velocity.x;
    player->hitBox.y += player->velocity.y;

    if (player->invincible && ((GetTime() - player->hurtTime) >= 2))     // invincibility lasts for 2 seconds,
        player->invincible = false;                                      // during this period the player
                                                                         // cannot be harmed

    for (int i = 0; i < mapLength; i++) {
        if (!map[i].blocking && !map[i].used &&  //if the current item isn't blocking, hasn't been consumed, and is in collision then proceed
            CheckCollisionRecs(player->hitBox, map[i].hitBox)) {
                switch (map[i].id) {
                    case 3:
                        // fire obstacle
                        if (!player->invincible){
                            player->hearts--;
                            PlaySound(gameSounds[2]);
                            player->invincible = true;
                            player->hurtTime = GetTime(); // store when the player was hurt
                            heartsLost++;
                        }
                        // todo check if player was hit "recently"
                        break;
                    case 5:
                        player->jumpHeight = DFLT_JMP_HT;
                        PlaySound(gameSounds[4]);
                        speedMult = 2; //double the players speed

                        break;
                    case 6:
                        speedMult = 1;
                        PlaySound(gameSounds[4]);
                        player->jumpHeight = MAX_JMP_HT;

                        break;
                    case 7:
                        if (player->hearts <= 2) {
                            PlaySound(gameSounds[5]);
                        }
                        player->hearts += !(player->hearts % 3) ? 0 : 1;
                        break;
                    case 8:
                        player->coins++;
                        PlaySound(gameSounds[0]);
                        totalCoins++;
                        break;
                    case 10:
                        //ResetGame(player, map, mapLength);
                        *game_state = false;
                        
                        break;
                    default:
                        printf("How did we end up here?\n");
                        break; //shouldn't get here
                }
                map[i].used = (map[i].id == 10 || map[i].id == 3) ? false : true; // if the item collided with isn't a goal or obstacle thenit has been consumed
            }
    }


    // now update the players x position
    // TODO: replace hard coded numbers with #defines for world borders

    // check if player is at the world border
    if (player->hitBox.x < 0) { player->hitBox.x = 0; player->velocity.x = 0; }

    float mapEdge = map[mapLength - 1].hitBox.x + map[mapLength - 1].hitBox.width;

    if (player->hitBox.x + player->hitBox.width > mapEdge) { // Prevent player from exceeding the edge of the map
       player->hitBox.x = mapEdge - player->hitBox.width; 
       player->velocity.x = 0; 
    }

    if (player->hitBox.y < 150) { player->hitBox.y = 150; player->velocity.y = 0; }

    //Check if player has fallen through pit/world, reset game and play death sound
    if (player->hitBox.y > 1300 || player->hearts <= 0) { 
        PlaySound(gameSounds[1]);
        ResetGame(player, map, mapLength); 
    };

    
}

/**
 * UpdateCameraCenter
 * ------------------
 * 
 * Updates the camera position and offset relative to the players position
 * and position of environment items.
 * 
 * Determines max/min between the players position, environment item position, and screen dimensions
 * to calculate the proper offset for the camera.
 * 
 * @param camera - pointer to the 2D camera being updated
 * @param player - pointer to the entity the camera should focus on
 * @param envItems - array of environment items
 * @param envItemsLength - length of the array of environment items
 * @param width  - screen width
 * @param height - screen height
 * 
 * @return none - returns nothing
 */

void UpdateCameraCenter(Camera2D *camera, Entity *player, EnvItem *map, int mapLength, int width, int height) {
    // reset camera position
    camera->target = (Vector2){player->hitBox.x, player->hitBox.y};
    camera->offset = (Vector2){width / 2, height / 2};

    float minX = 0, minY = 150, maxX = MAX_CMA_X, maxY = MAX_CMA_Y;

    /* Runs through the entire map and sets the min and max for the map*/
    for (int i = 0; i < mapLength; i++) {
        EnvItem temp = map[i];
        minX = fminf(temp.hitBox.x, minX);
        maxX = fmaxf(temp.hitBox.x, maxX);
    }

    Vector2 max = GetWorldToScreen2D((Vector2){maxX, maxY}, *camera); // sets the maximum position for the camera
    Vector2 min = GetWorldToScreen2D((Vector2){minX, minY}, *camera); // sets the minimum position for the camera

    if (max.x < width) camera->offset.x = width - (max.x - width / 2); // if max.x is less than width set the x offset to w - (max - w/2)
    if (min.x > 0) camera->offset.x = width / 2 - min.x; // if minimum pos exceeds 0 then set offest to (w / 2) - min

    camera->offset.y = height / 2 - min.y; // nothing special for the y-offset. (h / 2) - minY
}

/**
 * CreatePlayer
 * ------------
 * 
 * Initializes the player entity with default stats
 * 
 * @param player - pointer to the entity being initialized as player
 * 
 * @return none - returns nothing
 */

void CreatePlayer(Entity *player, Texture2D texture) {
    player->hitBox   = (Rectangle) {10, SCREEN_HEIGHT - 350, PLYR_SZ_X, PLYR_SZ_Y};
    player->velocity = (Vector2) {0,0};
    player->color = PINK;
    player->speed = DFLT_SPD;
    player->jumpHeight = DFLT_JMP_HT;
    player->canJump    = false;
    player->coins  = 0;
    player->hearts = 3;
    player->invincible = false;

    player->sprite.texture   = texture;
    player->sprite.maxFrame  = 6;//(int)(player->sprite.texture.width / (int)player->sprite.texture.height);

    player->sprite.frameWidth  = (float)(player->sprite.texture.width)  / 6;
    player->sprite.frameHeight = (float)(player->sprite.texture.height) / 2;

    player->sprite.timer = 0;
    player->sprite.frame = 0;

}

/**
 * CreateCamera
 * ------------
 * 
 * Initializes the 2D camera used to
 * track the player as it moves through the
 * game.
 * 
 * @param camera - pointer to 2D camera that is being initialized
 * @param player - pointer to player entity that the camera should focus on
 * @param width  - width of the grame window
 * @param height - height of the game window
 * 
 * @return none - returns nothing
 */

void CreateCamera(Camera2D *camera, Entity *player, int width, int height) {
    camera->target = (Vector2){player->hitBox.x, player->hitBox.y};
    camera->offset = (Vector2){width / 2, height / 2};
    camera->rotation = 0.0f;
    camera->zoom = 1.0f;
}

void ResetGame(Entity *player, EnvItem *envItems, int envItemsLength) {
    player->hitBox   = (Rectangle) {10, SCREEN_HEIGHT - 350, PLYR_SZ_X, PLYR_SZ_Y};
    player->velocity = (Vector2) {0,0};
    player->speed    = DFLT_SPD;
    speedMult = 1;
    player->canJump    = false;
    player->jumpHeight = DFLT_JMP_HT;
    player->coins  = 0;
    player->hearts = 3;
    player->invincible = false;

    resets++;
    for (int i = 0; i < envItemsLength; i++) if (envItems[i].used) envItems[i].used = false;
}

/**
 * Debug
 * -----
 * 
 * Displays general data for debugging purposes
 * 
 * @param player - pointer to the player entity being monitored
 * 
 * @return none - returns nothing
 */
void Debug(Entity *player) {
    DrawText(TextFormat("Player X velocity: %f", player->velocity.x), 0, 0, 20, WHITE);
    DrawText(TextFormat("Player Y velocity: %f", player->velocity.y), 0, 20, 20, WHITE);
    DrawText(TextFormat("Player Coordinates: X = %0.0f,  Y = %.0f", player->hitBox.x, player->hitBox.y), 0,40, 20, WHITE);
    DrawText(TextFormat("Coins: %d", player->coins), 0, 100, 20, WHITE);
    DrawText(TextFormat("FPS: %d", GetFPS()), 0, 140, 20, GREEN);
    DrawText(TextFormat("Players Jump Height: %.0f", player->jumpHeight), 0, 200, 20, WHITE);
    DrawText(TextFormat("Players speed: %.0f", player->speed), 0, 240, 20, WHITE);
    DrawText(TextFormat("Hearts: %d / 3", player->hearts),0,300, 20, RED);
    DrawText(TextFormat("Invincible: %s", player->invincible ? "true" : "false"), 0,400,20,BLUE);
}