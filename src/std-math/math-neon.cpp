/* Created std-math/math-neon.cpp by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifdef _USE_ARM_NEON_

#include <std-math/math.h>

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
 


#ifdef GCC
#define ALIGN(A) __attribute__ ((aligned (A))
#else
#define ALIGN(A)
#endif

  const float __expf_rng[2]={
    1.442695041f,
    0.693147180f
  };

  const float __expf_lut[8] = {
    0.9999999916728642,		//p0
    0.04165989275009526, 	//p4
    0.5000006143673624, 	//p2
    0.0014122663401803872, 	//p6
    1.000000059694879, 		//p1
    0.008336936973260111, 	//p5
    0.16666570253074878, 	//p3
    0.00019578093328483123	//p7
  };

  const float __logf_rng =  0.693147180f;

  const float __logf_lut[8] = {
	-2.295614848256274, 	//p0
	-2.470711633419806, 	//p4
	-5.686926051100417, 	//p2
	-0.165253547131978, 	//p6
	+5.175912446351073, 	//p1
	+0.844006986174912, 	//p5
	+4.584458825456749, 	//p3
	+0.014127821926000		//p7
  };

  const float __log10f_rng =  0.3010299957f;

  const float __log10f_lut[8] = {
	-0.99697286229624, 		//p0
	-1.07301643912502, 		//p4
	-2.46980061535534, 		//p2
	-0.07176870463131, 		//p6
	2.247870219989470, 		//p1
	0.366547581117400, 		//p5
	1.991005185100089, 		//p3
	0.006135635201050,		//p7
  };

  const float __powf_rng[2] = {
	1.442695041f,
	0.693147180f
  };

  const float __powf_lut[16] = {
	-2.295614848256274, 	//p0	log
	-2.470711633419806, 	//p4
	-5.686926051100417, 	//p2
	-0.165253547131978, 	//p6
	+5.175912446351073, 	//p1
	+0.844006986174912, 	//p5
	+4.584458825456749, 	//p3
	+0.014127821926000,		//p7
	0.9999999916728642,		//p0	exp
	0.04165989275009526, 	//p4
	0.5000006143673624, 	//p2
	0.0014122663401803872, 	//p6
	1.000000059694879, 		//p1
	0.008336936973260111, 	//p5
	0.16666570253074878, 	//p3
	0.00019578093328483123	//p7
  };


  const float __asinf_lut[4] = {
	0.105312459675071, 	//p7
	0.169303418571894,	//p3
	0.051599985887214, 	//p5
	0.999954835104825	//p1
  }; 

  const float __asinf_pi_2 = M_PI_2;

  const float __acosf_pi_2 = M_PI_2;

  const float __atanf_lut[4] = {
	-0.0443265554792128,	//p7
	-0.3258083974640975,	//p3
	+0.1555786518463281,	//p5
	+0.9997878412794807  	//p1
  }; 
 
  const float __atanf_pi_2 = M_PI_2;

  const float __atan2f_lut[4] = {
	-0.0443265554792128,	//p7
	-0.3258083974640975,	//p3
	+0.1555786518463281,	//p5
	+0.9997878412794807  	//p1
  }; 
 
  const float __atan2f_pi_2 = M_PI_2;

  static const float __sinf_rng[2] = {
	2.0 / M_PI,
	M_PI / 2.0
  } ALIGN(16);

  static const float __sinf_lut[4] = {
	-0.00018365f,	//p7
	-0.16664831f,	//p3
	+0.00830636f,	//p5
	+0.99999661f,	//p1
  } ALIGN(16);

  const float __tanf_rng[2] = {
	2.0 / M_PI,
	M_PI / 2.0
  };

  const float __tanf_lut[4] = {
	-0.00018365f,	//p7
	-0.16664831f,	//p3
	+0.00830636f,	//p5
	+0.99999661f,	//p1
  };

  const float __coshf_rng[2] = {
	1.442695041f,
	0.693147180f
  };

  const float __coshf_lut[16] = {
	0.00019578093328483123,	//p7
	0.00019578093328483123,	//p7
	0.0014122663401803872, 	//p6
	0.0014122663401803872, 	//p6
	0.008336936973260111, 	//p5
	0.008336936973260111, 	//p5
	0.04165989275009526, 	//p4
	0.04165989275009526, 	//p4
	0.16666570253074878, 	//p3
	0.16666570253074878, 	//p3
	0.5000006143673624, 	//p2
	0.5000006143673624, 	//p2
	1.000000059694879, 		//p1
	1.000000059694879, 		//p1
	0.9999999916728642,		//p0
	0.9999999916728642		//p0
  };

  const float __sinhf_rng[2] = {
	1.442695041f,
	0.693147180f
  };

  const float __sinhf_lut[16] = {
	0.00019578093328483123,	//p7
	0.00019578093328483123,	//p7
	0.0014122663401803872, 	//p6
	0.0014122663401803872, 	//p6
	0.008336936973260111, 	//p5
	0.008336936973260111, 	//p5
	0.04165989275009526, 	//p4
	0.04165989275009526, 	//p4
	0.16666570253074878, 	//p3
	0.16666570253074878, 	//p3
	0.5000006143673624, 	//p2
	0.5000006143673624, 	//p2
	1.000000059694879, 		//p1
	1.000000059694879, 		//p1
	0.9999999916728642,		//p0
	0.9999999916728642		//p0
  };

  int abs(int i)
  {
	return ((i>=0)?i:-i);
  }

  float fabs(float x)
  {
	asm volatile (
	"vabs.f32	 		s0, s0					\n\t"	//s0 = fabs(s0)
	);
  }

  long labs(long n)
  {
	return ((n>=0)?n:-n);
  }


/*
Based on: 

		e ^ x = (1+m) * (2^n)
		x = log(1+m) + n * log(2)
		n = (int) (x * 1.0 / log(2))
		(1+m) = e ^ (x - n * log(2))
		(1+m) = Poly(x - n * log(2))
		
		where Poly(x) is the Minimax approximation of e ^ x over the 
		range [-Log(2), Log(2)]

Test func : expf(x)
Test Range: 0 < x < 50
Peak Error:	~0.00024%
RMS  Error: ~0.00007%
*/

  float exp(float x)
  {
	asm volatile (
	"vdup.f32 		d0, d0[0]				\n\t"	//d0 = {x, x}
	
	//Range Reduction:
	"vld1.32 		d2, [%0]				\n\t"	//d2 = {invrange, range}
	"vmul.f32 		d6, d0, d2[0]			\n\t"	//d6 = d0 * d2[0] 
	"vcvt.s32.f32 	d6, d6					\n\t"	//d6 = (int) d6
	"vcvt.f32.s32 	d1, d6					\n\t"	//d1 = (float) d6
	"vmls.f32 		d0, d1, d2[1]			\n\t"	//d0 = d0 - d1 * d2[1]
		
	//polynomial:
	"vmul.f32 		d1, d0, d0				\n\t"	//d1 = d0*d0 = {x^2, x^2}	
	"vld1.32 		{d2, d3, d4, d5}, [%1]	\n\t"	//q1 = {p0, p4, p2, p6}, q2 = {p1, p5, p3, p7} ;
	"vmla.f32 		q1, q2, d0[0]			\n\t"	//q1 = q1 + q2 * d0[0]		
	"vmla.f32 		d2, d3, d1[0]			\n\t"	//d2 = d2 + d3 * d1[0]		
	"vmul.f32 		d1, d1, d1				\n\t"	//d1 = d1 * d1 = {x^4, x^4}	
	"vmla.f32 		d2, d1, d2[1]			\n\t"	//d2 = d2 + d1 * d2[1]		

	//multiply by 2 ^ m 	
	"vshl.i32 		d6, d6, #23				\n\t"	//d6 = d6 << 23		
	"vadd.i32 		d0, d2, d6				\n\t"	//d0 = d2 + d6		

	:: "r"(__expf_rng), "r"(__expf_lut) 
    : "d0", "d1", "q1", "q2", "d6"
	);
  }

  float floor(float x)
  {

	asm volatile (
	"vcvt.s32.f32 	d1, d0					\n\t"	//d1 = (int) d0;
	"vcvt.f32.s32 	d1, d1					\n\t"	//d1 = (float) d1;
	"vcgt.f32 		d0, d1, d0				\n\t"	//d0 = (d1 > d0);
	"vshr.u32 		d0, #31					\n\t"	//d0 = d0 >> 31;
	"vcvt.f32.u32 	d0, d0					\n\t"	//d0 = (float) d0;
	"vsub.f32 		d0, d1, d0				\n\t"	//d0 = d1 - d0;
	::: "d0", "d1"
	);
  }

  float ceil(float value)
  {
	asm volatile (
	"vmov		s0,%0					\n\t"
	"vcvt.s32.f32 	d1, d0					\n\t"	//d1 = (int) d0;
	"vcvt.f32.s32 	d1, d1					\n\t"	//d1 = (float) d1;
	"vcgt.f32 		d0, d0, d1				\n\t"	//d0 = (d0 > d1);
	"vshr.u32 		d0, #31					\n\t"	//d0 = d0 >> 31;
	"vcvt.f32.u32 	d0, d0					\n\t"	//d0 = (float) d0;
	"vadd.f32 		d0, d1, d0				\n\t"	//d0 = d1 + d0;

	::"r"(value): "d0", "d1"
	);
  }

  float frexp(float value, int *eptr)
  {
	union {
		float 	f;
		int 	i;
	} r;
	int n;
	
	r.f = value;
	n = r.i >> 23;
	n = n & 0xFF;
	n = n - 126;
	r.i = r.i - (n << 23);
	*eptr = n;
	return r.f;
  }

  float ldexp(float value, int exp)
  {
	float r;
	asm volatile (
	"lsl 			r0, r0, #23				\n\t"	//r0 = r0 << 23	
	"vdup.i32 		d1, r0					\n\t"	//d1 = {r0, r0}
	"vadd.i32 		d0, d0, d1				\n\t"	//d0 = d0 + d1
	::: "d0", "d1"
	);
  }

  float log(float x)
  {
	asm volatile (
	
	"vdup.f32		d0, d0[0]				\n\t"	//d0 = {x,x};
	
	//extract exponent
	"vmov.i32		d2, #127				\n\t"	//d2 = 127;
	"vshr.u32		d6, d0, #23				\n\t"	//d6 = d0 >> 23;
	"vsub.i32		d6, d6, d2				\n\t"	//d6 = d6 - d2;
	"vshl.u32		d1, d6, #23				\n\t"	//d1 = d6 << 23;
	"vsub.i32		d0, d0, d1				\n\t"	//d0 = d0 + d1;

	//polynomial:
	"vmul.f32 		d1, d0, d0				\n\t"	//d1 = d0*d0 = {x^2, x^2}	
	"vld1.32 		{d2, d3, d4, d5}, [%1]	\n\t"	//q1 = {p0, p4, p2, p6}, q2 = {p1, p5, p3, p7} ;
	"vmla.f32 		q1, q2, d0[0]			\n\t"	//q1 = q1 + q2 * d0[0]		
	"vmla.f32 		d2, d3, d1[0]			\n\t"	//d2 = d2 + d3 * d1[0]		
	"vmul.f32 		d1, d1, d1				\n\t"	//d1 = d1 * d1 = {x^4, x^4}	
	"vmla.f32 		d2, d1, d2[1]			\n\t"	//d2 = d2 + d1 * d2[1]		

	//add exponent 	
	"vdup.32 		d7, %0					\n\t"	//d7 = {rng, rng}
	"vcvt.f32.s32 	d6, d6					\n\t"	//d6 = (float) d6
	"vmla.f32 		d2, d6, d7				\n\t"	//d2 = d2 + d6 * d7		

	"vmov.f32 		s0, s4					\n\t"	//s0 = s4

	:: "r"(__logf_rng), "r"(__logf_lut) 
    : "d0", "d1", "q1", "q2", "d6", "d7"
	);
  }

/*
Based on: 

		log10(x) = log10((1+m) * (2^n))
		log(x) = n * log10(2) + log10(1 + m)
		log(1+m) = Poly(1+m)
		
		where Poly(x) is the Minimax approximation of log10(x) over the 
		range [1, 2]

Test func : log10f(x)
Test Range: 1 < x < 10000
Peak Error:	~0.000040%
RMS  Error: ~0.000008%
*/
  float log10(float x)
  {
	asm volatile (
	
	"vdup.f32		d0, d0[0]				\n\t"	//d0 = {x,x};
	
	//extract exponent
	"vmov.i32		d2, #127				\n\t"	//d2 = 127;
	"vshr.u32		d6, d0, #23				\n\t"	//d6 = d0 >> 23;
	"vsub.i32		d6, d6, d2				\n\t"	//d6 = d6 - d2;
	"vshl.u32		d1, d6, #23				\n\t"	//d1 = d6 << 23;
	"vsub.i32		d0, d0, d1				\n\t"	//d0 = d0 + d1;

	//polynomial:
	"vmul.f32 		d1, d0, d0				\n\t"	//d1 = d0*d0 = {x^2, x^2}	
	"vld1.32 		{d2, d3, d4, d5}, [%1]	\n\t"	//q1 = {p0, p4, p2, p6}, q2 = {p1, p5, p3, p7} ;
	"vmla.f32 		q1, q2, d0[0]			\n\t"	//q1 = q1 + q2 * d0[0]		
	"vmla.f32 		d2, d3, d1[0]			\n\t"	//d2 = d2 + d3 * d1[0]		
	"vmul.f32 		d1, d1, d1				\n\t"	//d1 = d1 * d1 = {x^4, x^4}	
	"vmla.f32 		d2, d1, d2[1]			\n\t"	//d2 = d2 + d1 * d2[1]		

	//add exponent 	
	"vdup.32 		d7, %0					\n\t"	//d7 = {rng, rng}
	"vcvt.f32.s32 	d6, d6					\n\t"	//d6 = (float) d6
	"vmla.f32 		d2, d6, d7				\n\t"	//d2 = d2 + d6 * d7		

	"vmov.f32 		s0, s4					\n\t"	//s0 = s4

	:: "r"(__log10f_rng), "r"(__log10f_lut) 
    : "d0", "d1", "q1", "q2", "d6", "d7"
	);
  }

  float pow(float x,float y)
{
	asm volatile (
		
	"vdup.f32		d16, d0[1]				\n\t"	//d16 = {y,y};	
	"vdup.f32		d0, d0[0]				\n\t"	//d0 = {x,x};
	
	//extract exponent
	"vmov.i32		d2, #127				\n\t"	//d2 = 127;
	"vshr.u32		d6, d0, #23				\n\t"	//d6 = d0 >> 23;
	"vsub.i32		d6, d6, d2				\n\t"	//d6 = d6 - d2;
	"vshl.u32		d1, d6, #23				\n\t"	//d1 = d6 << 23;
	"vsub.i32		d0, d0, d1				\n\t"	//d0 = d0 + d1;

	//polynomial:
	"vmul.f32 		d1, d0, d0				\n\t"	//d1 = d0*d0 = {x^2, x^2}	
	"vld1.32 		{d2, d3, d4, d5}, [%1]!	\n\t"	//q1 = {p0, p4, p2, p6}, q2 = {p1, p5, p3, p7} ;
	"vmla.f32 		q1, q2, d0[0]			\n\t"	//q1 = q1 + q2 * d0[0]		
	"vmla.f32 		d2, d3, d1[0]			\n\t"	//d2 = d2 + d3 * d1[0]		
	"vmul.f32 		d1, d1, d1				\n\t"	//d1 = d1 * d1 = {x^4, x^4}	
	"vmla.f32 		d2, d1, d2[1]			\n\t"	//d2 = d2 + d1 * d2[1]		

	//add exponent 	
	"vld1.32 		d7, [%0]				\n\t"	//d7 = {invrange, range}
	"vcvt.f32.s32 	d6, d6					\n\t"	//d6 = (float) d6
	"vmla.f32 		d2, d6, d7[1]			\n\t"	//d2 = d2 + d6 * d7[1]		

	"vdup.f32 		d0, d2[0]				\n\t"	//d0 = d2[0]		
	"vmul.f32 		d0, d0, d16				\n\t"	//d0 = d0 * d16	

	//Range Reduction:
	"vmul.f32 		d6, d0, d7[0]			\n\t"	//d6 = d0 * d7[0] 
	"vcvt.u32.f32 	d6, d6					\n\t"	//d6 = (int) d6
	"vcvt.f32.u32 	d1, d6					\n\t"	//d1 = (float) d6
	"vmls.f32 		d0, d1, d7[1]			\n\t"	//d0 = d0 - d1 * d7[1]
		
	//polynomial:
	"vmul.f32 		d1, d0, d0				\n\t"	//d1 = d0*d0 = {x^2, x^2}	
	"vld1.32 		{d2, d3, d4, d5}, [%1]	\n\t"	//q1 = {p0, p4, p2, p6}, q2 = {p1, p5, p3, p7} ;
	"vmla.f32 		q1, q2, d0[0]			\n\t"	//q1 = q1 + q2 * d0[0]		
	"vmla.f32 		d2, d3, d1[0]			\n\t"	//d2 = d2 + d3 * d1[0]		
	"vmul.f32 		d1, d1, d1				\n\t"	//d1 = d1 * d1 = {x^4, x^4}	
	"vmla.f32 		d2, d1, d2[1]			\n\t"	//d2 = d2 + d1 * d2[1]		

	//multiply by 2 ^ m 	
	"vshl.i32 		d6, d6, #23				\n\t"	//d6 = d6 << 23		
	"vadd.i32 		d0, d2, d6				\n\t"	//d0 = d2 + d6		


	:: "r"(__powf_rng), "r"(__powf_lut) 
    : "d0", "d1", "d2","d3", "d4", "d5", "d6", "d7"
	);
  }

  float pow10(int p)
  {
	return pow(10,p);
  }

  float sqrt(float x)
  {
	asm volatile(
	"vsqrt.f32		s0,s0				\n\t"
	:::
	);
/*
	asm volatile (
		
	//fast invsqrt approx
	"vmov.f32 		d1, d0					\n\t"	//d1 = d0
	"vrsqrte.f32 	d0, d0					\n\t"	//d0 = ~ 1.0 / sqrt(d0)
	"vmul.f32 		d2, d0, d1				\n\t"	//d2 = d0 * d1
	"vrsqrts.f32 	d3, d2, d0				\n\t"	//d3 = (3 - d0 * d2) / 2 	
	"vmul.f32 		d0, d0, d3				\n\t"	//d0 = d0 * d3
	"vmul.f32 		d2, d0, d1				\n\t"	//d2 = d0 * d1	
	"vrsqrts.f32 	d3, d2, d0				\n\t"	//d4 = (3 - d0 * d3) / 2	
	"vmul.f32 		d0, d0, d3				\n\t"	//d0 = d0 * d3	
		
	//fast reciporical approximation
	"vrecpe.f32		d1, d0					\n\t"	//d1 = ~ 1 / d0; 
	"vrecps.f32		d2, d1, d0				\n\t"	//d2 = 2.0 - d1 * d0; 
	"vmul.f32		d1, d1, d2				\n\t"	//d1 = d1 * d2; 
	"vrecps.f32		d2, d1, d0				\n\t"	//d2 = 2.0 - d1 * d0; 
	"vmul.f32		d0, d1, d2				\n\t"	//d0 = d1 * d2; 

	::: "d0", "d1", "d2", "d3"
	);
*/
  }

  float acos(float x)
  {
	asin(x);
	asm volatile (
	"vdup.f32	 	d1, %0					\n\t"	//d1 = {pi/2, pi/2};
	"vsub.f32	 	d0, d1, d0				\n\t"	//d0 = d1 - d0;
	::"r"(__acosf_pi_2):
	);
  }

  float asin(float x)
  {
	asm volatile (

	"vdup.f32	 	d0, d0[0]				\n\t"	//d0 = {x, x};
	"vdup.f32	 	d4, %1					\n\t"	//d4 = {pi/2, pi/2};
	"vmov.f32	 	d6, d0					\n\t"	//d6 = d0;
	"vabs.f32	 	d0, d0					\n\t"	//d0 = fabs(d0) ;

	"vmov.f32	 	d5, #0.5				\n\t"	//d5 = 0.5;
	"vmls.f32	 	d5, d0, d5				\n\t"	//d5 = d5 - d0*d5;

	//fast invsqrt approx
	"vmov.f32 		d1, d5					\n\t"	//d1 = d5
	"vrsqrte.f32 	d5, d5					\n\t"	//d5 = ~ 1.0 / sqrt(d5)
	"vmul.f32 		d2, d5, d1				\n\t"	//d2 = d5 * d1
	"vrsqrts.f32 	d3, d2, d5				\n\t"	//d3 = (3 - d5 * d2) / 2 	
	"vmul.f32 		d5, d5, d3				\n\t"	//d5 = d5 * d3
	"vmul.f32 		d2, d5, d1				\n\t"	//d2 = d5 * d1	
	"vrsqrts.f32 	d3, d2, d5				\n\t"	//d3 = (3 - d5 * d3) / 2	
	"vmul.f32 		d5, d5, d3				\n\t"	//d5 = d5 * d3	
		
	//fast reciporical approximation
	"vrecpe.f32		d1, d5					\n\t"	//d1 = ~ 1 / d5; 
	"vrecps.f32		d2, d1, d5				\n\t"	//d2 = 2.0 - d1 * d5; 
	"vmul.f32		d1, d1, d2				\n\t"	//d1 = d1 * d2; 
	"vrecps.f32		d2, d1, d5				\n\t"	//d2 = 2.0 - d1 * d5; 
	"vmul.f32		d5, d1, d2				\n\t"	//d5 = d1 * d2; 
	
	//if |x| > 0.5 -> ax = sqrt((1-ax)/2), r = pi/2
	"vsub.f32		d5, d0, d5				\n\t"	//d5 = d0 - d5; 
	"vmov.f32	 	d2, #0.5				\n\t"	//d2 = 0.5;
	"vcgt.f32	 	d3, d0, d2				\n\t"	//d3 = (d0 > d2);
	"vmov.f32		d1, #3.0 				\n\t"	//d5 = 3.0; 	
	"vshr.u32	 	d3, #31					\n\t"	//d3 = d3 >> 31;
	"vmov.f32		d16, #1.0 				\n\t"	//d16 = 1.0; 	
	"vcvt.f32.u32	d3, d3					\n\t"	//d3 = (float) d3;	
	"vmls.f32		d0, d5, d3[0]			\n\t"	//d0 = d0 - d5 * d3[0]; 	
	"vmul.f32		d7, d4, d3[0] 			\n\t"	//d7 = d5 * d4; 		
	"vmls.f32		d16, d1, d3[0] 			\n\t"	//d16 = d16 - d1 * d3; 	
		
	//polynomial:
	"vmul.f32 		d2, d0, d0				\n\t"	//d2 = d0*d0 = {ax^2, ax^2}	
	"vld1.32 		{d4, d5}, [%0]			\n\t"	//d4 = {p7, p3}, d5 = {p5, p1}
	"vmul.f32 		d3, d2, d2				\n\t"	//d3 = d2*d2 = {x^4, x^4}		
	"vmul.f32 		q0, q2, d0[0]			\n\t"	//q0 = q2 * d0[0] = {p7x, p3x, p5x, p1x}
	"vmla.f32 		d1, d0, d2[0]			\n\t"	//d1 = d1 + d0*d2[0] = {p5x + p7x^3, p1x + p3x^3}		
	"vmla.f32 		d1, d3, d1[0]			\n\t"	//d1 = d1 + d3*d1[0] = {..., p1x + p3x^3 + p5x^5 + p7x^7}		

	"vmla.f32 		d7, d1, d16				\n\t"	//d7 = d7 + d1*d16		

	"vadd.f32 		d2, d7, d7				\n\t"	//d2 = d7 + d7		
	"vclt.f32	 	d3, d6, #0				\n\t"	//d3 = (d6 < 0)	
	"vshr.u32	 	d3, #31					\n\t"	//d3 = d3 >> 31;
	"vcvt.f32.u32	d3, d3					\n\t"	//d3 = (float) d3	
	"vmls.f32 		d7, d2, d3[0]			\n\t"	//d7 = d7 - d2 * d3[0];

	"vmov.f32 		s0, s15					\n\t"	//s0 = s3

	:: "r"(__asinf_lut),  "r"(__asinf_pi_2) 
    : "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7"
	);
  }

  float atan(float x)
  {
	asm volatile (

	"vdup.f32	 	d0, d0[0]				\n\t"	//d0 = {x, x};

	"vdup.f32	 	d4, %1					\n\t"	//d4 = {pi/2, pi/2};
	"vmov.f32	 	d6, d0					\n\t"	//d6 = d0;
	"vabs.f32	 	d0, d0					\n\t"	//d0 = fabs(d0) ;

	//fast reciporical approximation
	"vrecpe.f32		d1, d0					\n\t"	//d1 = ~ 1 / d0; 
	"vrecps.f32		d2, d1, d0				\n\t"	//d2 = 2.0 - d1 * d0; 
	"vmul.f32		d1, d1, d2				\n\t"	//d1 = d1 * d2; 
	"vrecps.f32		d2, d1, d0				\n\t"	//d2 = 2.0 - d1 * d0; 
	"vmul.f32		d1, d1, d2				\n\t"	//d1 = d1 * d2; 

		
	//if |x| > 1.0 -> ax = -1/ax, r = pi/2
	"vadd.f32		d1, d1, d0				\n\t"	//d1 = d1 + d0; 
	"vmov.f32	 	d2, #1.0				\n\t"	//d2 = 1.0;
	"vcgt.f32	 	d3, d0, d2				\n\t"	//d3 = (d0 > d2);
	"vshr.u32	 	d3, #31					\n\t"	//d3 = (d0 > d2);
	"vcvt.f32.u32	d3, d3					\n\t"	//d5 = (float) d3;	
	"vmls.f32		d0, d1, d3[0]			\n\t"	//d0 = d0 - d1 * d3[0]; 	
	"vmul.f32		d7, d4, d3[0] 			\n\t"	//d7 = d5 * d4; 	
	
	//polynomial:
	"vmul.f32 		d2, d0, d0				\n\t"	//d2 = d0*d0 = {ax^2, ax^2}	
	"vld1.32 		{d4, d5}, [%0]			\n\t"	//d4 = {p7, p3}, d5 = {p5, p1}
	"vmul.f32 		d3, d2, d2				\n\t"	//d3 = d2*d2 = {x^4, x^4}		
	"vmul.f32 		q0, q2, d0[0]			\n\t"	//q0 = q2 * d0[0] = {p7x, p3x, p5x, p1x}
	"vmla.f32 		d1, d0, d2[0]			\n\t"	//d1 = d1 + d0*d2[0] = {p5x + p7x^3, p1x + p3x^3}		
	"vmla.f32 		d1, d3, d1[0]			\n\t"	//d1 = d1 + d3*d1[0] = {..., p1x + p3x^3 + p5x^5 + p7x^7}		
	"vadd.f32 		d1, d1, d7				\n\t"	//d1 = d1 + d7		

	"vadd.f32 		d2, d1, d1				\n\t"	//d2 = d1 + d1		
	"vclt.f32	 	d3, d6, #0				\n\t"	//d3 = (d6 < 0)	
	"vshr.u32	 	d3, #31					\n\t"	//d3 = (d0 > d2);
	"vcvt.f32.u32	d3, d3					\n\t"	//d3 = (float) d3	
	"vmls.f32 		d1, d3, d2				\n\t"	//d1 = d1 - d2 * d3;

	"vmov.f32 		s0, s3					\n\t"	//s0 = s3

	:: "r"(__atanf_lut),  "r"(__atanf_pi_2) 
    : "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7"
	);
  }

  float atan2(float y, float x)
  {
	asm volatile (

	"vdup.f32	 	d17, d0[1]				\n\t"	//d17 = {x, x};
	"vdup.f32	 	d16, d0[0]				\n\t"	//d16 = {y, y};
	
	//1.0 / x
	"vrecpe.f32		d18, d17				\n\t"	//d16 = ~ 1 / d1; 
	"vrecps.f32		d19, d18, d17			\n\t"	//d17 = 2.0 - d16 * d1; 
	"vmul.f32		d18, d18, d19			\n\t"	//d16 = d16 * d17; 
	"vrecps.f32		d19, d18, d17			\n\t"	//d17 = 2.0 - d16 * d1; 
	"vmul.f32		d18, d18, d19			\n\t"	//d16 = d16 * d17; 

	//y * (1.0 /x)
	"vmul.f32		d0, d16, d18			\n\t"	//d0 = d16 * d18; 


	"vdup.f32	 	d4, %1					\n\t"	//d4 = {pi/2, pi/2};
	"vmov.f32	 	d6, d0					\n\t"	//d6 = d0;
	"vabs.f32	 	d0, d0					\n\t"	//d0 = fabs(d0) ;

	//fast reciporical approximation
	"vrecpe.f32		d1, d0					\n\t"	//d1 = ~ 1 / d0; 
	"vrecps.f32		d2, d1, d0				\n\t"	//d2 = 2.0 - d1 * d0; 
	"vmul.f32		d1, d1, d2				\n\t"	//d1 = d1 * d2; 
	"vrecps.f32		d2, d1, d0				\n\t"	//d2 = 2.0 - d1 * d0; 
	"vmul.f32		d1, d1, d2				\n\t"	//d1 = d1 * d2; 

	//if |x| > 1.0 -> ax = 1/ax, r = pi/2
	"vadd.f32		d1, d1, d0				\n\t"	//d1 = d1 + d0; 
	"vmov.f32	 	d2, #1.0				\n\t"	//d2 = 1.0;
	"vcgt.f32	 	d3, d0, d2				\n\t"	//d3 = (d0 > d2);
	"vcvt.f32.u32	d3, d3					\n\t"	//d3 = (float) d3;
	"vmls.f32		d0, d1, d3				\n\t"	//d0 = d0 - d1 * d3; 	
	"vmul.f32		d7, d3, d4				\n\t"	//d7 = d3 * d4; 	
		
	//polynomial:
	"vmul.f32 		d2, d0, d0				\n\t"	//d2 = d0*d0 = {ax^2, ax^2}	
	"vld1.32 		{d4, d5}, [%0]			\n\t"	//d4 = {p7, p3}, d5 = {p5, p1}
	"vmul.f32 		d3, d2, d2				\n\t"	//d3 = d2*d2 = {x^4, x^4}		
	"vmul.f32 		q0, q2, d0[0]			\n\t"	//q0 = q2 * d0[0] = {p7x, p3x, p5x, p1x}
	"vmla.f32 		d1, d0, d2[0]			\n\t"	//d1 = d1 + d0*d2[0] = {p5x + p7x^3, p1x + p3x^3}		
	"vmla.f32 		d1, d3, d1[0]			\n\t"	//d1 = d1 + d3*d1[0] = {..., p1x + p3x^3 + p5x^5 + p7x^7}		
	"vadd.f32 		d1, d1, d7				\n\t"	//d1 = d1 + d7		
	
	"vadd.f32 		d2, d1, d1				\n\t"	//d2 = d1 + d1		
	"vclt.f32	 	d3, d6, #0				\n\t"	//d3 = (d6 < 0)	
	"vcvt.f32.u32	d3, d3					\n\t"	//d3 = (float) d3	
	"vmls.f32 		d1, d3, d2				\n\t"	//d1 = d1 - d2 * d3;

	"vmov.f32 		s0, s3					\n\t"	//s0 = s3

	:: "r"(__atan2f_lut),  "r"(__atan2f_pi_2) 
    : "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7"
	);
  }

  float cos(float x)
  {
	float xx = x+M_PI_2;
	return sin(xx);
  }

  float sin(float x)
  {
	asm volatile (
	
	"vld1.32 		d3, [%0]				\n\t"	//d3 = {invrange, range}
	"vdup.f32 		d0, d0[0]				\n\t"	//d0 = {x, x}
	"vabs.f32 		d1, d0					\n\t"	//d1 = {ax, ax}
	
	"vmul.f32 		d2, d1, d3[0]			\n\t"	//d2 = d1 * d3[0] 
	"vcvt.u32.f32 	d2, d2					\n\t"	//d2 = (int) d2
	"vmov.i32	 	d5, #1					\n\t"	//d5 = 1	
	"vcvt.f32.u32 	d4, d2					\n\t"	//d4 = (float) d2	
	"vshr.u32 		d7, d2, #1				\n\t"	//d7 = d2 >> 1
	"vmls.f32 		d1, d4, d3[1]			\n\t"	//d1 = d1 - d4 * d3[1]
	
	"vand.i32 		d5, d2, d5				\n\t"	//d5 = d2 & d5
	"vclt.f32 		d18, d0, #0				\n\t"	//d18 = (d0 < 0.0)
	"vcvt.f32.u32 	d6, d5					\n\t"	//d6 = (float) d5
	"vmls.f32 		d1, d6, d3[1]			\n\t"	//d1 = d1 - d6 * d3[1]
	"veor.i32 		d5, d5, d7				\n\t"	//d5 = d5 ^ d7	
	"vmul.f32 		d2, d1, d1				\n\t"	//d2 = d1*d1 = {x^2, x^2}	
	
	"vld1.32 		{d16, d17}, [%1]		\n\t"	//q8 = {p7, p3, p5, p1}
	"veor.i32 		d5, d5, d18				\n\t"	//d5 = d5 ^ d18	
	"vshl.i32 		d5, d5, #31				\n\t"	//d5 = d5 << 31
	"veor.i32 		d1, d1, d5				\n\t"	//d1 = d1 ^ d5
	
	"vmul.f32 		d3, d2, d2				\n\t"	//d3 = d2*d2 = {x^4, x^4}		
	"vmul.f32 		q0, q8, d1[0]			\n\t"	//q0 = q8 * d1[0] = {p7x, p3x, p5x, p1x}
	"vmla.f32 		d1, d0, d2[0]			\n\t"	//d1 = d1 + d0*d2 = {p5x + p7x^3, p1x + p3x^3}		
	"vmla.f32 		d1, d3, d1[0]			\n\t"	//d1 = d1 + d3*d0 = {...., p1x + p3x^3 + p5x^5 + p7x^7}		

	"vmov.f32 		s0, s3					\n\t"	//s0 = s3
	: 
	: "r"(__sinf_rng), "r"(__sinf_lut) 
    : "q0", "q1", "q2", "q3", "q8", "q9"
	);
  }

  float tan(float x)
  {
	asm volatile (

	"vdup.f32 		d0, d0[0]				\n\t"	//d0 = {x, x}
	"vabs.f32 		d1, d0					\n\t"	//d1 = {ax, ax}
	
	//Range Reduction:
	"vld1.32 		d3, [%0]				\n\t"	//d3 = {invrange, range}
	"vmul.f32 		d2, d1, d3[0]			\n\t"	//d2 = d1 * d3[0] 
	"vcvt.u32.f32 	d2, d2					\n\t"	//d2 = (int) d2
	"vcvt.f32.u32 	d4, d2					\n\t"	//d4 = (float) d2
	"vmls.f32 		d1, d4, d3[1]			\n\t"	//d1 = d1 - d4 * d3[1]
	
	//Checking Quadrant:
	//ax = ax - (k&1) * M_PI_2
	"vmov.i32 		d4, #1					\n\t"	//d4 = 1
	"vand.i32 		d2, d2, d4				\n\t"	//d2 = d2 & d4
	"vcvt.f32.u32 	d2, d2					\n\t"	//d2 = (float) d2
	"vmls.f32 		d1, d2, d3[1]			\n\t"	//d1 = d1 - d2 * d3[1]
	
	//ax = ax ^ ( x.i & 0x800000000)
	"vmov.i32 		d4, #0x80000000			\n\t"	//d4 = 0x80000000
	"vand.i32 		d0, d0, d4				\n\t"	//d0 = d0 & d4
	"veor.i32 		d1, d1, d0				\n\t"	//d1 = d1 ^ d0
	
	//polynomial:
	"vmul.f32 		d2, d1, d1				\n\t"	//d2 = d1*d1 = {x^2, x^2}	
	"vld1.32 		{d4, d5}, [%1]			\n\t"	//d4 = {p7, p3}, d5 = {p5, p1}
	"vmul.f32 		d3, d2, d2				\n\t"	//d3 = d2*d2 = {x^4, x^4}		
	"vmul.f32 		q0, q2, d1[0]			\n\t"	//q0 = q2 * d1[0] = {p7x, p3x, p5x, p1x}
	"vmla.f32 		d1, d0, d2[0]			\n\t"	//d1 = d1 + d0*d2 = {p5x + p7x^3, p1x + p3x^3}		
	"vmla.f32 		d1, d3, d1[0]			\n\t"	//d1 = d1 + d3*d0 = {..., p1x + p3x^3 + p5x^5 + p7x^7}		
	
	//cosine
	"vmov.f32 		s1, #1.0				\n\t"	//d0[1] = 1.0
	"vmls.f32 		d0, d1, d1				\n\t"	//d0 = {..., 1.0 - sx*sx}
	
	//invsqrt approx
	"vmov.f32 		d2, d0					\n\t"	//d2 = d0
	"vrsqrte.f32 	d0, d0					\n\t"	//d0 = ~ 1.0 / sqrt(d0)
	"vmul.f32 		d3, d0, d2				\n\t"	//d3 = d0 * d2
	"vrsqrts.f32 	d4, d3, d0				\n\t"	//d4 = (3 - d0 * d3) / 2 	
	"vmul.f32 		d0, d0, d4				\n\t"	//d0 = d0 * d4	
	"vmul.f32 		d3, d0, d2				\n\t"	//d3 = d0 * d2	
	"vrsqrts.f32 	d4, d3, d0				\n\t"	//d4 = (3 - d0 * d3) / 2	
	"vmul.f32 		d0, d0, d4				\n\t"	//d0 = d0 * d4	
	
	"vmul.f32 		d0, d0, d1				\n\t"	//d0 = d0 * d1
	
	"vmov.f32 		s0, s1					\n\t"	//s0 = s1
	
	:: "r"(__tanf_rng), "r"(__tanf_lut) 
    : "d0", "d1", "d2", "d3", "d4", "d5"
	);
  }

  float cosh(float x)
  {
	asm volatile (
	"vdup.f32 		d0, d0[0]				\n\t"	//d0 = {x, x}	
	"fnegs 			s1, s1					\n\t"	//s1 = -s1
	
	//Range Reduction:
	"vld1.32 		d2, [%0]				\n\t"	//d2 = {invrange, range}
	"vld1.32 		{d16, d17}, [%1]!		\n\t"	
	"vmul.f32 		d6, d0, d2[0]			\n\t"	//d6 = d0 * d2[0] 
	"vcvt.s32.f32 	d6, d6					\n\t"	//d6 = (int) d6
	"vld1.32 		{d18}, [%1]!			\n\t"	
	"vcvt.f32.s32 	d1, d6					\n\t"	//d1 = (float) d6
	"vld1.32 		{d19}, [%1]!			\n\t"	
	"vmls.f32 		d0, d1, d2[1]			\n\t"	//d0 = d0 - d1 * d2[1]
	"vld1.32 		{d20}, [%1]!			\n\t"	
		
	//polynomial:
	"vmla.f32 		d17, d16, d0			\n\t"	//d17 = d17 + d16 * d0;	
	"vld1.32 		{d21}, [%1]!			\n\t"	
	"vmla.f32 		d18, d17, d0			\n\t"	//d18 = d18 + d17 * d0;	
	"vld1.32 		{d22}, [%1]!			\n\t"	
	"vmla.f32 		d19, d18, d0			\n\t"	//d19 = d19 + d18 * d0;	
	"vld1.32 		{d23}, [%1]!			\n\t"	
	"vmla.f32 		d20, d19, d0			\n\t"	//d20 = d20 + d19 * d0;	
	"vmla.f32 		d21, d20, d0			\n\t"	//d21 = d21 + d20 * d0;	
	"vmla.f32 		d22, d21, d0			\n\t"	//d22 = d22 + d21 * d0;	
	"vmla.f32 		d23, d22, d0			\n\t"	//d23 = d23 + d22 * d0;	
	
	//multiply by 2 ^ m 	
	"vshl.i32 		d6, d6, #23				\n\t"	//d6 = d6 << 23		
	"vadd.i32 		d0, d23, d6				\n\t"	//d0 = d22 + d6		

	"vdup.f32 		d2, d0[1]				\n\t"	//d2 = s1		
	"vmov.f32 		d1, #0.5				\n\t"	//d1 = 0.5		
	"vadd.f32 		d0, d0, d2				\n\t"	//d0 = d0 + d2		
	"vmul.f32 		d0, d1					\n\t"	//d0 = d0 * d1		

	:: "r"(__coshf_rng), "r"(__coshf_lut) 
    : "d0", "d1", "q1", "q2", "d6"
	);
  }

  float sinh(float x)
  {
	asm volatile (
	"vdup.f32 		d0, d0[0]				\n\t"	//d0 = {x, x}	
	"fnegs 			s1, s1					\n\t"	//s1 = -s1
	
	//Range Reduction:
	"vld1.32 		d2, [%0]				\n\t"	//d2 = {invrange, range}
	"vld1.32 		{d16, d17}, [%1]!		\n\t"	
	"vmul.f32 		d6, d0, d2[0]			\n\t"	//d6 = d0 * d2[0] 
	"vcvt.s32.f32 	d6, d6					\n\t"	//d6 = (int) d6
	"vld1.32 		{d18}, [%1]!			\n\t"	
	"vcvt.f32.s32 	d1, d6					\n\t"	//d1 = (float) d6
	"vld1.32 		{d19}, [%1]!			\n\t"	
	"vmls.f32 		d0, d1, d2[1]			\n\t"	//d0 = d0 - d1 * d2[1]
	"vld1.32 		{d20}, [%1]!			\n\t"	
		
	//polynomial:
	"vmla.f32 		d17, d16, d0			\n\t"	//d17 = d17 + d16 * d0;	
	"vld1.32 		{d21}, [%1]!			\n\t"	
	"vmla.f32 		d18, d17, d0			\n\t"	//d18 = d18 + d17 * d0;	
	"vld1.32 		{d22}, [%1]!			\n\t"	
	"vmla.f32 		d19, d18, d0			\n\t"	//d19 = d19 + d18 * d0;	
	"vld1.32 		{d23}, [%1]!			\n\t"	
	"vmla.f32 		d20, d19, d0			\n\t"	//d20 = d20 + d19 * d0;	
	"vmla.f32 		d21, d20, d0			\n\t"	//d21 = d21 + d20 * d0;	
	"vmla.f32 		d22, d21, d0			\n\t"	//d22 = d22 + d21 * d0;	
	"vmla.f32 		d23, d22, d0			\n\t"	//d23 = d23 + d22 * d0;	
	
	//multiply by 2 ^ m 	
	"vshl.i32 		d6, d6, #23				\n\t"	//d6 = d6 << 23		
	"vadd.i32 		d0, d23, d6				\n\t"	//d0 = d22 + d6		

	"vdup.f32 		d2, d0[1]				\n\t"	//d2 = s1		
	"vmov.f32 		d1, #0.5				\n\t"	//d1 = 0.5		
	"vsub.f32 		d0, d0, d2				\n\t"	//d0 = d0 - d2		
	"vmul.f32 		d0, d1					\n\t"	//d0 = d0 * d1		

	:: "r"(__sinhf_rng), "r"(__sinhf_lut) 
    : "d0", "d1", "q1", "q2", "d6"
	);
  }

  float tanh(float x)
  {
	asm volatile ("vadd.f32 d0, d0, d0 		\n\t");
	exp(x);
	asm volatile (
	"vmov.f32 		d2, #1.0 				\n\t"
	"vsub.f32 		d3, d0, d2 				\n\t"
	"vadd.f32 		d0, d0, d2 				\n\t"

	"vrecpe.f32		d1, d0					\n\t"	//d1 = ~ 1 / d0; 
	"vrecps.f32		d2, d1, d0				\n\t"	//d2 = 2.0 - d1 * d0; 
	"vmul.f32		d1, d1, d2				\n\t"	//d1 = d1 * d2; 
	"vrecps.f32		d2, d1, d0				\n\t"	//d2 = 2.0 - d1 * d0; 
	"vmul.f32		d0, d1, d2				\n\t"	//d0 = d1 * d2; 
	"vmul.f32		d0, d0, d3				\n\t"	//d0 = d0 * d3; 	
	::: "d0", "d1", "d2", "d3"
	);
  }

  float hypot(float x, float y)
  {
	float z;
	asm volatile(
	"vmul.f32		d0,d0,d0			\n\t"
	"vpadd.f32		d0,d0,d0			\n\t"

	//fast invsqrt approx
	"vmov.f32 		d1, d0					\n\t"	//d1 = d0
	"vrsqrte.f32 	d0, d0					\n\t"	//d0 = ~ 1.0 / sqrt(d0)
	"vmul.f32 		d2, d0, d1				\n\t"	//d2 = d0 * d1
	"vrsqrts.f32 	d3, d2, d0				\n\t"	//d3 = (3 - d0 * d2) / 2 	
	"vmul.f32 		d0, d0, d3				\n\t"	//d0 = d0 * d3
	"vmul.f32 		d2, d0, d1				\n\t"	//d2 = d0 * d1	
	"vrsqrts.f32 	d3, d2, d0				\n\t"	//d4 = (3 - d0 * d3) / 2	
	"vmul.f32 		d0, d0, d3				\n\t"	//d0 = d0 * d3	
		
	//fast reciporical approximation
	"vrecpe.f32		d1, d0					\n\t"	//d1 = ~ 1 / d0; 
	"vrecps.f32		d2, d1, d0				\n\t"	//d2 = 2.0 - d1 * d0; 
	"vmul.f32		d1, d1, d2				\n\t"	//d1 = d1 * d2; 
	"vrecps.f32		d2, d1, d0				\n\t"	//d2 = 2.0 - d1 * d0; 
	"vmul.f32		d0, d1, d2				\n\t"	//d0 = d1 * d2; 
	::: "d0", "d1", "d2", "d3"
	);
  }

  float fmod(float x, float y)
  {
	asm volatile(
	"vdiv.f32		s2,s0,s1			\n\t"
	"vcvt.s32.f32		s2,s2				\n\t"
	"vcvt.f32.s32		s2,s2				\n\t"
	"vmul.f32		s2,s2,s1			\n\t"
	"vsub.f32		s0,s0,s2			\n\t"
	);
/*
	asm volatile (	
	"vcvt.s32.f32	d1, d0					\n\t"	//d1 = (int) d0; 
	"vcvt.f32.s32	d2, d1					\n\t"	//d2 = (float) d1;
	"vsub.f32		d0, d0, d2				\n\t"	//d0 = d0 - d2; 
	"vstr.i32		s2, [r0]				\n\t"	//[r0] = d1[0] 
	::: "d0", "d1", "d2"
	);
*/	
  }

}  // namespace math
}  // namespace sgbot

#endif  // _USE_ARM_NEON_
