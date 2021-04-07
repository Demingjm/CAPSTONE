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

bool newCreditScreen() {
    Texture2D credits = LoadTexture("assets/credits/credits.png");
    Texture2D title   = LoadTexture("assets/menu/The-Walk-Home-test.png");
    Texture2D bg      = LoadTexture("assets/background/credit_screen.png");

    Rectangle titlehitBox = (Rectangle){0 + title.width / 3, 0  + title.height/2,title.width, title.height};
    Rectangle creditsHitBox = (Rectangle){SCREEN_WIDTH - (title.width / 2), SCREEN_HEIGHT, credits.width, credits.height};

    Button quit_button = {
        LoadTexture("assets/menu/quit_sheet.png"),
        (Rectangle){ SCREEN_WIDTH / 2 - quit_button.texture.width*3,SCREEN_HEIGHT/1.5, 200,100},
        false
    };

    bool quit    = false;
    bool escaped = false;

    float scroll    = 1.0f;
    short amplitude = 0;

    double elapsedTime = GetElapsedTime(playTime);

    const char *timeComplete  = ConvertTime(elapsedTime);

    while (!quit) {
        if (ButtonHandler(&quit_button) || WindowShouldClose()) { escaped = true; break; }

        BeginDrawing();
            ClearBackground(WHITE);

            
            Rectangle src = (Rectangle) {0, 0, bg.width, bg.height};
            Rectangle dst = (Rectangle) {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
            Vector2 origin;

            DrawTexturePro(bg, src, dst, origin, 0.0f, WHITE);

            if ((creditsHitBox.y + creditsHitBox.height) > 0) {
                src = (Rectangle) {0,0,credits.width, credits.height};
                origin = (Vector2) {0,0};

                creditsHitBox.y -= scroll;

                DrawTexturePro(credits, src, creditsHitBox, origin, 0.0f, WHITE);
            } else {
                src = (Rectangle){0,0,title.width, title.height};
                dst = titlehitBox;
                origin = (Vector2) {0,0};

                Color fade = (Color) {255,255,255,amplitude};

                DrawTexturePro(title, src, dst, origin,0.0f, fade);
                if (amplitude < 255) {
                    amplitude = (amplitude + 16) > 255 ? 255 : amplitude + 16;  
                } else {
                    DrawButton(&quit_button);
                    DrawStats(timeComplete);
                }
            }
        EndDrawing();
    }

    UnloadTexture(quit_button.texture);
    UnloadTexture(title);

    return escaped;
}