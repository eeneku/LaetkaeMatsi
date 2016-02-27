#include"..\inc\Goalie.hpp"

Goalie::Goalie()
{
    speed = 85;
}

void Goalie::update(float nY)
{
    /*// Katellaan. Toimii mutta on vähän kökkö.
    float tX = target.x - position.x;
    float tY = target.y - position.y;

    float tP = sqrt(tX * tX + tX * tX);

    velocity.y = tY / tP * acceleration;

    if(velocity.y > speed) velocity.y = speed;

    position.y += velocity.y * FPS::speedFactor;

    if(position.y > (315 - animControl.frameHeight)) position.y = 315 - animControl.frameHeight;
    else if(position.y < 225) position.y = 225;
    */

    // Liikutetaan molaria y-suunnassa kiekon sijainnin mukaan (kömpelöä, mutta so what :O)
    if((position.y + animControl.frameHeight / 2) > nY)
    {
        if((position.y -= speed * FPS::speedFactor) < 225) position.y = 225;
        //if((velocity.y -= acceleration * FPS::speedFactor) < -acceleration) velocity.y = -acceleration;
    }
    else if((position.y + animControl.frameHeight / 2) < nY)
    {
        if((position.y += speed * FPS::speedFactor) > (315 - animControl.frameHeight)) position.y = 315 - animControl.frameHeight;
        //if((velocity.y += acceleration * FPS::speedFactor) > acceleration) velocity.y = acceleration;
    }

    //position.y += velocity.y * FPS::speedFactor;

    //if(position.y > (315 - animControl.frameHeight)) position.y = 315 - animControl.frameHeight;
    //if(position.y < 225) position.y = 225;

    // Päivitetään animaatiot
    animControl.update();
}
