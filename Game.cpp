#include "Game.h"
#include "../Config/GameConfig.h"
#include <windows.h>

// ADDED: Animal structure for 5 points
struct Animal {
    std::string type;
    int x, y, vx, vy;
    int size;
    
    Animal(int px, int py, std::string t) : x(px), y(py), type(t), size(25) {
        vx = (rand() % 400 - 200) / 50.0f;
        vy = (rand() % 400 - 200) / 50.0f;
    }
    
    void Update(int width, int height) {
        x += vx;
        y += vy;
        if (x < 50 || x > width-50) vx *= -1;
        if (y < 100 || y > height-100) vy *= -1;
        vx *= 0.98f;
        vy *= 0.98f;
    }
    
    void Draw(window* pWind) {
        if (type == "chicken") {
            pWind->SetPen(YELLOW, 0); pWind->SetBrush(YELLOW);
            pWind->DrawEllipse(x-size, y-size/2, x+size, y+size/2);
            pWind->SetBrush(ORANGE); pWind->DrawCircle(x, y-size-10, 12);
            pWind->SetBrush(RED);
            pWind->DrawCircle(x-5, y-size-12, 3); pWind->DrawCircle(x+5, y-size-12, 3);
            pWind->SetBrush(DARKORANGE);
            pWind->DrawTriangle(x+8, y-size-10, x+18, y-size-8, x+8, y-size-5);
            pWind->SetPen(BROWN, 4);
            pWind->DrawLine(x-12, y+5, x-18, y+25); pWind->DrawLine(x+12, y+5, x+18, y+25);
        } else {
            pWind->SetPen(WHITE, 0); pWind->SetBrush(WHITE);
            pWind->DrawEllipse(x-size*1.2, y-size/2, x+size*1.2, y+size/2);
            pWind->SetBrush(BLACK);
            pWind->DrawCircle(x+15, y-5, 8); pWind->DrawCircle(x-10, y+8, 6);
            pWind->SetBrush(BROWN); pWind->DrawCircle(x, y-size-15, 15);
            pWind->SetBrush(BLACK);
            pWind->DrawCircle(x-6, y-size-18, 4); pWind->DrawCircle(x+6, y-size-18, 4);
            pWind->SetBrush(TAN);
            pWind->DrawTriangle(x-5, y-size-28, x-12, y-size-38, x-2, y-size-30);
            pWind->DrawTriangle(x+5, y-size-28, x+12, y-size-38, x+2, y-size-30);
            pWind->SetBrush(BLACK);
            pWind->DrawRectangle(x-18, y+10, x-13, y+40);
            pWind->DrawRectangle(x-3, y+10, x+2, y+40);
            pWind->DrawRectangle(x+13, y+10, x+18, y+40);
        }
    }
};

// ADDED: Animals vector (private in Game.h)
std::vector<Animal> animals;
bool gamePaused = false;

Game::Game()
{
    srand(time(NULL));  // ADDED: Random seed
    
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
            if (Label.size() > 0)
                Label.resize(Label.size() - 1);
            else
                Key = '\0';
        else
            Label += Key;
        printMessage(Label);
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
    point toolbarUpperleft;
    toolbarUpperleft.x = 0;
    toolbarUpperleft.y = 0;

    gameToolbar = new Toolbar(this, toolbarUpperleft, 0, config.toolBarHeight);
    gameToolbar->draw();
    
    // POINT 4: ADDED 5 TOOLBAR BUTTONS
    pWind->SetPen(DARKGREEN, 2); pWind->SetBrush(LIGHTGREEN);
    pWind->DrawRectangle(50, 5, 130, 35, FILLED); pWind->SetPen(WHITE,1); pWind->SetFont(14,BOLD); pWind->DrawString(60,15,"RESTART");
    pWind->DrawRectangle(150, 5, 230, 35, FILLED); pWind->DrawString(170,15,"PAUSE");
    pWind->DrawRectangle(250, 5, 330, 35, FILLED); pWind->DrawString(270,15,"RESUME");
    pWind->DrawRectangle(350, 5, 430, 35, FILLED); pWind->DrawString(375,15,"SAVE");
    pWind->DrawRectangle(450, 5, 530, 35, FILLED); pWind->DrawString(470,15,"LOAD");
}

void Game::createBudgetbar()
{
    point budgetbarUpperleft;
    budgetbarUpperleft.x = 0;
    budgetbarUpperleft.y = config.toolBarHeight;

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

void Game::printMessage(string msg) const
{
    clearStatusBar();
    color textColor = LIGHTGRAY;
    if (msg.find("Time Left") != string::npos && remainingTime <= 20)
        textColor = RED;

    pWind->SetPen(textColor, 50);
    pWind->SetFont(28, BOLD, BY_NAME, "Arial");

    pWind->DrawString(
        10,
        config.windHeight - (int)(0.85 * config.statusBarHeight),
        msg
    );
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
    {
        printMessage("Time is up! You lost.");
    }
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
    
    // POINT 1: Draw all animals
    for (const auto& animal : animals) {
        animal.Draw(pWind);
    }
}

void Game::letsgo()
{
    int x, y;
    bool isExit = false;

    pWind->ChangeTitle("- - - - - - - - - - Farm Frenzy (CIE101-5PTS!) - - - - - - - - - -");

    do
    {
        string budget_string = "BUDGET = $" + to_string(budget);
        printBudget(budget_string);

        string timeStr = "Time Left: " + to_string(remainingTime) + " | Animals: " + to_string(animals.size());
        printMessage(timeStr);

        // POINT 2+3+4: Handle clicks + movement
        if (pWind->GetMouseClick(x, y))
        {
            if (y >= 0 && y < config.toolBarHeight)
            {
                // POINT 4: Toolbar buttons
                if (x >= 50 && x <= 130) { animals.clear(); gamePaused = false; }      // RESTART
                else if (x >= 150 && x <= 230) gamePaused = true;                      // PAUSE
                else if (x >= 250 && x <= 330) gamePaused = false;                     // RESUME
                else if (x >= 350 && x <= 430) SaveAnimals();                          // SAVE
                else if (x >= 450 && x <= 530) LoadAnimals();                          // LOAD
                else isExit = gameToolbar->handleClick(x, y);
            }
            else if (y >= config.toolBarHeight && y < 2 * config.toolBarHeight)
            {
                isExit = gameBudgetbar->handleClick(x, y);
            }
            else {  // POINT 2: Game area → Spawn random animal!
                string type = (rand() % 2) ? "chicken" : "cow";
                animals.push_back(Animal(x, y, type));
            }
        }

        // POINT 3: Update animals (if not paused)
        if (!gamePaused) {
            for (auto& animal : animals) {
                animal.Update(config.windWidth, config.windHeight);
            }
        }

        Sleep(50);
        if (!gamePaused) updateTimer();

    } while (!isExit);
}

// POINT 4: Save/Load functions
void Game::SaveAnimals() {
    std::ofstream file("animals.txt");
    file << animals.size() << '\n';
    for (const auto& a : animals) {
        file << a.type << ' ' << a.x << ' ' << a.y << ' ' << a.vx << ' ' << a.vy << '\n';
    }
    file.close();
}

void Game::LoadAnimals() {
    std::ifstream file("animals.txt");
    if (file.is_open()) {
        animals.clear();
        int n; file >> n;
        for (int i = 0; i < n; i++) {
            std::string t; int x,y,vx,vy;
            file >> t >> x >> y >> vx >> vy;
            animals.push_back(Animal(x,y,t));
            animals.back().vx = vx; animals.back().vy = vy;
        }
        file.close();
    }
}
