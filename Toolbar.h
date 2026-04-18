#pragma once
#include "../Core/Drawable.h"
#include <string>

class Game;

class ToolbarIcon : public Drawable
{
protected:
    string image_path;

public:
    ToolbarIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
    virtual void draw() const override;
    virtual void onClick() {}   // ❗ مش abstract مؤقتًا
};

class Toolbar : public Drawable
{
private:
    ToolbarIcon** iconsList;

public:
    Toolbar(Game* r_pGame, point r_point, int r_width, int r_height);
    ~Toolbar();
    void draw() const override;
    bool handleClick(int x, int y);
};

