#include "../CMUgraphicsLib/CMUgraphics.h"
#include "../UI/Toolbar.h"
#include "../Entities/Animal.h"
#include <vector>
#include "../UI/Budgetbar.h"

Budgetbar* getBudgetbar();
bool isPaused;
int budget;

class Game
{
private:
    window* pWind;
    Toolbar* gameToolbar;
    Budgetbar* gameBudgetbar;
    vector<Animal*> animals;
    int remainingTime;
    int currentLevel;
    int goal = 10;
    int animalscount = 0;
    int Animalsbuying = 0;
    int waterbuying = 0;

public:
    int budget = 30000;
    void AddAnimal(Animal* a);
    Game();
   
    ~Game();
    bool isPaused;

    clicktype getMouseClick(int& x, int& y) const;
    string getSrting() const;

    window* CreateWind(int, int, int, int) const;
 

    void createToolbar();
    void createBudgetbar();
    Budgetbar* getBudgetbar() const { return gameBudgetbar; }

    void clearBudget() const;
    void printBudget(string msg) const;

    void clearStatusBar() const;
    void printMessage() const;

    void letsgo();
    window* getWind() const;
  
    void updateTimer();
    void initLevel();

    void drawFoodArea();
    void drawField() const;
    void drawWarehouse() const;
    void drawProducts();
};
