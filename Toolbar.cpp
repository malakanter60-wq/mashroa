#include "Toolbar.h"
#include "../Config/GameConfig.h"
#include "../Core/Game.h"

ToolbarIcon::ToolbarIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Drawable(r_pGame, r_point, r_width, r_height)
{
	image_path = img_path;
}

void ToolbarIcon::draw() const
{
	//draw image of this object
	window* pWind = pGame->getWind();
	pWind->DrawImage(image_path, RefPoint.x, RefPoint.y, width, height);
}

RestartIcon::RestartIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : ToolbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{}

void RestartIcon::onClick()
{
	//TO DO: add code for restarting the game here
}

ExitIcon::ExitIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : ToolbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{}

void ExitIcon::onClick()
{
	//TO DO: add code for cleanup and game exit here
}

Toolbar::Toolbar(Game* r_pGame, point r_point, int r_width, int r_height)
    : Drawable(r_pGame, r_point, r_width, r_height)
{
    // images
    iconsImages[ICON_RESTART] = "images\\RESTART.jpg";
    iconsImages[ICON_EXIT]    = "images\\EXIT.jpg";
    iconsImages[ICON_PAUSE]   = "images\\PAUSE.jpg";
    iconsImages[ICON_RESUME]  = "images\\RESUME.jpg";
    iconsImages[ICON_SAVE]    = "images\\SAVE.jpg";
    iconsImages[ICON_LOAD]    = "images\\LOAD.jpg";

    point p;
    p.x = 0;
    p.y = 0;

    iconsList = new ToolbarIcon * [ICON_COUNT];

    // Restart
    iconsList[ICON_RESTART] = new RestartIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_RESTART]);
    p.x += config.iconWidth;

    // Exit
    iconsList[ICON_EXIT] = new ExitIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_EXIT]);
    p.x += config.iconWidth;

    // Pause
    iconsList[ICON_PAUSE] = new ToolbarIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_PAUSE]);
    p.x += config.iconWidth;

    // Resume
    iconsList[ICON_RESUME] = new ToolbarIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_RESUME]);
    p.x += config.iconWidth;

    // Save
    iconsList[ICON_SAVE] = new ToolbarIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_SAVE]);
    p.x += config.iconWidth;

    // Load
    iconsList[ICON_LOAD] = new ToolbarIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_LOAD]);
}
Toolbar::~Toolbar()
{
	for (int i = 0; i < ICON_COUNT; i++)
		delete iconsList[i];
	delete iconsList;
}

void Toolbar::draw() const
{
	for (int i = 0; i < ICON_COUNT; i++)
		iconsList[i]->draw();
	window* pWind = pGame->getWind();
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, config.toolBarHeight, pWind->GetWidth(), config.toolBarHeight);
}

bool Toolbar::handleClick(int x, int y)
{
	if (x > ICON_COUNT * config.iconWidth)	//click outside toolbar boundaries
		return false;


	//Check whick icon was clicked
	//==> This assumes that menu icons are lined up horizontally <==
	//Divide x co-ord of the point clicked by the icon width (int division)
	//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

	int clickedIconIndex = (x / config.iconWidth);
	iconsList[clickedIconIndex]->onClick();	//execute onClick action of clicled icon

	if (clickedIconIndex == ICON_EXIT) return true;

	return false;

}

