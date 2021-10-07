#ifndef __MUST_CATCH_COIN_H__
#define __MUST_CATCH_COIN_H__

#include "MovingObject.h"

class MustCatchCoin : public MovingObject {
    double coin_start_x;
    double coin_start_y;
    double release_speed;
    double release_angle_deg;
    double coin_ax;
    double coin_ay;
    
    // Moving parts
    Circle coin_circle;
    
public:
    MustCatchCoin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
        release_speed = speed;
        release_angle_deg = angle_deg;
        coin_ax = argax;
        coin_ay = argay;
        initCoin();
    }
    
    void initCoin();
    void resetCoin();
    void setTrajectory(double &coin_start_x, double &coin_speed, double &coin_angle_deg);
    void updateCoin(double stepTime, double currTime, double last_coin_jump_end, int &livesLeft);
    
}; // End class Coin

#endif
