#include "Drive.h"
#include <MsTimer2.h>

namespace Drive
{
    const double r_Wheel = 3.3;//车轮半径（厘米）
    const double L = 16.4;//左右轮间距（厘米）
    const double R1 = 4;//转小弯的转弯半径（厘米）
    const double R2 = 3;//转大弯的转弯半径（厘米）
    const double R3 = 1;//原先是0.5  
    bool isPatrolEnd = false;//巡线是否结束
    double wL, wR;
    const double Wmax = 30;
    void Move(double v, double w) {
        wL = (v - w * L / 2.0) / r_Wheel;
        wR = (v + w * L / 2.0) / r_Wheel;
        Limit(&wL, &Wmax); Limit(&wR, &Wmax);
        MotorL.Spin(wL);
        MotorR.Spin(wR);
    }

    double Vc = 25;//直线速度（cm/s）
    double Wc;//转弯速度（rad/s）
    void Patrol() {
        Wc = 0;
        int numOfData = 0;
        if ( L3_IR.GetIRStatus() ) {
            Wc += Vc / R3;
        }
        if ( L2_IR.GetIRStatus() ) {
            Wc += Vc / R2;
            numOfData ++;
        }
        if ( L1_IR.GetIRStatus() ) {
            Wc += Vc / R1;
            numOfData ++;
        }
        if ( R3_IR.GetIRStatus() ) {
            Wc += -(Vc / R3);
        }
        if ( R2_IR.GetIRStatus() ) {
            Wc += -(Vc / R2);
            numOfData ++;
        }
        if ( R1_IR.GetIRStatus() ) {
            Wc += -(Vc / R1);
            numOfData ++;
        }
        if ( Mid_IR.GetIRStatus()) {
            Wc += 0;
            numOfData ++;
        }
        if ( numOfData == 0 ){
            numOfData = 1;
        }
        Wc /= numOfData;
        Move(Vc, Wc);
    }

    void Turn() {
        Move(0, -10);
    }
    void RunTaskFor(void (*task)(), long runTime) {
        MsTimer2::stop();
        MsTimer2::set(period, task);
        MsTimer2::start();
        delay(runTime);
        MsTimer2::stop();
    }

    /// @brief 泊车模式，车会自己定住
    void Park() {
        Move(0, 0);
    }
    void PatrolEnd() {
        if ( L3_IR.GetIRStatus() && R3_IR.GetIRStatus() ) {
            //原地旋转180度
            RunTaskFor(Turn, 1700);
            MsTimer2::set(period, Park);
            MsTimer2::start();
            RobotArm::ClawDown();//放下物体
            while (1) { //进入死循环，程序中止
                delay(10);
            }
        }
    }

    void ObstacleAvoidace() {
        if ( Ranger.GetDistance() < 15 ) {
            MsTimer2::stop();
            RunTaskFor(Turn, 600);
            delay(500);
            MsTimer2::set(period, Patrol);
            MsTimer2::start();
        }
    }

    /// @brief 获取一个数的正负号
    /// @param x 
    /// @return x的正负号
    int Sign (double x) {
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
