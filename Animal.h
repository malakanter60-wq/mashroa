#pragma once
#include "../Core/Drawable.h"

enum ProductType
{
    NONE,
    EGG,
    MILK
};

class Animal :public Drawable
{
private:
	string image_path;
public:

    virtual ProductType getProductType() const = 0;
    virtual int getProductValue() const = 0;
	point curr_pos;
	point curr_vel;
	Animal(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void draw() const override;
	virtual void moveStep() = 0;   //The action that should be taken each time step
};

class Chick : public Animal
{
public:
	Chick(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void moveStep();
};

class Cow : public Animal
{
public:
	Cow(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void moveStep();
};

class Egg : public Drawable
{
public:
	Egg(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void moveStep();
};

class Milk : public Drwable
{
public:
	Milk(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void moveStep();
};


