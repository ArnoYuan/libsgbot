#ifndef __TYPE_SPATH_MSG_H__
#define __TYPE_SPATH_MSG_H__

#include <common/exception.h>

namespace sgbot{
    class SpathMsg
    {
    public:
        SpathMsg(float theta, int dir)
	{
            theta_ = theta;
	    dir_ = dir;
	}
	virtual SpathMsg(){}

	void setValue(float theta, int dir)
	{
            theta_ = theta;
            dir_ = dir;
	}

	void getValue(float &theta, int &dir)
        {
            theta = theta_;
            dir = dir_;
        }

    private:
	float theta_;
	int dir_;
    }
}


#endif
