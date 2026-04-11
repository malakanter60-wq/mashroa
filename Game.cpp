#include "Game.h"
#include "../Config/GameConfig.h"
#include <windows.h>

Game::Game()
{
    pWind = CreateWind(config.windWidth, config.windHeight, config.wx, config.wy);

    createToolbar();
    createBudgetbar();

    currentLevel = 1;
    initLevel();
    drawFoodArea();

    clearStatusBar();
}

Game::~Game()
{
}

clicktype Game::getMouseClick(int& x, int& y) const
{
    return pWind->WaitMouseClick(x, y);
}

string Game::getSrting() const
{
    string Label;
    char Key;
    keytype ktype;
    pWind->FlushKeyQueue();

    while (1)
    {
        ktype = pWind->WaitKeyPress(Key);

        if (ktype == ESCAPE)
            return "";

        if (Key == 13)
            return Label;

        if (Key == 8)
        {
            if (Label.size() > 0)
                Label.resize(Label.size() - 1);
        }
        else
        {
            Label += Key;
        }

        printMessage();
    }
}

window* Game::CreateWind(int w, int h, int x, int y) const
{
    window* pW = new window(w, h, x, y);
    pW->SetBrush(config.bkGrndColor);
    pW->SetPen(config.bkGrndColor, 1);
    pW->DrawRectangle(0, 0, w, h);
    return pW;
}

void Game::createToolbar()
{
    point toolbarUpperleft{ 0, 0 };

    gameToolbar = new Toolbar(this, toolbarUpperleft, 0, config.toolBarHeight);
    gameToolbar->draw();
}

void Game::createBudgetbar()
{
    point budgetbarUpperleft{ 0, config.toolBarHeight };

    gameBudgetbar = new Budgetbar(this, budgetbarUpperleft, 0, config.toolBarHeight);
    gameBudgetbar->draw();
}

void Game::clearBudget() const
{
    pWind->SetPen(config.bkGrndColor, 1);
    pWind->SetBrush(config.bkGrndColor);
    pWind->DrawRectangle(config.windWidth - 500, config.toolBarHeight, config.windWidth, 2 * config.toolBarHeight);
}

void Game::printBudget(string msg) const
{
    clearBudget();

    pWind->SetPen(config.penColor, 50);
    pWind->SetFont(24, BOLD, BY_NAME, "Arial");
    pWind->DrawString(config.windWidth - 200, config.toolBarHeight + 10, msg);
}

void Game::clearStatusBar() const
{
    pWind->SetPen(config.statusBarColor, 1);
    pWind->SetBrush(config.statusBarColor);
    pWind->DrawRectangle(0, config.windHeight - config.statusBarHeight, config.windWidth, config.windHeight);
}

void Game::printMessage() const
{
    clearStatusBar();

    pWind->SetPen(config.penColor, 50);
    pWind->SetFont(24, BOLD, BY_NAME, "Arial");

    int b = config.windHeight - (int)(0.85 * config.statusBarHeight);
    int spacing = config.windWidth / 4;

    pWind->DrawString(spacing * 0, b, "Time: " + to_string(remainingTime));
    pWind->DrawString(spacing * 1, b, "Goal: " + to_string(goal));
    pWind->DrawString(spacing * 2, b, "Level: " + to_string(currentLevel));
    pWind->DrawString(spacing * 3, b, "Animals: " + to_string(animalscount));
}

window* Game::getWind() const
{
    return pWind;
}

void Game::initLevel()
{
    if (currentLevel == 1)
        remainingTime = 120;
    else if (currentLevel == 2)
        remainingTime = 90;
    else
        remainingTime = 60;
}

void Game::updateTimer()
{
    remainingTime--;

    if (remainingTime <= 0)
        remainingTime = 0;
}

void Game::drawFoodArea()
{
    window* pWind = getWind();

    int yStart = 2 * config.toolBarHeight;

    pWind->DrawImage(
        "images\\grass.jpg",
        0,
        yStart,
        config.windWidth,
        config.windHeight - config.statusBarHeight
    );
}

void Game::letsgo()
{
    int x, y;
    bool isExit = false;

    pWind->ChangeTitle("- - - - - - - - - - Farm Frenzy (CIE101-project) - - - - - - - - - -");

    do
    {
        string budget_string = "BUDGET = $" + to_string(budget);
        printBudget(budget_string);

        printMessage();

        Sleep(100);
        updateTimer();

        if (remainingTime <= 0)
        {
            clearStatusBar();

            pWind->SetPen(RED, 50);
            pWind->SetFont(30, BOLD, BY_NAME, "Arial");

            pWind->DrawString(300, config.windHeight - 50, "Time is up! You lost.");
            break;
        }

        getMouseClick(x, y);

        if (y >= 0 && y < config.toolBarHeight)
        {
            isExit = gameToolbar->handleClick(x, y);
        }
        else if (y >= config.toolBarHeight && y < 2 * config.toolBarHeight)
        {
            isExit = gameBudgetbar->handleClick(x, y);
        }

    } while (!isExit);
}
