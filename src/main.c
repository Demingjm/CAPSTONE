/**
 * main.c
 */

#include "../inc/functions.h"

/**
 * main.c contains the main method for the game.
 * This file initializes the screen and pushes
 * all necessary functions on to the state manager
 * stack and destroys as needed
 * 
 * @author Joseph Deming
 * @author Hunter Craig
 * 
 * @version 0.1.4
 */


/**
 * main
 * ----
 * 
 * Main method for the game. This function
 * makes calls to other game functions inside the main loop
 * to make the game function as intended.
 * 
 * @param  none - no parameters
 * 
 * @return none - returns nothing
 */

    double playTime   = 0;
    short  totalCoins = 0;
    short  heartsLost = 0;
    short  resets     = 0;


int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The Walk Home");
    Image icon = LoadImage("assets/icon/icon.png");
    SetWindowIcon(icon);

    SetTargetFPS(60);
    //Level creation code goes here. Beware filepaths!
    int level4Length = 0;
    EnvItem *level4 = CreateLevel("assets/levels/level4.txt", &level4Length);
    // level4Length--;
    
    //Sound loading code
    InitAudioDevice();

    // Main game loop
    // Loop runs as long as the window
    // isn't set to close.
    while(!WindowShouldClose()) {
        //Todo: implement state manager stack



        if (StartGame()) break;
        Transition(1);
        playTime = GetTime();
        if (PlayGame(level1, LENGTH(level1)))  break;
        Transition(2);
        if (PlayGame(level2, LENGTH(level2))) break;
        Transition(3);
        if (PlayGame(level3, LENGTH(level3))) break;
        Transition(4);
        if ((level4 == NULL) || PlayGame(level4, level4Length)) break;



        FadeIn();
        if (newCreditScreen()) break;
        FadeIn();
    }
    free(level4);
    CloseAudioDevice();
    CloseWindow(); // tell opengl to close the window

    return 0;
}