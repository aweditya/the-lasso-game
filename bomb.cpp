#include "bomb.h"
#include "lasso.h"

/*
 Added Bomb that decreases score if caught
 */

void Bomb::setTrajectory(double &bomb_start_x, double &bomb_speed, double &bomb_angle_deg) {
    int offsetStartingPoint = 400;
    bomb_start_x = PLAY_X_START + offsetStartingPoint + rand() % (WINDOW_X - PLAY_X_START - offsetStartingPoint);
    
    int minSpeed = 50, maxSpeed = 120;
    int minAngle = 60, maxAngle = 120;
    bomb_speed = minSpeed + rand() % (maxSpeed - minSpeed);
    bomb_angle_deg = minAngle + rand() % (maxAngle - minAngle);
}

void Bomb::initBomb() {
    bomb_start_x = (PLAY_X_START+WINDOW_X)/2;
    bomb_start_y = PLAY_Y_HEIGHT;
    bomb_circle.reset(bomb_start_x, bomb_start_y, BOMB_SIZE);
    bomb_circle.setColor(COLOR("BLACK"));
    bomb_circle.setFill(true);
    addPart(&bomb_circle);
}

void Bomb::resetBomb() {
    // double bomb_speed = BOMB_SPEED;
    // double bomb_angle_deg = BOMB_ANGLE_DEG;
    double bomb_speed, bomb_angle_deg, bomb_start_x;
    setTrajectory(bomb_start_x, bomb_speed, bomb_angle_deg);
    bomb_ax = 0;
    bomb_ay = COIN_G;
    bool paused = true, rtheta = true;
    reset_all(bomb_start_x, bomb_start_y, bomb_speed, bomb_angle_deg, bomb_ax, bomb_ay, paused, rtheta);
}

void Bomb::updateBomb(double stepTime, double currTime, double last_bomb_jump_end) {
    this->nextStep(stepTime);
    if(this->isPaused()) {
        if((currTime-last_bomb_jump_end) >= BOMB_GAP) {
            this->unpause();
        }
    }
    
    if(this->getYPos() > PLAY_Y_HEIGHT) {
        this->resetBomb();
        last_bomb_jump_end = currTime;
    }
}
