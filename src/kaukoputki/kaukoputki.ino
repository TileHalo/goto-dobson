#include <Stepper.h>
#include "follow.h"
#include "pid.h"


#define CONTROLLERS 4 /* Two per each motor, one to follow and one to find */
struct pid controllers[CONTROLLERS];
double longitude;
double aoffset, Aoffset; /* The possible offsets due to uneven surfaces. */
int curtime;
unsigned short state; /* Three states, 0 = do nothing, 1 = track current path,
                         2 = find star, currently unused */
struct star_path current_path;

/* Because time will overflow at 70 minutes */
static int time_since(int);
static void star_follower(void);
static unsigned short check_follow(void);

void setup() {
  int i;

  state = 0;
  for (int i = 0; i < CONTROLLERS; i++) {
    controllers[i] = new_pid();
  }
  longitude = 60; /* set using the GPS */
  aoffset = 0; /* Possibility for future, default to zero */
  Aoffset = 0; /* Possibility for future, default to zero */
}

void loop() {
  if (state) {
    star_follower();
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
  double results[CONTROLLERS];
  double setpoints[CONTROLLERS];
  double measurements[CONTROLLERS];
  int dt;

  dt = time_since(curtime);
  for (int i = 0; i < CONTROLLERS; i++) {
    results[i] = run_pid(&controllers[i], setpoints[i] - measurements[i], dt);
  }
}

static unsigned short
check_follow()
{
  return 0;
}
