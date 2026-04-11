#pragma once
#include "../Core/Drawable.h"
#include <string> // Added for string support

enum ProductType
{
    NONE,
    EGG,
    MILK
};

class Animal : public Drawable
{enum AnimalType { CHICK, COW };
AnimalType type;
protected: // Changed to protected so Chick and Cow can access it easily
    string image_path;
public:
    virtual ProductType getProductType() const = 0;
    virtual int getProductValue() const = 0;
    
    point curr_pos;
    point curr_vel;

    Animal(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
    
    virtual void draw() const override;
    
    // Aim: Make animals move randomly
    virtual void moveStep() = 0;   
    
    // Aim: Put animal in random position on click
    void setRandomPosition(int windowWidth, int windowHeight);
};

class Chick : public Animal
{
public:
    Chick(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
    
    virtual ProductType getProductType() const override { return EGG; }
    virtual int getProductValue() const override { return 5; } // Example value
    
    virtual void moveStep() override;
};

class Cow : public Animal
{
public:
    Cow(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
    
    virtual ProductType getProductType() const override { return MILK; }
    virtual int getProductValue() const override { return 10; } // Example value
    
    virtual void moveStep() override;
};

// Fixed typo "Drwable" to "Drawable"
class Egg : public Drawable
{
public:
    Egg(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
    void draw() const override;
};

class Milk : public Drawable
{
public:
    Milk(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
    void draw() const override;
};
