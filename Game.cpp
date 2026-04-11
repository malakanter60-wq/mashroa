#include "Game.h"
#include "../Config/GameConfig.h"
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include "Animal.h"  // Your Animal.h

Game::Game()
{
    srand(time(NULL));  // Random seed for animals
    
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
}

void Game::createToolbar()
{
    point toolbarUpperleft{0, 0};
    gameToolbar = new Toolbar(this, toolbarUpperleft, 0, config.toolBarHeight);
    gameToolbar->draw();
    
    // POINT 4: 5 TOOLBAR BUTTONS
    pWind->SetPen(DARKGREEN, 2); pWind->SetBrush(LIGHTGREEN);
    pWind->DrawRectangle(50, 5, 130, 35, FILLED); 
    pWind->SetPen(WHITE,1); pWind->SetFont(14,BOLD); pWind->DrawString(60,15,"RESTART");
    pWind->DrawRectangle(150, 5, 230, 35, FILLED); pWind->DrawString(170,15,"PAUSE");
    pWind->DrawRectangle(250, 5, 330, 35, FILLED); pWind->DrawString(270,15,"RESUME");
    pWind->DrawRectangle(350, 5, 430, 35, FILLED); pWind->DrawString(375,15,"SAVE");
    pWind->DrawRectangle(450, 5, 530, 35, FILLED); pWind->DrawString(470,15,"LOAD");
}

// ... ALL YOUR OTHER FUNCTIONS UNCHANGED ...
clicktype Game::getMouseClick(int& x, int& y) const { return pWind->WaitMouseClick(x, y); }
string Game::getSrting() const { /* your code unchanged */ }
window* Game::CreateWind(int w, int h, int x, int y) const { /* unchanged */ }
void Game::createBudgetbar() { /* unchanged */ }
void Game::clearBudget() const { /* unchanged */ }
void Game::printBudget(string msg) const { /* unchanged */ }
void Game::clearStatusBar() const { /* unchanged */ }
void Game::printMessage(string msg) const { /* unchanged */ }
window* Game::getWind() const { return pWind; }
void Game::initLevel() { /* unchanged */ }
void Game::updateTimer() { /* unchanged */ }

void Game::drawFoodArea()
{
    int yStart = 2 * config.toolBarHeight;
    pWind->DrawImage("images\\grass.jpg", 0, yStart, config.windWidth, config.windHeight - config.statusBarHeight);
    
    // POINT 1: Draw all animals
    for (Animal* animal : animals) {
        animal->draw();
    }
}

void Game::letsgo()
{
    int x, y;
    bool isExit = false;

    pWind->ChangeTitle("- - - FARM FRENZY - 5PTS! - Click grass for animals!");

    do
    {
        string budget_string = "BUDGET = $" + to_string(budget);
        printBudget(budget_string);

        string timeStr = "Time Left: " + to_string(remainingTime) + " | Animals: " + to_string(animals.size());
        printMessage(timeStr);

        if (pWind->GetMouseClick(x, y))
        {
            if (y >= 0 && y < config.toolBarHeight)
            {
                // POINT 4+5: NEW TOOLBAR BUTTONS
                if (x >= 50 && x <= 130) {      // RESTART
                    for (Animal* a : animals) delete a;
                    animals.clear();
                    gamePaused = false;
                }
                else if (x >= 150 && x <= 230) gamePaused = true;     // PAUSE
                else if (x >= 250 && x <= 330) gamePaused = false;    // RESUME
                else if (x >= 350 && x <= 430) SaveAnimals();         // SAVE
                else if (x >= 450 && x <= 530) LoadAnimals();         // LOAD
                else isExit = gameToolbar->handleClick(x, y);
            }
            else if (y >= config.toolBarHeight && y < 2 * config.toolBarHeight)
            {
                isExit = gameBudgetbar->handleClick(x, y);
            }
            else {  // POINT 2: GRASS CLICK → RANDOM ANIMAL
                point spawnPos{x, y};
                if (rand() % 2) {
                    animals.push_back(new Chick(this, spawnPos, 40, 40, "chick.png"));
                } else {
                    animals.push_back(new Cow(this, spawnPos, 50, 50, "cow.png"));
                }
            }
        }

        // POINT 3: UPDATE ANIMALS
        if (!gamePaused) {
            for (Animal* animal : animals) {
                animal->moveStep();
            }
        }

        Sleep(50);
        if (!gamePaused) updateTimer();

    } while (!isExit);
}

void Game::SaveAnimals() {
    std::ofstream file("animals.txt");
    file << animals.size() << '\n';
    for (Animal* a : animals) {
        file << a->getImagePath() << ' ' << a->getPosition().x << ' ' 
             << a->getPosition().y << '\n';
    }
    file.close();
    printMessage("Saved " + std::to_string(animals.size()) + " animals!");
}

void Game::LoadAnimals() {
    std::ifstream file("animals.txt");
    if (file.is_open()) {
        for (Animal* a : animals) delete a;
        animals.clear();
        
        int count; file >> count;
        for (int i = 0; i < count; i++) {
            std::string type, path; int px, py;
            file >> path >> px >> py;
            point pos{px, py};
            if (path.find("chick") != std::string::npos) {
                animals.push_back(new Chick(this, pos, 40, 40, path));
            } else {
                animals.push_back(new Cow(this, pos, 50, 50, path));
            }
        }
        file.close();
        printMessage("Loaded " + std::to_string(count) + " animals!");
    }
}
