#ifndef __PUCK_HPP__
#define __PUCK_HPP__

#include<cmath>
#include"..\inc\Sprite.hpp"
#include"..\inc\FPS.hpp"

class Puck : public Sprite
{
    private :
    double curSpeed;
    double slowingSpeed;

    public :
    Puck();
    void resetVariables();
    void shoot(float nX, float nY, double nDir, double nSpeed);
    int checkCollisions(Sprite &sini, Sprite &puna);
    void update();
};

#endif
