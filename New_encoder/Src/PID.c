#include "PID.h"
#include "global.h"

extern float timer;

float Kp = 2;	//5
float Ki =5;	//10
float Kd =0.01;	//0.3

float resP;
float resI=0;
float resD;
float PID;
float Err;

float PrevErr=0;
 int val=0;

void SET_ARR_VELOSITY(){
	VELOSITY_UST[0]=10000;
	VELOSITY_UST[1]=7000;
	VELOSITY_UST[2]=8000;
	VELOSITY_UST[3]=0;
	VELOSITY_UST[4]=12000;
	VELOSITY_UST[5]=7000;
	VELOSITY_UST[6]=9000;
	SET_VELOSITY=VELOSITY_UST[0];
}

 void SET_DELAY_ZEROS()
 {
 	for (int i=0; i<DELAY;i++)
 	{
 		VELOSITY_DELAY[i]=0;
 		dt_DELAY[i]=0;
 	}
 }

 void PID_ENABLE(){
	 if (flag==CalculateMode){
	 			PWM=PID_set(SET_VELOSITY,VELOSITY);
	 			PWM_SET_VAL(PWM);
	 		flag=StopMode;
	 		}
 }




 int PID_set(float velosity_ust,float real_velosity){
	Err=velosity_ust - real_velosity;
	resP = Kp * (Err);
	if (resP < 0) {
			resP = 0;
		}
	if(resP>40000){
			resP=40000;
		}

	resI += Ki * (Err)*dt;

//	if (resI < 0) {
//				resI = 0;
//			}
	if(resI>40000){
		resI=40000;
	}

	resD = Kd * (Err-PrevErr)/dt;
	PrevErr=Err;
//	if (resD < 0) {
//					resD = 0;
//				}
//	if(resD>40000){
//		resD=40000;
//	}



	PID=resP+resI+resD;
	if(PID<0){
			PID=0;
		}
	if(PID>40000){
		PID=40000;
	}
	return PID;
	}



