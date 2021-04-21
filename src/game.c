/**
 * Game.c
 */

#include "../inc/functions.h"

/**
 * game.c holds the game functions for each level.
 * Each function will contain the textures and function calls necessary to 
 * load, play, and complete each level.
 * 
 * @author Joseph Deming
 * @version 0.1.0
 */




/**
 * PlayGame
 * -------
 * 
 * Contains the loop for the game itself
 * This function is called after the start menu
 * function has ended it's loop
 * 
 * @param none - no params currently
 * 
 * @return none - nothing to return;
 */

int PlayGame(EnvItem *map, int mapLength) {
    bool game_state = true; // change to false when game has complete

    //Initialize everything

    Texture2D bg_textures [] = {
        LoadTexture("assets/background/parallax-mountain-bg.png"),
        LoadTexture("assets/background/parallax-mountain-montain-far.png"),
        LoadTexture("assets/background/parallax-mountain-mountains.png"),
        LoadTexture("assets/background/parallax-mountain-trees.png")

    };

    Texture2D map_textures [] = {
        LoadTexture("assets/map/grass.png"),
        LoadTexture("assets/map/house.png"),
        LoadTexture("assets/map/grass_top.png"),
        LoadTexture("assets/map/coin.png"),
        LoadTexture("assets/map/jump-boost.png"),
        LoadTexture("assets/map/speed-boost.png"),
        LoadTexture("assets/hud/heart.png"),
        LoadTexture("assets/map/fire.png"),
        LoadTexture("assets/background/parallax-mountain-foreground-trees.png"),
        LoadTexture("assets/map/log.png"),
        LoadTexture("assets/map/boulder.png")
    };

    Texture2D hud_textures [] = {
        LoadTexture("assets/hud/heart.png"),
        LoadTexture("assets/hud/heart-empty.png"),
        LoadTexture("assets/map/coin.png"),
        LoadTexture("assets/map/jump-boost.png"),
        LoadTexture("assets/map/speed-boost.png")
    };

    Sound gameSounds [] = {
        LoadSound("assets/sounds/coin_pick_up.wav"),
        LoadSound("assets/sounds/death.wav"),
        LoadSound("assets/sounds/player_hurt.wav"),
        LoadSound("assets/sounds/player_jump.wav"),
        LoadSound("assets/sounds/power_up.wav")
    };

    Music gameMusic = LoadMusicStream("assets/sounds/game_music.mp3");
    SetMusicVolume(gameMusic, 0.2f);
    PlayMusicStream(gameMusic);
    gameMusic.looping = true;

    

    Texture2D playerSprite = LoadTexture("assets/player/player-sprite.png");

    Entity player = { 0 };
    CreatePlayer(&player, playerSprite);

    Camera2D camera = { 0 };
    CreateCamera(&camera, &player, SCREEN_WIDTH, SCREEN_HEIGHT);

    int bg_length           = LENGTH(bg_textures);
    int map_textures_length = LENGTH(map_textures);
    int hud_length          = LENGTH(hud_textures);
    int sound_length        = LENGTH(gameSounds);

    float deltaTime = 0;
    bool escaped    = false;

    while(game_state)  {

        if (WindowShouldClose()) { escaped = true; break; }
        if (IsKeyPressed(KEY_R)) ResetGame(&player, map, mapLength);
        
        // update delta time, player, and camera
        deltaTime = GetFrameTime();
        UpdateCameraCenter(&camera, &player, map, mapLength, SCREEN_WIDTH, SCREEN_HEIGHT);
        UpdateMusicStream(gameMusic);
        

        // begin drawing the window
        BeginDrawing(); {

            // reset the window and set background to white
            ClearBackground(WHITE);

            DrawBackground(bg_textures, player, camera); // draw this outside of the camera to prevent issues with how the image is drawn
            DrawHud(hud_textures, player, camera);
            

            // used to initialize 2d mode with the camera 
            BeginMode2D(camera); {

                DrawMap(map_textures, map, mapLength);
                UpdatePlayer(&player, map, mapLength, deltaTime, &game_state, gameSounds);
                DrawPlayer(&player, deltaTime);

            } EndMode2D();

            //This is simply for debugging
            //Todo: replace with helper function for debug uses
            if (DEBUG) Debug(&player);
            
        } EndDrawing();
    }

        UnloadTexture(playerSprite);
        UnloadTextures(bg_textures, bg_length);
        UnloadTextures(map_textures, map_textures_length);
        UnloadTextures(hud_textures, hud_length);
        for (int i = 0; i < sound_length; i++) {
            UnloadSound(gameSounds[i]);
        }   
        UnloadMusicStream(gameMusic);

        if (escaped) 
            return 1;
        
        return 0;
}