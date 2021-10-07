#ifndef __BOMB_H__
#define __BOMB_H__

#include "MovingObject.h"

/*
 Added Header for Bomb class
 */

class Bomb : public MovingObject {
    double bomb_start_x;
    double bomb_start_y;
    double release_speed;
    double release_angle_deg;
    double bomb_ax;
    double bomb_ay;
    
    // Moving parts
    Circle bomb_circle;
    
public:
    Bomb(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
        release_speed = speed;
        release_angle_deg = angle_deg;
        bomb_ax = argax;
        bomb_ay = argay;
        initBomb();
    }
    
    void initBomb();
    void resetBomb();
    void setTrajectory(double &bomb_start_x, double &bomb_speed, double &bomb_angle_deg);
    void updateBomb(double stepTime, double currTime, double last_bomb_jump_end);
}; // End class Bomb

#endif
