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

int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The Walk Home");
    Image icon = LoadImage("assets/icon/icon.png");
    SetWindowIcon(icon);

    SetTargetFPS(60);

    // Main game loop
    // Loop runs as long as the window
    // isn't set to close.
    while(!WindowShouldClose()) {
        //Todo: implement state manager stack



        if (StartGame()) break;
        Transition(1);
        if (PlayGame(level1, LENGTH(level1)))  break;
        Transition(2);
        if (PlayGame(level2, LENGTH(level2))) break;
        FadeIn();
        if (newCreditScreen())   break;
        FadeIn();
    }

    CloseWindow(); // tell opengl to close the window

    return 0;
}