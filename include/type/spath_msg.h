#ifndef __TYPE_SPATH_MSG_H__
#define __TYPE_SPATH_MSG_H__

#include <common/exception.h>

namespace sgbot{
    class SpathMsg
    {
    public:
        SpathMsg()
	{
            this->theta = 0;
	    this->dir = 0;
	}
	virtual ~SpathMsg(){}

	void setValue(float theta, int dir)
	{
            this->theta = theta;
            this->dir = dir;
	}

	void getValue(float &theta, int &dir) const
        {
            theta = this->theta;
            dir = this->dir;
        }

    public:
	float theta;
	int dir;
    };
}


#endif
