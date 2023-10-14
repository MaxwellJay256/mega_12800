#include "Drive.h"
#include <MsTimer2.h>

namespace Drive
{
    const double r_Wheel = 3.3;//车轮半径 (cm)
    const double L = 16.4;//左右轮间距 (cm)
    const double R1 = 8.1;//转小弯的转弯半径 (cm)
    const double R2 = 4.5;//转中弯的转弯半径 (cm)
    const double R3 = 1.9;//转大弯的转弯半径 (cm)  
    double wL, wR;
    // const double Wmax = 30;
    bool obstacle_avoid_flag = true;
    void move(double v, double w) {
        wL = (v - w * L / 2.0) / r_Wheel;
        wR = (v + w * L / 2.0) / r_Wheel;
        //Limit(&wL, &Wmax); Limit(&wR, &Wmax);
        motor_L.spin(wL);
        motor_R.spin(wR);
    }

    double Vc = 40; //直线速度 (cm/s)
    double Wc = 0; //转弯速度 (rad/s)
    void patrol() {
        //*/
        if (Mid_IR.get_IR_status()) {
            Wc = 0;
        }
        if (L1_IR.get_IR_status()) {
            Wc = Vc / R1;
        }
        if (R1_IR.get_IR_status()) {
            Wc = -(Vc / R1);
        }
        if (R2_IR.get_IR_status()) {
            Wc = -(Vc / R2);
        }
        if (L2_IR.get_IR_status()) {
            Wc = Vc / R2;
        }
        if (L3_IR.get_IR_status()) {
            Wc = Vc / R3;
        }
        if (R3_IR.get_IR_status()) {
            Wc = -(Vc / R3);
        }
        //*/
        move(Vc, Wc);
    }

/*******************一些简单动作函数*******************/
    /// @brief 右转
    void RightTurnCallback() {
        move(0, -30);
    }
    /// @brief 左转
    void LeftTurnCallback() {
        move(0, 30);
    }
    void ForwardCallback() {
        move(35, 0);
    }
    void BackwardCallback() {
        move(-50, 0);
    }
    /// @brief 泊车模式，车会自己定住
    void Park() {
        move(0, 0);
    }

/**********************执行任务**********************/
    void run_task_for(void (*task)(), long runTime) {
        MsTimer2::stop();
        MsTimer2::set(motor_L.period, task);
        MsTimer2::start();
        delay(runTime);
        MsTimer2::stop();
    }

    void patrol_end() {
        if ( L3_IR.get_IR_status() && R3_IR.get_IR_status() 
            && L2_IR.get_IR_status() && R2_IR.get_IR_status() 
            && L1_IR.get_IR_status() && R1_IR.get_IR_status() 
            && Mid_IR.get_IR_status() )
        {
            run_task_for(Park, 300);
            //原地旋转180度
            run_task_for(ForwardCallback, 350);
            run_task_for(RightTurnCallback, 340);
            MsTimer2::set(motor_L.period, Park);
            MsTimer2::start();
            RobotArm::claw_down();
            while (1) { //进入死循环，程序中止
                delay(10);
            }
        }
    }

    void obstacle_avoidace() {
        if ( ranger.get_distance() < 26 ) {
            run_task_for(LeftTurnCallback, 170);
            run_task_for(ForwardCallback, 700);
            run_task_for(RightTurnCallback, 100);
            run_task_for(ForwardCallback, 1000);
            run_task_for(RightTurnCallback, 100);
            obstacle_avoid_flag = false;
            MsTimer2::set(motor_L.period, patrol);
            MsTimer2::start();
        }
    }

    /// @brief 获取一个数的正负号
    /// @param x 
    /// @return x的正负号
    int Sign(double x) {
        int sgn;
        if ( x > 0 ) {
            sgn = 1;
        } else if ( x < 0 ) {
            sgn = -1;
        } else {
            sgn = 0;
        }
        return sgn;
    }
}