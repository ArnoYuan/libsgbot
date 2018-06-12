/* Created std-math/math.h by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifndef _STDM_MATH_H_
#define _STDM_MATH_H_

#ifndef _MATH_H
#define M_PI		3.14159265358979323846	/* pi */
#define M_PI_2		1.57079632679489661923	/* pi/2 */
#define M_PI_4		0.78539816339744830962	/* pi/4 */
#define M_E			2.7182818284590452354	/* e */
#define M_LOG2E		1.4426950408889634074	/* log_2 e */
#define M_LOG10E	0.43429448190325182765	/* log_10 e */
#define M_LN2		0.69314718055994530942	/* log_e 2 */
#define M_LN10		2.30258509299404568402	/* log_e 10 */
#define M_1_PI		0.31830988618379067154	/* 1/pi */
#define M_2_PI		0.63661977236758134308	/* 2/pi */
#define M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */
#define M_SQRT2		1.41421356237309504880	/* sqrt(2) */
#define M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2) */
#endif 


namespace sgbot {
namespace math {

  int abs(int i);

  float cabs(float a, float b);

  float fabs(float x);

  long labs(long n);

  float exp(float x);

  float floor(float x);

  float ceil(float value);

  float frexp(float value, int *eptr);

  float ldexp(float value, int exp);

  float log(float x);

  float log10(float x);

  float pow(float x, float y);

  float pow10(int p);

  float sqrt(float x);

  float acos(float x);

  float asin(float x);

  float atan(float x);

  float atan2(float y, float x);

  float cos(float x);

  float sin(float x);

  float tan(float x);

  float cosh(float x);

  float sinh(float x);

  float tanh(float x);

  float hypot(float x, float y);

  float fmod(float x, float y);

  inline int sign(int n)
  {
    return (n > 0) ? 1 : -1;
  }

  inline float sqr(float x)
  {
    return (x * x);
  }

}  // namespace math  
}  // namespace sgbot

#endif  // _STDM_MATH_H_
