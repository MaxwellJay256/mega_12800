#include "Drive.h"
#include <MsTimer2.h>
const float TARGET = 150;
namespace Drive
{
    const double r_Wheel = 3;//车轮半径
    const double L = 10;//左右轮间距
    const double R1 = 10;//转小弯的转弯半径
    const double R2 = 6;//转大弯的转弯半径
    bool PatrolStartFlag = false;//巡线是否开始
    bool isPatrolEnd = false;//巡线是否结束

    double vL, vR;
    void Move(double v, double w) {
        vL = v - w * L / 2.0;
        vR = v + w * L / 2.0;
        MotorL.Spin(vL/r_Wheel);
        MotorR.Spin(vR/r_Wheel);
    }

    double Vc = TARGET;
    double Wc;
    double GetCarDirection() {  //!这一部分要考虑到不同的转向情况,还要加入优先级
        static double W;
        if(Mid_IR.GetIRStatus())
            W = 0;
        if ( L1_IR.GetIRStatus() )
            W = Vc / R2;   
        if ( L2_IR.GetIRStatus() )
            W = Vc / R1;   
        if ( R1_IR.GetIRStatus() )
            W = -(Vc / R2);   
        if ( R2_IR.GetIRStatus() )
            W = -(Vc / R1);   
        return W;
    }
     /*if(Mid_IR.GetIRStatus())
        {
          vL = TARGET;
          vR = TARGET;

        }
        if ( L2_IR.GetIRStatus() )
        {
          vL = 0 * TARGET;
          vR = 0.8 * TARGET;
        }
               
        if ( L1_IR.GetIRStatus() )
        {
          vL = 0.9 * TARGET;
          vR = 0.7 * TARGET;
        }
           
        if ( R2_IR.GetIRStatus() )
        {
          vL = 0.8 * TARGET;
          vR = 0 * TARGET;
        }
           
        if ( R1_IR.GetIRStatus() )
        {
          vL = 0.7 * TARGET;
          vR = 0.9 * TARGET;
        }*/
    void classic_move() {  //这里新增了一个测试用的经典速度的函数
        int result = 0, num = 0;  
        int sensor[] = {A0,A1,A2,A3,A4};  // 用num考虑到了可能的优化方向
        for (int8_t i = 2, j = 2; i >= 0 && j < 5; i--, j++) {// 01234为传感器的编号
            if (digitalRead(sensor[i]) == HIGH)
                result += (i-2), num++;   //用result来度量不同的偏转程度
            if (digitalRead(sensor[j]) == HIGH)
                result += (j-2), num++;
        }
        vL = TARGET;
        vR = TARGET;
        if ( result <= -2 ) {//最左
            vL = 1.5 * TARGET;
            vR = -0.3 * TARGET;
        }
        if ( result >= 2 ) {//最右
            vL = -0.3 * TARGET;
            vR = 1.5 * TARGET;
        }
        if ( result < 2 && result > 0 ) {
            vL = 1.2 * TARGET;
            vR = 0.5 * TARGET;
        }
        if ( result > -2 && result < 0 ) {
            vL = 0.5 * TARGET;
            vR = 1.2 * TARGET;
        }
        MotorL.Spin(vL);
        MotorR.Spin(-vR);
    }

    void Patrol() {
        Wc = GetCarDirection();
        Move(Vc, Wc);
    }

    void PatrolEnd() {
        if ( L1_IR.GetIRStatus() && R1_IR.GetIRStatus() && L2_IR.GetIRStatus() && R2_IR.GetIRStatus() ) {
            MsTimer2::stop();
            //原地旋转180度


            ClawDown();//放下物体
            while (1) {
                delay(50);
            }
        }
    }
}