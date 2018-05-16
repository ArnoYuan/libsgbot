/* Created linear-algebra/vectorbase-neon.cpp by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifdef _USE_ARM_NEON_

#include <linear-algebra/vectorbase.h>
#include <std-math/math.h>
#include <stdio.h>

//#define USE_DBG

#ifdef USE_DBG
#define DBG_PRINT(fmt,...)	printf(fmt,##__VA_ARGS__)
#else
#define DBG_PRINT(fmt, ...)
#endif


namespace sgbot {
namespace la {
  VectorBase VectorBase::operator -() const
  {
    VectorBase v(*this);
    for(int i = 0; i < size(); i++)
    {
      v(i) = -v(i);
    }
    return v;
  }

  VectorBase& VectorBase::operator *=(const float scalar)
  {
    VectorBase& v = *this;
    assert(v.size()==2||v.size()==3||v.size()==6);
    DBG_PRINT("[*=]v.size()==%d\n", v.size());
    if(v.size()==2)
    {
	asm volatile(
	"vld1.32	{d0},[%0]		\n\t"
	"vmov		s4,%1			\n\t"
	"vmul.f32	d1,d0,d2[0]		\n\t"
	"vst1.32	{d1},[%0]			\n\t"
	::"r"(&v.items_[0]),"r"(scalar)
	:"d0","d1","d2","memory"
	);
    }
    else if(v.size()==3)
    {	
	asm volatile(
	"vld1.32	{d0,d1},[%0]			\n\t"
	"vmov		s4,%1				\n\t"
	"vmul.f32	d0,d0,d2[0]			\n\t"
	"vmul.f32	d1,d1,d2[0]			\n\t"
	"vst1.32	{d0},[%0]!			\n\t"
	"fsts		s2,[%0]				\n\t"
	::"r"(&v.items_[0]),"r"(scalar)
	:"r0","d0","d1","d2","d3","d4","memory"
	);
    }
    else if(v.size()==6)
    {

	asm volatile(
	"vld3.f32	{d0,d1,d2},[%0]			\n\t"
	"vmov		s6,%1				\n\t"
	"vmul.f32	q0,q0,d3[0]			\n\t"
	"vmul.f32	d2,d2,d3[0]			\n\t"
	"vst3.f32	{d0,d1,d2},[%0]			\n\t"
	::"r"(&v.items_[0]),"r"(scalar)
	:"d0","d1","d2","d3","memory"
	);

    }

    return v;
  }


  VectorBase& VectorBase::operator /=(const float scalar)
  {
    VectorBase& v = *this;
    
    assert(v.size()==2||v.size()==3||v.size()==6);
    DBG_PRINT("[/=]v.size()==%d\n", v.size());
    if(v.size()==2)
    {
	
	asm volatile(
	"vld1.32	{d0},[%0]		\n\t"
	"vmov		s2,%1			\n\t"
	"vmul.f32	s3,s2,s2		\n\t"
	"vdiv.f32	s2,s2,s3		\n\t"
	"vmul.f32	d0,d0,d1[0]		\n\t"
	"vst1.32	{d0},[%0]			\n\t"
	::"r"(&v.items_[0]),"r"(scalar)
	:"d0","d1","d2","s6","memory"
	);
    }
    else if(v.size()==3)
    {
	
	asm volatile(
	"mov		r1,%0				\n\t"
	"vld1.f32	{d0},[r1]!			\n\t"
	"flds		s2,[r1]				\n\t"
	"vmov		s8,%1				\n\t"
	"vmul.f32	s10,s8,s8			\n\t"
	"vdiv.f32	s8,s8,s10			\n\t"
	"vmul.f32	d2,d0,d4[0]			\n\t"
	"vmul.f32	d3,d1,d4[0]			\n\t"
	"vst1.32	{d2},[%0]			\n\t"
	"fsts		s6,[%0,#8]			\n\t"
	::"r"(&v.items_[0]),"r"(scalar)
	:"r1","d0","d1","d2","d3","d4","s10","memory"
	);
    }
    else if(v.size()==6)
    {
	asm volatile(
	"vld3.f32	{d0,d1,d2},[%0]			\n\t"
	"vmov		s6,%1				\n\t"
	"vmul.f32	s8,s6,s6			\n\t"
	"vdiv.f32	s6,s6,s8			\n\t"
	"vmul.f32	q0,q0,d3[0]			\n\t"
	"vmul.f32	d2,d2,d3[0]			\n\t"
	"vst3.f32	{d0,d1,d2},[%0]			\n\t"
	::"r"(&v.items_[0]),"r"(scalar)
	:"d0","d1","d2","d3","memory"
	);

    }
    return v;
  }


 VectorBase VectorBase::operator *(const float scalar) const
  {
    VectorBase v(*this);
    assert(v.size()==2||v.size()==3||v.size()==6);
    DBG_PRINT("[*]v.size()==%d\n", v.size());
    if(v.size()==2)
    {
	asm volatile(
	"vld1.32	{d0},[%0]		\n\t"
	"vmov		s2,%1			\n\t"
	"vmul.f32	d0,d0,d1[0]		\n\t"
	"vst1.32	{d0},[%0]		\n\t"
	::"r"(&v.items_[0]),"r"(scalar)
	:"d0","d1","memory"
	);

    }
    else if(v.size()==3)
    {	
	asm volatile(
	"mov		r1,%0				\n\t"
	"vld1.32	{d0},[r1]!			\n\t"
	"flds		s2,[r1]				\n\t"
	"vmov		s8,%1				\n\t"
	"vmul.f32	d2,d0,d4[0]			\n\t"
	"vmul.f32	d3,d1,d4[0]			\n\t"
	"vst1.32	{d2},[%0]			\n\t"
	"fsts		s6,[%0,#8]			\n\t"
	::"r"(&v.items_[0]),"r"(scalar)
	:"r0","d0","d1","d2","d3","d4","memory"
	);
    }
    else if(v.size()==6)
    {

	asm volatile(
	"vld3.f32	{d0,d1,d2},[%0]			\n\t"
	"vmov		s6,%1				\n\t"
	"vmul.f32	q0,q0,d3[0]			\n\t"
	"vmul.f32	d2,d2,d3[0]			\n\t"
	"vst3.f32	{d0,d1,d2},[%0]			\n\t"
	::"r"(&v.items_[0]),"r"(scalar)
	:"d0","d1","d2","d3","memory"
	);

    }
    return v;
  }

  VectorBase VectorBase::operator /(const float scalar) const
  {
    VectorBase v(*this);
    assert(v.size()==2||v.size()==3||v.size()==6);
    DBG_PRINT("[/]v.size()==%d\n", v.size());
    if(v.size()==2)
    {
	
	asm volatile(
	"vld1.32	{d0},[%0]		\n\t"
	"vmov		s4,%1			\n\t"
	"vmul.f32	s6,s4,s4		\n\t"
	"vdiv.f32	s4,s4,s6		\n\t"
	"vmul.f32	d1,d0,d2[0]		\n\t"
	"vst1.32	{d1},[%0]			\n\t"
	::"r"(&v.items_[0]),"r"(scalar)
	:"d0","d1","d2","s6","memory"
	);
    }
    else if(v.size()==3)
    {
	
	asm volatile(
	"vld1.f32	{d0},[%0]			\n\t"
	"add		r0,%0,#8			\n\t"
	"flds		s2,[r0]				\n\t"
	"vmov		s8,%1				\n\t"
	"vmul.f32	s10,s8,s8			\n\t"
	"vdiv.f32	s8,s8,s10			\n\t"
	"vmul.f32	d2,d0,d4[0]			\n\t"
	"vmul.f32	d3,d1,d4[0]			\n\t"
	"vst1.32	{d2},[%0]			\n\t"
	"fsts		s6,[r0]				\n\t"
	::"r"(&v.items_[0]),"r"(scalar)
	:"r0","d0","d1","d2","d3","d4","s10","memory"
	);
    }
    else if(v.size()==6)
    {
	asm volatile(
	"vld3.f32	{d0,d1,d2},[%0]			\n\t"
	"vmov		s6,%1				\n\t"
	"vmul.f32	s8,s6,s6			\n\t"
	"vdiv.f32	s6,s6,s8			\n\t"
	"vmul.f32	q0,q0,d3[0]			\n\t"
	"vmul.f32	d2,d2,d3[0]			\n\t"
	"vst3.f32	{d0,d1,d2},[%0]			\n\t"
	::"r"(&v.items_[0]),"r"(scalar)
	:"d0","d1","d2","d3","memory"
	);

    }
    return v;
  }

  VectorBase& VectorBase::operator +=(const VectorBase& vector)
  {
    VectorBase& v = *this;
    assert(v.size() == vector.size());
    assert(v.size()==2||v.size()==3||v.size()==6);
    int i=0;
    DBG_PRINT("[+=vector]v.size()==%d\n", v.size());
    if(v.size()==2)
    {
	asm volatile(
	"vld1.32		{d0},[%0]			\n\t"
	"vld1.32		{d1},[%1]			\n\t"
	"vadd.f32		d2,d0,d1			\n\t"
	"vst1.f32		{d2},[%0]			\n\t"
	::"r"(&v.items_[0]),"r"(&vector.items_[0])
	:"d0","d1","d2","memory"
        );

    }
    else if(v.size()==3)
    {
	asm volatile(
	"vld1.32		{d0},[%0]			\n\t"
	"flds			s2,[%0,#8]			\n\t"
	"vld1.32		{d2},[%1]			\n\t"
	"flds			s6,[%1,#8]			\n\t"
	"vadd.f32		d4,d0,d2			\n\t"
	"vadd.f32		d5,d1,d3			\n\t"
	"vst1.f32		{d4},[%0]			\n\t"
	"fsts			s10,[%0,#8]			\n\t"
	::"r"(&v.items_[0]),"r"(&vector.items_[0])
	:"d0","d1","d2","d3","d4","d5","memory"
        );

    }
    else if(v.size()==6)
    {
	asm volatile(
	"vld1.32		{d0,d1,d2},[%0]			\n\t"
	"vld1.32		{d4,d5,d6},[%1]			\n\t"
	"vadd.f32		q0,q0,q2			\n\t"
	"vadd.f32		d2,d2,d6			\n\t"
	"vst1.f32		{d0,d1,d2},[%0]			\n\t"
	::"r"(&v.items_[0]),"r"(&vector.items_[0])
	:"d0","d1","d2","d3","d4","d5","d6","memory"
        );

    }


    return v;
  }

  VectorBase& VectorBase::operator -=(const VectorBase& vector)
  {
    VectorBase& v = *this;
    assert(v.size() == vector.size());
    assert(v.size()==2||v.size()==3||v.size()==6);
    int i=0;
    DBG_PRINT("[-=vector]v.size()==%d\n", v.size());
    if(v.size()==2)
    {
	asm volatile(
	"vld1.32		{d0},[%0]			\n\t"
	"vld1.32		{d1},[%1]			\n\t"
	"vsub.f32		d2,d0,d1			\n\t"
	"vst1.f32		{d2},[%0]			\n\t"
	::"r"(&v.items_[0]),"r"(&vector.items_[0])
	:"d0","d1","d2","memory"
        );
    }
    else if(v.size()==3)
    {
	asm volatile(
	"vld1.32		{d0},[%0]			\n\t"
	"flds			s2,[%0,#8]			\n\t"
	"vld1.32		{d2},[%1]			\n\t"
	"flds			s6,[%1,#8]			\n\t"
	"vsub.f32		d4,d0,d2			\n\t"
	"vsub.f32		d5,d1,d3			\n\t"
	"vst1.f32		{d4},[%0]			\n\t"
	"fsts			s10,[%0,#8]			\n\t"
	::"r"(&v.items_[0]),"r"(&vector.items_[0])
	:"d0","d1","d2","d3","d4","d5","memory"
        );

    }
    else if(v.size()==6)
    {
	asm volatile(
	"vld1.32		{d0,d1,d2},[%0]			\n\t"
	"vld1.32		{d4,d5,d6},[%1]			\n\t"
	"vsub.f32		q0,q0,q2			\n\t"
	"vsub.f32		d2,d2,d6			\n\t"
	"vst1.f32		{d0,d1,d2},[%0]			\n\t"
	::"r"(&v.items_[0]),"r"(&vector.items_[0])
	:"d0","d1","d2","d3","d4","d5","d6","memory"
        );

    }

    return v;
  }

  VectorBase VectorBase::operator +(const VectorBase& vector) const
  {
    VectorBase v(*this);
    assert(v.size() == vector.size());
    assert(v.size()==2||v.size()==3||v.size()==6);
    int i=0;
    DBG_PRINT("[+vector]v.size()==%d\n", v.size());
    if(v.size()==2)
    {
	asm volatile(
	"vld1.32		{d0},[%0]			\n\t"
	"vld1.32		{d1},[%1]			\n\t"
	"vadd.f32		d2,d0,d1			\n\t"
	"vst1.f32		{d2},[%0]			\n\t"
	::"r"(&v.items_[0]),"r"(&vector.items_[0])
	:"d0","d1","d2","memory"
        );
    }
    else if(v.size()==3)
    {
	asm volatile(
	"vld1.32		{d0},[%0]			\n\t"
	"flds			s2,[%0,#8]			\n\t"
	"vld1.32		{d2},[%1]			\n\t"
	"flds			s6,[%1,#8]			\n\t"
	"vadd.f32		d4,d0,d2			\n\t"
	"vadd.f32		d5,d1,d3			\n\t"
	"vst1.f32		{d4},[%0]			\n\t"
	"fsts			s10,[%0,#8]			\n\t"
	::"r"(&v.items_[0]),"r"(&vector.items_[0])
	:"d0","d1","d2","d3","d4","d5","memory"
        );

    }
    else if(v.size()==6)
    {
	asm volatile(
	"vld1.32		{d0,d1,d2},[%0]			\n\t"
	"vld1.32		{d4,d5,d6},[%1]			\n\t"
	"vadd.f32		q0,q0,q2			\n\t"
	"vadd.f32		d2,d2,d6			\n\t"
	"vst1.f32		{d0,d1,d2},[%0]			\n\t"
	::"r"(&v.items_[0]),"r"(&vector.items_[0])
	:"d0","d1","d2","d3","d4","d5","d6","memory"
        );

    }


    return v;
  }

  VectorBase VectorBase::operator -(const VectorBase& vector) const
  {
    VectorBase v(*this);
    assert(v.size() == vector.size());
    assert(v.size()==2||v.size()==3||v.size()==6);
    int i=0;
    DBG_PRINT("[-vector]v.size()==%d\n", v.size());
    if(v.size()==2)
    {
	asm volatile(
	"vld1.32		{d0},[%0]			\n\t"
	"vld1.32		{d1},[%1]			\n\t"
	"vsub.f32		d2,d0,d1			\n\t"
	"vst1.f32		{d2},[%0]			\n\t"
	::"r"(&v.items_[0]),"r"(&vector.items_[0])
	:"d0","d1","d2","memory"
        );

    }
    else if(v.size()==3)
    {

	asm volatile(
	"vld1.32		{d0},[%0]			\n\t"
	"flds			s2,[%0,#8]			\n\t"
	"vld1.32		{d2},[%1]			\n\t"
	"flds			s6,[%1,#8]			\n\t"
	"vsub.f32		d4,d0,d2			\n\t"
	"vsub.f32		d5,d1,d3			\n\t"
	"vst1.f32		{d4},[%0]			\n\t"
	"fsts			s10,[%0,#8]			\n\t"
	::"r"(&v.items_[0]),"r"(&vector.items_[0])
	:"d0","d1","d2","d3","d4","d5","memory"
        );

    }
    else if(v.size()==6)
    {
	asm volatile(
	"vld1.32		{d0,d1,d2},[%0]			\n\t"
	"vld1.32		{d4,d5,d6},[%1]			\n\t"
	"vsub.f32		q0,q0,q2			\n\t"
	"vsub.f32		d2,d2,d6			\n\t"
	"vst1.f32		{d0,d1,d2},[%0]			\n\t"
	::"r"(&v.items_[0]),"r"(&vector.items_[0])
	:"d0","d1","d2","d3","d4","d5","d6","memory"
        );
    }

    return v;
  }

  bool VectorBase::operator ==(const VectorBase& vector) const
  {
    if(this->size() != vector.size())
    {
      return false;
    }
    DBG_PRINT("[==vector]v.size()==%d\n", vector.size());
    for(int i = 0; i < size(); i++)
    {
      if(items_[i] != vector(i))
      {
        return false;
      }
    }

    return true;
  }

  float VectorBase::length() const
  {
    return sgbot::math::sqrt(dot(*this));
  }

  void VectorBase::normalize()
  {

    VectorBase& v = *this;
    DBG_PRINT("v.size=%d\n", v.size());
    assert(v.size()==2||v.size()==3||v.size()==6);
    int i=0;
    DBG_PRINT("[normalize]v.size()==%d\n", v.size());

    if(v.size()==2)
    {
	asm volatile(
	"vld1.32		{d4},[%0]				\n\t"
	"vmul.f32		d0,d4,d4				\n\t"
	"vpadd.f32		d1,d0,d0				\n\t"
	
	"vsqrt.f32		s0,s2					\n\t"
	"vdiv.f32		s0,s0,s2				\n\t"
	"vmul.f32		d4,d4,d0[0]				\n\t"
	"vst1.32		{d4},[%0]				\n\t"
	::"r"(&v.items_[0])
	:"d0","d1","d4","memory"
	);
/*
	asm volatile (
	"vld1.32 		{d4}, [%0]				\n\t"	//d4 = {x0,y0}
	"vmul.f32 		d0, d4, d4				\n\t"	//d0 = d2*d2
	"vpadd.f32 		d0, d0					\n\t"	//d0 = d[0] + d[1]
	
	"vmov.f32 		d1, d0					\n\t"	//d1 = d0
	"vrsqrte.f32 	d0, d0					\n\t"	//d0 = ~ 1.0 / sqrt(d0)
	"vmul.f32 		d2, d0, d1				\n\t"	//d2 = d0 * d1
	"vrsqrts.f32 	d3, d2, d0				\n\t"	//d3 = (3 - d0 * d2) / 2 	
	"vmul.f32 		d0, d0, d3				\n\t"	//d0 = d0 * d3
	"vmul.f32 		d2, d0, d1				\n\t"	//d2 = d0 * d1	
	"vrsqrts.f32 	d3, d2, d0				\n\t"	//d3 = (3 - d0 * d2) / 2	
	"vmul.f32 		d0, d0, d3				\n\t"	//d0 = d0 * d3	

	"vmul.f32 		d4, d4, d0[0]			\n\t"	//d4 = d4*d0[0]
	"vst1.32 		{d4}, [%0]				\n\t"	//
	
	:: "r"(&v.items_[0])
    	: "d0", "d1", "d2", "d3", "d4", "memory"
	);
*/

    }
    else if(v.size()==3)
    {	
	asm volatile(
	"vld1.32		{d4,d5},[%0]				\n\t"
	"vmul.f32		q1,q2,q2				\n\t"
	"vpadd.f32		d2,d2,d2				\n\t"
	"vadd.f32		s4,s4,s6				\n\t"
	"vsqrt.f32		s0,s4					\n\t"
	"vdiv.f32		s0,s0,s4				\n\t"
	
	"vmul.f32		q2,q2,d0[0]				\n\t"
	"vst1.32		{d4,d5},[%0]				\n\t"
	::"r"(&v.items_[0])
	:"d0","d1","d2","d3","d4","d5","memory"
	);
	/*
	asm volatile (
	"vld1.32 		{d4}, [%0]				\n\t"	//d4={x0,y0}
	"flds 			s10, [%0, #8]			\n\t"	//d5[0]={z0}

	"vmul.f32 		d0, d4, d4				\n\t"	//d0= d4*d4
	"vpadd.f32 		d0, d0					\n\t"	//d0 = d[0] + d[1]
	"vmla.f32 		d0, d5, d5				\n\t"	//d0 = d0 + d5*d5 
	
	"vmov.f32 		d1, d0					\n\t"	//d1 = d0
	"vrsqrte.f32 	d0, d0					\n\t"	//d0 = ~ 1.0 / sqrt(d0)
	"vmul.f32 		d2, d0, d1				\n\t"	//d2 = d0 * d1
	"vrsqrts.f32 	d3, d2, d0				\n\t"	//d3 = (3 - d0 * d2) / 2 	
	"vmul.f32 		d0, d0, d3				\n\t"	//d0 = d0 * d3
	"vmul.f32 		d2, d0, d1				\n\t"	//d2 = d0 * d1	
	"vrsqrts.f32 	d3, d2, d0				\n\t"	//d4 = (3 - d0 * d3) / 2	
	"vmul.f32 		d0, d0, d3				\n\t"	//d0 = d0 * d4	

	"vmul.f32 		q2, q2, d0[0]			\n\t"	//d0= d2*d4
	"vst1.32 		{d4}, [%0]				\n\t"	//
	"fsts 			s10, [%0, #8]			\n\t"	//
	
	:: "r"(&v.items_[0])
        : "d0", "d1", "d2", "d3", "d4", "d5", "memory"
	);
	*/
    }
    else if(v.size()==6)
    {
	asm volatile(
	"vld1.32		{d4,d5,d6},[%0]			\n\t"
	"vmul.f32		d0,d4,d4			\n\t"
	"vmla.f32		d0,d5,d5			\n\t"
	"vmla.f32		d0,d6,d6			\n\t"
	"vpadd.f32		d0,d0,d0			\n\t"
	
	"vsqrt.f32		s1,s0				\n\t"
	"vdiv.f32		s0,s1,s0			\n\t"
	"vmul.f32		q2,q2,d0[0]			\n\t"
	"vmul.f32		d6,d6,d0[0]			\n\t"

	"vst1.32		{d4,d5,d6},[%0]			\n\t"
	::"r"(&v.items_[0])
	:"d0","d4","d5","d6","memory"
	);
/*
	asm volatile(
	"vld1.32		{d4,d5,d6},[%0]			\n\t"
	"vmul.f32		d0,d4,d4			\n\t"
	"vmla.f32		d0,d5,d5			\n\t"
	"vmla.f32		d0,d6,d6			\n\t"
	
	"vmov.f32		d1,d0				\n\t"
	"vrsqrte.f32		d0,d0				\n\t"
	"vmul.f32		d2,d0,d1			\n\t"
	"vrsqrts.f32		d3,d2,d0			\n\t"
	"vmul.f32		d0,d0,d3			\n\t"
	"vmul.f32		d2,d0,d1			\n\t"
	"vrsqrts.f32		d3,d2,d0			\n\t"
	"vmul.f32		d0,d0,d3			\n\t"
	
	"vmul.f32		q2,q2,d0[0]			\n\t"
	"vmul.f32		d6,d6,d0[0]			\n\t"
	"vst1.32		{d4,d5,d6},[%0]			\n\t"
	
	::"r"(&v.items_[0])
	:"d0","d1","d2","d3","d4","d5","d6","memory"
        );
*/
    }

  }

  float VectorBase::dot(const VectorBase& vector) const
  {
    assert(this->size() == vector.size());
    assert(this->size()==2||this->size()==3||this->size()==6);
    float result=0;

   // DBG_PRINT("[dot]v.size()==%d\n", v.size());
    if(this->size()==2)
    {

	asm volatile(
	"vld1.32		{d2},[%1]			\n\t"
	"vld1.32		{d4},[%2]			\n\t"
	"vmul.f32		d0,d2,d4			\n\t"
	"vpadd.f32		d0,d0,d0			\n\t"
	"vmov.f32		%0,s0				\n\t"
	:"=r"(result):"r"(&items_[0]),"r"(&vector.items_[0])
	:"d0","d2","d4"
	);
    }
    else if(this->size()==3)
    {
	asm volatile(
	"vld1.32		{d2,d3},[%1]			\n\t"
	"vld1.32		{d4,d5},[%2]			\n\t"
	"vmul.f32		q0,q1,q2			\n\t"
	"vpadd.f32		d0,d0				\n\t"
	"vadd.f32		s0,s2				\n\t"
	"vmov.f32		%0,s0				\n\t"
	:"=r"(result):"r"(&items_[0]),"r"(&vector.items_[0])
	:"d0","d2","d3","d4","d5"
	);
    }
    else if(this->size()==6)
    {
	asm volatile(
	"vld1.32	{d2,d3,d4},[%1]				\n\t"
	"vld1.32	{d6,d7,d8},[%2]				\n\t"
	"vmul.f32	d0,d2,d6				\n\t"
	"vmla.f32	d0,d3,d7				\n\t"
	"vmla.f32	d0,d4,d8				\n\t"
	"vpadd.f32	d0,d0					\n\t"
	"vmov.f32	%0,s0					\n\t"
	:"=r"(result):"r"(&items_[0]),"r"(&vector.items_[0])
	:"d0","d2","d3","d4","d6","d7","d8"
	);
    }

    return result;
  }

  VectorBase VectorBase::cross(const VectorBase& vector) const
  {
    assert(this->size() == 3);
    assert(this->size() == vector.size());
    VectorBase v(3);
    DBG_PRINT("[cross]v.size==%d\n", v.size());


    asm volatile(
    "mov		r1,%0				\n\t"
    "vld1.32		{d2,d3},[r1]			\n\t"
    "flds		s7,[r1]				\n\t"
    "add		r1,r1,#4			\n\t"
    "vld1.32		{d4},[r1]			\n\t"
    "flds		s3,[%1]				\n\t"
    "vmul.f32		d7,d4,d1[1]			\n\t"
    "flds		s3,[%1,#4]			\n\t"
    "vmul.f32		d6,d3,d1[1]			\n\t"
    "flds		s3,[%1,#8]			\n\t"
    "vmul.f32		d5,d2,d1[1]			\n\t"
    "vsub.f32		s0,s11,s12			\n\t"
    "vsub.f32		s1,s15,s10			\n\t"
    "vsub.f32		s2,s13,s14			\n\t"
    "vst1.32		{d0},[%2]			\n\t"
    "fsts		s2,[%2,#8]			\n\t"
    ::"r"(&items_[0]),"r"(&vector.items_[0]),"r"(&v.items_[0])
    :"r1","d0","d1","d2","d3","d4","d5","d6","d7","memory"
    );

    return v;
  }

}  // namespace la  
}  // namespace sgbot

#endif  // _USE_ARM_NEON_
