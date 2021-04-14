/*
 * parser.c
 */

#include "../inc/functions.h"
#include <stdio.h>

/**
 * Parser.c handles all functions related to 
 * creating levels from text files. This is
 * both for ease of creation as well as
 * allowing outside users to make levels.
 * 
 * For more details, see Level_Creation.txt
 *
 *  @author Hunter Craig
 *  @version 0.0.1
 */

EnvItem * CreateLevel(char * filename) {
    FILE * file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    char newLine;
    int numLines = 0;

    while((newLine = fgetc(file)) != EOF) {
        if (newLine == "\n") {
            numLines++;
        }
    }
    fclose(file);
    FILE * write = fopen(filename, "r");

    EnvObject list[numLines];
    EnvItem builtMap[numLines];
    for (int i = 0; i < numLines; i++) {
        list[i] = (struct EnvObject) {0}; //Delcaring empty structs for each
        builtMap[i] = (struct EnvItem) {0};
    }
    for (int i = 0; i < numLines; i++) {
        list[i].type = fscanf("%s", write);
        list[i].startPoint = fscanf("%d", write);
        list[i].height = fscanf("%d", write);
        list[i].size = fscanf("%d", write);
    }
    for (int i = 0; i < numLines; i++) {
        switch(list[i].type) {
            case 0:
                builtMap[i].hitBox = (struct Rectangle) {list[i].startPoint, list[i].height, list[i].size, list[i].size};
                builtMap[i].color = BROWN;
                builtMap[i].blocking = YES;
                builtMap[i].id = 0;
                builtMap[i].used = false;
                break;
            case 1:
                builtMap[i].hitBox = (struct Rectangle) {list[i].startPoint, list[i].height, list[i].size, list[i].size};
                builtMap[i].color = WHITE;
                builtMap[i].blocking = YES;
                builtMap[i].id = 1;
                builtMap[i].used = false;
                break;
            case 2:
                builtMap[i].hitBox = (struct Rectangle) {list[i].startPoint, list[i].height, list[i].size, list[i].size};
                builtMap[i].color = WHITE;
                builtMap[i].blocking = YES;
                builtMap[i].id = 0; //Ice becomes a platform until implemented
                builtMap[i].used = false;
                printf("Type automatically converted to 0 (floor). Ice not yet implemented.");
                break;
            case 3:
                builtMap[i].hitBox = (struct Rectangle) {list[i].startPoint, list[i].height, list[i].size, list[i].size};
                builtMap[i].color = RED;
                builtMap[i].blocking = false;
                builtMap[i].id = 3;
                builtMap[i].used = false;
                break;
            case 4:
                builtMap[i].hitBox = (struct Rectangle) {list[i].startPoint, list[i].height, list[i].size, list[i].size};
                builtMap[i].color = RED;
                builtMap[i].blocking = false;
                builtMap[i].id = 3; //Spikes become fire until implemented
                builtMap[i].used = false;
                printf("Type automatically converted to 3 (fire). Spikes not yet implemented.");
                break;
            case 5:
                builtMap[i].hitBox = (struct Rectangle) {list[i].startPoint, list[i].height, list[i].size, list[i].size};
                builtMap[i].color = GREEN;
                builtMap[i].blocking = false;
                builtMap[i].id = 5;
                builtMap[i].used = false;
                break;
            case 6:
                builtMap[i].hitBox = (struct Rectangle) {list[i].startPoint, list[i].height, list[i].size, list[i].size};
                builtMap[i].color = BLUE;
                builtMap[i].blocking = false;
                builtMap[i].id = 6;
                builtMap[i].used = false;
                break;
            case 7:
                builtMap[i].hitBox = (struct Rectangle) {list[i].startPoint, list[i].height, list[i].size, list[i].size};
                builtMap[i].color = RED;
                builtMap[i].blocking = false;
                builtMap[i].id = 7;
                builtMap[i].used = false;
                break;
            case 8:
                builtMap[i].hitBox = (struct Rectangle) {list[i].startPoint, list[i].height, list[i].size, list[i].size};
                builtMap[i].color = GOLD;
                builtMap[i].blocking = false;
                builtMap[i].id = 8;
                builtMap[i].used = false;
                break;
            case 10:
                builtMap[i].hitBox = (struct Rectangle) {list[i].startPoint, list[i].height, list[i].size, list[i].size};
                builtMap[i].color = WHITE;
                builtMap[i].blocking = false;
                builtMap[i].id = 10;
                builtMap[i].used = false;
                break;
            case 11:
                builtMap[i].hitBox = (struct Rectangle) {list[i].startPoint, list[i].height, list[i].size, list[i].size};
                builtMap[i].color = BROWN;
                builtMap[i].blocking = YES;
                builtMap[i].id = 11;
                builtMap[i].used = false;
                break;
            case 12:
                builtMap[i].hitBox = (struct Rectangle) {list[i].startPoint, list[i].height, list[i].size, list[i].size};
                builtMap[i].color = GRAY;
                builtMap[i].blocking = YES;
                builtMap[i].id = 12;
                builtMap[i].used = false;
                break;
            default:
                printf("This is not a valid type!");
                break;
        }
    }
    fclose(write);

    return builtMap;
}