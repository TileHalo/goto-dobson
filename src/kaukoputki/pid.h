#ifndef PID_H
#define PID_H
#ifdef __cplusplus
extern "C" {
#endif

/* The PID-controller used to drive motors
 *
 * members:
 * P: Propotional gain
 * I: Integral gain
 * D: Derivative gain
 * E: Previous error
 * Kp: Propotional parameter
 * Ki: Integral parameter
 * Kd: Derivative parameter
 */
struct pid {
	double P, I, D;
	double previous_error;

	double Kp, Ki, Kd;
};


/* Create a new PID with default parameters */
struct pid new_pid(void);
/* Tunes the PID controller
 *
 * params:
 * struct pid * controller: controller to be tuned.
 * double Kp: new Kp parameter
 * double Ki: new Ki parameter
 * double Kd: new Kd parameter
 */
void tune_pid(struct pid *, double, double, double);
/* Runs the PID controller once.
 *
 * params:
 * struct pid *controller: controller to be run.
 * double error: The current error
 * int dt: The time taken since previous step.
 */
double run_pid(struct pid *, double, int);


#ifdef __cplusplus
}
#endif
#endif /* end of include guard: PID_H */
