# mega 12800
- Designed for HITSZ 2022 自动化认识与实践课程项目。
- 所有者：[Maxwell Jay](https://github.com/MaxwellJay256 "github.com/MaxwellJay256")，[CYCLECHENHUOHUA](https://github.com/CYCLECHENHUOHUA "github.com/CYCLECHENHUOHUA")
- Q: 为什么给项目起名叫“mega 12800”？

  A: 开发小车的途中，有5块Arduino mega 2560阵亡在了我们手中。因此小车做出来后，我们决定用这个名字纪念**我们花掉的**那一两百块钱。R.I.P.
### 文件说明
1. [mega_12800.ino](mega_12800.ino)：小车的主程序
2. [Motor.h](Motor.h)和[Motor.cpp](Motor.cpp)：电机对象的声明和实现，内置PID控制器。
3. [Sensor.h](Sensor.h)和[Sensor.cpp](Sensor.cpp)：光电传感器、超声波传感器对象的声明和实现。
4. [RobotArm.h](RobotArm.h)和[RobotArm.cpp](RobotArm.cpp)：对机械臂的一些操纵函数。
5. [Device.h](Device.h)和[Device.cpp](Device.cpp)：此处集中定义了电机、光电传感器、超声波传感器和机械臂对象，以及对它们的初始化函数。
6. [Drive.h](Drive.h)和[Drive.cpp](Drive.cpp)：调用电机和传感器对象，实现对底盘的操纵，包括巡线、避障以及到达终点时执行的动作。
---
## 一些闲话
我们作为HITSZ自动化专业的大一学生，免不了上一门名字叫做“自动化认识与实践”的考试课。2022年秋季学期，自动化专业进行课程改革，将多门冗杂的专业课合并，压缩学时，创造出了一门让大一新生认识和体验“自动化”的课程。这当然是一件好事情，减轻了学生的课业负担。

课程按时间顺序，包含了工程制图、~~机械设计~~、电路、Arduino入门、自动控制理论（PID算法介绍）、轮式机器人运动建模。当然，还有从Arduino开始教学后穿插的实验课。读到这里的你无论是不是HITSZ自动化专业学生，都会好奇搞教学的怎么有信心一学期教完这么多东西。然而事实是他们把该教的都教了，至于学生学到了多少，只有我们自己清楚。
>Maxwell Jay：如果是我，我会回答其实还是挺多的，有相当多内容与实验课直接挂钩，但这是我的结论。

实验课两人一组，前期让学生使用Arduino UNO开发板制作一些简单的小项目，后期让学生利用实验室提供的硬件制作<u>一个能够巡线、使用机械臂抓取物体的小车</u>。但由于2022年底的新冠疫情，我们不得不返乡学习，实验课也搁置了。没有实验室提供材料，我们二人的小车在寒假没有什么进展。

开学后，老师要求4个星期内完成小车。大家也没闲着，赶紧完善硬件结构，一点点开发程序。然而，考核的要求实在是难以让人接受——

就在考核还剩大约两周的时间内，教师一会儿要求用自制3D打印机械臂，一会儿在考核中增加超声波避障，一会儿说除了基础考核外，还有竞速赛，并且以上都计入了加分或减分项。要知道，这门课在我们这届由考察课变成了考试课，意味着小车的好坏与学分绩直接挂钩。事实上上述要求在之前的课程内容中都有涉及，但是学生们不一定都掌握了。并且到了后期，许多同学的硬件出现不可逆的故障，并且学校不提供更换。对于分数就是命的我们，这种并非由于老师教学造成的成绩差距是无法接受的。
>我的意思是，一般学生只听老师讲的课很难在考核前开发出满足这些要求的东西，除非给予足够的自学或者准备时间。幸运的是，我当时掌握一些使用C++开发机器人的技术，因此并没有感到非常惊慌。但是我毕竟和同学们站在一起，无丝毫幸灾乐祸。

后来在学生们的努力下，老师降低了考核要求，超声波避障成为了选考项，机械臂只需提交工程图，竞速赛被取消。我们二人在经历了烧坏若干开发板后（事实上有无数同学损坏了自己的元器件，~~并且老师无法提供更换~~，于是**我们自费**），总算在2023.3.17制作出了满足全部要求的小车。然而前两次考核时出了一些意外，小车无法一次完成避障和巡线两个任务，于是我们暂停考核，改改代码，在附近场地调了调车，最后在第三次考核有惊无险地拿到了全部的分数:wink:。

就在考核前几天，我们得知我们的劳动成果是要回收的，零件要留给下一届继续使用，毕竟大多数材料还是取自实验室。此外，我们在准备小车的过程中也目睹了众多同学由于缺少一些必要的开发知识，导致花在调车上的时间数倍于我们，并且遭遇了许多难以排查的问题。于是我决定在对这辆小车还有印象时，利用这个仓库保存尽量多的知识和经验，未来的学弟学妹们即使无基础，看了我们的分享后，或许能在这门课里面少走点弯路。

>《礼记》里面有一句话：“学(xiào)学(xué)半”，意思是教别人东西，自己也能学到一半的知识。我用这句话勉励自己在课外投入时间去做这些事情，**也希望能帮到大家。**

<p align="right">2023年3月</p>

---
## 如何使用这个仓库
- 点击本页面右上角的"Star"按钮，可以将本仓库加入你的GitHub收藏夹，下次就能很方便找到我啦！

这个仓库有两大内容：[Code](https://github.com/MaxwellJay256/mega_12800)（就是本页面）和[Wiki](https://github.com/MaxwellJay256/mega_12800/wiki)。

1. Code：本项目保存的小车代码。你可以在线阅览它们，也可以将仓库克隆到本地进行学习。我们建议您使用Visual Studio Code打开这个文件夹，因为我们使用了*Doxygen注释*为变量和函数进行备注和说明。
2. Wiki：是我自制的教程，包含硬件、软件、调试三大部分内容。在这里，我会详细讲解如何用限制内的硬件制作出好用又美观的小车。

## 本工程的特点
1. 采用多文件，将功能分散。
2. 利用了C++的类和面向对象，将硬件抽象化，有利于代码维护。
例如在[Motor.h](Motor.h)和[Motor.cpp](Motor.cpp)中，一个减速电机内包装了多种变量以及函数，在主程序中，只需定义MotorL，MotorR两个对象，即可非常方便地对它们进行控制。