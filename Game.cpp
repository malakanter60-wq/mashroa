void Game::letsgo()
{
    int x, y;
    bool isExit = false;

    pWind->ChangeTitle("- - - - - - - - - - Farm Frenzy (CIE101-project) - - - - - - - - - -");

    int frameCounter = 0;

    do
    {
        // --- 1. CLEAR AND DRAW BACKGROUND ---
        // This is CRITICAL. We must redraw the grass every frame 
        // to "erase" the animals from their previous positions.
        drawFoodArea(); 

        // --- 2. UPDATE UI ---
        string budget_string = "BUDGET = $" + to_string(budget);
        printBudget(budget_string);

        string timeStr = "Time Left: " + to_string(remainingTime);
        printMessage(timeStr);

        // --- 3. MOVE AND DRAW ANIMALS ---
        // This updates x,y AND calls draw() for each animal
        gameBudgetbar->updateAnimals();

        // --- 4. TIMER LOGIC ---
        frameCounter += 10; 
        if (frameCounter >= 1000) {
            updateTimer();
            frameCounter = 0;
        }

        if (remainingTime <= 0) break;

        // --- 5. INPUT HANDLING ---
        if (pWind->GetMouseClick(x, y))
        {
            if (y >= 0 && y < config.toolBarHeight)
            {
                isExit = gameToolbar->handleClick(x, y);
            }
            else if (y >= config.toolBarHeight)
            {
                isExit = gameBudgetbar->handleClick(x, y);
            }
        }

        // --- 6. RENDER SYNC ---
        // We use a small Sleep for smooth animation (roughly 100 FPS)
        Sleep(10); 

    } while (!isExit);
}
// ... [Keep the rest of your functions like drawFoodArea and printMessage] ...
