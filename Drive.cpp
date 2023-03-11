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
    double vL, vR;
    void Move(double v, double w) {
        vL = v - w * L / 2.0;
        vR = v + w * L / 2.0;
        MotorL.Spin(vL/r_Wheel);
        MotorR.Spin(vR/r_Wheel);
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

    void Turnback() {
        Move(0, 10);
    }
    void RunTaskFor(void (*task)(), long runTime) {
        MsTimer2::stop();
        MsTimer2::set(period, task);
        long timeCount = 0;
        MsTimer2::start();
        while ( timeCount <= runTime ) {
            timeCount += period;
            delay(period);
        }
        MsTimer2::stop();
    }

    void Park() {
        Move(0, 0);
    }
    void PatrolEnd() {
        if ( L3_IR.GetIRStatus() && R3_IR.GetIRStatus() ) {
            //原地旋转180度
            Drive::RunTaskFor(Turnback, 1700);
            MsTimer2::set(period, Park);
            MsTimer2::start();
            ClawDown();//放下物体
            while (1) {
                delay(10);
            }
        }
    }
}
