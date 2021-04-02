#include <Stepper.h>
#include "follow.h"
#include "pid.h"


struct pid controllers[4]; /* Two per each motor, one to follow and one to find */
double longitude;
double aoffset, Aoffset; /* The possible offsets due to uneven surfaces. */
int curtime;
int steps_per_revolution = 200;
int steps_per_cycle = 2;
unsigned short state; /* Three states, 0 = do nothing, 1 = track current path,
                         2 = find star, currently unused */
struct star_path current_path;

/* Because time will overflow at 70 minutes */
static int time_since(int);
static void star_follower(void);
static unsigned short check_follow(void);
Stepper azimuth(stepsPerRevolution, 10, 11);
Stepper altitude(stepsPerRevolution, 8, 9);
Stepper steppers[2];

void setup() {
  int i;

  state = 0;
  for (int i = 0; i < CONTROLLERS; i++) {
    controllers[i] = new_pid();
  }
  longitude = 60; /* set using the GPS */
  aoffset = 0; /* Possibility for future, default to zero */
  Aoffset = 0; /* Possibility for future, default to zero */
  steppers[0] = azimuth;
  steppers[1] = altitude;
}

void loop() {
  if (state) {
    /* Reset the seeker controllers */
    for (int i = 2; i < 4; i++) {
      controllers[i].P = 0;
      controllers[i].I = 0;
      controllers[i].D = 0;
      controllers[i].previous_error = 0;
    }
    star_follower();
  } else if (state >> 1) {
    /* Reset following controllers */
    for (int i = 0; i < 2; i++) {
      controllers[i].P = 0;
      controllers[i].I = 0;
      controllers[i].D = 0;
      controllers[i].previous_error = 0;
    }
  } else {
    /* Reset all controllers, not used here */
    for (int i = 0; i < 4; i++) {
      controllers[i].P = 0;
      controllers[i].I = 0;
      controllers[i].D = 0;
      controllers[i].previous_error = 0;
    }
  }
  if (check_follow()) {
    state = abs(state  - 1);
  }
  curtime = micros();
}

static int
time_since(int time)
{
  return micros() - time;
}

static void
star_follower(void)
{
  double results[2];
  double setpoints[2];
  double measurements[2];
  int dt;

  dt = time_since(curtime);
  for (int i = 0; i < 2; i++) {
    results[i] = run_pid(&controllers[i], setpoints[i] - measurements[i], dt);
    results[i] = map(results[i], 0, 10, 0, 100);
    steppers[i].setSpeed(results[i]);
    steppers[i].step(steps_per_cycle);
  }
}

static unsigned short
check_follow()
{
  return 0;
}
