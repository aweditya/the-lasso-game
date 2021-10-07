#include "speedup_coin.h"
#include "lasso.h"

void SpeedupCoin::initCoin() {
    speedup_coin_start_x = (PLAY_X_START+WINDOW_X)/2;
    speedup_coin_start_y = PLAY_Y_HEIGHT;
    coin_circle.reset(speedup_coin_start_x, speedup_coin_start_y, COIN_SIZE);
    coin_circle.setColor(COLOR("RED"));
    coin_circle.setFill(true);
    addPart(&coin_circle);
}

void SpeedupCoin::resetCoin() {
    // double coin_speed = COIN_SPEED;
    // double coin_angle_deg = COIN_ANGLE_DEG;
    speedup_coin_ax = 0;
    speedup_coin_ay = COIN_G;
    bool paused = true, rtheta = true;
    reset_all(speedup_coin_start_x, speedup_coin_start_y, COIN_SPEED, COIN_ANGLE_DEG, speedup_coin_ax, speedup_coin_ay, paused, rtheta);
}

void SpeedupCoin::updateSpeedup(double stepTime, double currTime, double last_speedup_coin_jump_end, bool &speedup) {
    if (currTime <= 10) {
        this->nextStep(stepTime);
        if(this->isPaused()) {
            if((currTime-last_speedup_coin_jump_end) >= COIN_GAP) {
                this->unpause();
            }
        }
        
        if(this->getYPos() > PLAY_Y_HEIGHT) {
            this->resetCoin();
            last_speedup_coin_jump_end = currTime;
        }
        if (this->checkForSpeedup()) {
            speedup = true;
            this->resetCoin();
        }
    }
    else {
        this->resetCoin();
        speedup = false;
        last_speedup_coin_jump_end = 0;
    }
}
