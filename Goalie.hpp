#ifndef __GOALIE_HPP__
#define __GOALIE_HPP__

#include<cmath>
#include"..\inc\Sprite.hpp"
#include"..\inc\FPS.hpp"

class Goalie : public Sprite
{
    private :

    public :
    Goalie();
    void update(float nY);
};

#endif
