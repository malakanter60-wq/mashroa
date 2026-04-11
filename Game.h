#pragma once
#include "../CMUgraphicsLib/CMUgraphics.h"
#include "../UI/Toolbar.h"
#include "../UI/BudgetBar.h"

// ADDED FOR 5 POINTS:
#include <vector>
#include <string>
#include <fstream>

class Game
{
private:
    window* pWind;
    Toolbar* gameToolbar;
    Budgetbar* gameBudgetbar;

    int remainingTime;
    int currentLevel;
    
    // ADDED FOR 5 POINTS:
    std::vector<Animal> animals;
    bool gamePaused;

public:
    int budget = 30000;

    Game();
    ~Game();

    clicktype getMouseClick(int& x, int& y) const;
    string getSrting() const;

    window* CreateWind(int, int, int, int) const;

    void createToolbar();
    void createBudgetbar();

    void clearBudget() const;
    void printBudget(string msg) const;

    void clearStatusBar() const;
    void printMessage(string msg) const;

    void letsgo();   
    window* getWind() const;

    // elTIMER welLEVEL
    void updateTimer();
    void initLevel();

    // elFOODAREA
    void drawFoodArea();
    void drawProducts();
    
    // ADDED FOR 5 POINTS:
    void SaveAnimals();
    void LoadAnimals();
};
