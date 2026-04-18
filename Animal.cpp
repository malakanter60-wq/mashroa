#include "Animal.h"
#include "../Core/Game.h"
#include <iostream>

// Base Animal Constructor
Animal::Animal(Game* r_pGame, point r_point, int r_width, int r_height, string img_path)
    : Drawable(r_pGame, r_point, r_width, r_height)
{
    image_path = img_path;
    curr_pos = r_point;

    // AIM: Make animals move randomly (Initialize with a small random velocity)
    curr_vel.x = (rand() % 5) - 2; // Speed between -2 and 2
    curr_vel.y = (rand() % 5) - 2;
}

// AIM: Draw chicken and cow
void Animal::draw() const
{
    window* pWind = pGame->getWind();
    pWind->DrawImage(image_path, curr_pos.x, curr_pos.y, width, height);
    
}

// --- Chick Implementation ---
Chick::Chick(Game* r_pGame, point r_point, int r_width, int r_height, string img_path)
    : Animal(r_pGame, r_point, r_width, r_height, img_path) {
}

void Chick::moveStep()
{
    // AIM: Make animals move randomly
    // 1. Update position based on velocity
    curr_pos.x += curr_vel.x;
    curr_pos.y += curr_vel.y;

    // 2. Occasionally change direction randomly (Jitter)
    if (rand() % 50 == 0) {
        curr_vel.x = (rand() % 3) - 1;
        curr_vel.y = (rand() % 3) - 1;
    }

    // 3. Screen Boundary Check (Keep them in the field)
    if (curr_pos.x < 0 || curr_pos.x > config.windWidth - width) curr_vel.x *= -1;
    if (curr_pos.y < config.toolBarHeight * 2 || curr_pos.y > config.windHeight - config.statusBarHeight - height) curr_vel.y *= -1;
}

// --- Cow Implementation ---
Cow::Cow(Game* r_pGame, point r_point, int r_width, int r_height, string img_path)
    : Animal(r_pGame, r_point, r_width, r_height, img_path) {
}

void Cow::moveStep()
{
    // AIM: Make animals move randomly
    // Cows move slower than chicks generally
    curr_pos.x += curr_vel.x * 0.5;
    curr_pos.y += curr_vel.y * 0.5;

    if (rand() % 100 == 0) { // Changes direction less often than the chick
        curr_vel.x = (rand() % 5) - 2;
        curr_vel.y = (rand() % 5) - 2;
    }

    // Boundary Check
    if (curr_pos.x < 0 || curr_pos.x > config.windWidth - width) curr_vel.x *= -1;
    if (curr_pos.y < config.toolBarHeight * 2 || curr_pos.y > config.windHeight - config.statusBarHeight - height) curr_vel.y *= -1;
}
