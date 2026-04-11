#include "Animal.h"
#include "../Config/GameConfig.h"
#include "../Core/Game.h"
#include <iostream>
using namespace std;

Animal::Animal(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Drawable(r_pGame, r_point, r_width, r_height)
{
	image_path = img_path;
	curr_pos = r_point;
	curr_vel.x = 1;
	curr_vel.y = 1;

}

void Animal::draw() const
{
	//draw image of this object
	window* pWind = pGame->getWind();
	pWind->DrawImage(image_path, RefPoint.x, RefPoint.y, width, height);
}

Chick::Chick(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Animal(r_pGame, r_point, r_width, r_height, img_path)
{}

void Chick::moveStep()
{
	//TO DO: add code for cleanup and game exit here
	/*
	//draw image of this object in the field
	window* pWind = pGame->getWind();
	pWind->DrawImage(image_path, RefPoint.x, RefPoint.y, width, height);
	*/
	
    window* pWind = pGame->getWind();


    pWind->SetBrush(WHITE);
    pWind->SetPen(WHITE);
    pWind->DrawRectangle(RefPoint.x, RefPoint.y, RefPoint.x + width, RefPoint.y + height);

    
    RefPoint.x += (rand() % 11) - 5; 
    RefPoint.y += (rand() % 11) - 5;

    
    if (RefPoint.x < range_min_x)
        RefPoint.x = range_min_x;
    if (RefPoint.x > range_max_x)
        RefPoint.x = range_max_x;

    if (RefPoint.y < range_min_y)
        RefPoint.y = range_min_y;
    if (RefPoint.y > range_max_y)
        RefPoint.y = range_max_y;

    draw();

	
}

Cow::Cow(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Animal(r_pGame, r_point, r_width, r_height, img_path)
{}


	//TO DO: add code for cleanup and game exit here
	void Cow::moveStep()
{
    window* pWind = pGame->getWind();

    pWind->SetBrush(WHITE);
    pWind->SetPen(WHITE);
    pWind->DrawRectangle(RefPoint.x, RefPoint.y, RefPoint.x + width, RefPoint.y + height);

    RefPoint.x += (rand() % 11) - 5;
    RefPoint.y += (rand() % 11) - 5;

    if (RefPoint.x < range_min_x)
        RefPoint.x = range_min_x;
    if (RefPoint.x > range_max_x)
        RefPoint.x = range_max_x;

    if (RefPoint.y < range_min_y)
        RefPoint.y = range_min_y;
    if (RefPoint.y > range_max_y)
        RefPoint.y = range_max_y;

    draw();
}
