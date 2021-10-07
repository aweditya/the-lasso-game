#include "magnet.h"
#include "lasso.h"

void Magnet::initMagnet() {
    magnet_start_x = (PLAY_X_START+WINDOW_X) * 3 / 4;
    magnet_start_y = PLAY_Y_HEIGHT;
    magnet_circle.reset(magnet_start_x, magnet_start_y, MAGNET_SIZE);
    magnet_circle.setColor(COLOR("BLACK"));
    magnet_circle.setFill(true);
    addPart(&magnet_circle);
}

void Magnet::resetMagnet() {
    double magnet_speed = MAGNET_SPEED;
    double magnet_angle_deg = COIN_ANGLE_DEG;
    magnet_ax = 0;
    magnet_ay = MAGNET_G;
    bool paused = true, rtheta = true;
    reset_all(magnet_start_x, magnet_start_y, magnet_speed, magnet_angle_deg, magnet_ax, magnet_ay, paused, rtheta);
}

void Magnet::updateMagnet(double stepTime, double currTime, double last_magnet_jump_end) {
    this->nextStep(stepTime);
    if(this->isPaused()) {
        if((currTime-last_magnet_jump_end) >= MAGNET_GAP) {
            this->unpause();
        }
    }
    
    if(this->getYPos() > PLAY_Y_HEIGHT) {
        this->resetMagnet();
        last_magnet_jump_end = currTime;
    }
}

