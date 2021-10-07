#include <simplecpp>
#include <string>
#include "MovingObject.h"
#include "lasso.h"
#include "coin.h"
#include "speedup_coin.h"
#include "bomb.h"
#include "must_catch_coin.h"
#include "magnet.h"

using namespace simplecpp;

main_program {
    
    initCanvas("Lasso", WINDOW_X, WINDOW_Y);
    int stepCount = 0;
    float stepTime = STEP_TIME;
    float runTime = -1; // sec; -ve means infinite
    float currTime = 0;
    
    // Implemented time limit
    char timerStr[256];
    sprintf(timerStr, "Time Left: %d", 10-(int)currTime);
    Text timer(WINDOW_X-75, PLAY_Y_HEIGHT+20, timerStr);
    
    // Draw lasso at start position
    double release_speed = INIT_RELEASE_SPEED; // m/s
    double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
    double lasso_ax = 0;
    double lasso_ay = LASSO_G;
    bool paused = true;
    bool rtheta = true;
    Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
    
    Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
    b1.setColor(COLOR("blue"));
    Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
    b2.setColor(COLOR("blue"));
    
    string msg("Cmd: _");
    Text charPressed(PLAY_X_START+45, PLAY_Y_HEIGHT+20, msg);
    char coinScoreStr[256];
    char livesLeftStr[256];
    sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
    Text coinScore(PLAY_X_START+50, PLAY_Y_HEIGHT+50, coinScoreStr);
    
    // Added lives
    int livesLeft = 3;
    sprintf(livesLeftStr, "Lives Left: %d", livesLeft);
    Text lives(PLAY_X_START+75, PLAY_Y_HEIGHT+80, livesLeftStr);
    
    paused = true; rtheta = true;
    double coin_speed = COIN_SPEED;
    double coin_angle_deg = COIN_ANGLE_DEG;
    double coin_ax = 0;
    double coin_ay = COIN_G;
    Coin coin1(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
    
    // Added multiple coins
    Coin coin2(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
    Coin coin3(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
    
    // After every COIN_GAP sec, make the coin jump
    double last_coin_jump_end = 0;
    
    // Added bomb
    paused = true; rtheta = true;
    double bomb_speed = BOMB_SPEED;
    double bomb_angle_deg = BOMB_ANGLE_DEG;
    double bomb_ax = 0;
    double bomb_ay = BOMB_G;
    Bomb bomb(bomb_speed, bomb_angle_deg, bomb_ax, bomb_ay, paused, rtheta);
    
    // After every BOMB_GAP sec, make the coin jump
    double last_bomb_jump_end = 0;
    
    // Speedup only allowed after getting coin
    bool speedup = false;
    double speedup_speed = COIN_SPEED;
    double speedup_angle_deg = COIN_ANGLE_DEG;
    double speedup_ax = 0;
    double speedup_ay = COIN_G;
    SpeedupCoin speedup_coin(speedup_speed, speedup_angle_deg, speedup_ax, speedup_ay, paused = true, rtheta);
    
    // After every COIN_GAP sec, make the speedup coin jump
    double last_speedup_coin_jump_end = 0;
    
    // Added a coin that must be caught or else the score will reduce
    MustCatchCoin must_catch_coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused = true, rtheta);
    
    // After every COIN_GAP sec, make the must catch coin jump
    double last_must_catch_coin_jump_end = 0;
    
    // Added a magnet which if caught, allows multiple coins to be caught simultaneously
    double magnet_speed = MAGNET_SPEED;
    double magnet_angle_deg = MAGNET_ANGLE_DEG;
    double magnet_ax = 0;
    double magnet_ay = MAGNET_G;
    Magnet magnet(magnet_speed, magnet_angle_deg, magnet_ax, magnet_ay, paused, rtheta);
    
    // After every MAGNET_GAP sec, make the magnet jump
    double last_magnet_jump_end = 0;
    
    // When t is pressed, throw lasso
    // If lasso within range, make coin stick
    // When y is pressed, yank lasso
    // When l is pressed, loop lasso
    // When q is pressed, quit
    
    for(;;) {
        if((runTime > 0) && (currTime > runTime)) { break; }
        
        XEvent e;
        bool pendingEv = checkEvent(e);
        if(pendingEv) {
            char c = charFromEvent(e);
            msg[msg.length()-1] = c;
            charPressed.setMessage(msg);
            switch(c) {
                case 't':
                    lasso.unpause();
                    break;
                case 'y':
                    lasso.yank();
                    break;
                case 'l':
                    lasso.loopit();
                    lasso.check_for_coin(&coin1);
                    lasso.check_for_coin(&coin2);
                    lasso.check_for_coin(&coin3);
                    lasso.check_for_bomb(&bomb);
                    lasso.check_for_speedup(&speedup_coin);
                    lasso.check_for_must_catch(&must_catch_coin);
                    lasso.check_for_magnet(&magnet);
                    wait(STEP_TIME*5);
                    break;
                    
                case '[':
                    if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
                    break;
                case ']':
                    if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
                    break;
                case '-':
                    if(lasso.isPaused() && speedup) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
                    break;
                case '=':
                    if(lasso.isPaused() && speedup) { lasso.addSpeed(+RELEASE_SPEED_STEP); }
                    break;
                case 'q':
                    // closeCanvas();
                    // initCanvas("Exit Window", WINDOW_X / 2, WINDOW_Y / 2);
                    // wait(3);
                    exit(0);
                default:
                    break;
            }
        }
        
        lasso.nextStep(stepTime);
        
        coin1.updateCoin(stepTime, currTime, last_coin_jump_end);
        coin2.updateCoin(stepTime, currTime, last_coin_jump_end);
        coin3.updateCoin(stepTime, currTime, last_coin_jump_end);
        bomb.updateBomb(stepTime, currTime, last_bomb_jump_end);
        speedup_coin.updateSpeedup(stepTime, currTime, last_speedup_coin_jump_end, speedup);
        must_catch_coin.updateCoin(stepTime, currTime, last_must_catch_coin_jump_end, livesLeft);
        magnet.updateMagnet(stepTime, currTime, last_magnet_jump_end);
        
        sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins() - lasso.getNumBombs());
        coinScore.setMessage(coinScoreStr);
        
        stepCount++;
        currTime += stepTime;

        // Timer countdown
        sprintf(timerStr, "Time Left: %d", 20-(int)currTime);
        timer.setMessage(timerStr);
        
        // Lives left
        sprintf(livesLeftStr, "Lives Left: %d", livesLeft);
        lives.setMessage(livesLeftStr);
        
        // Expiry of level
        if (20 - (int)currTime == 0) {
            lasso.yank();
            if (lasso.getNumCoins() - lasso.getNumBombs() <= 0) {
                livesLeft--;
                sprintf(livesLeftStr, "Lives Left: %d", livesLeft);
                lives.setMessage(livesLeftStr);
                if (livesLeft == 0) break;
            }
            speedup_coin.resetCoin();
            must_catch_coin.resetCoin();
            magnet.resetMagnet();
            lasso.setMagnetPtr();
            speedup = false;
            lasso.setSpeed();
            currTime = 0;
        }
        wait(stepTime);
    } // End for(;;)
    
    wait(3);
} // End main_program
