#ifndef __MAGNET_H__
#define __MAGNET_H__

#include "MovingObject.h"

class Magnet : public MovingObject {
    double magnet_start_x;
    double magnet_start_y;
    double release_speed;
    double release_angle_deg;
    double magnet_ax;
    double magnet_ay;
    
    // Moving parts
    Circle magnet_circle;
    
public:
    Magnet(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
        release_speed = speed;
        release_angle_deg = angle_deg;
        magnet_ax = argax;
        magnet_ay = argay;
        initMagnet();
    }
    
    void initMagnet();
    void resetMagnet();
    void updateMagnet(double stepTime, double currTime, double last_magnet_jump_end);
    
}; // End class Coin

#endif
