#ifndef FOLLOW_H
#define FOLLOW_H

struct vec3 {
	double x, y, z;
};

struct svec {
	double a, A;
};

struct star_path {
	/* Place of the star at t=zerotime */
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

void new_star_path(struct star_path *, double, double, double, int);
void new_vec3(struct vec3 *, double, double, double);
void new_svec(struct svec *, double, double);
void vec3_to_svec(struct vec3, struct svec*);
void svec_to_vec3(struct svec, struct vec3*);
struct svec star_now(struct star_path, int);
struct svec dir_now(struct star_path, int);
#endif /* FOLLOW_H */
