/**
 * Credit.c
 */

#include "../inc/functions.h"

/**
 * Contains function calls to draw and handle the 
 * credit screen
 * 
 * @author Joseph Deming
 * @version 0.0.1
 */


/**
 * Credits
 * -------
 * 
 * Primary function for the Credit Scene to load.
 * 
 * @param none
 * @return bool - true or false depending on the exit condition for this function
 */
bool Credits() {
    Texture2D title   = LoadTexture("assets/menu/The-Walk-Home-test.png");
    Texture2D bg      = LoadTexture("assets/background/credit_screen.png");
    Texture2D assets  = LoadTexture("assets/credits/Assets.png");
    Texture2D programming = LoadTexture("assets/credits/programming.png"); 

    Rectangle titlehitBox = (Rectangle){0 + title.width / 3, 0  + title.height/2,title.width, title.height};

    Button quit_button = {
        LoadTexture("assets/menu/quit_sheet.png"),
        (Rectangle){ SCREEN_WIDTH / 2 - quit_button.texture.width*3,SCREEN_HEIGHT/1.5, 200,100},
        false
    };

    bool state   = false;
    bool escaped = false;

    while (!state) { // while the game isn't supposed to start
        if (ButtonHandler(&quit_button) || WindowShouldClose()) { escaped = true; break; }

        BeginDrawing();
        {
            ClearBackground(WHITE);

            DrawCreditScreen(bg, assets, programming);
            DrawTitle(title, titlehitBox);
            DrawButton(&quit_button);
            
        } EndDrawing();
    }


    UnloadTexture(quit_button.texture);
    UnloadTexture(assets);
    UnloadTexture(programming);
    UnloadTexture(title);

    return escaped;

}