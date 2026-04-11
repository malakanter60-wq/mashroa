#include "Game.h"
#include "../Config/GameConfig.h"
#include <windows.h>
#include "Animal.h"

Game::Game()
{
    srand(time(NULL));
    pWind = CreateWind(config.windWidth, config.windHeight, config.wx, config.wy);
    createToolbar();
    createBudgetbar();
    currentLevel = 1;
    initLevel();
    drawFoodArea();
    clearStatusBar();
    gamePaused = false;
}

Game::~Game()
{
    for (Animal* a : animals) delete a;
}

clicktype Game::getMouseClick(int& x, int& y) const
{
    return pWind->WaitMouseClick(x, y);
}

std::string Game::getSrting() const
{
    std::string Label;
    char Key;
    keytype ktype;
    pWind->FlushKeyQueue();
    while (1)
    {
        ktype
