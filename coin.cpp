#include "coin.h"
#include "lasso.h"

void Coin::setTrajectory(double &coin_start_x, double &coin_speed, double &coin_angle_deg) {
    int offsetStartingPoint = 400;
    coin_start_x = PLAY_X_START + offsetStartingPoint + rand() % (WINDOW_X - PLAY_X_START - offsetStartingPoint);
    
    int minSpeed = 50, maxSpeed = 120;
    int minAngle = 60, maxAngle = 120;
    coin_speed = minSpeed + rand() % (maxSpeed - minSpeed);
    coin_angle_deg = minAngle + rand() % (maxAngle - minAngle);
}

void Coin::initCoin() {
    coin_start_x = (PLAY_X_START+WINDOW_X)/2;
    coin_start_y = PLAY_Y_HEIGHT;
    coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
    coin_circle.setColor(COLOR("GREEN"));
    coin_circle.setFill(true);
    addPart(&coin_circle);
}

void Coin::resetCoin() {
    // double coin_speed = COIN_SPEED;
    // double coin_angle_deg = COIN_ANGLE_DEG;
    double coin_speed, coin_angle_deg, coin_start_x;
    setTrajectory(coin_start_x, coin_speed, coin_angle_deg);
    coin_ax = 0;
    coin_ay = COIN_G;
    bool paused = true, rtheta = true;
    reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}

void Coin::updateCoin(double stepTime, double currTime, double last_coin_jump_end) {
    this->nextStep(stepTime);
    if(this->isPaused()) {
        if((currTime-last_coin_jump_end) >= COIN_GAP) {
            this->unpause();
        }
    }
    
    if(this->getYPos() > PLAY_Y_HEIGHT) {
        this->resetCoin();
        last_coin_jump_end = currTime;
    }
}

