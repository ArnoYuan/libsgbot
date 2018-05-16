/* Created linear-algebra/matrix-neon.cpp by CybernikLee
 *
 * E-Mail <cyberniklee@gmail.com>
 *
 * Copyright 2018 GuangZhou SmartGiant Tech 
 * 
 */

#ifdef _USE_ARM_NEON_

#include <linear-algebra/matrix.h>
#include <string.h>
//#define USE_DBG

#ifdef USE_DBG
#include <stdio.h>
#define DBG_PRINT(fmt,...)	printf(fmt, ##__VA_ARGS__)
#else
#define DBG_PRINT(fmt,...)
#endif

namespace sgbot {
namespace la {

  MatrixBase& MatrixBase::operator +=(const float scalar)
  {
   	MatrixBase& matrix = *this;
    	assert((matrix.getRows()==2||matrix.getRows()==3||matrix.getRows()==6)
		&&matrix.getRows()==matrix.getColumns());
    	if(matrix.getRows()==2)
    	{
		asm volatile(
		"vld1.32		{d2},[%0]			\n\t"
		"vld1.32		{d3},[%1]			\n\t"
		"vmov			s0,%2				\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vadd.f32		q1,q0,q1			\n\t"
		"vst1.32		{d2},[%0]			\n\t"
		"vst1.32		{d3},[%1]			\n\t"
		::"r"(&matrix_[0][0]),"r"(&matrix_[1][0]),"r"(scalar): "d0","d1","d2","d3","memory"
		);
    	}
	else if(matrix.getRows()==3)
	{
		asm volatile(
		"vld1.32		{d2,d3},[%0]			\n\t"
		"vld1.32		{d4,d5},[%1]			\n\t"
		"vld1.32		{d6,d7},[%2]			\n\t"
		"vmov			s0,%3				\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vadd.f32		q1,q1,q0			\n\t"
		"vadd.f32		q2,q2,q0			\n\t"
		"vadd.f32		q3,q3,q0			\n\t"
		"vst1.32		{d2},[%0]!			\n\t"
		"fsts			s6,[%0]				\n\t"
		"vst1.32		{d4},[%1]!			\n\t"
		"fsts			s10,[%1]			\n\t"
		"vst1.32		{d6},[%2]!			\n\t"
		"fsts			s14,[%2]			\n\t"
		::"r"(&matrix_[0][0]),"r"(&matrix_[1][0]),"r"(&matrix_[2][0]),"r"(scalar):"d0","d1","d2","d3","d4","d5","d6","d7","memory"
		);
	}
	else if(matrix.getRows()==4)
	{
		asm volatile(
		"vld1.32		{d2,d3},[%0]			\n\t"
		"vld1.32		{d4,d5},[%1]			\n\t"
		"vld1.32		{d6,d7},[%2]			\n\t"
		"vld1.32		{d8,d9},[%3]			\n\t"
		"vmov			s0,%4				\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vadd.f32		q1,q1,q0			\n\t"
		"vadd.f32		q2,q2,q0			\n\t"
		"vadd.f32		q3,q3,q0			\n\t"
		"vadd.f32		q4,q4,q0			\n\t"
		"vst1.32		{d2,d3},[%0]			\n\t"
		"vst1.32		{d4,d5},[%1]			\n\t"
		"vst1.32		{d6,d7},[%2]			\n\t"
		"vst1.32		{d8,d9},[%3]			\n\t"
		::"r"(&matrix_[0][0]),"r"(&matrix_[1][0]),"r"(&matrix_[2][0]),"r"(&matrix_[3][0]),"r"(scalar)
		:"r1","d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","memory"
		);
	}
	else if(matrix.getRows()==6)
	{
/*
		int i=0;
		for(i=0;i<3;i++)
		{
			asm volatile(
			"vmov		s0,%2				\n\t"
			"vld1.32	{d4,d5,d6},[%0]			\n\t"
			"vld1.32	{d8,d9,d10},[%1]		\n\t"
			"vdup.32	q0,d0[0]			\n\t"
			"vdup.32	d2,d0[0]			\n\t"
			"vadd.f32	q2,q2,q0			\n\t"
			"vadd.f32	d6,d6,d0			\n\t"
			"vadd.f32	q4,q4,q0			\n\t"
			"vadd.f32	d10,d10,d0			\n\t"
			"vld1.32	{d4,d5,d6},[%0]			\n\t"
			"vld1.32	{d8,d9,d10},[%1]			\n\t"
			::"r"(&matrix_[i*2][0]),"r"(&matrix_[i*2+1][0]),"r"(scalar)
			:"r1","d0","d1","d2","d3","d4","d5","d6","d7","d9","d10","memory"
			);
		}
*/
	}

	return matrix;
  }
  

  MatrixBase& MatrixBase::operator -=(const float scalar)
  {
   	MatrixBase& matrix = *this;
    	assert((matrix.getRows()==2||matrix.getRows()==3||matrix.getRows()==6)
		&&matrix.getRows()==matrix.getColumns());
    	if(matrix.getRows()==2)
    	{
		asm volatile(
		"vld1.32		{d2},[%0]			\n\t"
		"vld1.32		{d3},[%1]			\n\t"
		"vmov			s0,%2				\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vsub.f32		q1,q1,q0			\n\t"
		"vst1.32		{d2},[%0]			\n\t"
		"vst1.32		{d3},[%1]			\n\t"
		::"r"(&matrix_[0][0]),"r"(&matrix_[1][0]),"r"(scalar): "d0","d1","d2","d3","memory"
		);
    	}
	else if(matrix.getRows()==3)
	{
		asm volatile(
		"vld1.32		{d2,d3},[%0]			\n\t"
		"vld1.32		{d4,d5},[%1]			\n\t"
		"vld1.32		{d6,d7},[%2]			\n\t"
		"vmov			s0,%3				\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vsub.f32		q1,q1,q0			\n\t"
		"vsub.f32		q2,q2,q0			\n\t"
		"vsub.f32		q3,q3,q0			\n\t"
		"vst1.32		{d2},[%0]!			\n\t"
		"fsts			s6,[%0]				\n\t"
		"vst1.32		{d4},[%1]!			\n\t"
		"fsts			s10,[%1]			\n\t"
		"vst1.32		{d6},[%2]!			\n\t"
		"fsts			s14,[%2]			\n\t"
		::"r"(&matrix_[0][0]),"r"(&matrix_[1][0]),"r"(&matrix_[2][0]),"r"(scalar):"d0","d1","d2","d3","d4","d5","d6","d7","memory"
		);
	}
	else if(matrix.getRows()==4)
	{
		asm volatile(
		"vld1.32		{d2,d3},[%0]			\n\t"
		"vld1.32		{d4,d5},[%1]			\n\t"
		"vld1.32		{d6,d7},[%2]			\n\t"
		"vld1.32		{d8,d9},[%3]			\n\t"
		"vmov			s0,%4				\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vsub.f32		q1,q1,q0			\n\t"
		"vsub.f32		q2,q2,q0			\n\t"
		"vsub.f32		q3,q3,q0			\n\t"
		"vsub.f32		q4,q4,q0			\n\t"
		"vst1.32		{d2,d3},[%0]			\n\t"
		"vst1.32		{d4,d5},[%1]			\n\t"
		"vst1.32		{d6,d7},[%2]			\n\t"
		"vst1.32		{d8,d9},[%3]			\n\t"
		::"r"(&matrix_[0][0]),"r"(&matrix_[1][0]),"r"(&matrix_[2][0]),"r"(&matrix_[3][0]),"r"(scalar)
		:"r1","d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","memory"
		);
	}
	else if(matrix.getRows()==6)
	{
/*
		int i=0;
		for(i=0;i<3;i++)
		{
			asm volatile(
			"vmov		s0,%2				\n\t"
			"vld1.32	{d4,d5,d6},[%0]			\n\t"
			"vld1.32	{d8,d9,d10},[%1]		\n\t"
			"vdup.32	q0,d0[0]			\n\t"
			"vdup.32	d2,d0[0]			\n\t"
			"vsub.f32	q2,q2,q0			\n\t"
			"vsub.f32	d6,d6,d0			\n\t"
			"vsub.f32	q4,q4,q0			\n\t"
			"vsub.f32	d10,d10,d0			\n\t"
			"vld1.32	{d4,d5,d6},[%0]			\n\t"
			"vld1.32	{d8,d9,d10},[%1]			\n\t"
			::"r"(&matrix_[i*2][0]),"r"(&matrix_[i*2+1][0]),"r"(scalar)
			:"r1","d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","d10","memory"
			);
		}
*/
	}

	return matrix;
  }


  MatrixBase& MatrixBase::operator *=(const float scalar)
  {
   	MatrixBase& matrix = *this;
    	assert((matrix.getRows()==2||matrix.getRows()==3||matrix.getRows()==6)
		&&matrix.getRows()==matrix.getColumns());
    	if(matrix.getRows()==2)
    	{
		asm volatile(
		"vld1.32		{d2},[%0]			\n\t"
		"vld1.32		{d3},[%1]			\n\t"
		"vmov			s0,%2				\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vmul.f32		q1,q0,q1			\n\t"
		"vst1.32		{d2},[%0]			\n\t"
		"vst1.32		{d3},[%1]			\n\t"
		::"r"(&matrix_[0][0]),"r"(&matrix_[1][0]),"r"(scalar): "d0","d1","d2","d3","memory"
		);
    	}
	else if(matrix.getRows()==3)
	{
		asm volatile(
		"vld1.32		{d2,d3},[%0]			\n\t"
		"vld1.32		{d4,d5},[%1]			\n\t"
		"vld1.32		{d6,d7},[%2]			\n\t"
		"vmov			s0,%3				\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vmul.f32		q1,q1,q0			\n\t"
		"vmul.f32		q2,q2,q0			\n\t"
		"vmul.f32		q3,q3,q0			\n\t"
		"vst1.32		{d2},[%0]!			\n\t"
		"fsts			s6,[%0]				\n\t"
		"vst1.32		{d4},[%1]!			\n\t"
		"fsts			s10,[%1]			\n\t"
		"vst1.32		{d6},[%2]!			\n\t"
		"fsts			s14,[%2]			\n\t"
		::"r"(&matrix_[0][0]),"r"(&matrix_[1][0]),"r"(&matrix_[2][0]),"r"(scalar):"d0","d1","d2","d3","d4","d5","d6","d7","memory"
		);
	}
	else if(matrix.getRows()==4)
	{
		asm volatile(
		"vld1.32		{d2,d3},[%0]			\n\t"
		"vld1.32		{d4,d5},[%1]			\n\t"
		"vld1.32		{d6,d7},[%2]			\n\t"
		"vld1.32		{d8,d9},[%3]			\n\t"
		"vmov			s0,%4				\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vmul.f32		q1,q1,q0			\n\t"
		"vmul.f32		q2,q2,q0			\n\t"
		"vmul.f32		q3,q3,q0			\n\t"
		"vmul.f32		q4,q4,q0			\n\t"
		"vst1.32		{d2,d3},[%0]			\n\t"
		"vst1.32		{d4,d5},[%1]			\n\t"
		"vst1.32		{d6,d7},[%2]			\n\t"
		"vst1.32		{d8,d9},[%3]			\n\t"
		::"r"(&matrix_[0][0]),"r"(&matrix_[1][0]),"r"(&matrix_[2][0]),"r"(&matrix_[3][0]),"r"(scalar)
		:"r1","d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","memory"
		);
	}
	else if(matrix.getRows()==6)
	{
/*
		int i=0;
		for(i=0;i<3;i++)
		{
			asm volatile(
			"vmov		s0,%2				\n\t"
			"vld1.32	{d4,d5,d6},[%0]			\n\t"
			"vld1.32	{d8,d9,d10},[%1]		\n\t"
			"vdup.32	q0,d0[0]			\n\t"
			"vdup.32	d2,d0[0]			\n\t"
			"vmul.f32	q2,q2,q0			\n\t"
			"vmul.f32	d6,d6,d0			\n\t"
			"vmul.f32	q4,q4,q0			\n\t"
			"vmul.f32	d10,d10,d0			\n\t"
			"vld1.32	{d4,d5,d6},[%0]			\n\t"
			"vld1.32	{d8,d9,d10},[%1]			\n\t"
			::"r"(&matrix_[i*2][0]),"r"(&matrix_[i*2+1][0]),"r"(scalar)
			:"r1","d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","d10","memory"
			);
		}
*/
	}

	return matrix;
  }

  MatrixBase& MatrixBase::operator /=(const float scalar)
  {
   	MatrixBase& matrix = *this;
    	assert((matrix.getRows()==2||matrix.getRows()==3||matrix.getRows()==6)
		&&matrix.getRows()==matrix.getColumns());
    	if(matrix.getRows()==2)
    	{
		asm volatile(
		"vld1.32		{d2},[%0]			\n\t"
		"vld1.32		{d3},[%1]			\n\t"
		"vmov			s0,%2				\n\t"
		"vmul.f32		s1,s0,s0			\n\t"
		"vdiv.f32		s0,s0,s1			\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vmul.f32		q1,q1,q0			\n\t"
		"vst1.32		{d2},[%0]			\n\t"
		"vst1.32		{d3},[%1]			\n\t"
		::"r"(&matrix_[0][0]),"r"(&matrix_[1][0]),"r"(scalar): "d0","d1","d2","d3","memory"
		);
    	}
	else if(matrix.getRows()==3)
	{
		asm volatile(
		"vld1.32		{d2,d3},[%0]			\n\t"
		"vld1.32		{d4,d5},[%1]			\n\t"
		"vld1.32		{d6,d7},[%2]			\n\t"
		"vmov			s0,%3				\n\t"
		"vmul.f32		s1,s0,s0			\n\t"
		"vdiv.f32		s0,s0,s1			\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vmul.f32		q1,q1,q0			\n\t"
		"vmul.f32		q2,q2,q0			\n\t"
		"vmul.f32		q3,q3,q0			\n\t"
		"vst1.32		{d2},[%0]!			\n\t"
		"fsts			s6,[%0]				\n\t"
		"vst1.32		{d4},[%1]!			\n\t"
		"fsts			s10,[%1]			\n\t"
		"vst1.32		{d6},[%2]!			\n\t"
		"fsts			s14,[%2]			\n\t"
		::"r"(&matrix_[0][0]),"r"(&matrix_[1][0]),"r"(&matrix_[2][0]),"r"(scalar):"d0","d1","d2","d3","d4","d5","d6","d7","memory"
		);
	}
	else if(matrix.getRows()==4)
	{
		asm volatile(
		"vld1.32		{d2,d3},[%0]			\n\t"
		"vld1.32		{d4,d5},[%1]			\n\t"
		"vld1.32		{d6,d7},[%2]			\n\t"
		"vld1.32		{d8,d9},[%3]			\n\t"
		"vmov			s0,%2				\n\t"
		"vmul.f32		s1,s0,s0			\n\t"
		"vdiv.f32		s0,s0,s1			\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vmul.f32		q1,q1,q0			\n\t"
		"vmul.f32		q2,q2,q0			\n\t"
		"vmul.f32		q3,q3,q0			\n\t"
		"vmul.f32		q4,q4,q0			\n\t"
		"vst1.32		{d2,d3},[%0]			\n\t"
		"vst1.32		{d4,d5},[%1]			\n\t"
		"vst1.32		{d6,d7},[%2]			\n\t"
		"vst1.32		{d8,d9},[%3]			\n\t"
		::"r"(&matrix_[0][0]),"r"(&matrix_[1][0]),"r"(&matrix_[2][0]),"r"(&matrix_[3][0]),"r"(scalar)
		:"r1","d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","memory"
		);
	}
	else if(matrix.getRows()==6)
	{
/*
		int i=0;
		for(i=0;i<3;i++)
		{
			asm volatile(
			"vmov		s0,%2				\n\t"
			"vmul.f32	s1,s0,s0			\n\t"
			"vdiv.f32	s0,s0,s1			\n\t"
			"vld1.32	{d4,d5,d6},[%0]			\n\t"
			"vld1.32	{d8,d9,d10},[%1]		\n\t"
			"vdup.32	q0,d0[0]			\n\t"
			"vdup.32	d2,d0[0]			\n\t"
			"vmul.f32	q2,q2,q0			\n\t"
			"vmul.f32	d6,d6,d0			\n\t"
			"vmul.f32	q4,q4,q0			\n\t"
			"vmul.f32	d10,d10,d0			\n\t"
			"vld1.32	{d4,d5,d6},[%0]			\n\t"
			"vld1.32	{d8,d9,d10},[%1]			\n\t"
			::"r"(&matrix_[i*2][0]),"r"(&matrix_[i*2+1][0]),"r"(scalar)
			:"r1","d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","d10","memory"
			);
		}
*/
	}

	return matrix;
  }


  MatrixBase MatrixBase::operator +(const float scalar) const
  {
   	MatrixBase matrix(*this);
    	assert((matrix.getRows()==2||matrix.getRows()==3||matrix.getRows()==6)
		&&matrix.getRows()==matrix.getColumns());
    	if(matrix.getRows()==2)
    	{
		asm volatile(
		"vld1.32		{d2},[%0]			\n\t"
		"vld1.32		{d3},[%1]			\n\t"
		"vmov			s0,%2				\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vadd.f32		q1,q0,q1			\n\t"
		"vst1.32		{d2},[%0]			\n\t"
		"vst1.32		{d3},[%1]			\n\t"
		::"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(scalar): "d0","d1","d2","d3","memory"
		);
    	}
	else if(matrix.getRows()==3)
	{
		asm volatile(
		"vld1.32		{d2,d3},[%0]			\n\t"
		"vld1.32		{d4,d5},[%1]			\n\t"
		"vld1.32		{d6,d7},[%2]			\n\t"
		"vmov			s0,%3				\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vadd.f32		q1,q1,q0			\n\t"
		"vadd.f32		q2,q2,q0			\n\t"
		"vadd.f32		q3,q3,q0			\n\t"
		"vst1.32		{d2},[%0]!			\n\t"
		"fsts			s6,[%0]				\n\t"
		"vst1.32		{d4},[%1]!			\n\t"
		"fsts			s10,[%1]			\n\t"
		"vst1.32		{d6},[%2]!			\n\t"
		"fsts			s14,[%2]			\n\t"
		::"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&matrix.matrix_[2][0]),"r"(scalar):"d0","d1","d2","d3","d4","d5","d6","d7","memory"
		);
	}
	else if(matrix.getRows()==4)
	{
		asm volatile(
		"vld1.32		{d2,d3},[%0]			\n\t"
		"vld1.32		{d4,d5},[%1]			\n\t"
		"vld1.32		{d6,d7},[%2]			\n\t"
		"vld1.32		{d8,d9},[%3]			\n\t"
		"vmov			s0,%4				\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vadd.f32		q1,q1,q0			\n\t"
		"vadd.f32		q2,q2,q0			\n\t"
		"vadd.f32		q3,q3,q0			\n\t"
		"vadd.f32		q4,q4,q0			\n\t"
		"vst1.32		{d2,d3},[%0]			\n\t"
		"vst1.32		{d4,d5},[%1]			\n\t"
		"vst1.32		{d6,d7},[%2]			\n\t"
		"vst1.32		{d8,d9},[%3]			\n\t"
		::"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&matrix.matrix_[2][0]),"r"(&matrix.matrix_[3][0]),"r"(scalar)
		:"r1","d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","memory"
		);
	}
	else if(matrix.getRows()==6)
	{
/*
		int i=0;
		for(i=0;i<3;i++)
		{
			asm volatile(
			"vmov		s0,%2				\n\t"
			"vld1.32	{d4,d5,d6},[%0]			\n\t"
			"vld1.32	{d8,d9,d10},[%1]		\n\t"
			"vdup.32	q0,d0[0]			\n\t"
			"vdup.32	d2,d0[0]			\n\t"
			"vadd.f32	q2,q2,q0			\n\t"
			"vadd.f32	d6,d6,d0			\n\t"
			"vadd.f32	q4,q4,q0			\n\t"
			"vadd.f32	d10,d10,d0			\n\t"
			"vld1.32	{d4,d5,d6},[%0]			\n\t"
			"vld1.32	{d8,d9,d10},[%1]			\n\t"
			::"r"(&matrix.matrix_[i*2][0]),"r"(&matrix.matrix_[i*2+1][0]),"r"(scalar)
			:"r1","d0","d1","d2","d3","d4","d5","d6","d7","d9","d10","memory"
			);
		}
*/
	}

	return matrix;
  }

  MatrixBase MatrixBase::operator -(const float scalar) const
  {
	MatrixBase matrix(*this);

    	assert((matrix.getRows()==2||matrix.getRows()==3||matrix.getRows()==6)
		&&matrix.getRows()==matrix.getColumns());
    	if(matrix.getRows()==2)
    	{
		asm volatile(
		"vld1.32		{d2},[%0]			\n\t"
		"vld1.32		{d3},[%1]			\n\t"
		"vmov			s0,%2				\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vsub.f32		q1,q1,q0			\n\t"
		"vst1.32		{d2},[%0]			\n\t"
		"vst1.32		{d3},[%1]			\n\t"
		::"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(scalar): "d0","d1","d2","d3","memory"
		);
    	}
	else if(matrix.getRows()==3)
	{
		asm volatile(
		"vld1.32		{d2,d3},[%0]			\n\t"
		"vld1.32		{d4,d5},[%1]			\n\t"
		"vld1.32		{d6,d7},[%2]			\n\t"
		"vmov			s0,%3				\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vsub.f32		q1,q1,q0			\n\t"
		"vsub.f32		q2,q2,q0			\n\t"
		"vsub.f32		q3,q3,q0			\n\t"
		"vst1.32		{d2},[%0]!			\n\t"
		"fsts			s6,[%0]				\n\t"
		"vst1.32		{d4},[%1]!			\n\t"
		"fsts			s10,[%1]			\n\t"
		"vst1.32		{d6},[%2]!			\n\t"
		"fsts			s14,[%2]			\n\t"
		::"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&matrix.matrix_[2][0]),"r"(scalar):"d0","d1","d2","d3","d4","d5","d6","d7","memory"
		);
	}
	else if(matrix.getRows()==4)
	{
		asm volatile(
		"vld1.32		{d2,d3},[%0]			\n\t"
		"vld1.32		{d4,d5},[%1]			\n\t"
		"vld1.32		{d6,d7},[%2]			\n\t"
		"vld1.32		{d8,d9},[%3]			\n\t"
		"vmov			s0,%4				\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vsub.f32		q1,q1,q0			\n\t"
		"vsub.f32		q2,q2,q0			\n\t"
		"vsub.f32		q3,q3,q0			\n\t"
		"vsub.f32		q4,q4,q0			\n\t"
		"vst1.32		{d2,d3},[%0]			\n\t"
		"vst1.32		{d4,d5},[%1]			\n\t"
		"vst1.32		{d6,d7},[%2]			\n\t"
		"vst1.32		{d8,d9},[%3]			\n\t"
		::"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&matrix.matrix_[2][0]),"r"(&matrix.matrix_[3][0]),"r"(scalar)
		:"r1","d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","memory"
		);
	}
	else if(matrix.getRows()==6)
	{/*
		int i=0;
		for(i=0;i<3;i++)
		{
			asm volatile(
			"vmov		s0,%2				\n\t"
			"vld1.32	{d4,d5,d6},[%0]			\n\t"
			"vld1.32	{d8,d9,d10},[%1]		\n\t"
			"vdup.32	q0,d0[0]			\n\t"
			"vdup.32	d2,d0[0]			\n\t"
			"vsub.f32	q2,q2,q0			\n\t"
			"vsub.f32	d6,d6,d0			\n\t"
			"vsub.f32	q4,q4,q0			\n\t"
			"vsub.f32	d10,d10,d0			\n\t"
			"vld1.32	{d4,d5,d6},[%0]			\n\t"
			"vld1.32	{d8,d9,d10},[%1]			\n\t"
			::"r"(&matrix.matrix_[i*2][0]),"r"(&matrix.matrix_[i*2+1][0]),"r"(scalar)
			:"r1","d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","d10","memory"
			);
		}
*/
	}

	return matrix;

  }

  MatrixBase MatrixBase::operator *(const float scalar) const
  {
    	MatrixBase matrix(*this);
    	assert((matrix.getRows()==2||matrix.getRows()==3||matrix.getRows()==6)
		&&matrix.getRows()==matrix.getColumns());
    	if(matrix.getRows()==2)
    	{
		asm volatile(
		"vld1.32		{d2},[%0]			\n\t"
		"vld1.32		{d3},[%1]			\n\t"
		"vmov			s0,%2				\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vmul.f32		q1,q0,q1			\n\t"
		"vst1.32		{d2},[%0]			\n\t"
		"vst1.32		{d3},[%1]			\n\t"
		::"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(scalar): "d0","d1","d2","d3","memory"
		);
    	}
	else if(matrix.getRows()==3)
	{
		asm volatile(
		"vld1.32		{d2,d3},[%0]			\n\t"
		"vld1.32		{d4,d5},[%1]			\n\t"
		"vld1.32		{d6,d7},[%2]			\n\t"
		"vmov			s0,%3				\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vmul.f32		q1,q1,q0			\n\t"
		"vmul.f32		q2,q2,q0			\n\t"
		"vmul.f32		q3,q3,q0			\n\t"
		"vst1.32		{d2},[%0]!			\n\t"
		"fsts			s6,[%0]				\n\t"
		"vst1.32		{d4},[%1]!			\n\t"
		"fsts			s10,[%1]			\n\t"
		"vst1.32		{d6},[%2]!			\n\t"
		"fsts			s14,[%2]			\n\t"
		::"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&matrix.matrix_[2][0]),"r"(scalar):"d0","d1","d2","d3","d4","d5","d6","d7","memory"
		);
	}
	else if(matrix.getRows()==4)
	{
		asm volatile(
		"vld1.32		{d2,d3},[%0]			\n\t"
		"vld1.32		{d4,d5},[%1]			\n\t"
		"vld1.32		{d6,d7},[%2]			\n\t"
		"vld1.32		{d8,d9},[%3]			\n\t"
		"vmov			s0,%4				\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vmul.f32		q1,q1,q0			\n\t"
		"vmul.f32		q2,q2,q0			\n\t"
		"vmul.f32		q3,q3,q0			\n\t"
		"vmul.f32		q4,q4,q0			\n\t"
		"vst1.32		{d2,d3},[%0]			\n\t"
		"vst1.32		{d4,d5},[%1]			\n\t"
		"vst1.32		{d6,d7},[%2]			\n\t"
		"vst1.32		{d8,d9},[%3]			\n\t"
		::"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&matrix.matrix_[2][0]),"r"(&matrix.matrix_[3][0]),"r"(scalar)
		:"r1","d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","memory"
		);
	}
	else if(matrix.getRows()==6)
	{
/*
		int i=0;
		for(i=0;i<3;i++)
		{
			asm volatile(
			"vmov		s0,%2				\n\t"
			"vld1.32	{d4,d5,d6},[%0]			\n\t"
			"vld1.32	{d8,d9,d10},[%1]		\n\t"
			"vdup.32	q0,d0[0]			\n\t"
			"vdup.32	d2,d0[0]			\n\t"
			"vmul.f32	q2,q2,q0			\n\t"
			"vmul.f32	d6,d6,d0			\n\t"
			"vmul.f32	q4,q4,q0			\n\t"
			"vmul.f32	d10,d10,d0			\n\t"
			"vld1.32	{d4,d5,d6},[%0]			\n\t"
			"vld1.32	{d8,d9,d10},[%1]			\n\t"
			::"r"(&matrix.matrix_[i*2][0]),"r"(&matrix.matrix_[i*2+1][0]),"r"(scalar)
			:"r1","d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","d10","memory"
			);
		}
*/
	}

	return matrix;
  }


  MatrixBase MatrixBase::operator /(const float scalar) const
  {
    	MatrixBase matrix(*this);
    	assert((matrix.getRows()==2||matrix.getRows()==3||matrix.getRows()==6)
		&&matrix.getRows()==matrix.getColumns());

    	if(matrix.getRows()==2)
    	{
		asm volatile(
		"vld1.32		{d2},[%0]			\n\t"
		"vld1.32		{d3},[%1]			\n\t"
		"vmov			s0,%2				\n\t"
		"vmul.f32		s1,s0,s0			\n\t"
		"vdiv.f32		s0,s0,s1			\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vmul.f32		q1,q1,q0			\n\t"
		"vst1.32		{d2},[%0]			\n\t"
		"vst1.32		{d3},[%1]			\n\t"
		::"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(scalar): "d0","d1","d2","d3","memory"
		);
    	}
	else if(matrix.getRows()==3)
	{
		asm volatile(
		"vld1.32		{d2,d3},[%0]			\n\t"
		"vld1.32		{d4,d5},[%1]			\n\t"
		"vld1.32		{d6,d7},[%2]			\n\t"
		"vmov			s0,%3				\n\t"
		"vmul.f32		s1,s0,s0			\n\t"
		"vdiv.f32		s0,s0,s1			\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vmul.f32		q1,q1,q0			\n\t"
		"vmul.f32		q2,q2,q0			\n\t"
		"vmul.f32		q3,q3,q0			\n\t"
		"vst1.32		{d2},[%0]!			\n\t"
		"fsts			s6,[%0]				\n\t"
		"vst1.32		{d4},[%1]!			\n\t"
		"fsts			s10,[%1]			\n\t"
		"vst1.32		{d6},[%2]!			\n\t"
		"fsts			s14,[%2]			\n\t"
		::"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&matrix.matrix_[2][0]),"r"(scalar):"d0","d1","d2","d3","d4","d5","d6","d7","memory"
		);
	}
	else if(matrix.getRows()==4)
	{
		asm volatile(
		"vld1.32		{d2,d3},[%0]			\n\t"
		"vld1.32		{d4,d5},[%1]			\n\t"
		"vld1.32		{d6,d7},[%2]			\n\t"
		"vld1.32		{d8,d9},[%3]			\n\t"
		"vmov			s0,%2				\n\t"
		"vmul.f32		s1,s0,s0			\n\t"
		"vdiv.f32		s0,s0,s1			\n\t"
		"vdup.32		q0,d0[0]			\n\t"
		"vmul.f32		q1,q1,q0			\n\t"
		"vmul.f32		q2,q2,q0			\n\t"
		"vmul.f32		q3,q3,q0			\n\t"
		"vmul.f32		q4,q4,q0			\n\t"
		"vst1.32		{d2,d3},[%0]			\n\t"
		"vst1.32		{d4,d5},[%1]			\n\t"
		"vst1.32		{d6,d7},[%2]			\n\t"
		"vst1.32		{d8,d9},[%3]			\n\t"
		::"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&matrix.matrix_[2][0]),"r"(&matrix.matrix_[3][0]),"r"(scalar)
		:"r1","d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","memory"
		);
	}
	else if(matrix.getRows()==6)
	{
/*
		int i=0;
		for(i=0;i<3;i++)
		{
			asm volatile(
			"vmov		s0,%2				\n\t"
			"vmul.f32	s1,s0,s0			\n\t"
			"vdiv.f32	s0,s0,s1			\n\t"
			"vld1.32	{d4,d5,d6},[%0]			\n\t"
			"vld1.32	{d8,d9,d10},[%1]		\n\t"
			"vdup.32	q0,d0[0]			\n\t"
			"vdup.32	d2,d0[0]			\n\t"
			"vmul.f32	q2,q2,q0			\n\t"
			"vmul.f32	d6,d6,d0			\n\t"
			"vmul.f32	q4,q4,q0			\n\t"
			"vmul.f32	d10,d10,d0			\n\t"
			"vld1.32	{d4,d5,d6},[%0]			\n\t"
			"vld1.32	{d8,d9,d10},[%1]			\n\t"
			::"r"(&matrix.matrix_[i*2][0]),"r"(&matrix.matrix_[i*2+1][0]),"r"(scalar)
			:"r1","d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","d10","memory"
			);
		}
*/
	}

	return matrix;
  }


  MatrixBase& MatrixBase::operator +=(const MatrixBase& matrix)
  {
	MatrixBase& result = *this;

	assert(result.getRows() == matrix.getRows());
	assert(result.getColumns() == matrix.getColumns());

    	assert((matrix.getRows()==2||matrix.getRows()==3||matrix.getRows()==6)
		&&matrix.getRows()==matrix.getColumns());
    	if(matrix.getRows()==2)
    	{
		asm volatile(
		"vld1.32		{d2},[%0]			\n\t"
		"vld1.32		{d3},[%1]			\n\t"
		"vld1.32		{d4},[%2]			\n\t"
		"vld1.32		{d5},[%3]			\n\t"
		"vadd.f32		q0,q1,q2			\n\t"
		"vst1.32		{d0},[%0]			\n\t"
		"vst1.32		{d1},[%1]			\n\t"
		::"r"(&result.matrix_[0][0]),"r"(&result.matrix_[1][0]),"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0])
		:"d0","d1","d2","d3","d4","d5","memory"
		);
    	}
	else if(matrix.getRows()==3)
	{
		asm volatile(
		"vld1.32		{d0,d1},[%0]			\n\t"
		"vld1.32		{d2,d3},[%3]			\n\t"
		"vadd.f32		q0,q0,q1			\n\t"
		"vst1.32		{d0},[%0]!			\n\t"
		"fsts			s2,[%0]				\n\t"
		"vld1.32		{d0,d1},[%1]			\n\t"
		"vld1.32		{d2,d3},[%4]			\n\t"
		"vadd.f32		q0,q0,q1			\n\t"
		"vst1.32		{d0},[%1]!			\n\t"
		"fsts			s2,[%1]				\n\t"
		"vld1.32		{d0,d1},[%2]			\n\t"
		"vld1.32		{d2,d3},[%5]			\n\t"
		"vadd.f32		q0,q0,q1			\n\t"
		"vst1.32		{d0},[%2]!			\n\t"
		"fsts			s2,[%2]				\n\t"
		::"r"(&result.matrix_[0][0]),"r"(&result.matrix_[1][0]),"r"(&result.matrix_[2][0]),"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&matrix.matrix_[2][0])
		:"d0","d1","d2","d3","memory"
		);
	}
	else if(matrix.getRows()==4)
	{
		for(int i=0;i<4;i++)
		{
			asm volatile(
			"vld1.32		{d0,d1},[%0]			\n\t"
			"vld1.32		{d2,d3},[%1]			\n\t"
			"vadd.f32		q0,q0,q1			\n\t"
			"vst1.32		{d0,d1},[%0]			\n\t"
			::"r"(&result.matrix_[i][0]),"r"(&matrix.matrix_[i][0])
			:"r1","d0","d1","d2","d3","memory"
			);
		}

	}
	else if(matrix.getRows()==6)
	{
/*
		int i=0;
		for(i=0;i<6;i++)
		{
			asm volatile(
			"vld1.32		{d0,d1,d2},[%0]			\n\t"
			"vld1.32		{d4,d5,d6},[%1]			\n\t"
			"vadd.f32		q0,q0,q2			\n\t"
			"vadd.f32		d3,d3,d6			\n\t"
			"vst1.32		{d0,d1,d2},[%0]			\n\t"
			::"r"(&result.matrix_[i][0]),"r"(&matrix.matrix_[i][0])
			:"r1","d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","d10","d11","memory"
			);
		}
*/
	}

	return result;

  }


  MatrixBase& MatrixBase::operator -=(const MatrixBase& matrix)
  {
	MatrixBase& result = *this;

	assert(result.getRows() == matrix.getRows());
	assert(result.getColumns() == matrix.getColumns());

    	assert((matrix.getRows()==2||matrix.getRows()==3||matrix.getRows()==6)
		&&matrix.getRows()==matrix.getColumns());
    	if(matrix.getRows()==2)
    	{
		asm volatile(
		"vld1.32		{d2},[%0]			\n\t"
		"vld1.32		{d3},[%1]			\n\t"
		"vld1.32		{d4},[%2]			\n\t"
		"vld1.32		{d5},[%3]			\n\t"
		"vsub.f32		q0,q1,q2			\n\t"
		"vst1.32		{d0},[%0]			\n\t"
		"vst1.32		{d1},[%1]			\n\t"
		::"r"(&result.matrix_[0][0]),"r"(&result.matrix_[1][0]),"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0])
		:"d0","d1","d2","d3","d4","d5","memory"
		);
    	}
	else if(matrix.getRows()==3)
	{
		asm volatile(
		"vld1.32		{d0,d1},[%0]			\n\t"
		"vld1.32		{d2,d3},[%3]			\n\t"
		"vsub.f32		q0,q0,q1			\n\t"
		"vst1.32		{d0},[%0]!			\n\t"
		"fsts			s2,[%0]				\n\t"
		"vld1.32		{d0,d1},[%1]			\n\t"
		"vld1.32		{d2,d3},[%4]			\n\t"
		"vsub.f32		q0,q0,q1			\n\t"
		"vst1.32		{d0},[%1]!			\n\t"
		"fsts			s2,[%1]				\n\t"
		"vld1.32		{d0,d1},[%2]			\n\t"
		"vld1.32		{d2,d3},[%5]			\n\t"
		"vsub.f32		q0,q0,q1			\n\t"
		"vst1.32		{d0},[%2]!			\n\t"
		"fsts			s2,[%2]				\n\t"
		::"r"(&result.matrix_[0][0]),"r"(&result.matrix_[1][0]),"r"(&result.matrix_[2][0]),"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&matrix.matrix_[2][0])
		:"d0","d1","d2","d3","memory"
		);

	}
	else if(matrix.getRows()==4)
	{
		for(int i=0;i<4;i++)
		{
			asm volatile(
			"vld1.32		{d0,d1},[%0]			\n\t"
			"vld1.32		{d2,d3},[%1]			\n\t"
			"vsub.f32		q0,q0,q1			\n\t"
			"vst1.32		{d0,d1},[%0]			\n\t"
			::"r"(&result.matrix_[i][0]),"r"(&matrix.matrix_[i][0])
			:"r1","d0","d1","d2","d3","memory"
			);
		}

	}
	else if(matrix.getRows()==6)
	{
/*
		int i=0;
		for(i=0;i<6;i++)
		{
			asm volatile(
			"vld1.32		{d0,d1,d2},[%0]			\n\t"
			"vld1.32		{d4,d5,d6},[%1]			\n\t"
			"vsub.f32		q0,q0,q2			\n\t"
			"vsub.f32		d3,d3,d6			\n\t"
			"vst1.32		{d0,d1,d2},[%0]			\n\t"
			::"r"(&result.matrix_[i][0]),"r"(&matrix.matrix_[i][0])
			:"r1","d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","d10","d11","memory"
			);
		}
*/
	}

	return result;
  }


  MatrixBase MatrixBase::operator +(const MatrixBase& matrix) const
  {
	MatrixBase result(*this);

	assert(result.getRows() == matrix.getRows());
	assert(result.getColumns() == matrix.getColumns());

    	assert((matrix.getRows()==2||matrix.getRows()==3||matrix.getRows()==6)
		&&matrix.getRows()==matrix.getColumns());
    	if(matrix.getRows()==2)
    	{
		asm volatile(
		"vld1.32		{d2},[%0]			\n\t"
		"vld1.32		{d3},[%1]			\n\t"
		"vld1.32		{d4},[%2]			\n\t"
		"vld1.32		{d5},[%3]			\n\t"
		"vadd.f32		q0,q1,q2			\n\t"
		"vst1.32		{d0},[%0]			\n\t"
		"vst1.32		{d1},[%1]			\n\t"
		::"r"(&result.matrix_[0][0]),"r"(&result.matrix_[1][0]),"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0])
		:"d0","d1","d2","d3","d4","d5","memory"
		);
    	}
	else if(matrix.getRows()==3)
	{
		asm volatile(
		"vld1.32		{d0,d1},[%0]			\n\t"
		"vld1.32		{d2,d3},[%3]			\n\t"
		"vadd.f32		q0,q0,q1			\n\t"
		"vst1.32		{d0},[%0]!			\n\t"
		"fsts			s2,[%0]				\n\t"
		"vld1.32		{d0,d1},[%1]			\n\t"
		"vld1.32		{d2,d3},[%4]			\n\t"
		"vadd.f32		q0,q0,q1			\n\t"
		"vst1.32		{d0},[%1]!			\n\t"
		"fsts			s2,[%1]				\n\t"
		"vld1.32		{d0,d1},[%2]			\n\t"
		"vld1.32		{d2,d3},[%5]			\n\t"
		"vadd.f32		q0,q0,q1			\n\t"
		"vst1.32		{d0},[%2]!			\n\t"
		"fsts			s2,[%2]				\n\t"
		::"r"(&result.matrix_[0][0]),"r"(&result.matrix_[1][0]),"r"(&result.matrix_[2][0]),"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&matrix.matrix_[2][0])
		:"d0","d1","d2","d3","memory"
		);
	}
	else if(matrix.getRows()==4)
	{
		for(int i=0;i<4;i++)
		{
			asm volatile(
			"vld1.32		{d0,d1},[%0]			\n\t"
			"vld1.32		{d2,d3},[%1]			\n\t"
			"vadd.f32		q0,q0,q1			\n\t"
			"vst1.32		{d0,d1},[%0]			\n\t"
			::"r"(&result.matrix_[i][0]),"r"(&matrix.matrix_[i][0])
			:"r1","d0","d1","d2","d3","memory"
			);
		}

	}
	else if(matrix.getRows()==6)
	{
/*
		int i=0;
		for(i=0;i<6;i++)
		{
			asm volatile(
			"vld1.32		{d0,d1,d2},[%0]			\n\t"
			"vld1.32		{d4,d5,d6},[%1]			\n\t"
			"vadd.f32		q0,q0,q2			\n\t"
			"vadd.f32		d3,d3,d6			\n\t"
			"vst1.32		{d0,d1,d2},[%0]			\n\t"
			::"r"(&result.matrix_[i][0]),"r"(&matrix.matrix_[i][0])
			:"r1","d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","d10","d11","memory"
			);
		}
*/
	}

	return result;
  }


  MatrixBase MatrixBase::operator -(const MatrixBase& matrix) const
  {
	MatrixBase result(*this);

	assert(result.getRows() == matrix.getRows());
	assert(result.getColumns() == matrix.getColumns());

    	assert((matrix.getRows()==2||matrix.getRows()==3||matrix.getRows()==6)
		&&matrix.getRows()==matrix.getColumns());
    	if(matrix.getRows()==2)
    	{
		asm volatile(
		"vld1.32		{d2},[%0]			\n\t"
		"vld1.32		{d3},[%1]			\n\t"
		"vld1.32		{d4},[%2]			\n\t"
		"vld1.32		{d5},[%3]			\n\t"
		"vsub.f32		q0,q1,q2			\n\t"
		"vst1.32		{d0},[%0]			\n\t"
		"vst1.32		{d1},[%1]			\n\t"
		::"r"(&result.matrix_[0][0]),"r"(&result.matrix_[1][0]),"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0])
		:"d0","d1","d2","d3","d4","d5","memory"
		);
    	}
	else if(matrix.getRows()==3)
	{
		asm volatile(
		"vld1.32		{d0,d1},[%0]			\n\t"
		"vld1.32		{d2,d3},[%3]			\n\t"
		"vsub.f32		q0,q0,q1			\n\t"
		"vst1.32		{d0},[%0]!			\n\t"
		"fsts			s2,[%0]				\n\t"
		"vld1.32		{d0,d1},[%1]			\n\t"
		"vld1.32		{d2,d3},[%4]			\n\t"
		"vsub.f32		q0,q0,q1			\n\t"
		"vst1.32		{d0},[%1]!			\n\t"
		"fsts			s2,[%1]				\n\t"
		"vld1.32		{d0,d1},[%2]			\n\t"
		"vld1.32		{d2,d3},[%5]			\n\t"
		"vsub.f32		q0,q0,q1			\n\t"
		"vst1.32		{d0},[%2]!			\n\t"
		"fsts			s2,[%2]				\n\t"
		::"r"(&result.matrix_[0][0]),"r"(&result.matrix_[1][0]),"r"(&result.matrix_[2][0]),"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&matrix.matrix_[2][0])
		:"d0","d1","d2","d3","memory"
		);
	}
	else if(matrix.getRows()==4)
	{
		for(int i=0;i<4;i++)
		{
			asm volatile(
			"vld1.32		{d0,d1},[%0]			\n\t"
			"vld1.32		{d2,d3},[%1]			\n\t"
			"vsub.f32		q0,q0,q1			\n\t"
			"vst1.32		{d0,d1},[%0]			\n\t"
			::"r"(&result.matrix_[i][0]),"r"(&matrix.matrix_[i][0])
			:"r1","d0","d1","d2","d3","memory"
			);
		}

	}
	else if(matrix.getRows()==6)
	{
/*
		int i=0;
		for(i=0;i<6;i++)
		{
			asm volatile(
			"vld1.32		{d0,d1,d2},[%0]			\n\t"
			"vld1.32		{d4,d5,d6},[%1]			\n\t"
			"vsub.f32		q0,q0,q2			\n\t"
			"vsub.f32		d3,d3,d6			\n\t"
			"vst1.32		{d0,d1,d2},[%0]			\n\t"
			::"r"(&result.matrix_[i][0]),"r"(&matrix.matrix_[i][0])
			:"r1","d0","d1","d2","d3","d4","d5","d6","memory"
			);
		}
*/
	}

	return result;
  }


  MatrixBase MatrixBase::operator *(const MatrixBase& matrix) const
  {
    	assert(this->getColumns() == matrix.getRows());

	MatrixBase result(this->getRows(),matrix.getColumns());
	
	if(result.getRows()==1)
	{
		if(result.getColumns()==2)
		{
			asm volatile(
			"vld1.32		{d2},[%0]			\n\t"
			"vld1.32		{d3},[%1]			\n\t"
			"vld1.32		{d4},[%2]			\n\t"
			"vmul.f32		d0,d3,d2[0]			\n\t"
			"vmla.f32		d0,d4,d2[1]			\n\t"
			
			"vst1.32		{d0},[%3]			\n\t"
			::"r"(&matrix_[0][0]),"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&result.matrix_[0][0])
			:"d0","d1","d2","d3","d4","memory"
			);

		}
		else if(result.getColumns()==3)
		{
			asm volatile(
			"vld1.32		{d2,d3},[%0]			\n\t"
			"vld1.32		{d4,d5},[%1]			\n\t"
			"vld1.32		{d6,d7},[%2]			\n\t"
			"vld1.32		{d8,d9},[%3]			\n\t"
			"vmul.f32		q0,q2,d2[0]			\n\t"
			"vmla.f32		q0,q3,d2[1]			\n\t"
			"vmla.f32		q0,q4,d3[0]			\n\t"
			"vst1.32		{d0},[%4]!			\n\t"
			"fsts			s2,[%4]				\n\t"
			::"r"(&matrix_[0][0]),"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&matrix.matrix_[2][0]),"r"(&result.matrix_[0][0])
			:"d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","memory"	
			);
		}
	}
	else if(result.getRows()==2)
	{
		if(result.getColumns()==1)
		{
			float vec[]={matrix.matrix_[0][0],matrix.matrix_[1][0]};
			asm volatile(
			"vld1.32		{d2},[%0]		\n\t"
			"vld1.32		{d3},[%1]		\n\t"
			"vld1.32		{d4},[%2]		\n\t"
			"vmul.f32		d2,d2,d4		\n\t"
			"vmul.f32		d3,d3,d4		\n\t"
			"vpadd.f32		d2,d2,d2		\n\t"
			"vpadd.f32		d3,d3,d3		\n\t"
			"vst2.32		{d2[0],d3[0]},[%2]	\n\t"
			::"r"(&matrix_[0][0]),"r"(&matrix_[1][0]),"r"(vec)
			:"d2","d3","d4","memory"
			);
			result.matrix_[0][0]=vec[0];
			result.matrix_[1][0]=vec[1];
		}
		else if(result.getColumns()==2)
		{
			asm volatile(
			"vld1.32		{d2},[%0]		\n\t"
			"vld1.32		{d3},[%1]		\n\t"
			"vld1.32		{d4},[%2]		\n\t"
			"vld1.32		{d5},[%3]		\n\t"
			"vmul.f32		d0,d4,d2[0]		\n\t"
			"vmla.f32		d0,d5,d2[1]		\n\t"
			"vst1.32		{d0},[%4]		\n\t"
			"vmul.f32		d0,d4,d3[0]		\n\t"
			"vmla.f32		d0,d5,d3[1]		\n\t"
			"vst1.32		{d0},[%5]		\n\t"
			::"r"(&matrix_[0][0]),"r"(&matrix_[1][0]),"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&result.matrix_[0][0]),"r"(&result.matrix_[1][0])
			:"d0","d1","d2","d3","d4","d5","memory"
			);
		}
	}
	else if(result.getRows()==3)
	{
		if(result.getColumns()==1)
		{
			float vec[]={matrix.matrix_[0][0],matrix.matrix_[1][0],matrix.matrix_[2][0]};
			
			asm volatile(
			"vld1.32	{d2,d3},[%0]			\n\t"
			"vld1.32	{d4,d5},[%1]			\n\t"
			"vld1.32	{d6,d7},[%2]			\n\t"
			"vld1.32	{d8,d9},[%3]			\n\t"
			"vmul.f32	q1,q1,q4			\n\t"
			"vmul.f32	q2,q2,q4			\n\t"
			"vmul.f32	q3,q3,q4			\n\t"
			"vpadd.f32	d2,d2,d2			\n\t"
			"vadd.f32	s0,s4,s6			\n\t"
			"vpadd.f32	d4,d4,d4			\n\t"
			"vadd.f32	s1,s8,s10			\n\t"
			"vpadd.f32	d6,d6,d6			\n\t"
			"vadd.f32	s2,s12,s14			\n\t"
			"vst1.32	{d0},[%3]!			\n\t"
			"fsts		s2,[%3]				\n\t"
			::"r"(&matrix_[0][0]),"r"(&matrix_[1][0]),"r"(&matrix_[2][0]),"r"(vec)
			:"d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","memory"
			);

			result.matrix_[0][0]=vec[0];
			result.matrix_[1][0]=vec[1];
			result.matrix_[2][0]=vec[2];
		}
		else if(result.getColumns()==3)
		{
			memcpy(&result.matrix_[0][0],&matrix_[0][0],sizeof(float)*3);
			memcpy(&result.matrix_[1][0],&matrix_[1][0],sizeof(float)*3);
			memcpy(&result.matrix_[2][0],&matrix_[2][0],sizeof(float)*3);

			asm volatile(
			"vld1.32		{d2,d3},[%3]				\n\t"
			"vld1.32		{d4,d5},[%4]				\n\t"
			"vld1.32		{d6,d7},[%5]				\n\t"
		
			"vld1.32		{d8,d9},[%0]				\n\t"
			"vmul.f32		q0,q1,d8[0]				\n\t"
			"vmla.f32		q0,q2,d8[1]				\n\t"
			"vmla.f32		q0,q3,d9[0]				\n\t"
			"vst1.32		{d0},[%0]				\n\t"
			"fsts			s2,[%0,#8]				\n\t"
		
			"vld1.32		{d8,d9},[%1]				\n\t"
			"vmul.f32		q0,q1,d8[0]				\n\t"
			"vmla.f32		q0,q2,d8[1]				\n\t"
			"vmla.f32		q0,q3,d9[0]				\n\t"
			"vst1.32		{d0},[%1]				\n\t"
			"fsts			s2,[%1,#8]				\n\t"

			"vld1.32		{d8,d9},[%2]				\n\t"
			"vmul.f32		q0,q1,d8[0]				\n\t"
			"vmla.f32		q0,q2,d8[1]				\n\t"
			"vmla.f32		q0,q3,d9[0]				\n\t"
			"vst1.32		{d0},[%2]				\n\t"
			"fsts			s2,[%2,#8]				\n\t"

			::"r"(&result.matrix_[0][0]),"r"(&result.matrix_[1][0]),"r"(&result.matrix_[2][0]),"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&matrix.matrix_[2][0])
			:"d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","memory"
			);
		}
	}
/*

	if(result.getRows()==1&&result.getColumns()==3)
	{
		asm volatile(
		"vld1.32		{d2,d3},[%0]			\n\t"
		"vld1.32		{d4,d5},[%1]			\n\t"
		"vld1.32		{d6,d7},[%2]			\n\t"
		"vld1.32		{d8,d9},[%3]			\n\t"
		"vmul.f32		q0,q2,d2[0]			\n\t"
		"vmla.f32		q0,q3,d2[1]			\n\t"
		"vmla.f32		q0,q4,d3[0]			\n\t"
		"vst1.32		{d0},[%4]!			\n\t"
		"fsts			s2,[%4]				\n\t"
		::"r"(&matrix_[0][0]),"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&matrix.matrix_[2][0]),"r"(&result.matrix_[0][0])
		:"d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","memory"	
		);

	}
    	else if(result.getRows()==3)
	{
		if(result.getColumns()==1)
		{
			float vec[]={matrix.matrix_[0][0],matrix.matrix_[1][0],matrix.matrix_[2][0]};
			
			asm volatile(
			"vld1.32	{d2,d3},[%0]			\n\t"
			"vld1.32	{d4,d5},[%1]			\n\t"
			"vld1.32	{d6,d7},[%2]			\n\t"
			"vld1.32	{d8,d9},[%3]			\n\t"
			"vmul.f32	q1,q1,q4			\n\t"
			"vmul.f32	q2,q2,q4			\n\t"
			"vmul.f32	q3,q3,q4			\n\t"
			"vpadd.f32	d2,d2,d2			\n\t"
			"vadd.f32	s0,s4,s6			\n\t"
			"vpadd.f32	d4,d4,d4			\n\t"
			"vadd.f32	s1,s8,s10			\n\t"
			"vpadd.f32	d6,d6,d6			\n\t"
			"vadd.f32	s2,s12,s14			\n\t"
			"vst1.32	{d0},[%3]!			\n\t"
			"fsts		s2,[%3]				\n\t"
			::"r"(&matrix_[0][0]),"r"(&matrix_[1][0]),"r"(&matrix_[2][0]),"r"(vec)
			:"d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","memory"
			);

			result.matrix_[0][0]=vec[0];
			result.matrix_[1][0]=vec[1];
			result.matrix_[2][0]=vec[2];
		}
		else
		{
			memcpy(&result.matrix_[0][0],&matrix_[0][0],sizeof(float)*3);
			memcpy(&result.matrix_[1][0],&matrix_[1][0],sizeof(float)*3);
			memcpy(&result.matrix_[2][0],&matrix_[2][0],sizeof(float)*3);

			asm volatile(
			"vld1.32		{d2,d3},[%3]				\n\t"
			"vld1.32		{d4,d5},[%4]				\n\t"
			"vld1.32		{d6,d7},[%5]				\n\t"
		
			"vld1.32		{d8,d9},[%0]				\n\t"
			"vmul.f32		q0,q1,d8[0]				\n\t"
			"vmla.f32		q0,q2,d8[1]				\n\t"
			"vmla.f32		q0,q3,d9[0]				\n\t"
			"vst1.32		{d0},[%0]				\n\t"
			"fsts			s2,[%0,#8]				\n\t"
		
			"vld1.32		{d8,d9},[%1]				\n\t"
			"vmul.f32		q0,q1,d8[0]				\n\t"
			"vmla.f32		q0,q2,d8[1]				\n\t"
			"vmla.f32		q0,q3,d9[0]				\n\t"
			"vst1.32		{d0},[%1]				\n\t"
			"fsts			s2,[%1,#8]				\n\t"

			"vld1.32		{d8,d9},[%2]				\n\t"
			"vmul.f32		q0,q1,d8[0]				\n\t"
			"vmla.f32		q0,q2,d8[1]				\n\t"
			"vmla.f32		q0,q3,d9[0]				\n\t"
			"vst1.32		{d0},[%2]				\n\t"
			"fsts			s2,[%2,#8]				\n\t"

			::"r"(&result.matrix_[0][0]),"r"(&result.matrix_[1][0]),"r"(&result.matrix_[2][0]),"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&matrix.matrix_[2][0])
			:"d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","memory"
			);

		}
	
	}
	else if(matrix.getRows()==4)
	{
		memcpy(&result.matrix_[0][0],&matrix_[0][0],sizeof(float)*4);
		memcpy(&result.matrix_[1][0],&matrix_[1][0],sizeof(float)*4);
		memcpy(&result.matrix_[2][0],&matrix_[2][0],sizeof(float)*4);
		memcpy(&result.matrix_[3][0],&matrix_[3][0],sizeof(float)*4);

		for(int i=0;i<4;i++)
		{
			asm volatile(
			"vld1.32		{d2,d3},[%1]			\n\t"
			"vld1.32		{d4,d5},[%2]			\n\t"
			"vld1.32		{d6,d7},[%3]			\n\t"
			"vld1.32		{d8,d9},[%4]			\n\t"
			"vld1.32		{d10,d11},[%0]			\n\t"
			"vmul.f32		q0,q1,d10[0]			\n\t"
			"vmla.f32		q0,q2,d10[1]			\n\t"
			"vmla.f32		q0,q3,d11[0]			\n\t"
			"vmla.f32		q0,q4,d11[1]			\n\t"
			"vst1.32		{d0,d1},[%0]			\n\t"
			::"r"(&result.matrix_[i][0]),"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&matrix.matrix_[2][0]),"r"(&matrix.matrix_[3][0])
			:"d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","d10","d11","memory"
			);

		}

	}
	else if(matrix.getRows()==6)
	{
		int i=0;
		memcpy(&result.matrix_[0][0],&matrix_[0][0],sizeof(float)*6);
		memcpy(&result.matrix_[1][0],&matrix_[1][0],sizeof(float)*6);
		memcpy(&result.matrix_[2][0],&matrix_[2][0],sizeof(float)*6);
		memcpy(&result.matrix_[3][0],&matrix_[3][0],sizeof(float)*6);
		memcpy(&result.matrix_[4][0],&matrix_[4][0],sizeof(float)*6);
		memcpy(&result.matrix_[5][0],&matrix_[5][0],sizeof(float)*6);

		for(i=0;i<6;i++)
		{
			asm volatile(
			"vld1.32		{d8,d9,d10},[%1]		\n\t"
			"vld1.32		{d12,d13,d14},[%2]		\n\t"
			"vld1.32		{d16,d17,d18},[%3]		\n\t"
			"vld1.32		{d20,d21,d22},[%4]		\n\t"
			"vld1.32		{d24,d25,d26},[%5]		\n\t"
			"vld1.32		{d28,d29,d30},[%6]			\n\t"
			
			"vld1.32		{d4,d5,d6},[%0]			\n\t"
			"vmul.f32		q0,q4,d4[0]			\n\t"
			"vmla.f32		q0,q6,d4[0]			\n\t"
			"vmla.f32		q0,q8,d4[0]			\n\t"
			"vmla.f32		q0,q10,d4[0]			\n\t"
			"vmla.f32		q0,q12,d4[0]			\n\t"
			"vmla.f32		q0,q14,d4[0]			\n\t"

			"vmul.f32		d2,d10,d4[0]			\n\t"
			"vmla.f32		d2,d14,d4[0]			\n\t"
			"vmla.f32		d2,d18,d4[0]			\n\t"
			"vmla.f32		d2,d22,d4[0]			\n\t"
			"vmla.f32		d2,d26,d4[0]			\n\t"
			"vmla.f32		d2,d30,d4[0]			\n\t"

			"vst1.32		{d0,d1,d2},[%0]			\n\t"
			::"r"(&result.matrix_[i][0]),"r"(&matrix.matrix_[0][0]),"r"(&matrix.matrix_[1][0]),"r"(&matrix.matrix_[2][0]),"r"(&matrix.matrix_[3][0]),"r"(&matrix.matrix_[4][0]),"r"(&matrix.matrix_[5][0])
			:"d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","d10","d11","d12","d13","d14","d15","d16","d17","d18","d19","d20","d21","d22","d23","d24","d25","d26","d27","d28","d29","d30","memory"
			);
		}
	}
*/
	return result;
  }


  bool MatrixBase::operator ==(const MatrixBase& matrix) const
  {
    MatrixBase left_mat(*this);

    if(left_mat.getRows() != matrix.getRows())
    {
      return false;
    }

    if(left_mat.getColumns() != matrix.getColumns())
    {
      return false;
    }

    for(int i = 0; i < left_mat.getRows(); i++)
    {
      for(int j = 0; j < left_mat.getColumns(); j++)
      {
        if(left_mat(i, j) != matrix(i, j))
        {
          return false;
        }
      }
    }

    return true;
  }


  static inline float det2x2(float *matrix)
  {
	float result;

	asm volatile(
	"vld1.32	{d0,d1},[%1]			\n\t"
	"vrev64.32	d1,d1				\n\t"
	"vmul.f32	d0,d1,d0			\n\t"
	"vsub.f32	s0,s0,s1			\n\t"
	"vmov		%0,s0				\n\t"
	:"=r"(result):"r"(matrix)
	:"d0","d1","memory"
	);
/*
#ifdef USE_DBG
	int i=0;
	int j=0;
	DBG_PRINT("------------det2x2----------------\n");
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			DBG_PRINT("%f,",matrix[i*2+j]);
		}
		DBG_PRINT("\n");
	}
	DBG_PRINT("result:%f\n", result);
	DBG_PRINT("----------------------------------\n");
#endif
*/
	return result;
  }
  static inline float det3x3(float matrix[])
  {
	float result;
/*
#ifdef USE_DBG
	for(int j=0;j<9;j++)
	{
		if(j!=0&&j%3==0)
			DBG_PRINT("\n");
		DBG_PRINT("%f,", matrix[j]);
	}
	DBG_PRINT("\n");
#endif
*/

	float subm11[]={
		matrix[1*3+1],matrix[1*3+2],
		matrix[2*3+1],matrix[2*3+2],
	};
	float subm12[]={
		matrix[1*3+0],matrix[1*3+2],
		matrix[2*3+0],matrix[2*3+2],
	};
	float subm13[]={
		matrix[1*3+0],matrix[1*3+1],
		matrix[2*3+0],matrix[2*3+1],
	};	

	float Avec[]={det2x2(subm11),-det2x2(subm12),det2x2(subm13)};
/*
#ifdef USE_DBG
	for(int i=0;i<3;i++)
	{
		DBG_PRINT("%f,", Avec[i]);
	}
	DBG_PRINT("\n");
#endif
*/
	asm volatile(
	"vld1.32		{d0,d1},[%1]			\n\t"
	"vld1.32		{d2,d3},[%2]			\n\t"
	"vmul.f32		q0,q0,q1			\n\t"
	"vpadd.f32		d0,d0,d0			\n\t"
	"vadd.f32		s0,s0,s2			\n\t"
	"vmov			%0,s0				\n\t"
	:"=r"(result):"r"(matrix),"r"(Avec)
	:"d0","d1","d2","d3","memory"	
	);

	return result;
  }

  static inline float det4x4(float *matrix)
  {
	float result = 0;
	float subm11[]={
		matrix[1*4+1],matrix[1*4+2],matrix[1*4+3],
		matrix[2*4+1],matrix[2*4+2],matrix[2*4+3],
		matrix[3*4+1],matrix[3*4+2],matrix[3*4+3],
	};
	float subm12[]={
		matrix[1*4+0],matrix[0*4+2],matrix[0*4+3],
		matrix[2*4+0],matrix[2*4+2],matrix[2*4+3],
		matrix[3*4+0],matrix[3*4+2],matrix[3*4+3],
	};
	float subm13[]={
		matrix[1*4+0],matrix[1*4+1],matrix[1*4+3],
		matrix[2*4+0],matrix[2*4+1],matrix[2*4+3],
		matrix[3*4+0],matrix[3*4+1],matrix[3*4+3],
	};
	float subm14[]={
		matrix[1*4+0],matrix[1*4+1],matrix[1*4+2],
		matrix[2*4+0],matrix[2*4+1],matrix[2*4+2],
		matrix[3*4+0],matrix[3*4+1],matrix[3*4+2],
	};
	float Avec[]={
		det3x3(subm11),-det3x3(subm12),	det3x3(subm13),-det3x3(subm14)
	};
	
	asm volatile(
	"vld1.32		{d0,d1},[%1]			\n\t"
	"vld1.32		{d2,d3},[%2]			\n\t"
	"vmul.f32		q0,q0,q1			\n\t"
	"vpadd.f32		d0,d0,d1			\n\t"
	"vpadd.f32		d0,d0,d0			\n\t"
	"fsts			s0,[%0]				\n\t"
	:"=r"(result):"r"(matrix),"r"(Avec)
	:"d0","d1","d2","d3","memory"
	);
	
	return result;	
  }

  static inline float det5x5(float *matrix)
  {
	float result = 0;
	float subm11[]={
		matrix[1*5+1],matrix[1*5+2],matrix[1*5+3],matrix[1*5+4],
		matrix[2*5+1],matrix[2*5+2],matrix[2*5+3],matrix[2*5+4],
		matrix[3*5+1],matrix[3*5+2],matrix[3*5+3],matrix[3*5+4],
		matrix[4*5+1],matrix[4*5+2],matrix[4*5+3],matrix[4*5+4],
	};
	float subm12[]={
		matrix[1*5+0],matrix[1*5+2],matrix[1*5+3],matrix[1*5+4],
		matrix[2*5+0],matrix[2*5+2],matrix[2*5+3],matrix[2*5+4],
		matrix[3*5+0],matrix[3*5+2],matrix[3*5+3],matrix[3*5+4],
		matrix[4*5+0],matrix[4*5+2],matrix[4*5+3],matrix[4*5+4],
	};
	float subm13[]={
		matrix[1*5+0],matrix[1*5+1],matrix[1*5+3],matrix[1*5+4],
		matrix[2*5+0],matrix[2*5+1],matrix[2*5+3],matrix[2*5+4],
		matrix[3*5+0],matrix[3*5+1],matrix[3*5+3],matrix[3*5+4],
		matrix[4*5+0],matrix[4*5+1],matrix[4*5+3],matrix[4*5+4],
	};
	float subm14[]={
		matrix[1*5+0],matrix[1*5+1],matrix[1*5+2],matrix[1*5+4],
		matrix[2*5+0],matrix[2*5+1],matrix[2*5+2],matrix[2*5+4],
		matrix[3*5+0],matrix[3*5+1],matrix[3*5+2],matrix[3*5+4],
		matrix[4*5+0],matrix[4*5+1],matrix[4*5+2],matrix[4*5+4],
	};
	float subm15[]={
		matrix[1*5+0],matrix[1*5+1],matrix[1*5+2],matrix[1*5+3],
		matrix[2*5+0],matrix[2*5+1],matrix[2*5+2],matrix[2*5+3],
		matrix[3*5+0],matrix[3*5+1],matrix[3*5+2],matrix[3*5+3],
		matrix[4*5+0],matrix[4*5+1],matrix[4*5+2],matrix[4*5+3],	
	};

	float Avec[]={
		det4x4(subm11),-det4x4(subm12),det4x4(subm13),-det4x4(subm14),det4x4(subm15),
	};
	asm volatile(
	"vld1.32		{d2,d3},[%1]			\n\t"
	"vld1.32		{d4,d5},[%2]			\n\t"
	"vmul.f32		q0,q1,q2			\n\t"
	"vpadd.f32		d0,d0,d1			\n\t"
	"vpadd.f32		d0,d0,d0			\n\t"
	"flds			s2,[%1,#16]			\n\t"
	"flds			s3,[%2,#16]			\n\t"
	"vmla.f32		s0,s2,s3			\n\t"
	"fsts			s0,[%0]				\n\t"
	:"=r"(result):"r"(matrix),"r"(Avec)
	:"d0","d1","d2","d3","d4","d5","memory"
	);

	return result;
  }
  static inline float det6x6(float *matrix)
  {
	float result = 0;
	float subm11[]={
		matrix[1*6+1],matrix[1*6+2],matrix[1*6+3],matrix[1*6+4],matrix[1*6+5],
		matrix[2*6+1],matrix[2*6+2],matrix[2*6+3],matrix[2*6+4],matrix[2*6+5],
		matrix[3*6+1],matrix[3*6+2],matrix[3*6+3],matrix[3*6+4],matrix[3*6+5],
		matrix[4*6+1],matrix[4*6+2],matrix[4*6+3],matrix[4*6+4],matrix[4*6+5],
		matrix[5*6+1],matrix[5*6+2],matrix[5*6+3],matrix[5*6+4],matrix[5*6+5],
	};
	float subm12[]={
		matrix[1*6+0],matrix[1*6+2],matrix[1*6+3],matrix[1*6+4],matrix[1*6+5],
		matrix[2*6+0],matrix[2*6+2],matrix[2*6+3],matrix[2*6+4],matrix[2*6+5],
		matrix[3*6+0],matrix[3*6+2],matrix[3*6+3],matrix[3*6+4],matrix[3*6+5],
		matrix[4*6+0],matrix[4*6+2],matrix[4*6+3],matrix[4*6+4],matrix[4*6+5],
		matrix[5*6+0],matrix[5*6+2],matrix[5*6+3],matrix[5*6+4],matrix[5*6+5],
	};
	float subm13[]={
		matrix[1*6+0],matrix[1*6+1],matrix[1*6+3],matrix[1*6+4],matrix[1*6+5],
		matrix[2*6+0],matrix[2*6+1],matrix[2*6+3],matrix[2*6+4],matrix[2*6+5],
		matrix[3*6+0],matrix[3*6+1],matrix[3*6+3],matrix[3*6+4],matrix[3*6+5],
		matrix[4*6+0],matrix[4*6+1],matrix[4*6+3],matrix[4*6+4],matrix[4*6+5],
		matrix[5*6+0],matrix[5*6+1],matrix[5*6+3],matrix[5*6+4],matrix[5*6+5],
	};
	float subm14[]={
		matrix[1*6+0],matrix[1*6+1],matrix[1*6+2],matrix[1*6+4],matrix[1*6+5],
		matrix[2*6+0],matrix[2*6+1],matrix[2*6+2],matrix[2*6+4],matrix[2*6+5],
		matrix[3*6+0],matrix[3*6+1],matrix[3*6+2],matrix[3*6+4],matrix[3*6+5],
		matrix[4*6+0],matrix[4*6+1],matrix[4*6+2],matrix[4*6+4],matrix[4*6+5],
		matrix[5*6+0],matrix[5*6+1],matrix[5*6+2],matrix[5*6+4],matrix[5*6+5],
	};
	float subm15[]={
		matrix[1*6+0],matrix[1*6+1],matrix[1*6+2],matrix[1*6+3],matrix[1*6+5],
		matrix[2*6+0],matrix[2*6+1],matrix[2*6+2],matrix[2*6+3],matrix[2*6+5],
		matrix[3*6+0],matrix[3*6+1],matrix[3*6+2],matrix[3*6+3],matrix[3*6+5],
		matrix[4*6+0],matrix[4*6+1],matrix[4*6+2],matrix[4*6+3],matrix[4*6+5],
		matrix[5*6+0],matrix[5*6+1],matrix[5*6+2],matrix[5*6+3],matrix[5*6+5],	
	};
	float subm16[]={
		matrix[1*6+0],matrix[1*6+1],matrix[1*6+2],matrix[1*6+3],matrix[1*6+4],
		matrix[2*6+0],matrix[2*6+1],matrix[2*6+2],matrix[2*6+3],matrix[2*6+4],
		matrix[3*6+0],matrix[3*6+1],matrix[3*6+2],matrix[3*6+3],matrix[3*6+4],
		matrix[4*6+0],matrix[4*6+1],matrix[4*6+2],matrix[4*6+3],matrix[4*6+4],
		matrix[5*6+0],matrix[5*6+1],matrix[5*6+2],matrix[5*6+3],matrix[5*6+4],	
	};

	float Avec[]={
		det5x5(subm11),-det5x5(subm12),det5x5(subm13),-det5x5(subm14),det5x5(subm15),-det5x5(subm16)
	};
	asm volatile(
	"vld1.32		{d4,d5,d6},[%1]			\n\t"
	"vld1.32		{d8,d9,d10},[%2]		\n\t"
	"vmul.f32		d0,d4,d8			\n\t"
	"vmla.f32		d0,d5,d9			\n\t"
	"vmla.f32		d0,d6,d10			\n\t"
	"vpadd.f32		d0,d0,d0			\n\t"
	"fsts			s0,[%0]				\n\t"
	:"=r"(result):"r"(matrix),"r"(Avec)
	:"d0","d4","d5","d6","d8","d9","d10","memory"
	);

	return result;
  }

  MatrixBase MatrixBase::inverse() const
  {
    MatrixBase result(*this);

    assert(result.getRows() == result.getColumns());

    if(result.getRows()==2)
    {
	float detm2 = 0;
	asm volatile(
	"vld1.32		{d2},[%0]			\n\t"
	"vld1.32		{d3},[%1]			\n\t"
	"vrev64.32		d4,d3				\n\t"
	"vmul.f32		d0,d4,d2			\n\t"
	"vsub.f32		s0,s0,s1			\n\t"
	"vmul.f32		s1,s0,s0			\n\t"
	"vdiv.f32		s0,s0,s1			\n\t"
	
	"vrev64.32		d5,d2				\n\t"
	"vmul.f32		q2,q2,d0[0]			\n\t"
	"vst1.32		{d4},[%2]			\n\t"
	"vst1.32		{d5},[%3]			\n\t"
	::"r"(&matrix_[0][0]),"r"(&matrix_[1][0]),"r"(&result.matrix_[0][0]),"r"(&result.matrix_[1][0])
	:"d0","d1","memory"
	);
	
    }
    else if(result.getRows()==3)
    {
	float subm11[]={result.matrix_[1][1], result.matrix_[1][2], result.matrix_[2][1],result.matrix_[2][2]};
	float subm12[]={result.matrix_[1][0], result.matrix_[1][2], result.matrix_[2][0],result.matrix_[2][2]};
	float subm13[]={result.matrix_[1][0], result.matrix_[1][1], result.matrix_[2][0],result.matrix_[2][1]};
	float subm21[]={result.matrix_[0][1], result.matrix_[0][2], result.matrix_[2][1],result.matrix_[2][2]};
	float subm22[]={result.matrix_[0][0], result.matrix_[0][2], result.matrix_[2][0],result.matrix_[2][2]};
	float subm23[]={result.matrix_[0][0], result.matrix_[0][1], result.matrix_[2][0],result.matrix_[2][1]};
	float subm31[]={result.matrix_[0][1], result.matrix_[0][2], result.matrix_[1][1],result.matrix_[1][2]};
	float subm32[]={result.matrix_[0][0], result.matrix_[0][2], result.matrix_[1][0],result.matrix_[1][2]};
	float subm33[]={result.matrix_[0][0], result.matrix_[0][1], result.matrix_[1][0],result.matrix_[1][1]};

	float matrix[9];
	memcpy(matrix,&matrix_[0][0],sizeof(float)*3);
	memcpy(matrix+3,&matrix_[1][0],sizeof(float)*3);
	memcpy(matrix+6,&matrix_[2][0],sizeof(float)*3);

	float detResult = det3x3(matrix);
	DBG_PRINT("**************************\n");
	result.matrix_[0][0]=det2x2(subm11);
	result.matrix_[0][1]=-det2x2(subm21);
	result.matrix_[0][2]=det2x2(subm31);
	result.matrix_[1][0]=-det2x2(subm12);
	result.matrix_[1][1]= det2x2(subm22);
	result.matrix_[1][2]=-det2x2(subm32);
	result.matrix_[2][0]=det2x2(subm13);
	result.matrix_[2][1]=-det2x2(subm23);
	result.matrix_[2][2]= det2x2(subm33);
	DBG_PRINT("*****************************\n");
	/*float *rows[]={&result.matrix_[0][0],&result.matrix_[1][0], &result.matrix_[2][0]};
	
	
	asm volatile(
	"mov			r1,%0					\n\t"
	"ldr			r2,[r1]					\n\t"
	"vld1.32		{d2,d3},[r2]				\n\t"
	"add			r1,r1,#4				\n\t"
	"ldr			r2,[r1]					\n\t"
	"flds			s7,[r2]					\n\t"
	"add			r2,r2,#4				\n\t"
	"vld1.32		{d4},[r2]				\n\t"
	"add			r1,r1,#4				\n\t"
	"ldr			r2,[r1]					\n\t"
	"vld1.32		{d5},[r2]!				\n\t"
	"flds			s12,[r2]				\n\t"

	"vmov			s0,%1					\n\t"
	"vmul.f32		s1,s0,s0				\n\t"
	"vdiv.f32		s0,s0,s1				\n\t"
	"vmul.f32		q1,q1,d0[0]				\n\t"
	"vmul.f32		q2,q2,d0[0]				\n\t"
	"vmul.f32		s12,s12,s0				\n\t"

	"mov			r1,%0					\n\t"
	"ldr			r2,[r1]					\n\t"
	"vst1.32		{d2},[r2]				\n\t"
	"add			r2,r2,#8				\n\t"
	"fsts			s6,[r2]					\n\t"
	"add			r1,r1,#4				\n\t"
	"ldr			r2,[r1]					\n\t"
	"fsts			s7,[r2]					\n\t"
	"add			r2,r2,#4				\n\t"
	"vst1.32		{d4},[r2]				\n\t"
	"add			r1,r1,#4				\n\t"
	"ldr			r2,[r1]					\n\t"
	"vst1.32		{d5},[r2]				\n\t"
	"add			r2,r2,#8				\n\t"
	"fsts			s12,[r2]				\n\t"
	::"r"(rows),"r"(detResult)
	:"r1","r2","d0","d1","d2","d3","d4","d5","d6","memory"
	);
*/

	asm volatile(
	"vld1.32		{d2,d3},[%0]				\n\t"
	"mov			r1,%1					\n\t"
	"flds			s7,[r1]					\n\t"
	"add			r1,r1,#4				\n\t"
	"vld1.32		{d4},[r1]				\n\t"
	"mov			r1,%2					\n\t"
	"vld1.32		{d5,d6},[r1]				\n\t"

	"vmov			s0,%3					\n\t"
	"vmul.f32		s1,s0,s0				\n\t"
	"vdiv.f32		s0,s0,s1				\n\t"
	"vmul.f32		q1,q1,d0[0]				\n\t"
	"vmul.f32		q2,q2,d0[0]				\n\t"
	"vmul.f32		s12,s12,s0				\n\t"

	"mov			r1,%0					\n\t"
	"vst1.32		{d2},[r1]				\n\t"
	"fsts			s6,[r1,#8]				\n\t"
	"mov			r1,%1					\n\t"
	"fsts			s7,[r1]					\n\t"
	"add			r1,r1,#4				\n\t"
	"vst1.32		{d4},[r1]				\n\t"
	"mov			r1,%2					\n\t"
	"vst1.32		{d5},[r1]!				\n\t"
	"fsts			s12,[r1]				\n\t"
	::"r"(&result.matrix_[0][0]),"r"(&result.matrix_[1][0]),"r"(&result.matrix_[2][0]),"r"(detResult)
	:"r1","d0","d1","d2","d3","d4","d5","d6","memory"
	);

	
    }
    else if(result.getRows()==6)
    {
	float tm[6*6];
	memcpy(&tm[0*6],&result.matrix_[0][0],sizeof(float)*6);
	memcpy(&tm[1*6],&result.matrix_[1][0],sizeof(float)*6);
	memcpy(&tm[2*6],&result.matrix_[2][0],sizeof(float)*6);
	memcpy(&tm[3*6],&result.matrix_[3][0],sizeof(float)*6);
	memcpy(&tm[4*6],&result.matrix_[4][0],sizeof(float)*6);
	memcpy(&tm[5*6],&result.matrix_[5][0],sizeof(float)*6);

	float detResult = det6x6(tm);
	int i;
	
	for(i=0;i<6;i++)
	{
		for(int j=0;j<6;j++)
		{
			float Am[5][5]={0};
			for(int m=0;m<5;m++)
			{
				for(int n=0;n<5;n++)
				{
					if(m<i&&n<j)
						Am[m][n]=result.matrix_[m][n];
					else if(m>=i&&n<j)
					{
						Am[m][n]=result.matrix_[m+1][n];
					}
					else if(m<i&&n>=j)
					{
						Am[m][n]=result.matrix_[m][n+1];
					}
					else if(m>=i&&n>=j)
					{
						Am[m][n]=result.matrix_[m+1][n+1];
					}
				}
			}
			tm[j*6+i]=((i+j)%2?-1:1)*det5x5((float *)Am);
		}
	}	
	float *p1 = tm;
	detResult = 1.0f/detResult;

	for(i=0;i<6;i++)
	{
		p1+=i*6;
		asm volatile(
		"vmov		s0,%1						\n\t"
		"vld1.32	{d2,d3,d4},[%0]					\n\t"
		"vmul.f32	q1,q1,d0[0]					\n\t"
		"vmul.f32	d4,d4,d0[0]					\n\t"
		"vst1.32	{d2,d3,d4},[%2]					\n\t"
		::"r"(p1),"r"(detResult),"r"(&result.matrix_[i][0])
		:"r1","d0","d2","d3","d4","memory"
		);
	}
    }


    return result;
  }


  MatrixBase MatrixBase::transpose() const
  {
    //assert(this->getRows() > 0);
    //assert(this->getColumns() > 0);
    assert(this->getRows()==this->getColumns());
    assert(this->getRows()==2||this->getRows()==3);

    MatrixBase result(this->getColumns(), this->getRows());
    if(this->getRows()==2)
    {
	asm volatile(
	"vld1.32	{d0},[%0]	\n\t"
	"vld1.32	{d1},[%1]	\n\t"
	"vmov		s4,s1		\n\t"
	"vmov		s1,s2		\n\t"
	"vmov		s2,s4		\n\t"
	"vst1.32	{d0},[%2]	\n\t"
	"vst1.32	{d1},[%3]	\n\t"
	::"r"(&matrix_[0][0]),"r"(&matrix_[1][0]),"r"(&result.matrix_[0][0]),"r"(&result.matrix_[1][0])
	:"d0","d1","d2","memory"
	);
    }
    if(this->getRows()==3&&this->getRows()==3)
    {
	asm volatile(
	"vld1.32		{d0,d1},[%0]		\n\t"
	"vld1.32		{d2,d3},[%1]		\n\t"
	"vld1.32		{d4,d5},[%2]		\n\t"
	"vmov			s16,s0			\n\t"
	"vmov			s17,s4			\n\t"
	"vmov			s18,s8			\n\t"

	"vmov			s20,s1			\n\t"
	"vmov			s21,s5			\n\t"
	"vmov			s22,s9			\n\t"

	"vmov			s24,s2			\n\t"
	"vmov			s25,s6			\n\t"
	"vmov			s26,s10			\n\t"
	"vst1.32		{d8},[%3]!		\n\t"
	"vst1.32		{d10},[%4]!		\n\t"
	"vst1.32		{d12},[%5]!		\n\t"
	"fsts			s18,[%3]		\n\t"
	"fsts			s22,[%4]		\n\t"
	"fsts			s26,[%5]		\n\t"
	
	::"r"(&matrix_[0][0]),"r"(&matrix_[1][0]),"r"(&matrix_[2][0]),"r"(&result.matrix_[0][0]),"r"(&result.matrix_[1][0]),"r"(&result.matrix_[2][0])
	:"d0","d1","d2","d3","d4","d5","d6","d7","d8","d9","d10","d11","d12","d13","memory"
	);
    }



    for(int i = 0; i < result.getRows(); i++)
    {
      for(int j = 0; j < result.getColumns(); j++)
      {
        result(i, j) = matrix_[j][i];
      }
    }

    return result;
  }


  float MatrixBase::determinant() const
  {
    assert(getRows() == getColumns());
    assert(getRows()==2||getRows()==3||getRows()==6);
    float matrix[16];
    if(getRows()==2)
    {

	memcpy(matrix,&matrix_[0][0],sizeof(float)*2);
	memcpy(matrix+2,&matrix_[1][0],sizeof(float)*2);
	return det2x2(matrix);
    }
    else if(getRows()==3)
    {
/*
#ifdef USE_DBG
	int i=0;
	int j=0;

	DBG_PRINT("------------------------------------\n");
	for(i=0;i<3;i++)
	{
		DBG_PRINT("address:0x%x\n",(unsigned int)&matrix_[i][0]);
		for(j=0;j<3;j++)
		{
			DBG_PRINT("%f,",(&matrix_[i][0])[j]);
		}
		DBG_PRINT("\n");
	}
	DBG_PRINT("--------------------------------------\n");
	for(i=0;i<3;i++)
	{
		DBG_PRINT("address:0x%x\n",&matrix_[i]);
		for(j=0;j<3;j++)
		{
			DBG_PRINT("%f,",((float *)&(matrix_[i]))[j]);
		}
		DBG_PRINT("\n");
	}
	DBG_PRINT("-----------------------------------------\n");
	float *p = (float *)&matrix_[0][0];
	for(i=0;i<3;i++)
	{
		DBG_PRINT("address:0x%x\n",&p[i*3]);
		for(j=0;j<3;j++)
		{
			DBG_PRINT("%f,",p[i*3+j]);
		}
		DBG_PRINT("\n");
	}
	DBG_PRINT("-------------------------------------------\n");

#endif
*/
	
	memcpy(matrix+0,&matrix_[0][0],sizeof(float)*3);
	memcpy(matrix+3,&matrix_[1][0],sizeof(float)*3);
	memcpy(matrix+6,&matrix_[2][0],sizeof(float)*3);

	float result = det3x3(matrix);
	return result;
    }
    else if(getRows()==6)
    {

	memcpy(matrix, &matrix_[0][0],sizeof(float)*4);
	memcpy(matrix, &matrix_[1][0],sizeof(float)*4);
	memcpy(matrix, &matrix_[2][0],sizeof(float)*4);
	return det6x6(matrix);
    }


    return 0;
  }

}  // namespace la  
}  // namespace sgbot

#endif  // _USE_ARM_NEON_
