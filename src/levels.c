/**
 * Levels.c
 */

#include "../inc/functions.h"

/**
 * levels.c contaisn the maps
 * for each level. These maps are used in
 * game.c for collision detection, and drawing textures
 * 
 * @author Hunter Craig
 * @version 0.0.1
 */

/* level 1 */
EnvItem level1[16] = {
    {{0, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{150, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{200, SCREEN_HEIGHT - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GOLD, false, 8, false},
    {{300, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{400, SCREEN_HEIGHT - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GOLD, false, 8, false},
    {{450, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{600, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{600, SCREEN_HEIGHT - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GOLD, false, 8, false},
    {{750, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{800, SCREEN_HEIGHT - 75, 75, 100}, RED, true, 1, false},
    {{825, SCREEN_HEIGHT - 100 - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GOLD, false, 8, false},
    {{1100, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{1135, SCREEN_HEIGHT - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GOLD, false, 8, false},
    {{1300, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{1515, SCREEN_HEIGHT - PLYR_SZ_Y, PLYR_SZ_X, PLYR_SZ_Y}, WHITE, false, 10, false},
    {{1450, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
};

/* level 2 */
EnvItem level2[12] = {
    {{0, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{150, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{275, SCREEN_HEIGHT - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, BLUE, false, 6, false},
    {{300, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{400, SCREEN_HEIGHT - 200, 200, 200}, BLUE, true, 1, false},
    {{450, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{500, SCREEN_HEIGHT - 200 - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GREEN, false, 5, false},
    {{800, SCREEN_HEIGHT - 300 - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GOLD, false, 8, false},
    {{1000, SCREEN_HEIGHT - 275 - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GOLD, false, 8, false},
    {{1200, SCREEN_HEIGHT - 250 - ITEM_SZ * 2, ITEM_SZ, ITEM_SZ}, GOLD, false, 8, false},
    {{1450, SCREEN_HEIGHT, PLTFRM_SZ, PLTFRM_SZ}, BROWN, true, 0, false},
    {{1515, SCREEN_HEIGHT - PLYR_SZ_Y, PLYR_SZ_X, PLYR_SZ_Y}, WHITE, false, 10, false}
};