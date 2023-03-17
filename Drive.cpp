#include "Drive.h"
#include <MsTimer2.h>

namespace Drive
{
    const double r_Wheel = 3.3;//车轮半径（厘米）
    const double L = 16.4;//左右轮间距（厘米）
    const double R1 = 8;//转小弯的转弯半径（厘米）
    const double R2 = 4.5;//转中弯的转弯半径（厘米）
    const double R3 = 1.9;//转大弯的转弯半径（厘米）  
    double wL, wR;
    const double Wmax = 30;
    bool ObstacleAvoidFlag = true;
    void Move(double v, double w) {
        wL = (v - w * L / 2.0) / r_Wheel;
        wR = (v + w * L / 2.0) / r_Wheel;
        //Limit(&wL, &Wmax); Limit(&wR, &Wmax);
        MotorL.Spin(wL);
        MotorR.Spin(wR);
    }

    double Vc = 40;//直线速度（cm/s）
    double Wc = 0;//转弯速度（rad/s）
    void Patrol() {
        //*/
        if ( Mid_IR.GetIRStatus()) {
            Wc = 0;
        }
        if ( L1_IR.GetIRStatus() ) {
            Wc = Vc / R1;
        }
        if ( R1_IR.GetIRStatus() ) {
            Wc = -(Vc / R1);
        }
        if ( R2_IR.GetIRStatus() ) {
            Wc = -(Vc / R2);
        }
        if ( L2_IR.GetIRStatus() ) {
            Wc = Vc / R2;
        }
        if ( L3_IR.GetIRStatus() ) {
            Wc = Vc / R3;
        }
        if ( R3_IR.GetIRStatus() ) {
            Wc = -(Vc / R3);
        }
        //*/
        Move(Vc, Wc);
    }

/*******************一些简单动作函数*******************/
    /// @brief 右转
    void RightTurnCallback() {
        Move(0, -30);
    }
    /// @brief 左转
    void LeftTurnCallback() {
        Move(0, 30);
    }
    void ForwardCallback() {
        Move(35, 0);
    }
    void BackwardCallback() {
        Move(-50, 0);
    }
    /// @brief 泊车模式，车会自己定住
    void Park() {
        Move(0, 0);
    }

/**********************执行任务**********************/
    void RunTaskFor(void (*task)(), long runTime) {
        MsTimer2::stop();
        MsTimer2::set(period, task);
        MsTimer2::start();
        delay(runTime);
        MsTimer2::stop();
    }

    void PatrolEnd() {
        if ( L3_IR.GetIRStatus() && R3_IR.GetIRStatus() ) {
            RunTaskFor(Park, 500);
            //原地旋转180度
            RunTaskFor(ForwardCallback, 350);
            RunTaskFor(RightTurnCallback, 300);
            MsTimer2::set(period, Park);
            MsTimer2::start();
            RobotArm::ClawDown();//放下物体
            while (1) { //进入死循环，程序中止
                delay(10);
            }
        }
    }

    void ObstacleAvoidace() {
        if ( Ranger.GetDistance() < 26 ) {
            RunTaskFor(LeftTurnCallback, 170);
            RunTaskFor(ForwardCallback, 700);
            RunTaskFor(RightTurnCallback, 100);
            RunTaskFor(ForwardCallback, 1000);
            RunTaskFor(RightTurnCallback, 100);
            ObstacleAvoidFlag = false;
            MsTimer2::set(period, Patrol);
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
    /// @brief 将数 x 限制在 [-limit,+limit] 内
    void Limit(double *x, const double *limit) {
        if ( abs(*x) > *limit ) {
            *x = Sign(*x) * *limit;
        }
    }
}
