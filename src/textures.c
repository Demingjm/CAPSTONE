/**
 * Textures.c
 */

#include "../inc/functions.h"

/**
 * textures.c contains the functions for drawing textures to the screen
 * there are also helper routines in this file to assist with loading
 * and unloading the textures used
 * 
 * @author Joseph Deming
 * @version 0.2.2
 */

/**
 * UnloadTextures
 * --------------
 * 
 * Used for unloading arrays of textures
 * 
 * @param textures - array of textures
 * @param length   - length of the array
 * 
 * @return none
 */
void UnloadTextures(Texture2D *textures, int length) {
    for (int i = 0; i < length; i++) {
        UnloadTexture(textures[i]);
    }
}

/**
 * DrawBackground
 * --------------
 * 
 * Draws the images and handles the
 * animation of the background to generate
 * a 2d parallax.
 * 
 * @param bg_textures - array of 2d textures used in the background
 * @param player - used to provide new positions for the background scrolling
 * @param camera - used to provide a stationary position for background images that shouldn't move
 * 
 * @return none - returns nothing
 */
void DrawBackground(Texture2D *textures, Entity player, Camera2D camera) {
 
    // these are the rates that each layer will move
    float scrollingBack  = 0.05f,
          scrollingMid   = 0.1f,
          scrollingFront = 0.3f;
    
    // Draw the sky
    DrawTextureEx(textures[0], (Vector2){0, 0}, 0.0f, 6.0f, WHITE);

    // Draw the farthest mountain
    DrawTextureEx(textures[1], (Vector2){scrollingBack * -player.hitBox.x, 125}, 0.0f, 4.0f, WHITE);
    DrawTextureEx(textures[1], (Vector2){textures[1].width * 2 + scrollingBack * -player.hitBox.x + 20, 125}, 0.0f, 4.0f, WHITE);

    // Draw the closets mountains
    DrawTextureEx(textures[2], (Vector2){scrollingMid * -player.hitBox.x, 125}, 0.0f, 4.0f, WHITE);
    DrawTextureEx(textures[2], (Vector2){textures[2].width * 2 + scrollingMid * -player.hitBox.x, 125}, 0.0f, 4.0f, WHITE);


    // Draw the farthest trees
    DrawTextureEx(textures[3], (Vector2){scrollingFront * -player.hitBox.x, -50}, 0.0f, 5.0f, WHITE);
    DrawTextureEx(textures[3], (Vector2){textures[3].width * 2 + scrollingFront * -player.hitBox.x, -50}, 0.0f, 5.0f, WHITE);

    // Draw the foreground trees, these move with the map itself so they don't change at a separate rate
    DrawTextureEx(textures[4], (Vector2){0, -SCREEN_HEIGHT/4}, 0.0f, 6.0f, WHITE);
    DrawTextureEx(textures[4], (Vector2){textures[4].width * 4 , -SCREEN_HEIGHT/2}, 0.0f, 6.0f, WHITE);
    DrawTextureEx(textures[4], (Vector2){textures[4].width * 8 , -SCREEN_HEIGHT/2}, 0.0f, 6.0f, WHITE);

}

/**
 * DrawMap
 * -------
 * 
 * Draws all of the textures to their corresponding 
 * envItem
 * 
 * @param textures - array of textures that will be drawn
 * @param envItems - array of envItems that are rendered
 * 
 * @return none
 */
void DrawMap(Texture2D *textures, EnvItem *map, int mapLength) {

    /**
     * Textures:
     *  0 - Grass platform block
     *  1 - House Goal Point
     *  2 - standing grass
     *  3 - coin
     *  4 - jump boost
     *  5 - speed boost
     *  6 - heart
     */

    DrawTextureEx(textures[1], (Vector2){1350,SCREEN_HEIGHT-textures[1].height*5}, 0.0f,5.0f,WHITE);
    for (int i = 0; i < mapLength; i ++) {
        switch (map[i].id) {
            case 0:
                DrawTextureEx(textures[0], (Vector2){map[i].hitBox.x, map[i].hitBox.y}, 0.0f, 1.0f, WHITE);
                break;
            case 5:
                if (!map[i].used) DrawTextureEx(textures[5], (Vector2){map[i].hitBox.x, map[i].hitBox.y}, 0.0f, 2.0f, WHITE);
                break;
            case 6:
                if (!map[i].used) DrawTextureEx(textures[4], (Vector2){map[i].hitBox.x, map[i].hitBox.y}, 0.0f, 2.0f, WHITE);
                break;
            case 7:
                if (!map[i].used) DrawTextureEx(textures[6], (Vector2){map[i].hitBox.x, map[i].hitBox.y}, 0.0f, 2.0f, WHITE);
                break;
            case 8:
                if (!map[i].used) DrawTextureEx(textures[3], (Vector2){map[i].hitBox.x, map[i].hitBox.y}, 0.0f, 1.5f, WHITE);
                break;
            default:
                if ((map[i].id != 10) && !map[i].used) DrawRectangleRec(map[i].hitBox, map[i].color);
                break;
        }
    }
    DrawTextureEx(textures[2], (Vector2){map[1].hitBox.x+map[0].hitBox.width, map[0].hitBox.y-textures[2].height*3}, 0.0f, 3.0f, WHITE); // standing grass
}

/**
 * DrawPlayer
 * ----------
 * 
 * Draws the players texture
 * 
 *
 * @param player - pointer to the player entity
 * @param deltaTime - time that has elapsed since the last frame was drawn
 * 
 * @return none - doesn't return anything
 */
void DrawPlayer(Entity *player, float deltaTime) {
    if (DEBUG) DrawRectangleRec(player->hitBox, player->color); //draw players hitBox
    
    player->sprite.timer += deltaTime; // update the frame time
    float height = 0;
    float width  = 0;

    if (player->sprite.timer >= 0.2f) { // if enough time has elapsed draw the next frame
        player->sprite.timer  = 0;      // reset the timer
        player->sprite.frame++;         // increment the frame
    }

    player->sprite.frame %= player->sprite.maxFrame - 1; // check if current frame is out of range
    if (player->sprite.frame == 0) player->sprite.frame++;

    if (player->velocity.x <  0.0f) height = (float)player->sprite.frameHeight;
    if (player->velocity.y != 0.0f) width  = player->sprite.frameWidth * 5;
    else width = player->sprite.frameWidth * player->sprite.frame;

    if (round(player->velocity.x) == 0 && player->velocity.y == 0) width = 0;


    Rectangle src  = (Rectangle) {width, height, player->sprite.frameWidth, player->sprite.frameHeight}; // this is the dimension of the current frame
    Rectangle dst  = player->hitBox; // players hitBox
    Vector2 origin = (Vector2) {0,0}; // origin point for the sprite sheet

    Color fade = WHITE;

    if (player->invincible) {
        if (player->sprite.timer >= 0.1f)
            fade.a = 0;
    }
    
    DrawTexturePro(player->sprite.texture, src, dst, origin, 0.0f, fade); // draw the current sprite frame to the players htiBox

}

/**
 * DrawStartScreen
 * ---------------
 * 
 * Draws the textures for the start screen
 * and animates those textures
 * 
 * @param textures - list of textures to use
 * @param texturesLength - length of the list
 * 
 * @return none
 */
void DrawStartScreen(Texture2D *textures, int textureLength, ScrollState *state) {
    /*
        List of Textures
        0 - sunset background - scale 6
        1 - farthest mountains - scale 4
        2 - closest mountains - scale 4
        3 - farthest trees - scale 4
        4 - closest trees - scale 5
        5 - grass platform block - scale 1
    */


    // Update each rate

    state->f_m_scroll -= 0.1f;
    state->c_m_scroll -= 0.5f;
    state->f_t_scroll -= 1.0f;
    state->c_t_scroll -= 1.5f;
    state->p_scroll   -= 2.0f;

    // Check if out of bounds

    if (state->f_m_scroll <= -textures[1].width*2) state->f_m_scroll = 0.0f;
    if (state->c_m_scroll <= -textures[2].width*2) state->c_m_scroll = 0.0f;
    if (state->f_t_scroll <= -textures[3].width*2) state->f_t_scroll = 0.0f;
    if (state->c_t_scroll <= -textures[4].width*2) state->c_t_scroll = 0.0f;
    if (state->p_scroll <= -textures[5].width*2)   state->p_scroll = 0.0f;

    // Draw the textures

    // The Sunset
    DrawTextureEx(textures[0], (Vector2){0, 0}, 0.0f, 6.0f, WHITE); // this isn't moving so no need to update it

    // Draw the farthest mountain
    DrawTextureEx(textures[1], (Vector2){state->f_m_scroll, 125}, 0.0f, 4.0f, WHITE);
    DrawTextureEx(textures[1], (Vector2){textures[1].width * 2 + state->f_m_scroll, 125}, 0.0f, 4.0f, WHITE);

    // Draw the closets mountains
    DrawTextureEx(textures[2], (Vector2){state->c_m_scroll, 175}, 0.0f, 4.0f, WHITE);
    DrawTextureEx(textures[2], (Vector2){textures[2].width * 2 + state->c_m_scroll, 175}, 0.0f, 4.0f, WHITE);


    // Draw the farthest trees
    DrawTextureEx(textures[3], (Vector2){state->f_t_scroll, 100}, 0.0f, 5.0f, WHITE);
    DrawTextureEx(textures[3], (Vector2){textures[3].width * 2 + state->f_t_scroll, 100}, 0.0f, 5.0f, WHITE);

    // Draw the closest trees
    DrawTextureEx(textures[4], (Vector2){state->c_t_scroll, -50}, 0.0f, 6.0f, WHITE);
    DrawTextureEx(textures[4], (Vector2){textures[4].width * 2 + state->c_t_scroll, -50}, 0.0f, 6.0f, WHITE);
    DrawTextureEx(textures[4], (Vector2){textures[4].width * 4 + state->c_t_scroll, -50}, 0.0f, 6.0f, WHITE);
}

/**
 * DrawStartButton
 * ---------------
 * 
 * Draws the specific frame of the start button
 * based on the current button state
 * x
 * @param button - button struct
 * 
 * @return none
 */
 void DrawButton(Button *button) {

    Rectangle src  = {0,0,button->texture.width, button->texture.height/2};
    Rectangle dst  = button->hitBox;
    Vector2 origin = (Vector2){0,0};

    if (button->state) {
        src.y = button->texture.height/2;
        button->state = false;
    }

    DrawTexturePro(button->texture, src, dst, origin, 0.0f, WHITE);
 }

/**
 * DrawTitle
 * ---------
 * 
 * Draws the title image to a designated rectangle
 * 
 * @param title  - Image of the title
 * @param hitBox - rectangle being drawn too
 * 
 * @return none
 */
 void DrawTitle(Texture2D title, Rectangle hitBox) {
     Rectangle src = (Rectangle){0,0,title.width, title.height};
     Rectangle dst = hitBox;
     Vector2 origin;

     DrawTexturePro(title, src, dst, origin, 0.0f, WHITE);
 }

 /**
  * DrawCreditScreen
  * ----------------
  * 
  * Draws the games credit screen
  * 
  * @param
  * @return none - returns nothing
  */
 void DrawCreditScreen(Texture2D background, Texture2D assets, Texture2D programming) {
    Rectangle src = (Rectangle) {0, 0, background.width, background.height};
    Rectangle dst = (Rectangle) {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    Vector2 origin;

    DrawTexturePro(background, src, dst, origin, 0.0f, WHITE);

    src = (Rectangle) {0,0,assets.width, assets.height};
    dst = (Rectangle) {100,500, assets.width * 2, assets.height * 2};

    DrawTexturePro(assets, src, dst, origin, 0.0f, WHITE);

    src = (Rectangle) {0, 0, programming.width, programming.height};
    dst = (Rectangle) {100, 350, programming.width * 2, programming.height * 2};

    DrawTexturePro(programming, src, dst, origin, 0.0f, WHITE);
 }

/**
 * TransitionSceneOff
 * ------------------
 * 
 * Does a fade in on the screen for smoother transitions
 */
bool SceneFadeOut(Scene *scene) {

    Rectangle src  = (Rectangle) {0,0,scene->screen.width, scene->screen.height};
    Rectangle dst  = scene->hitBox;
    Vector2 origin = {0};
    Color fade = (Color) {0,0,0,scene->frame};

    BeginDrawing();
        ClearBackground(WHITE);
        DrawTexturePro(scene->screen,src, dst, origin, 0.0f, fade);
    EndDrawing();

    scene->frame -= 8;

    if (scene->frame <= 0)
        return true;

    return false;
}

bool SceneFadeIn(Scene *scene) {

    Rectangle src  = (Rectangle) {0,0,scene->screen.width, scene->screen.height};
    Rectangle dst  = scene->hitBox;
    Vector2 origin = {0};
    Color fade = (Color) {0,0,0,scene->frame};

    BeginDrawing();
        ClearBackground(WHITE);
        DrawTexturePro(scene->screen,src, dst, origin, 0.0f, fade);
    EndDrawing();

    scene->frame += 8;

    if (scene->frame >= 255) 
        return true;

    return false;
}

 