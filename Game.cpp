#include "Game.h"
#include "../Config/GameConfig.h"
#include <windows.h>

// ... [Keep your existing constructors and helper functions] ...

void Game::letsgo()
{
    int x, y;
    bool isExit = false;

    pWind->ChangeTitle("- - - - - - - - - - Farm Frenzy (CIE101-project) - - - - - - - - - -");

    // We use a counter to track 1 second (1000ms) while the loop runs every 10ms
    int frameCounter = 0;

    do
    {
        // 1. Update the UI Text
        string budget_string = "BUDGET = $" + to_string(budget);
        printBudget(budget_string);

        string timeStr = "Time Left: " + to_string(remainingTime);
        printMessage(timeStr);

        // 2. AIM: Make animals move randomly 
        // We call this every loop (every 10ms) for smooth animation
        gameBudgetbar->updateAnimals();

        // 3. Update the Timer (once per second)
        frameCounter += 10; 
        if (frameCounter >= 1000) {
            updateTimer();
            frameCounter = 0;
        }

        if (remainingTime <= 0) break;

        // 4. Handle Input
        // Non-blocking check for mouse clicks
        if (pWind->GetMouseClick(x, y))
        {
            // Toolbar 1 (Top)
            if (y >= 0 && y < config.toolBarHeight)
            {
                isExit = gameToolbar->handleClick(x, y);
            }
            // Toolbar 2 (Budget/Animals) AND Field clicks
            // This ensures "Random position on click" works when clicking the grass
            else if (y >= config.toolBarHeight)
            {
                isExit = gameBudgetbar->handleClick(x, y);
            }
        }

        // AIM: Keep movement fluid while saving CPU
        Sleep(10); 

    } while (!isExit);
}

// ... [Keep the rest of your functions like drawFoodArea and printMessage] ...
