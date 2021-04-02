#include "pid.h"

#define KP 1
#define KI 0
#define KD 0

struct pid
new_pid(void)
{
	struct pid cont;

	cont.P = 0;
	cont.I = 0;
	cont.D = 0;

	cont.previous_error = 0;

	cont.Kp = KP;
	cont.Ki = KI;
	cont.Kd = KD;


	return cont;
}

void
tune_pid(struct pid *cont, double Kp, double Ki, double Kd)
{
	cont->Kp = Kp;
	cont->Ki = Ki;
	cont->Kd = Kd;
}

double
run_pid(struct pid *cont, double error, int dt)
{
	cont->P = error;
	cont->I += error*dt;
	cont->D = (error - cont->previous_error)/dt;
	cont->previous_error = error;

	return cont->Kp*cont->P + cont->Ki*cont->I + cont->Kd*cont->D;

}
