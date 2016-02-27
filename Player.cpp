#include"..\inc\Player.hpp"

Player::Player()
{
    defAngle = 0;
    keyForward = SDLK_UNKNOWN;
    keyBackward = SDLK_UNKNOWN;
    keyRight = SDLK_UNKNOWN;
    keyLeft = SDLK_UNKNOWN;
    keyShoot = SDLK_UNKNOWN;
    resetVariables();
}

void Player::resetVariables()
{
    left = false;
    right = false;
    angle = defAngle;
    movingForward = false;
    movingBackwards = false;
    puck = false;
    shooting = false;
    shotPuck = false;
    takingPuck = false;
    animControl.animating = false;
    position.x = defPosition.x;
    position.y = defPosition.y;
    turnSpeed = 225;
    acceleration = 200;
    maxSpeed = 250;
    backSpeed = -150;
    curSpeed = 0.0;
    maxPower = 720;
    curPower = 0;
    accPower = 720;
    velocity.x = 0;
    velocity.y = 0;
    direction.x = cos(angle * (3.14/180));
    direction.y = sin(angle * (3.14/180));
    animControl.curColFrame = (int)(angle / 10);
}

void Player::update()
{
    // Katotaan ollaanko ampumas eli keräämäs POWERIA
    if(shooting)
    {
        if((curPower += (accPower * FPS::speedFactor)) > maxPower) curPower = maxPower;
    }

    // Katsotaan onko kiekko
    if(puck)
        animControl.curRowFrame = 1;
    else
        animControl.curRowFrame = 0;


    // Katotaan käännytäänkö johonkin
    if(left || right)
    {
        // Käännytään vasemmalle
        if(left)
        {
            if((angle -= (turnSpeed * FPS::speedFactor)) < 0) angle += 360;
        }
        // Käännytään oikealle
        else if(right)
        {
            if((angle += (turnSpeed * FPS::speedFactor)) > 360) angle -= 360;
        }

        // Päivitetään kuva
        animControl.curColFrame = (int)(angle / 10);

        // Päivitetään suuntavektori
        direction.x = cos(angle * (3.14/180));
        direction.y = sin(angle * (3.14/180));
    }

    // Katotaan liikutaanko ja minne
    if(movingForward)
    {
        if((curSpeed += (acceleration * FPS::speedFactor)) > maxSpeed) curSpeed = maxSpeed;
    }
    else if(movingBackwards)
    {
        if((curSpeed -= (acceleration * FPS::speedFactor)) < backSpeed) curSpeed = backSpeed;
    }
    else
    {
        if(curSpeed > 0 && (curSpeed -= (150 * FPS::speedFactor)) < 0) curSpeed = 0;
        else if(curSpeed < 0 && (curSpeed += (150 * FPS::speedFactor)) > 0) curSpeed = 0;
    }

    // Otetaan aiempi sijainti talteen (emt miksi mut otetaan silti)
    prevPosition.x = position.x;
    prevPosition.y = position.y;

    // Luodaan nopeusvektori
    velocity.x = curSpeed * direction.x;
    velocity.y = curSpeed * direction.y;

    // Siirretään!
    position.x += velocity.x * FPS::speedFactor;
    position.y += velocity.y * FPS::speedFactor;
}

void Player::launch(Puck &puck)
{
    // Laukastaan kiekko!
    shooting = false;
    puck.shoot(position.x + 22, position.y + 22, angle,curSpeed + curPower);
    this->puck = false;
    shotPuck = true;
    curPower = 0;
}

void Player::checkCollisions(Player &plr, Sprite &puck, Sprite &goalie1, Sprite &goalie2)
{
    // Tarkastetaan törmäykset toiseen pelaajaan
    if(checkCollision(plr))
    {
        if(plr.hasPuck() && takingPuck)
        {
            this->puck = true;
            plr.setPuck(false);
        }

        // Katotaan miten törmättiin ja palautetaan alkuperäisia sijainteja jos kävi niin notta
        if(checkCollisionX(plr)) position.x = prevPosition.x;
        if(checkCollisionY(plr)) position.y = prevPosition.y;
    }

    // Tarkastetaan törmäykset kiekkoon
    if(puck.isAlive() && checkCollision(puck))
    {
        // Jos ei olla just ammuttu kiekkoa niin tapetaan kiekko ja otetaan se itelle
        if(!shotPuck)
        {
            this->puck = true;
            puck.kill();
        }
    }
    else if(shotPuck) shotPuck = false;

    // Tarkastetaan törmäykset maalivahteihin
    if(checkCollision(goalie1))
    {
         // Katotaan miten törmättiin ja palautetaan alkuperäisia sijainteja jos kävi niin notta
        if(checkCollisionX(goalie1)) position.x = prevPosition.x;
        if(checkCollisionY(goalie1)) position.y = prevPosition.y;
    }
    // Pistetään tähän else if sillä ei oo _MITENKÄÄN_ mahdollista törmätä kumpaankin, muihin voi törmätäkin yhtäaikaa
    else if(checkCollision(goalie2))
    {
        // Katotaan miten törmättiin ja palautetaan alkuperäisia sijainteja jos kävi niin notta
        if(checkCollisionX(goalie2)) position.x = prevPosition.x;
        if(checkCollisionY(goalie2)) position.y = prevPosition.y;
    }

    // Tarkastetaan törmäykset maalin reunoihin (ylä, ala, taka)
    // Sininen maali. Ensin katotaan epämääräsesti ollaanko edes maalilla päin ja tarkistetaan jos ollaan. Turhaan tehdä kutsuja.
    if(position.x < 110)
    {
        if(checkCollision(58,230,40,3))
        {
            if(checkCollisionX(58,230,40,3))
                position.x = prevPosition.x;
            if(checkCollisionY(58,230,40,3))
                position.y = prevPosition.y;
        }
        if(checkCollision(58,233,3,74))
        {
            if(checkCollisionX(58,233,3,74))
                position.x = prevPosition.x;
            if(checkCollisionY(58,233,3,74))
                position.y = prevPosition.y;
        }
        if(checkCollision(58,307,40,3))
        {
            if(checkCollisionX(58,307,40,3))
                position.x = prevPosition.x;
            if(checkCollisionY(58,307,40,3))
                position.y = prevPosition.y;
        }
    }
    // Punanen maali. Ensin katotaan epämääräsesti ollaanko edes maalilla päin ja tarkistetaan jos ollaan. Turhaan tehdä kutsuja.
    else if(position.x > 530)
    {
        if(checkCollision(542,230,40,3))
        {
            if(checkCollisionX(542,230,40,3))
                position.x = prevPosition.x;
            if(checkCollisionY(542,230,40,3))
                position.y = prevPosition.y;
        }
        if(checkCollision(579,233,3,74))
        {
            if(checkCollisionX(579,233,3,74))
                position.x = prevPosition.x;
            if(checkCollisionY(579,233,3,74))
                position.y = prevPosition.y;
        }
        if(checkCollision(542,307,40,3))
        {
            if(checkCollisionX(542,307,40,3))
                position.x = prevPosition.x;
            if(checkCollisionY(542,307,40,3))
                position.y = prevPosition.y;
        }
    }

    // Tarkastetaan törmäykset reunoihin
    if((position.x + colBox.x) < 16) position.x = 16 - colBox.x;
    else if((position.x + colBox.w) > 624) position.x = 624 - colBox.w;

    if((position.y + colBox.y) < 76) position.y = 76 - colBox.y;
    else if((position.y + colBox.h) > 464) position.y = 464 - colBox.h;
}

void Player::drawPowerMeter(SDL_Surface * surfScreen)
{
    // Luodaan se voimamittarin ääriviivat
    SDL_Rect rect;
    rect.x = (Sint16) position.x;
    rect.y = (Sint16) (position.y + animControl.frameHeight - 4);
    rect.h = 4;
    rect.w = (Uint16)((curPower/maxPower) * animControl.frameWidth);

    // Pistetään näytölle
    Surface::fillRect(surfScreen,&rect,clrRed);
}
