#pragma config(Sensor, in1,    Bat2,           sensorAnalog)
#pragma config(Sensor, dgtl1,  solenoid,       sensorDigitalOut)
#pragma config(Sensor, dgtl2,  BallIn,         sensorTouch)
#pragma config(Sensor, dgtl3,  BallOut,        sensorTouch)
#pragma config(Sensor, dgtl7,  IntakeEncoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  RightSpeed,     sensorQuadEncoder)
#pragma config(Sensor, dgtl11, LeftSpeed,      sensorQuadEncoder)
#pragma config(Motor,  port1,           FRD,           tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           BLD,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           LauncherR,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           LauncherRY,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           balllift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           BallL,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           LauncherL,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           LauncherLY,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           BRD,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          FLD,           tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"


////////////////////////////////////////////////////////////////////////////////////////////////////
//INTEGERS/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
int change = 0;


int mid = 55;
int close = 53 ;
int full = 60 ;

int battery1Level;
int battery2Level;
int bat;

int rightSpeed,leftSpeed,lastRightSpeed,lastLeftSpeed;
int intakeSpeed;

int Priority = 0;
int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;

int Balls = 0;
int pause;

int MVR;
int MVL;


////////////////////////////////////////////////////////////////////////////////////////////////////
//FIRST DRIVER/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////



void ball()   //counts balls
{
	if (SensorValue[BallIn]== 1 && pause != 1)
	{
		Balls = Balls+1;
		pause = 1;
		if (pause == 1)
		{
			if (SensorValue[BallIn]!= 1)
				pause = 0;
		}
	}


	if (SensorValue[BallOut]== 1 && pause != 1)
	{
		Balls = Balls-1;
		pause = 1;
		if (pause == 1)
		{
			if (SensorValue[BallIn]!= 1)
				pause = 0;
		}
	}

}

void Pnumatics() //brake
{
	if(vexRT[Btn6U] == 1)
		SensorValue[solenoid] = 1;
	else
		SensorValue[solenoid] = 0;
}


void Drive()
{
	if(Priority == 1 || Priority == 0)
	{
		if(abs(vexRT[Ch4]) > threshold)
		{
			Priority = 1;
			x1 = -vexRT[Ch4];
		}
		else
		{
			x1 = 0;
			Priority = 0;
		}

		if(abs(vexRT[Ch1]) > threshold)
		{
			Priority = 1;
			X2 = vexRT[Ch1];
		}
		else
		{
			X2 = 0;
			Priority = 0;
		}

		if(abs(vexRT[Ch3]) > threshold)
		{
			Priority = 1;
			Y1 = -vexRT[Ch3];
		}
		else
		{
			Y1 = 0;
			Priority = 0;
		}
	}

  motor[FRD] = Y1 - X2 - X1;
    motor[BRD] =  Y1 - X2 + X1;
    motor[FLD] = Y1 + X2 + X1;
    motor[BLD] =  Y1 + X2 - X1;
}


void Speed()
{

	lastLeftSpeed = leftSpeed;
	lastRightSpeed = rightSpeed;
	rightSpeed = SensorValue[RightSpeed];
	leftSpeed = SensorValue[LeftSpeed];

}


void Pid()
{if (rightSpeed < change )
	{
		MVR=MVR+1;
	}
	else if (rightSpeed > change && MVR > 0)
	{
MVR=MVR-1;
	}

	if (leftSpeed < change )
	{
		MVL=MVL+1;
	}
	else if (leftSpeed > change && MVL > 0)
	{
		MVL=MVL-1;
	}




	if(vexRT[Btn8U] == 1)
	{
		change = full;
		MVR = 80;
		MVL = 80;
		wait1Msec(20);
	}
	if(vexRT[Btn8D] == 1)
	{
		change = 0;
		MVR = 0;
		MVL = 0;
		wait1Msec(20);
	}
	if(vexRT[Btn8R] == 1)
	{
		change = mid;
		MVR = 64;
		MVL = 64;
		wait1Msec(20);
	}
	if(vexRT[Btn8L] == 1)
	{
		change = close;
		MVR = 58;
		MVL = 58;
		wait1Msec(20);
	}

	if(vexRT[Btn7D] == 1)
	{
		if(MVR >=0)
		{
			change = change -1;
			wait1Msec(200);
		}
	}

	if(vexRT[Btn7U] == 1)
	{
		change = change +1;
		wait1Msec(200);
	}
	motor[LauncherRY] = MVR;
	motor[LauncherR] = MVR;
	motor[LauncherL] = MVL;
	motor[LauncherLY] = MVL;
}


void Fire()
{
	if(vexRT[Btn5U] == 1)
	{
		motor[BallL] = 127;
		motor[balllift] = 127;
	}
	else if(vexRT[Btn5D] == 1)
	{
		motor[BallL] = -127;
		motor[balllift] = -127;
	}
	else
	{
		motor[BallL] = 0;
		motor[balllift] = 0;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//SECOND DRIVER/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////


void Pnumatics2()
{
	if(vexRT[Btn6UXmtr2] == 1)
		SensorValue[solenoid] = 1;
	else
		SensorValue[solenoid] = 0;
}


void Drive2()
{
	if(Priority == 2 || Priority == 0)
	{
		if(abs(vexRT[Ch3Xmtr2]) > threshold)
		{
			Priority = 1;
			Y1 = vexRT[Ch3Xmtr2];
		}
		else
		{
			Y1 = 0;
			Priority = 0;
		}

		if(abs(vexRT[Ch4Xmtr2]) > threshold)
		{
			Priority = 1;
			X1 = vexRT[Ch4Xmtr2];
		}
		else
		{
			X1 = 0;
			Priority = 0;
		}

		if(abs(vexRT[Ch1Xmtr2]) > threshold)
		{
			Priority = 1;
			X2 = -vexRT[Ch1Xmtr2];
		}
		else
		{
			X2 = 0;
			Priority = 0;
		}
	}
}


void Pid2()
{
	if(vexRT[Btn8UXmtr2] == 1)
	{
		change = full;
	}
	if(vexRT[Btn8DXmtr2] == 1)
	{
		change = 0;
	}
	if(vexRT[Btn8RXmtr2] == 1)
	{
		change = mid;
	}
	if(vexRT[Btn8LXmtr2] == 1)
	{
		change = close;
	}

	if(vexRT[Btn7DXmtr2] == 1)
	{
		if(MVR >0)
		{
			MVR = MVR-1;
			MVL = MVL-1;
			wait1Msec(200);
		}
	}

	if(vexRT[Btn7UXmtr2] == 1)
	{
		MVR = MVR+1;
		MVL = MVL+1;
		wait1Msec(200);
	}
}

void Fire2()
{
	if(vexRT[Btn5UXmtr2] == 1)
	{
		motor[BallL] = 127;
		motor[balllift] = 127;
	}
	else if(vexRT[Btn5DXmtr2] == 1)
	{
		motor[BallL] = -127;
		motor[balllift] = -127;
	}
	else
	{
		motor[BallL] = 0;
		motor[balllift] = 0;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//TASK CONTROL/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////


void pre_auton()
{
	SensorValue[LeftSpeed] = 0;
	SensorValue[RightSpeed] = 0;
	SensorValue[IntakeEncoder] = 0;
}


task autonomous()
{
	//Pid();
	//Shoot();
	//change = full;
}

task usercontrol()
{
	while (true)
	{
		ball();
		if (time1[T1]>100)
		{
			Speed();
			resetTimer();
			SensorValue[LeftSpeed] = 0;
			SensorValue[RightSpeed] = 0;
		}

		Drive();
		Fire();
		Pnumatics();
		Pid();
		Drive2();
		Fire2();
		Pnumatics2();
		Pid2();
	}
}
