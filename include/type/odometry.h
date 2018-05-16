#ifndef _TYPE_ODOMETRY_H_
#define _TYPE_ODOMETRY_H_
#include "pose2d.h"
#include "velocity2d.h"
namespace sgbot{
	class Odometry{
	public:
		Odometry(){

		}
		Odometry(Pose2D pose2d_,Velocity2D velocity2d_):pose2d(pose2d_),velocity2d(velocity2d_){

		}
	    Odometry& operator=(const Odometry& p)
	    {
	    	this->pose2d = p.pose2d;
	    	this->velocity2d = p.velocity2d;
	        return *this;
	    }
		Pose2D pose2d;
		Velocity2D velocity2d;
	};
}


#endif