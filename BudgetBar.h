#pragma once
#include "../Core/Drawable.h"
#include "../Entities/Animal.h"
#include "../Config/GameConfig.h"
#include <fstream> // Required for Save/Load
#include <vector>  // Easier management of animals
class Game;

// Ranges for generating a random location
const int range_min_x = 50;
const int range_max_x = config.windWidth - 50;
const int range_min_y = (config.toolBarHeight * 2) + 50;
const int range_max_y = config.windHeight - config.statusBarHeight - 50;


class BudgetbarIcon : public Drawable
{
public:
    string image_path;
    BudgetbarIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
    virtual void draw() const override;
    virtual void onClick() = 0;
};

// --- Animal Creation Icons ---
class ChickIcon : public BudgetbarIcon {
public:
    ChickIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
    virtual void onClick() override;
    Animal** chickList;
    int count;
};

class CowIcon : public BudgetbarIcon {
public:
    CowIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
    virtual void onClick() override;
    Animal** cowList;
    int count;
};

// --- Aim: Toolbar Icons (Restart, Pause, Resume, Save, Load) ---

class RestartIcon : public BudgetbarIcon {
public:
    RestartIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
    virtual void onClick() override; // Should clear all animals
};

class PauseIcon : public BudgetbarIcon {
public:
    PauseIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
    virtual void onClick() override; // Should set isPaused = true
};

class ResumeIcon : public BudgetbarIcon {
public:
    ResumeIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
    virtual void onClick() override; // Should set isPaused = false
};

class SaveIcon : public BudgetbarIcon {
public:
    SaveIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
    virtual void onClick() override; // Logic to write to file
};

class LoadGameIcon : public BudgetbarIcon {
public:
   LoadGameIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
    virtual void onClick() override; // Logic to read from file
};

enum ANIMAL_ICONS
{
    ICON_CHICK,
    ICON_COW,
    BB_ICON_RESTART, // Added
    BB_ICON_PAUSE,   // Added
    BB_ICON_RESUME,  // Added
    BB_ICON_SAVE,    // Added
    BB_ICON_LOAD,    // Added
    BB_ANIMAL_COUNT
};

class Budgetbar : public Drawable
{
private:
    BudgetbarIcon** iconsList;
    string iconsImages[BB_ANIMAL_COUNT];

public:
    Budgetbar(Game* r_pGame, point r_point, int r_width, int r_height);
    ~Budgetbar();
    void draw() const override;

    // Aim: Put animal in random position on click (handled here if clicking outside icons)
    bool handleClick(int x, int y);

    // Aim: Make animals move randomly (called every frame in game loop)
    void updateAnimals();
    BudgetbarIcon* getIcon(int id) const;//I add this new
};
