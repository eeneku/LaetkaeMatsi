#include"..\inc\Puck.hpp"

Puck::Puck()
{
    resetVariables();
}

void Puck::resetVariables()
{
    curSpeed = 0;
    slowingSpeed = 240;
    velocity.y = 0;
    velocity.x = 0;
    position.x = defPosition.x;
    position.y = defPosition.y;
    visible = true;
}

void Puck::update()
{
    // Katotaan liikutaanko, eli onko curSpeed > 0)
    if(curSpeed > 0)
    {
        // Päivitetään nopeusvektori
        velocity.x = curSpeed * direction.x;
        velocity.y = curSpeed * direction.y;

        // Otetaan vanha sijainti talteen (kimpoamiseen maaleista ym)
        prevPosition.x = position.x;
        prevPosition.y = position.y;

        // Siirretään!
        position.x += velocity.x * FPS::speedFactor;
        position.y += velocity.y * FPS::speedFactor;

        // Vähennetään nopeutta
        if((curSpeed -= (240 * FPS::speedFactor)) < 0) curSpeed = 0;
    }
}

int Puck::checkCollisions(Sprite &puna, Sprite &sini)
{
    // Tarkastetaan törmäykset maalivahteihin
    if(checkCollision(puna) || checkCollision(sini))
    {
        curSpeed = curSpeed * 0.7;
        position.x = prevPosition.x;
        direction.x = -direction.x;
    }

    // Tarkastetaan törmäykset maaleihin
    // Siniseen maaliin (return 1)
    if(checkCollision(61,233,34,74))
    {
        return 1;
    }
    // Punaseen maaliin (return 2)
    else if(checkCollision(545,233,34,74))
    {
        return 2;
    }

    // Tarkastetaan törmäykset maalin reunoihin (ylä, ala, taka)
    // Sininen maali. Ensin katotaan epämääräsesti ollaanko edes maalilla päin ja tarkistetaan jos ollaan. Turhaan tehdä kutsuja.
    if(position.x < 110)
    {
        if(checkCollision(58,230,40,3))
        {
            if(checkCollisionX(58,230,40,3))
            {
                direction.x = -direction.x;
                position.x = prevPosition.x;
            }
            if(checkCollisionY(58,230,40,3))
            {
                direction.y = -direction.y;
                position.y = prevPosition.y;
            }
            curSpeed = curSpeed * 0.7;
        }
        if(checkCollision(58,233,3,76))
        {
            if(checkCollisionX(58,233,3,76))
            {
                direction.x = -direction.x;
                position.x = prevPosition.x;
            }
            if(checkCollisionY(58,233,3,76))
            {
                direction.y = -direction.y;
                position.y = prevPosition.y;
            }
            curSpeed = curSpeed * 0.7;
        }
        if(checkCollision(58,307,40,3))
        {
            if(checkCollisionX(58,307,40,3))
            {
                direction.x = -direction.x;
                position.x = prevPosition.x;
            }
            if(checkCollisionY(58,307,40,3))
            {
                direction.y = -direction.y;
                position.y = prevPosition.y;
            }
            curSpeed = curSpeed * 0.7;
        }
    }
    // Punanen maali. Ensin katotaan epämääräsesti ollaanko edes maalilla päin ja tarkistetaan jos ollaan. Turhaan tehdä kutsuja.
    else if(position.x > 530)
    {
        if(checkCollision(542,230,40,3))
        {
            if(checkCollisionX(542,230,40,3))
            {
                direction.x = -direction.x;
                position.x = prevPosition.x;
            }
            if(checkCollisionY(542,230,40,3))
            {
                direction.y = -direction.y;
                position.y = prevPosition.y;
            }
            curSpeed = curSpeed * 0.7;
        }
        if(checkCollision(579,233,3,76))
        {
            if(checkCollisionX(579,233,3,76))
            {
                direction.x = -direction.x;
                position.x = prevPosition.x;
            }
            if(checkCollisionY(579,233,3,76))
            {
                direction.y = -direction.y;
                position.y = prevPosition.y;
            }
            curSpeed = curSpeed * 0.7;
        }
        if(checkCollision(542,307,40,3))
        {
            if(checkCollisionX(542,307,40,3))
            {
                direction.x = -direction.x;
                position.x = prevPosition.x;
            }
            if(checkCollisionY(542,307,40,3))
            {
                direction.y = -direction.y;
                position.y = prevPosition.y;
            }
            curSpeed = curSpeed * 0.7;
        }
    }

    // Tarkastetaan törmäykset x-reunoihin
    if(position.x < 16)
    {
        curSpeed = curSpeed * 0.7;
        position.x = 16;
        direction.x = -direction.x;
    }
    else if(position.x > 620)
    {
        curSpeed = curSpeed * 0.7;
        position.x = 620;
        direction.x = -direction.x;
    }

    // Tarkastetaan törmäykset y-reunoihin
    if(position.y < 76)
    {
        curSpeed = curSpeed * 0.7;
        position.y = 76;
        direction.y = -direction.y;
    }
    else if(position.y > 460)
    {
        curSpeed = curSpeed * 0.7;
        position.y = 460;
        direction.y = -direction.y;
    }

    return 0;
}

void Puck::shoot(float nX, float nY, double nDir, double nSpeed)
{
    // Alustetaan nää niin tärkeät muuttujat
    visible = true;
    position.x = nX;
    position.y = nY;
    curSpeed = nSpeed;

    // Laitetaan lähtönopeus
    direction.x = cos(nDir * (3.14/180));
    direction.y = sin(nDir * (3.14/180));
}
