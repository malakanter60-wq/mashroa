#pragma once
#include "../CMUgraphicsLib/CMUgraphics.h"
#include <string>

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
    int budget = 1000;
    bool isPaused = false; // AIM: Required for Pause/Resume functionality

    Game();
    ~Game();

    clicktype getMouseClick(int& x, int& y) const;
    string getSrting() const;

    window* CreateWind(int w, int h, int x, int y) const;
    window* getWind() const;
    
    // AIM: Getter so icons can access animal lists for Save/Load/Restart
    Budgetbar* getBudgetbar() const { return gameBudgetbar; }

    void createToolbar();
    void createBudgetbar();

    void clearStatusBar() const;
    void printMessage(string msg) const;

    void clearBudget() const;
    void printBudget(string msg) const;

    void initLevel();
    void updateTimer();
    void drawFoodArea();

    void letsgo();
};
