/* MATH.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

#ifndef  _MATH_H
#ifdef __cplusplus
extern "C" {
#endif
#define  _MATH_H

#include <sys/reent.h>
#include <machine/ieeefp.h>
#include "_ansi.h"

/* Reentrant ANSI C functions	*/

IMPORT_C double atan (double);
IMPORT_C double cos (double);
IMPORT_C double sin (double);
IMPORT_C double tan (double);
IMPORT_C double tanh (double);
IMPORT_C double frexp (double, int *);
IMPORT_C double modf (double, double *);
IMPORT_C double ceil (double);
IMPORT_C double fabs (double);
IMPORT_C double floor (double);

/* Non reentrant ANSI C functions.  */

#ifndef _REENT_ONLY
IMPORT_C double acos (double);
IMPORT_C double asin (double);
IMPORT_C double atan2 (double, double);
IMPORT_C double cosh (double);
IMPORT_C double sinh (double);
IMPORT_C double exp (double);
IMPORT_C double ldexp (double, int);
IMPORT_C double log (double);
IMPORT_C double log10 (double);
IMPORT_C double pow (double, double);
IMPORT_C double sqrt (double);
IMPORT_C double fmod (double, double);
#endif /* ! defined (_REENT_ONLY) */

/* Non ANSI functions provided by EPOC32 */

IMPORT_C double	copysign(double, double);
IMPORT_C double	expm1	(double);
IMPORT_C int	finite	(double);
IMPORT_C int	isnan	(double);
IMPORT_C int	isinf	(double);
IMPORT_C double	rint	(double);
IMPORT_C double	scalbn	(double, int);

#ifndef _STRICT_ANSI

/* Non ANSI double precision functions.  */

extern double infinity (void);
extern double nan (void);
extern int ilogb (double);

extern double asinh (double);
extern double cbrt (double);
extern double nextafter (double, double);

extern double log1p (double);

#ifndef _REENT_ONLY
extern double acosh (double);
extern double atanh (double);
extern double remainder (double, double);
extern double gamma (double);
extern double gamma_r (double, int *);
extern double lgamma (double);
extern double lgamma_r (double, int *);
extern double erf (double);
extern double erfc (double);
extern double y0 (double);
extern double y1 (double);
extern double yn (int, double);
extern double j0 (double);
extern double j1 (double);
extern double jn (int, double);
#define log2(x) (log (x) / M_LOG2_E)

extern double hypot (double, double);

extern double cabs();
extern double drem (double, double);

#endif /* ! defined (_REENT_ONLY) */

/* Single precision versions of ANSI functions.  */

extern float atanf (float);
extern float cosf (float);
extern float sinf (float);
extern float tanf (float);
extern float tanhf (float);
extern float frexpf (float, int *);
extern float modff (float, float *);
extern float ceilf (float);
extern float fabsf (float);
extern float floorf (float);

#ifndef _REENT_ONLY
extern float acosf (float);
extern float asinf (float);
extern float atan2f (float, float);
extern float coshf (float);
extern float sinhf (float);
extern float expf (float);
extern float ldexpf (float, int);
extern float logf (float);
extern float log10f (float);
extern float powf (float, float);
extern float sqrtf (float);
extern float fmodf (float, float);
#endif /* ! defined (_REENT_ONLY) */

/* Other single precision functions.  */

extern float infinityf (void);
extern float nanf (void);
extern int isnanf (float);
extern int isinff (float);
extern int finitef (float);
extern float copysignf (float, float);
extern int ilogbf (float);

extern float asinhf (float);
extern float cbrtf (float);
extern float nextafterf (float, float);
extern float rintf (float);
extern float scalbnf (float, int);
extern float log1pf (float);
extern float expm1f (float);

#ifndef _REENT_ONLY
extern float acoshf (float);
extern float atanhf (float);
extern float remainderf (float, float);
extern float gammaf (float);
extern float gammaf_r (float, int *);
extern float lgammaf (float);
extern float lgammaf_r (float, int *);
extern float erff (float);
extern float erfcf (float);
extern float y0f (float);
extern float y1f (float);
extern float ynf (int, float);
extern float j0f (float);
extern float j1f (float);
extern float jnf (int, float);
#define log2f(x) (logf (x) / (float) M_LOG2_E)
extern float hypotf (float, float);

extern float cabsf();
extern float dremf (float, float);

#endif /* ! defined (_REENT_ONLY) */

/* The gamma functions use a global variable, signgam.  */

extern int signgam;

/* The exception structure passed to the matherr routine.  */

struct exception 
{
  int type;
  char *name;
  double arg1;
  double arg2;
  double retval;
  int err;
};

extern int matherr (struct exception *e);

/* Values for the type field of struct exception.  */

#define DOMAIN 1
#define SING 2
#define OVERFLOW 3
#define UNDERFLOW 4
#define TLOSS 5
#define PLOSS 6

/* Useful constants.  */

#define M_E		2.7182818284590452354
#define M_LOG2E		1.4426950408889634074
#define M_LOG10E	0.43429448190325182765
#define M_LN2		0.69314718055994530942
#define M_LN10		2.30258509299404568402
#define M_PI		3.14159265358979323846
#define M_TWOPI         (M_PI * 2.0)
#define M_PI_2		1.57079632679489661923
#define M_PI_4		0.78539816339744830962
#define M_3PI_4		2.3561944901923448370E0
#define M_SQRTPI        1.77245385090551602792981
#define M_1_PI		0.31830988618379067154
#define M_2_PI		0.63661977236758134308
#define M_2_SQRTPI	1.12837916709551257390
#define M_SQRT2		1.41421356237309504880
#define M_SQRT1_2	0.70710678118654752440
#define M_LN2LO         1.9082149292705877000E-10
#define M_LN2HI         6.9314718036912381649E-1
#define M_SQRT3   	1.73205080756887719000
#define M_IVLN10        0.43429448190325182765 /* 1 / log(10) */
#define M_LOG2_E        0.693147180559945309417
#define M_INVLN2        1.4426950408889633870E0  /* 1 / log(2) */

/* Global control over fdlibm error handling.  */

enum __fdlibm_version
{
  __fdlibm_ieee = -1,
  __fdlibm_svid,
  __fdlibm_xopen,
  __fdlibm_posix
};

#define _LIB_VERSION_TYPE enum __fdlibm_version
#define _LIB_VERSION __fdlib_version

extern _LIB_VERSION_TYPE _LIB_VERSION;

#define _IEEE_  __fdlibm_ieee
#define _SVID_  __fdlibm_svid
#define _XOPEN_ __fdlibm_xopen
#define _POSIX_ __fdlibm_posix

#endif /* ! defined (_STRICT_ANSI) */

#ifdef __cplusplus
}
#endif
#endif /* _MATH_H */
