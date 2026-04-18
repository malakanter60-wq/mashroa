#include "Game.h"
#include "../Config/GameConfig.h"
#include <windows.h>
#include "../Entities/Animal.h"

Game::Game()
{
    isPaused = false;
    pWind = CreateWind(config.windWidth, config.windHeight, config.wx, config.wy);

    createToolbar();
    createBudgetbar();
    drawField();
    drawWarehouse();


    currentLevel = 1;
    initLevel();
    drawFoodArea();

    clearStatusBar();
}

Game::~Game()
{
    delete pWind;
    delete gameToolbar;
    delete gameBudgetbar;
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
void Game::drawField() const
{
    window* pWind = getWind();

    int left = 0;
    int right = config.windWidth;

    int top = 2 * config.toolBarHeight;
    int bottom = config.windHeight - config.statusBarHeight;

    // الأرض
    pWind->SetBrush(LIGHTGREEN);
    pWind->SetPen(DARKGREEN, 2);
    pWind->DrawRectangle(left, top, right, bottom);

    // الحدود
    pWind->SetPen(BLACK, 4);
    pWind->DrawRectangle(left + 2, top + 2, right - 2, bottom - 2);
}

void Game::drawWarehouse() const
{
    window* pWind = getWind();

    int top = 2 * config.toolBarHeight;

    int x = config.windWidth - 150;   
    int y = config.windHeight - config.statusBarHeight - 150;

    pWind->DrawImage("images\\warehouse.png", x, y, 120, 120);
}


void Game::drawProducts()
{
    window* pWind = getWind();

    // Egg
    pWind->SetBrush(WHITE);
    pWind->SetPen(BLACK);
    pWind->DrawCircle(300, 300, 10);

    // Milk
    pWind->SetBrush(LIGHTBLUE);
    pWind->SetPen(BLACK);
    pWind->DrawRectangle(400, 290, 430, 320);
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
        drawProducts();
        Sleep(100);
        updateTimer();
        gameToolbar->draw();
        gameBudgetbar->draw();
        drawField();
        drawWarehouse();
       

        if (remainingTime <= 0)
        {
            clearStatusBar();

            pWind->SetPen(RED, 50);
            pWind->SetFont(30, BOLD, BY_NAME, "Arial");

            pWind->DrawString(300, config.windHeight - 50, "Time is up! You lost.");
            break;
        }


        getMouseClick(x, y);

        if (y >= 2 * config.toolBarHeight &&
            y < config.windHeight - config.statusBarHeight)
        {
            int startX = 0;
            int startY = 2 * config.toolBarHeight;

            int cellSize = 50;
            int randX = (rand() % (config.windWidth / cellSize)) * cellSize + startX;
            int randY = (rand() % ((config.windHeight - config.statusBarHeight - startY) / cellSize)) * cellSize + startY;

            /*point p;
            p.x = randX;
            p.y = randY;

            Animal* a = new Chick(this, p);
            AddAnimal(a);*/
        }
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
void Game::AddAnimal(Animal* a)
{
    animals.push_back(a);
}
