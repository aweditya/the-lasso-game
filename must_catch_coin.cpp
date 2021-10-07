#include "must_catch_coin.h"
#include "lasso.h"

void MustCatchCoin::initCoin() {
    coin_start_x = (PLAY_X_START+WINDOW_X)/2;
    coin_start_y = PLAY_Y_HEIGHT;
    coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
    coin_circle.setColor(COLOR("BLUE"));
    coin_circle.setFill(true);
    addPart(&coin_circle);
}

void MustCatchCoin::resetCoin() {
    double coin_speed = COIN_SPEED;
    double coin_angle_deg = COIN_ANGLE_DEG;
    coin_ax = 0;
    coin_ay = COIN_G;
    bool paused = true, rtheta = true;
    reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}

void MustCatchCoin::updateCoin(double stepTime, double currTime, double last_must_catch_coin_jump_end, int &livesLeft) {
    this->nextStep(stepTime);
    if (currTime >= 10 && currTime <= 20) {
        if(this->isPaused()) {
            if((currTime-last_must_catch_coin_jump_end) >= COIN_GAP) {
                this->unpause();
            }
        }
    }
    
    if(this->getYPos() > PLAY_Y_HEIGHT) {
        this->resetCoin();
        last_must_catch_coin_jump_end = currTime;
        livesLeft--;
    }
}

