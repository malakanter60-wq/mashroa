#include "Budgetbar.h"
#include "../Config/GameConfig.h"
#include "../Core/Game.h"
#include <iostream>
#include <fstream> // For Save/Load

using namespace std;

// --- Helper for Random Positioning ---
void randomizeAnimal(Animal* a) {
    if (!a) return;
    a->curr_pos.x = range_min_x + (rand() % (range_max_x - range_min_x));
    a->curr_pos.y = range_min_y + (rand() % (range_max_y - range_min_y));
}

// ... [Existing BudgetbarIcon and ChickIcon/CowIcon constructors] ...

// AIM: Draw toolbar icons (Restart, Pause, Resume, Save, Load)
// Note: You need to create these classes in Budgetbar.h as shown in the previous step

void RestartIcon::onClick() {
    ChickIcon* ci = (ChickIcon*)pGame->getBudgetbar()->getIcon(ICON_CHICK);
    CowIcon* co = (CowIcon*)pGame->getBudgetbar()->getIcon(ICON_COW);
    
    // Clear Chick list
    for(int i=0; i < ci->count; i++) { delete ci->chickList[i]; ci->chickList[i] = nullptr; }
    ci->count = 0;
    
    // Clear Cow list
    for(int i=0; i < co->count; i++) { delete co->cowList[i]; co->cowList[i] = nullptr; }
    co->count = 0;
    
    pGame->budget = 1000; // Reset budget
    cout << "Game Restarted" << endl;
}

void PauseIcon::onClick() { pGame->isPaused = true; cout << "Game Paused" << endl; }
void ResumeIcon::onClick() { pGame->isPaused = false; cout << "Game Resumed" << endl; }

void SaveIcon::onClick() {
    ofstream outFile("farm_save.txt");
    ChickIcon* ci = (ChickIcon*)pGame->getBudgetbar()->getIcon(ICON_CHICK);
    CowIcon* co = (CowIcon*)pGame->getBudgetbar()->getIcon(ICON_COW);

    outFile << ci->count << " " << co->count << endl;
    for(int i=0; i<ci->count; i++) outFile << ci->chickList[i]->curr_pos.x << " " << ci->chickList[i]->curr_pos.y << endl;
    for(int i=0; i<co->count; i++) outFile << co->cowList[i]->curr_pos.x << " " << co->cowList[i]->curr_pos.y << endl;
    
    outFile.close();
    cout << "Progress Saved" << endl;
}

// --- Budgetbar Implementation ---

Budgetbar::Budgetbar(Game* r_pGame, point r_point, int r_width, int r_height) : Drawable(r_pGame, r_point, r_width, r_height)
{
    iconsImages[ICON_CHICK] = "images\\chick.jpg";
    iconsImages[ICON_Cow] = "images\\cow.jpg";
    iconsImages[ICON_RESTART] = "images\\restart.jpg";
    iconsImages[ICON_PAUSE] = "images\\pause.jpg";
    iconsImages[ICON_RESUME] = "images\\resume.jpg";
    iconsImages[ICON_SAVE] = "images\\save.jpg";
    iconsImages[ICON_LOAD] = "images\\load.jpg";

    iconsList = new BudgetbarIcon*[ANIMAL_COUNT];
    point p = {0, config.toolBarHeight};

    for(int i=0; i < ANIMAL_COUNT; i++) {
        // Factory-style creation for icons
        if(i == ICON_CHICK) iconsList[i] = new ChickIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[i]);
        else if(i == ICON_COW) iconsList[i] = new CowIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[i]);
        else if(i == ICON_RESTART) iconsList[i] = new RestartIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[i]);
        // ... repeat for PAUSE, RESUME, SAVE, LOAD ...
        p.x += config.iconWidth;
    }
}

bool Budgetbar::handleClick(int x, int y)
{
    // AIM: Put animal in random position on click
    // If click is below the toolbar (in the field)
    if (y > 2 * config.toolBarHeight && y < config.windHeight - config.statusBarHeight) 
    {
        ChickIcon* ci = (ChickIcon*)iconsList[ICON_CHICK];
        CowIcon* co = (CowIcon*)iconsList[ICON_COW];
        
        for(int i=0; i < ci->count; i++) randomizeAnimal(ci->chickList[i]);
        for(int i=0; i < co->count; i++) randomizeAnimal(co->cowList[i]);
        
        cout << "Animals Teleported!" << endl;
        return false;
    }

    if (x > ANIMAL_COUNT * config.iconWidth || y > config.toolBarHeight) return false;

    int clickedIconIndex = (x / config.iconWidth);
    if(clickedIconIndex < ANIMAL_COUNT)
        iconsList[clickedIconIndex]->onClick();

    return false;
}

void Budgetbar::updateAnimals()
{
    // AIM: Make animals move randomly (controlled by isPaused)
    if (pGame->isPaused) return; 

    ChickIcon* chick = (ChickIcon*)iconsList[ICON_CHICK];
    CowIcon* cow = (CowIcon*)iconsList[ICON_Cow];

    for (int i = 0; i < chick->count; i++)
        if (chick->chickList[i]) chick->chickList[i]->moveStep();

    for (int i = 0; i < cow->count; i++)
        if (cow->cowList[i]) cow->cowList[i]->moveStep();
}
