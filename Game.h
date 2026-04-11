#pragma once
#include "../CMUgraphicsLib/CMUgraphics.h"
#include <string>

// Forward declarations to avoid circular inclusion
class Toolbar;
class Budgetbar;

using namespace std;

class Game
{
private:
    window* pWind;
    Toolbar* gameToolbar;
    Budgetbar* gameBudgetbar;

    int currentLevel;
    int remainingTime;

public:
    // --- UPDATED DATA MEMBERS ---
    int budget = 1000;
    bool isPaused = false; // AIM: Required to stop moveStep() when Pause is clicked

    Game();
    ~Game();

    // --- INPUT & WINDOW ---
    clicktype getMouseClick(int& x, int& y) const;
    string getSrting() const;
    window* CreateWind(int w, int h, int x, int y) const;
    window* getWind() const;
    
    // --- UPDATED GETTER ---
    // AIM: Needed so the Icons can access Chick/Cow lists for Save, Load, and Restart
    Budgetbar* getBudgetbar() const { return gameBudgetbar; }

    // --- UI & DRAWING ---
    void createToolbar();
    void createBudgetbar();
    void clearStatusBar() const;
    void printMessage(string msg) const;
    void clearBudget() const;
    void printBudget(string msg) const;

    // --- GAME LOGIC ---
    void initLevel();
    void updateTimer();
    void drawFoodArea();
    void letsgo(); // Contains the updated high-speed loop
};
