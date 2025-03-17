```c
	/*PID巡线算法程序*/

/*假设检测到黑线状态为1*/

#define TRACK_1    //1号循迹模块  

#define TRACK_2    //...

#define TRACK_3  

#define TRACK_4

/*PID参数修改处*/

float  kp = 0,

 ki = 0,

 kd = 0;

/*巡线状态检测及PID运算*/

float PID_Output(void)
{

	float error,last_error;    //此次和上次的误差      

	static float integral;    //积分累加项

	float output;      //PID输出

 

	if( (TRACK_1 == 0) && (TRACK_2 == 1) && (TRACK_3 == 0) && (TRACK_4 == 0) )    //0 1 0 0

	 error = -1;

	else if( (TRACK_1 == 1) && (TRACK_2 == 1) && (TRACK_3 == 0) && (TRACK_4 == 0) )   //1 1 0 0

	 error = -2;

	else if( (TRACK_1 == 1) && (TRACK_2 == 0) && (TRACK_3 == 0) && (TRACK_4 == 0) )   //1 0 0 0  

	 error = -3;

	else if( (TRACK_1 == 0) && (TRACK_2 == 0) && (TRACK_3 == 1) && (TRACK_4 == 0) )   //0 0 1 0  

	 error = 1;                    

	else if( (TRACK_1 == 0) && (TRACK_2 == 0) && (TRACK_3 == 1) && (TRACK_4 == 1) )   //0 0 1 1

	 error = 2;  

	else if( (TRACK_1 == 0) && (TRACK_2 == 0) && (TRACK_3 == 0) && (TRACK_4 == 1) )   //0 0 0 1

	 error = 3;

	else

	 error = 0;

 

integral += error;

 

output = kp * error + ki * integral + kd * (error - last_error);

 

last_error = error;

 

return output;   //最后PID运算得到的是一个电机的差速调整值，左边的的机就加上相应的PID输出，右边则减去（具体是加还是减不重要，调整KP极性即可）

}
```

