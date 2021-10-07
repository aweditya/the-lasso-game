#ifndef __LASSO_H__
#define __LASSO_H__

#include "MovingObject.h"
#include "coin.h"
#include "bomb.h"
#include "speedup_coin.h"
#include "must_catch_coin.h"
#include "magnet.h"

//#define WINDOW_X 1200
//#define WINDOW_Y 960
#define WINDOW_X 800
#define WINDOW_Y 600

#define STEP_TIME 0.05

#define PLAY_X_START 100
#define PLAY_Y_START 0
#define PLAY_X_WIDTH (WINDOW_X-PLAY_X_START)
#define PLAY_Y_HEIGHT (WINDOW_Y-100)

#define LASSO_X_OFFSET 100
#define LASSO_Y_HEIGHT 100
#define LASSO_BAND_LENGTH LASSO_X_OFFSET
#define LASSO_THICKNESS 5

#define COIN_GAP 1
#define BOMB_GAP 5
#define MAGNET_GAP 10

#define RELEASE_ANGLE_STEP_DEG 5
#define MIN_RELEASE_ANGLE_DEG 0
#define MAX_RELEASE_ANGLE_DEG (360-RELEASE_ANGLE_STEP_DEG)
#define INIT_RELEASE_ANGLE_DEG 45

#define RELEASE_SPEED_STEP 20
#define MIN_RELEASE_SPEED 0
#define MAX_RELEASE_SPEED 200
#define INIT_RELEASE_SPEED 100

#define COIN_SPEED 120
#define COIN_ANGLE_DEG 90

#define BOMB_SPEED 120
#define BOMB_ANGLE_DEG 90

#define MAGNET_SPEED 120
#define MAGNET_ANGLE_DEG 120

#define LASSO_G 30
#define COIN_G 30
#define BOMB_G 30
#define MAGNET_G 30

#define LASSO_SIZE 10
#define LASSO_RADIUS 50
#define COIN_SIZE 5
#define BOMB_SIZE 10
#define MAGNET_SIZE 5

class Lasso : public MovingObject {
    double lasso_start_x;
    double lasso_start_y;
    double release_speed;
    double release_angle_deg;
    double lasso_ax;
    double lasso_ay;
    
    // Moving parts
    Circle lasso_circle;
    Circle lasso_loop;
    
    // Non-moving parts
    Line lasso_line;
    Line lasso_band;
    
    // State info
    bool lasso_looped;
    Coin *the_coin;
    Bomb *the_bomb;
    SpeedupCoin *the_speedup;
    MustCatchCoin *the_must_catch;
    Magnet* the_magnet;
    int num_coins;
    int num_bombs;
    
    void initLasso();
public:
    Lasso(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
        release_speed = speed;
        release_angle_deg = angle_deg;
        lasso_ax = argax;
        lasso_ay = argay;
        initLasso();
    }
    
    void setMagnetPtr();
    
    void draw_lasso_band();
    void yank();
    void loopit();
    void addAngle(double angle_deg);
    void addSpeed(double speed);
    void setSpeed();
    
    void nextStep(double t);
    void check_for_coin(Coin *coin);
    void check_for_bomb(Bomb *bomb);
    void check_for_speedup(SpeedupCoin *coin);
    void check_for_must_catch(MustCatchCoin *coin);
    void check_for_magnet(Magnet *magnet);
    
    int getNumCoins() { return num_coins; }
    int getNumBombs() { return num_bombs; }
    
}; // End class Lasso

#endif
