// main.cpp - 5 Points Complete!
#include "Game.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

int main() {
    srand(time(NULL));
    
    // Create window
    window w(800, 600);
    w.SetWaitForClick(false);
    
    Game game(w);
    game.StartGame();
    
    return 0;
}
