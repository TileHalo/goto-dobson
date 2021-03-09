#include "follow.h"

#define PI 3.1415

static double atan2(double, double);
static double innerpr(struct vec3, struct vec3);
static double norm(struct vec3);
static void mulvec(struct vec3 *, double);
static void cross(struct vec3 *, struct vec3);
static void addvec(struct vec3 *, struct vec3);
static void subvec(struct vec3 *, struct vec3);

void
new_star_path(struct star_path *p, double a, double A, double lon, int zero)
{
	struct vec3 k;
	double d;

	p->s.a = PI/2.0 - PI/180.0*a;
	p->s.A = -PI/180.0*A;
	p->c = svec_to_vec3(p->s);
	p->lon = PI/180.0*lon;
	p->zerotime = zero;

	/* Calculate the parallel vector K */
	k = -1.0*sin(lon) + cos(lon)

	/* Calculate the distance d and vectors n and v */
	d = innerpr(p->c, k);
	mulvec(&(p->n), d);
	p->v = p->c;
	subvec(&(p->v), p->n)
	p->r = norm(temp);
	mulvec(&(p->v), 1/p->r);

	/* Calculate the second difference vector */
	p->w = p->n;
	cross(&(p->w), p->v);
	mulvec(&(p->w), norm(p->w));
}

void
vec3_to_svec(struct vec3 v, struct svec *u)
{
	u->a = acos(1/z);
	u->A = atan2(v.x, v.y);
}

void svec_to_vec3(struct svec v, struct vec3 *u)
{
	u->x = sin(v.a)*cos(v.A);
	u->y = sin(v.a)*sin(v.A);
	u->z = cos(v.a);
}

struct svec
star_now(struct star_path p, int time)
{
	struct vec3 t, t1, t2;
	struct svec res;
	double tau;

	t = p.n;
	t1 = p.w;
	t2 = p.v;
	tau = -1.0*2*PI/8860*(double)time;

	mulvec(&t1, p->r*sin(tau));
	mulvec(&t2, p->r*cos(tau));
	addvec(&t, t1);
	addvec(&t, t2);

	vec3_to_svec(t, &res);

	return res;
}

struct svec
dir_now(struct star_path p, int time)
{
	struct vec3 t1, t2;
	struct svec res;
	double tau, dtau;

	t1 = p.w;
	t2 = p.v;
	dtau = -1.0*2*PI/8860.0;
	tau = dtau*(double)time;

	mulvec(&t1, p->r*dtau*cos(tau));
	mulvec(&t2, p->r*-1.0*dtau*sin(tau));
	addvec(&t1, t2);

	vec3_to_svec(t1, &res);

	return res;
}


static double
atan2(double x, double y)
{
	return atan(x/y);
}

static double
innerpr(struct vec3 v, struct vec3 u)
{
	return v.x*u.x + v.y*u.y + v.z*u.z;
}

static double
norm(struct vec3 v)
{
	return sqrt(innerpr(v, v);
}

static void
mulvec(struct vec3 *v, double k)
{
	v->x *= k;
	v->y *= k;
	v->z *= k;
}

static void
cross(struct vec3 *v, struct vec3 u)
{
	struct vec3 t;
	t.x = v->y*u.z - v->z*u.y;
	t.y = v->z*u.x - v->x*u.z;
	t.z = v->x*u.y - v->y*u.x;

	v->x = t.x;
	v->y = t.y;
	v->z = t.z;
}

static void
addvec(struct vec3 *v, struct vec3 u)
{
	v->x += u.x;
	v->x += u.y;
	v->x += u.z;
}

static void
subvec(struct vec3 *v, struct vec3 u)
{
	v->x -= u.x;
	v->x -= u.y;
	v->x -= u.z;
}
