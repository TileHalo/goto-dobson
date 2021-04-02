#ifndef FOLLOW_H
#define FOLLOW_H
#ifdef __cplusplus
extern "C" {
#endif

/* Cartesian coordinates */
struct vec3 {
	double x, y, z;
};

/* Position in the night sky as spherical coordinates. Radius is assumed to be one.
 *
 * double a: The altitude of the point, measured from horizon, between [-90, 90].
 * double A: The azimuth of the point, measured from the south pole clockwise.
 * Range [0, 360]
 * */
struct svec {
	double a, A;
};

struct star_path {
	/* Place of the star at t=zerotime, in both coordinates */
	struct vec3 c;
	struct svec s;
	/* vector in the direction of celestial pole */
	struct vec3 n, w, v;
	/* The radius of parametrized circle */
	double r;
	/* Current longitude */
	double lon;
	int zerotime;
};

/* Normalized path is the path which is described by three components.
 *
 * members:
 * double a: the altitude at the highest point. Range [0, 90]. Unit degrees
 * double A: the azimuth at the highest point. Should be either 0 or 180.
 * double L: the longitude at current observation point. Should be in range [-90, 90].
 * int time: the zerotime of the path. Time at the highest point.
 */
struct normalized_path {
	double a, A, L;
	int time;
};

/* Create a new starpath from raw parameters
 *
 * params:
 * struct star_path * path: pointer to the path being created
 * double a: The desired altitude at zerotime, between [0, 90].
 * double A: The desired azimuth at zerotime, between [0, 360].
 * double lon: The desired observation longitude, between [-90, 90].
 * int zero: The desired zerotime.
 *
 * returns: void
 */
void new_star_path(struct star_path *, double, double, double, int);
/* Create a new Cartesian vector
 *
 * params:
 * struct vec3 * vec: pointer to the vector being created
 * double x: x-component
 * doubly y: y-component
 * double z: z-component
 */
void new_vec3(struct vec3 *, double, double, double);
void new_svec(struct svec *, double, double);
void vec3_to_svec(struct vec3, struct svec*);
void svec_to_vec3(struct svec, struct vec3*);
/* Given star path, returns the current position of said path.
 *
 * params:
 * struct star_path: The star path in which the position lies.
 * int time: The current time
 *
 * returns:
 * The current star position in spherical coordinates
 */
struct svec star_now(struct star_path, int);
/* Given star path, returns the current tangent of said path.
 *
 * params:
 * struct star_path: The star path in which the position lies.
 * int time: The current time
 *
 * returns:
 * The current tangent in spherical coordinates
 */
struct svec dir_now(struct star_path, int);
#ifdef __cplusplus
}
#endif
#endif /* FOLLOW_H */
