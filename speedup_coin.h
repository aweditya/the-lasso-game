#ifndef __SPEEDUP_COIN_H__
#define __SPEEDUP_COIN_H__

#include "MovingObject.h"

class SpeedupCoin : public MovingObject {
    double speedup_coin_start_x;
    double speedup_coin_start_y;
    double release_speed;
    double release_angle_deg;
    double speedup_coin_ax;
    double speedup_coin_ay;
    bool allow;
    
    // Moving parts
    Circle coin_circle;
    
public:
    SpeedupCoin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
        release_speed = speed;
        release_angle_deg = angle_deg;
        speedup_coin_ax = argax;
        speedup_coin_ay = argay;
        allow = false;
        initCoin();
    }
    
    void initCoin();
    void resetCoin();
    bool checkForSpeedup() {
        return allow;
    }
    void allowSpeedup() {
        allow = true;
    }
    
    void updateSpeedup(double stepTime, double currTime, double last_speedup_coin_jump_end,  bool &speedup);
    
}; // End class SpeedupCoin

#endif
