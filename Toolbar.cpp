#include "Toolbar.h"
#include "../Core/Game.h"
#include "../Config/GameConfig.h"

ToolbarIcon::ToolbarIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path)
    : Drawable(r_pGame, r_point, r_width, r_height)
{
    image_path = img_path;
}

void ToolbarIcon::draw() const
{
    window* pWind = pGame->getWind();
    pWind->DrawImage(image_path, RefPoint.x, RefPoint.y, width, height);
}

Toolbar::Toolbar(Game* r_pGame, point r_point, int r_width, int r_height)
    : Drawable(r_pGame, r_point, r_width, r_height)
{
    iconsList = new ToolbarIcon * [2];

    point p = { 0, 0 };

    iconsList[0] = new ToolbarIcon(pGame, p, config.iconWidth, config.toolBarHeight, "images\\RESTART.jpg");
    p.x += config.iconWidth;

    iconsList[1] = new ToolbarIcon(pGame, p, config.iconWidth, config.toolBarHeight, "images\\EXIT.jpg");
}

Toolbar::~Toolbar()
{
    for (int i = 0; i < 2; i++)
        delete iconsList[i];

    delete[] iconsList;
}

void Toolbar::draw() const
{
    for (int i = 0; i < 2; i++)
        iconsList[i]->draw();
}

bool Toolbar::handleClick(int x, int y)
{
    return false;
}
