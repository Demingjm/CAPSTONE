/*********************************************************************
 _____ _            __    __      _ _                                 
/__   \ |__   ___  / / /\ \ \__ _| | | __   /\  /\___  _ __ ___   ___ 
  / /\/ '_ \ / _ \ \ \/  \/ / _` | | |/ /  / /_/ / _ \| '_ ` _ \ / _ \
 / /  | | | |  __/  \  /\  / (_| | |   <  / __  / (_) | | | | | |  __/
 \/   |_| |_|\___|   \/  \/ \__,_|_|_|\_\ \/ /_/ \___/|_| |_| |_|\___|
                                                                      
----------------------------------------------------------------------
By: Joseph Deming & Hunter Craig

Version: alpha-1.1.6


***********************************************************************/


#ifndef FUCNTIONS_H
#define FUNCTIONS_H

#include "raylib.h"
#include "raymath.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

//physics constants
#define GRAVITY 9.80665f
#define MAX_VELOCITY 200.0f
#define FRICTION 0.5f

//player constants
#define MAX_JMP_HT 6
#define DFLT_JMP_HT 3
#define DFLT_SPD 1.5f
#define DFLT_SPRNT_SPD 4.0f
#define PLYR_SZ_X 35.0f
#define PLYR_SZ_Y 70.0f

// envItems constants
#define ITEM_SZ 25.0f
#define PLTFRM_SZ 150.f

//camera constants
#define MAX_CMA_X 1600
#define MAX_CMA_Y 5000

#define DEBUG true //set to true for debug info

//for fun
#define YES 1

// general purpose macros
//#define LENGTH(arr) ((sizeof(arr)/sizeof(0[arr])) / ((size_t)(!(sizeof(arr) % sizeof(0[arr]))))) <- cool macro for getting length of array
#define LENGTH(arr) (sizeof(arr) / sizeof(*arr))




typedef struct Sprite {
    Texture2D texture;
    int maxFrame;   // 
    float frameWidth; // number of columns in the sprite frame
    float frameHeight;
    Vector2 origin; // starting point for drawing the sprite
    int frame;      //
    float timer; 
} Sprite;

typedef struct Entity {
    Rectangle hitBox;
    Vector2 velocity;
    Color color;
    Sprite sprite;
    bool canJump; //used to prevent double jumps
    bool invincible;
    float speed;  //for setting the players speed
    float jumpHeight; //for setting the players jump height
    int coins;
    char hearts;
    float hurtTime;
} Entity;

typedef struct EnvItem {
    Rectangle hitBox;
    Color color;
    bool blocking;
    short id;
    bool used;
} EnvItem;

// Special Struct for maintaining the state of 
// the scrolling background in the StartMenu
typedef struct ScrollState {
    float f_m_scroll;
    float c_m_scroll;
    float f_t_scroll;
    float c_t_scroll;
    float p_scroll;
} ScrollState;

typedef struct Button {
    Texture2D texture;  // Sprite Sheet for the button
    Rectangle hitBox;   // This is the where the button is drawn and checked for collision
    bool state;         // Changes when button is pressed
} Button;

/**
 * Levels.c
 */
extern EnvItem level1[16];
extern EnvItem level2[12];

/**
 * Functions.c
 */
void UpdatePlayer(Entity *player, EnvItem *envItems, int envItemsLength, float deltaTime, bool *game_state);
void UpdateCameraCenter(Camera2D *camera, Entity *player, EnvItem *map, int mapLength, int width, int height);
void CreatePlayer(Entity *player, Texture2D texture);
void CreateCamera(Camera2D *camera, Entity *player, int width, int height);
void ResetGame(Entity *player, EnvItem *envItems, int envItemsLength);
void Debug(Entity *player);

/**
 * Textures.c
 */
void UnloadTextures(Texture2D *textures, int length);
void DrawBackground(Texture2D *bg_textures, Entity player, Camera2D camera);
void DrawMap(Texture2D *textures, EnvItem *envItems, int envItemsLength);
void DrawPlayer(Entity *player, float deltaTime);
void DrawStartScreen(Texture2D *textures, int textureLength, ScrollState *state);
void DrawButton(Button *button); // todo generalize and make into DrawButton
void DrawTitle(Texture2D title, Rectangle hitBox);

/**
 * Helper.c
 */
Vector2 CalculateCollisionDistance(Entity player, EnvItem target);
void ResolveCollision(Entity *player, EnvItem target, float deltaTime);
bool PredictCollision(Entity player, EnvItem target);
Vector2 GetRectCenter(Rectangle rec);
Vector2 Vector2Abs(Vector2 v);
bool ButtonHandler(Button *button);

/**
 * Game.c
 */
int PlayGame();
int PlayGame2();

/**
 * Start.c
 */
bool StartGame();

/**
 * Environtment Items IDs:
 *  This is a list of all IDs for future reference when checking collision
 *  
 *  0 - basic platform 
 *  1 - raised platform
 *  2 - ice platform (implement in future: refactor physics)
 *  3 - fire
 *  4 - spikes/barbedwire
 *  5 - speed boost
 *  6 - jump boost
 *  7 - heart
 *  8 - coin
 *  9 - reserved
 * 10 - goal post
 */






#endif