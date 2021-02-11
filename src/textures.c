#include "../inc/functions.h"

Texture2D* LoadTextures() {
    Texture2D textures [] = {
        LoadTexture("assets/background/parallax-mountain-bg.png"),              
        LoadTexture("assets/background/parallax-mountain-montain-far.png"),
        LoadTexture("assets/background/parallax-mountain-mountains.png"),
        LoadTexture("assets/background/parallax-mountain-trees.png"),
        LoadTexture("assets/background/parallax-mountain-foreground-trees.png")
    };

    return textures;
}