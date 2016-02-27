#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include<cmath>
#include"SDL.h"
#include"..\inc\Sprite.hpp"
#include"..\inc\Puck.hpp"
#include"..\inc\FPS.hpp"

class Player : public Sprite
{
    private :
    // Pelaajan toimintomuuttujia, eli tiedet‰‰n mit‰ tehd‰‰n
    bool left;
    bool right;
    bool movingForward;
    bool movingBackwards;
    bool shooting;
    bool puck;
    bool shotPuck;
    bool takingPuck;

    // Muuttujia pelaajan liikutteluun etc.
    double angle;
    double defAngle;
    double turnSpeed;
    double maxSpeed;
    double curSpeed;
    double backSpeed;
    double acceleration;
    double maxPower;
    double curPower;
    double accPower;

    // N‰pp‰imet
    SDLKey keyForward;
    SDLKey keyBackward;
    SDLKey keyLeft;
    SDLKey keyRight;
    SDLKey keyShoot;

    public :

    Player();
    // P‰ivitt‰‰ pelaajan
    void update();

    // Resetoi muuttujat
    void resetVariables();

    // Pelaajan toimintometodit
    void turnLeft(bool n) { left = n; }
    void turnRight(bool n) { right = n; }
    void takePuck(bool n) { takingPuck = n; }
    void moveBackwards(bool n) { movingBackwards = n; }
    void moveForward(bool n) { movingForward = n; }
    void shoot(bool n) { shooting = n; }
    void launch(Puck &puck);

    // Kyselymetodit
    double getSpeed() { return curSpeed; }
    bool hasPuck() { return puck; }
    bool isTakingPuck() { return takingPuck; }
    bool isShooting() { return shooting; }
    // N‰pp‰imet
    SDLKey getKeyForward() { return keyForward; }
    SDLKey getKeyBackward() { return keyBackward; }
    SDLKey getKeyLeft() { return keyLeft; }
    SDLKey getKeyRight() { return keyRight; }
    SDLKey getKeyShoot() { return keyShoot; }

    // Asetusmetodit
    void setPuck(bool n) { puck = n; }
    void setDefaultAngle(float n) { defAngle = n; }
    void setAngle(float n) { angle = n; }
    // N‰pp‰imet
    void setKeyForward(SDLKey n) { keyForward = n; }
    void setKeyBackward(SDLKey n) { keyBackward = n; }
    void setKeyLeft(SDLKey n) { keyLeft = n; }
    void setKeyRight(SDLKey n) { keyRight = n; }
    void setKeyShoot(SDLKey n) { keyShoot = n; }

    // Tˆrm‰ystarkistusmetodi
    void checkCollisions(Player &plr, Sprite &puck, Sprite &goalie1, Sprite &goalie2);

    // Piirt‰‰ voimamittarin
    void drawPowerMeter(SDL_Surface * surfScreen);
};

#endif
