#include <std-math/math.h>
#include <linear-algebra/vector.h>
#include <linear-algebra/matrix.h>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include <time.h>
#include <unistd.h>
#ifdef WIN32
#include <time.h>
#else
#include <sys/time.h>
#include <sys/resource.h>
#endif
#define randf()	(rand() / (RAND_MAX + 1.0f))

using namespace std;


struct	test1_s {
	const char*	name;
	float 		(*func)(float);	//the function
	float 		rng0, rng1;
	int			num;
	float 		val;
	float 		result;
	int			time;				//time to execute num functions;
};

struct	test2_s {
	const char*	name;
	float 		(*func)(float, float);	//the function
	float 		rng0, rng1;
	int			num;
	float		val1,val2;
	float		result;
	int			time;				//time to execute num functions;
};

typedef struct test1_s test1_t;
typedef struct test2_s test2_t;


test1_t test1[]={
	{"fabs		",sgbot::math::fabs, -100, 100, 500000, -1.3},
	{"exp		",sgbot::math::exp, 1,1000,	500000,	2.4},
	{"floor		",sgbot::math::floor,1,1000,	500000,	1.4},
	{"ceil		",sgbot::math::ceil, 1,1000,	500000,	2.7},
	{"log		",sgbot::math::log, 1,1000,	500000,	10},
	{"log10		",sgbot::math::log10, 1, 1000, 	500000,	3},
	{"sqrt		",sgbot::math::sqrt, 1, 1000,	500000,	100},
	{"acos		",sgbot::math::acos, -1,1,	500000,	0.708},
	{"asin		",sgbot::math::asin, -1, 1,	500000,	0.708},
	{"atan		",sgbot::math::atan, 1, 1000,	500000,	1},
	{"cos		",sgbot::math::cos, -M_PI,M_PI,	500000,	M_PI/4},
	{"sin		",sgbot::math::sin, -M_PI, M_PI, 	500000, M_PI/4},
	{"tan		",sgbot::math::tan, -M_PI/4,M_PI/4,	500000, M_PI/4},
	{"cosh		",sgbot::math::cosh, 1,1000,		500000, 5},
	{"sinh		",sgbot::math::sinh, 1,1000,		500000, 5},
	{"tanh		",sgbot::math::tanh, 1,1000,		500000,	5},
};

test2_t test2[]={
	{"pow		",sgbot::math::pow, 1, 1000,		500000, 10,	3},
	{"atan2		",sgbot::math::atan2, 1,1000,		500000,	2,	-1},
	{"hypot		",sgbot::math::hypot, 1, 1000,		500000,	3,	4},
	{"fmod		",sgbot::math::fmod, 1, 1000,		500000, 5.6,	1.3},
};


void test_vectorfunc(void)
{
	int i=0;
	sgbot::la::Vector<float, 2>v2;
	sgbot::la::Vector<float, 3>v3;
	sgbot::la::Vector<float, 6>v6;
	
	v2(0)=-0.21;
	v2(1)=-2.35;

	v3(0)=2.29;
	v3(1)=1.93;
	v3(2)=-3.17;
	
	v6(0)=-3.75;
	v6(1)=-2.04;
	v6(2)=-2.81;
	v6(3)=-0.04;
	v6(4)=-3.84;
	v6(5)=2.16;
	
/*

	v2(0)=10*randf()-5;
	v2(1)=10*randf()-5;
	
	v3(0)=10*randf()-5;
	v3(1)=10*randf()-5;
	v3(2)=10*randf()-5;

	v6(0)=10*randf()-5;
	v6(1)=10*randf()-5;
	v6(2)=10*randf()-5;
	v6(3)=10*randf()-5;
	v6(4)=10*randf()-5;
	v6(5)=10*randf()-5;
*/
	std::cout<<"Vector test"<<endl;
	

	int testnum = 500000;
	sgbot::la::Vector<float, 2>vt2;
	sgbot::la::Vector<float, 3>vt3;
	sgbot::la::Vector<float, 6>vt6;
	
	std::cout<<"test vectors:"<<endl;
	std::cout<<"v2:,"<<v2<<endl;
	std::cout<<"v3:,"<<v3<<endl;
	std::cout<<"v6:,"<<v6<<endl;

	struct timeval tm_val;
	int last_time = 0;

	std::cout<<"function,result,num,time"<<endl;
//-------------*=--------------------

	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt2 = v2;
		vt2*=10;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v2*=10: "<<vt2<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v2<<"\""<<"*="<<10<<","<<"\""<<vt2<<"\","<<testnum<<","<<last_time<<endl;

	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt3 = v3;
		vt3*=10;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v3*=10: "<<vt3<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v3<<"\""<<"*="<<10<<","<<"\""<<vt3<<"\","<<testnum<<","<<last_time<<endl;


	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt6 = v6;
		vt6*=10;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v6*=10: "<<vt6<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v6<<"\""<<"*="<<10<<","<<"\""<<vt6<<"\","<<testnum<<","<<last_time<<endl;

//-------------/=--------------------
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt2 = v2;
		vt2/=10;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v2/=10: "<<vt2<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v2<<"\""<<"/="<<10<<","<<"\""<<vt2<<"\","<<testnum<<","<<last_time<<endl;

	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt3 = v3;
		vt3/=10;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v3/=10: "<<vt3<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v3<<"\""<<"/="<<10<<","<<"\""<<vt3<<"\","<<testnum<<","<<last_time<<endl;
	


	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt6 = v6;
		vt6/=10;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v6/=10: "<<vt6<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v6<<"\""<<"/="<<10<<","<<"\""<<vt6<<"\","<<testnum<<","<<last_time<<endl;

//-------------*--------------------
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt2=v2*10;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v2*10: "<<vt2<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v2<<"\""<<"*"<<10<<","<<"\""<<vt2<<"\","<<testnum<<","<<last_time<<endl;


	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt3=v3*10;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v3*10: "<<vt3<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v3<<"\""<<"*"<<10<<","<<"\""<<vt3<<"\","<<testnum<<","<<last_time<<endl;


	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt6=v6/10;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v6*10: "<<vt6<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v6<<"\""<<"*"<<10<<","<<"\""<<vt6<<"\","<<testnum<<","<<last_time<<endl;

//-------------/--------------------
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt2=v2/10;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v2/10: "<<vt2<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v2<<"\""<<"/"<<10<<","<<"\""<<vt2<<"\","<<testnum<<","<<last_time<<endl;

	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt3=v3/10;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v3/10: "<<vt3<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v3<<"\""<<"/"<<10<<","<<"\""<<vt3<<"\","<<testnum<<","<<last_time<<endl;


	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt6=v6/10;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v6/10: "<<vt6<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v6<<"\""<<"/"<<10<<","<<"\""<<vt6<<"\","<<testnum<<","<<last_time<<endl;

//-------------+=--------------------
	
	sgbot::la::Vector<float, 2> _vt2;
	sgbot::la::Vector<float, 3> _vt3;
	sgbot::la::Vector<float, 6> _vt6;
	_vt2(0)=1;
	_vt2(1)=2;
	
	_vt3(0)=1;
	_vt3(1)=2;
	_vt3(2)=3;
	
	_vt6(0)=1;
	_vt6(1)=2;
	_vt6(2)=3;
	_vt6(3)=4;
	_vt6(4)=5;	
	_vt6(5)=6;
		

	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt2 = v2;
		vt2+=_vt2;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v2+=_vt2: "<<vt2<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v2<<"+="<<_vt2<<"\",\""<<vt2<<"\","<<testnum<<","<<last_time<<endl;

	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt3 = v3;
		vt3+=_vt3;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v3+=_vt3: "<<vt3<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v3<<"+="<<_vt3<<"\""<<","<<"\""<<vt3<<"\","<<testnum<<","<<last_time<<endl;


	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt6=v6;
		vt6+=_vt6;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v6+=_vt6: "<<vt6<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v6<<"+="<<_vt6<<"\""<<","<<"\""<<vt6<<"\","<<testnum<<","<<last_time<<endl;
//-------------  -=--------------------
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt2 = v2;
		vt2-=_vt2;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v2-=_vt2: "<<vt2<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v2<<"-="<<_vt2<<"\""<<","<<"\""<<vt2<<"\","<<testnum<<","<<last_time<<endl;

	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt3 = v3;
		vt3-=_vt3;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v3-=_vt3: "<<vt3<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v3<<"-="<<_vt3<<"\""<<","<<"\""<<vt3<<"\","<<testnum<<","<<last_time<<endl;
	


	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt6=v6;
		vt6-=_vt6;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v6-=_vt6: "<<vt6<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v6<<"-="<<_vt6<<"\""<<","<<"\""<<vt6<<"\","<<testnum<<","<<last_time<<endl;

//-------------=--------------------
	
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt2 = v2+_vt2;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v2+_vt2: "<<vt2<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v2<<"+"<<_vt2<<"\""<<","<<"\""<<vt2<<"\","<<testnum<<","<<last_time<<endl;

	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt3 = v3+_vt3;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v3+_vt3: "<<vt3<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v3<<"+"<<_vt3<<"\""<<","<<"\""<<vt3<<"\","<<testnum<<","<<last_time<<endl;


	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt6 = v6+_vt6;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v6+_vt6: "<<vt6<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v6<<"+"<<_vt6<<"\""<<","<<"\""<<vt6<<"\","<<testnum<<","<<last_time<<endl;

//-------------  -=--------------------
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt2=v2-_vt2;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v2-_vt2: "<<vt2<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v2<<"-"<<_vt2<<"\""<<","<<"\""<<vt2<<"\","<<testnum<<","<<last_time<<endl;

	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		
		vt3=v3-_vt3;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v3-_vt3: "<<vt3<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v3<<"-"<<_vt3<<"\""<<","<<"\""<<vt3<<"\","<<testnum<<","<<last_time<<endl;


	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		vt6=v6-_vt6;
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v6-vt6: "<<vt6<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v6<<"-"<<_vt6<<"\","<<"\""<<vt6<<"\","<<testnum<<","<<last_time<<endl;

//------------dot-----------------
	float rv;
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		rv=v2.dot(_vt2);
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v2 dot _vt2: "<<rv<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v2<<"dot"<<_vt2<<"\","<<rv<<","<<testnum<<","<<last_time<<endl;


	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		
		rv=v3.dot(_vt3);
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v3 dot vt3: "<<rv<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v3<<"dot"<<_vt3<<"\","<<rv<<","<<testnum<<","<<last_time<<endl;


	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		rv=v6.dot(_vt6);
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v6 dot vt6: "<<rv<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v6<<"dot"<<_vt6<<"\","<<rv<<","<<testnum<<","<<last_time<<endl;

//------------cross-----------------

	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	for(i=0;i<testnum;i++)
	{
		
		vt3=v3.cross(_vt3);
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"v3 cross vt3: "<<vt3<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v3<<"cross"<<_vt3<<"\",\""<<vt3<<"\","<<testnum<<","<<last_time<<endl;
	
//------------normalize-----------------
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	
	for(i=0;i<testnum;i++)
	{
		vt2 = v2;
		vt2.normalize();
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"vt2 normalize: "<<vt2<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v2<<"normalize \",\""<<vt2<<"\","<<testnum<<","<<last_time<<endl;

	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	vt3 = v3;
	for(i=0;i<testnum;i++)
	{
		vt3 = v3;
		vt3.normalize();
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"vt3 normalize: "<<vt3<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v3<<"normalize \",\""<<vt3<<"\","<<testnum<<","<<last_time<<endl;


	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec;
	vt6 = v6;
	for(i=0;i<testnum;i++)
	{
		vt6 = v6;
		vt6.normalize();
	}
	gettimeofday(&tm_val, NULL);
	last_time = tm_val.tv_sec*1000000+tm_val.tv_usec-last_time;
	//std::cout<<"vt6 normalize: "<<vt6<<endl;
	//std::cout<<"time="<<last_time<<endl;
	std::cout<<"\""<<v6<<"normalize \",\""<<vt6<<"\","<<testnum<<","<<last_time<<endl;
}


void test_matrixfunc(void)
{
	int testnum = 500000;
	struct timeval tmval;
	int last_time = 0;
	int i=0;

	sgbot::la::Matrix<float, 3,3>a33;
	sgbot::la::Matrix<float, 3,1>a31;
	sgbot::la::Matrix<float, 1,3>a13;

	a33(0,0)=1.0f;
	a33(0,1)=2.0f;
	a33(0,2)=3.0f;
	a33(1,0)=6.0f;
	a33(1,1)=5.0f;
	a33(1,2)=4.0f;
	a33(2,0)=8.0f;
	a33(2,1)=7.0f;
	a33(2,2)=9.0f;

	
	sgbot::la::Matrix<float,3,3>at33;
	sgbot::la::Matrix<float,3,1>at31;
	sgbot::la::Matrix<float,1,3>at13;


	float result;
	std::cout<<"Matrix test"<<endl;
	std::cout<<"function,reuslt,num,time"<<endl;
//---------------det-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	
	for(i=0;i<testnum;i++)
	{
		result=a33.determinant();
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"det: "<<result<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;
	std::cout<<"\"det: "<<a33<<"\","<<result<<","<<testnum<<","<<last_time<<endl;
//---------------inverse-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	
	for(i=0;i<testnum;i++)
	{
		at33=a33.inverse();
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"inverse: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\" inverse: "<<a33<<"\",\""<<at33<<"\","<<testnum<<","<<last_time<<endl;

//---------------transpose-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	
	for(i=0;i<testnum;i++)
	{
		at33=a33.transpose();
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"transpose: "<<at33<<std::endl;
	//std::cout<<"time:"<<last_time<<endl;	
	std::cout<<"\"transpose: "<<a33<<"\",\""<<at33<<"\","<<testnum<<","<<last_time<<endl;
	
//---------------multi-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	sgbot::la::Matrix<float, 3,3> rm33;
	for(i=0;i<testnum;i++)
	{
		rm33=a33*at33;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"multi: "<<rm33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a33<<" multi "<<at33<<"\",\""<<rm33<<"\","<<testnum<<","<<last_time<<endl;
	

//---------------+=1-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	for(i=0;i<testnum;i++)
	{
		at33 = a33;
		at33 += 1;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"+=1: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a33<<" +=1 \",\""<<at33<<"\","<<testnum<<","<<last_time<<endl;
//---------------  -=1-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	for(i=0;i<testnum;i++)
	{
		at33 = a33;
		at33 -= 1;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"+=1: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a33<<" -=1 \",\""<<at33<<"\","<<testnum<<","<<last_time<<endl;
//---------------  *=2-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	for(i=0;i<testnum;i++)
	{
		at33 = a33;
		at33 *= 2;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"+=1: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a33<<" *=2 \",\""<<at33<<"\","<<testnum<<","<<last_time<<endl;

//---------------  /=2-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	for(i=0;i<testnum;i++)
	{
		at33 = a33;
		at33 /= 2;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"+=1: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a33<<" /=2 \",\""<<at33<<"\","<<testnum<<","<<last_time<<endl;


//---------------+1-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	for(i=0;i<testnum;i++)
	{
		at33 = a33+1;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"+1: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a33<<" +1 \",\""<<at33<<"\","<<testnum<<","<<last_time<<endl;
//--------------- -1-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	for(i=0;i<testnum;i++)
	{
		at33 = a33-1;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"-1: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a33<<" -1 \",\""<<at33<<"\","<<testnum<<","<<last_time<<endl;
//--------------- x2-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	for(i=0;i<testnum;i++)
	{
		at33 = a33*2;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"x2: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a33<<" x2 \",\""<<at33<<"\","<<testnum<<","<<last_time<<endl;

//--------------- /2-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	for(i=0;i<testnum;i++)
	{
		at33 = a33/2;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"/2: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a33<<" /2 \",\""<<at33<<"\","<<testnum<<","<<last_time<<endl;

//------------------ +=m----------------------------
	sgbot::la::Matrix<float, 3, 3>_a33;
	_a33(0,0)=1;
	_a33(0,1)=2;
	_a33(0,2)=1.2;
	_a33(1,0)=2.1;
	_a33(1,1)=4.2f;
	_a33(1,2)=4.3;
	_a33(2,0)=0.2;
	_a33(2,1)=5.2;
	_a33(2,2)=2.5;

	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	
	for(i=0;i<testnum;i++)
	{
		at33 = a33;
		at33 += _a33;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"/2: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a33<<" += "<<_a33<<"\",\""<<at33<<"\","<<testnum<<","<<last_time<<endl;	

//------------------ -=m----------------------------

	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	
	for(i=0;i<testnum;i++)
	{
		at33 = a33;
		at33 -= _a33;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"/2: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a33<<" -= "<<_a33<<"\",\""<<at33<<"\","<<testnum<<","<<last_time<<endl;	

//------------------ +m----------------------------

	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	at33 = a33;
	for(i=0;i<testnum;i++)
	{
		at33 = a33 + _a33;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"/2: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a33<<" + "<<_a33<<"\",\""<<at33<<"\","<<testnum<<","<<last_time<<endl;	

//------------------ -m----------------------------

	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	at33 = a33;
	for(i=0;i<testnum;i++)
	{
		at33 = a33 - _a33;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"/2: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a33<<" -"<<_a33<<"\",\""<<at33<<"\","<<testnum<<","<<last_time<<endl;	

//--------------multi---------------------------------
	a31(0,0)=1.0f;
	a31(1,0)=2.0f;
	a31(2,0)=3.0f;

	a13(0,0)=1.0f;
	a13(0,1)=2.0f;
	a13(0,2)=3.0f;
	sgbot::la::Matrix<float, 3,1> ra31;
	sgbot::la::Matrix<float, 1,3> ra13;

	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	for(i=0;i<testnum;i++)
	{
		ra31= a33*a31;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"a33*a31: "<<ra31<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a33<<" * "<<a31<<"\",\""<<ra31<<"\","<<testnum<<","<<last_time<<endl;
	
//-----------------------------------------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	for(i=0;i<testnum;i++)
	{
		ra13= a13*a33;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"a31*a33: "<<ra13<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a13<<" * "<<a33<<" \",\""<<ra13<<"\","<<testnum<<","<<last_time<<endl;

//--------------------------------------------------------

}

void test_matrix2x2(void)
{
	sgbot::la::Matrix<float, 2,2>a22;
	sgbot::la::Matrix<float, 2,1>a21;
	sgbot::la::Matrix<float, 1,2>a12;
	a22(0,0)=1.0f;
	a22(0,1)=5.0f;
	a22(1,0)=3.0f;
	a22(1,1)=6.0f;

	a21(0,0)=2.1f;
	a21(1,0)=1.5f;

	a12(0,0)=1.6f;
	a12(0,1)=4.0f;

	sgbot::la::Matrix<float, 2,2>at22;

	float result;
	struct timeval tmval;
	int last_time = 0;
	int i=0;
	int testnum = 500000;
	
	std::cout<<"function,reuslt,num,time"<<endl;
//---------------det-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	
	for(i=0;i<testnum;i++)
	{
		result=a22.determinant();
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"det: "<<result<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;
	std::cout<<"\"det: "<<a22<<"\","<<result<<","<<testnum<<","<<last_time<<endl;
//---------------inverse-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	
	for(i=0;i<testnum;i++)
	{
		at22=a22.inverse();
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"inverse: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\" inverse: "<<a22<<"\",\""<<at22<<"\","<<testnum<<","<<last_time<<endl;

//---------------transpose-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	
	for(i=0;i<testnum;i++)
	{
		at22=a22.transpose();
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"transpose: "<<at33<<std::endl;
	//std::cout<<"time:"<<last_time<<endl;	
	std::cout<<"\"transpose: "<<a22<<"\",\""<<at22<<"\","<<testnum<<","<<last_time<<endl;
	
//---------------multi-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	sgbot::la::Matrix<float, 2,2> rm22;
	for(i=0;i<testnum;i++)
	{
		rm22=a22*at22;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"multi: "<<rm33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a22<<" multi "<<at22<<"\",\""<<rm22<<"\","<<testnum<<","<<last_time<<endl;
	
//---------------+1-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	for(i=0;i<testnum;i++)
	{
		at22 = a22+1;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"+1: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a22<<" +1 \",\""<<at22<<"\","<<testnum<<","<<last_time<<endl;
//--------------- -1-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	for(i=0;i<testnum;i++)
	{
		at22 = a22-1;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"-1: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a22<<" -1 \",\""<<at22<<"\","<<testnum<<","<<last_time<<endl;
//--------------- x2-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	for(i=0;i<testnum;i++)
	{
		at22 = a22*2;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"x2: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a22<<" x2 \",\""<<at22<<"\","<<testnum<<","<<last_time<<endl;

//--------------- /2-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	for(i=0;i<testnum;i++)
	{
		at22 = a22/2;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"/2: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a22<<" /2 \",\""<<at22<<"\","<<testnum<<","<<last_time<<endl;

//---------------+=1-----------------------

	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;

	
	for(i=0;i<testnum;i++)
	{
		at22 = a22;
		at22 += 1;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"+1: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a22<<" +=1 \",\""<<at22<<"\","<<testnum<<","<<last_time<<endl;
//--------------- -=1-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	for(i=0;i<testnum;i++)
	{
		at22 = a22;
		at22 -= 1;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"-1: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a22<<" -=1 \",\""<<at22<<"\","<<testnum<<","<<last_time<<endl;
//--------------- x=2-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	for(i=0;i<testnum;i++)
	{
		at22 = a22;
		at22 *= 2;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"x2: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a22<<" x=2 \",\""<<at22<<"\","<<testnum<<","<<last_time<<endl;

//--------------- /=2-----------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	for(i=0;i<testnum;i++)
	{
		at22 = a22;
		at22 /= 2;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"/2: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a22<<" /=2 \",\""<<at22<<"\","<<testnum<<","<<last_time<<endl;


//------------------ +=m----------------------------
	sgbot::la::Matrix<float, 2, 2>_a22;
	_a22(0,0)=1.1;
	_a22(0,1)=2.6;
	_a22(1,0)=2.1;
	_a22(1,1)=4.2f;

	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	
	for(i=0;i<testnum;i++)
	{
		at22 = a22;
		at22 += _a22;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"/2: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a22<<" += "<<_a22<<"\",\""<<at22<<"\","<<testnum<<","<<last_time<<endl;	

//------------------ -=m----------------------------

	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	
	for(i=0;i<testnum;i++)
	{
		at22 = a22;
		at22 -= _a22;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"/2: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a22<<" -  = "<<_a22<<"\",\""<<at22<<"\","<<testnum<<","<<last_time<<endl;	

//------------------ +m----------------------------

	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	
	for(i=0;i<testnum;i++)
	{
		at22 = a22 + _a22;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"/2: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a22<<" + "<<_a22<<"\",\""<<at22<<"\","<<testnum<<","<<last_time<<endl;	

//------------------ -m----------------------------

	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;

	for(i=0;i<testnum;i++)
	{
		at22 = a22 - _a22;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"/2: "<<at33<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a22<<" -"<<_a22<<"\",\""<<at22<<"\","<<testnum<<","<<last_time<<endl;	

//--------------multi---------------------------------
	a21(0,0)=1.0f;
	a21(1,0)=2.0f;


	a12(0,0)=1.0f;
	a12(0,1)=2.0f;

	sgbot::la::Matrix<float, 2,1> ra21;
	sgbot::la::Matrix<float, 1,2> ra12;

	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	for(i=0;i<testnum;i++)
	{
		ra21= a22*a21;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"a33*a31: "<<ra31<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a22<<" * "<<a21<<" \",\""<<ra21<<"\","<<testnum<<","<<last_time<<endl;
	
//-----------------------------------------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	for(i=0;i<testnum;i++)
	{
		ra12= a12*a22;
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;
	
	//std::cout<<"a31*a33: "<<ra13<<std::endl;
	//std::cout<<"time: "<<last_time<<endl;	
	std::cout<<"\""<<a12<<" * "<<a22<<" \",\""<<ra12<<"\","<<testnum<<","<<last_time<<endl;

//--------------------------------------------------------


}
/*
void test_transform(void)
{
	struct timeval tmval;
	int last_time = 0;
	int testnum = 500000;
	int i=0;
	
	sgbot::tf::Transform2D tf1(1.0f,2.0f,M_PI/4, 1.0f);
	sgbot::Pose2D p1(0.5f,0.5f,M_PI/8);

	std::cout << "p1:"<<p1;

	std::cout<<"P1 in TF2"<<tf2.transform(p1);

	sgbot::Pose2D p2;	

	std::cout<<"operation,result,num,time"<<endl;

//---------------(tf1*tf2).transform(p1)-------------------
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;

	for(i=0;i<testnum;i++)
	{
		p2 = (tf1*tf2).transform(p1);
	}
	gettimeofday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec-last_time;

	std::cout<<"(tf1*tf2).transform(p1),\""<<p2<<"\","<<testnum<<","<<last_time<<endl;

//--------------(tf1*tf2.inverse()).transform(p1)----------------

	gettimeoday(&tmval, NULL);
	last_time = tmval.tv_sec*1000000+tmval.tv_usec;
	
	for(i=0;i<testnum;i++)
	{
		p2 = (tf1*tf1.inverse()).transform(p1);
	}
	std::cout<<"(tf1*tf1.inverse()).transform(p1),\""<<p2<<"\","<<testnum<<",",last_time<<endl
}
*/
void test_mathfunc1(test1_t *tst)
{
	float x;
	float dx = (tst->rng1-tst->rng0)/((float)tst->num);
	
	struct timeval tmval;
	gettimeofday(&tmval,NULL);
	tst->time = tmval.tv_sec * 1000000 + tmval.tv_usec;
	
	for(x=tst->rng0;x<tst->rng1;x+=dx)
	{
		(tst->func)((float)x);
	}
	gettimeofday(&tmval,NULL);
	tst->time = tmval.tv_sec * 1000000 + tmval.tv_usec - tst->time;
	tst->result = (tst->func)(tst->val);
}

void test_mathfunc2(test2_t *tst)
{
	float x, y;
	float rng = tst->rng1-tst->rng0;
	float d = (rng*rng)/((float)tst->num);

	struct timeval tmval;
	gettimeofday(&tmval, NULL);
	tst->time = tmval.tv_sec * 1000000 + tmval.tv_usec;
	for(y=(tst->rng0);y<(tst->rng1);y+=d)
	{
		for(x=(tst->rng0);x<(tst->rng1);x+=d)
		{
			tst->func((float)x, y);
		}
	
	}
	gettimeofday(&tmval,NULL);
	tst->time = tmval.tv_sec * 1000000 + tmval.tv_usec - tst->time;
	tst->result = tst->func(tst->val1, tst->val2);
}


int main(void)
{

	srand(time(NULL));
	int i=0;
	float theta = sgbot::math::atan2(1, 1);
	printf("atan2(1,1)=%f\n", theta);
	theta = sgbot::math::atan2(0.00235682,0.00735271);
	printf("atan2(0.00235682,0.00735271)=%f\n", theta);


	printf("name,range,num,time,val,result\n");
	for(i=0;i<sizeof(test1)/sizeof(test1[0]);i++)
	{
		test_mathfunc1(&test1[i]);
		printf("%s,", test1[i].name);
		printf("\"[%0.2f, %0.2f]\",", test1[i].rng0, test1[i].rng1);
		printf("%i,",test1[i].num);
		printf("%d,", test1[i].time);
		printf("%f,", test1[i].val);
		printf("%f", test1[i].result);
		printf("\n");
	}
	printf("name,range,num,time,val1,val2,result\n");
	for(i=0;i<sizeof(test2)/sizeof(test2[0]);i++)
	{
		test_mathfunc2(&test2[i]);
		printf("%s,", test2[i].name);
		printf("\"[%0.2f, %0.2f]\",", test2[i].rng0, test2[i].rng1);
		printf("%i,",test2[i].num);
		printf("%d,", test2[i].time);
		printf("%f,%f,%f",test2[i].val1,test2[i].val2,test2[i].result);
		printf("\n");
	}

	test_vectorfunc();
	test_matrixfunc();
	test_matrix2x2();

	return 0;
}



