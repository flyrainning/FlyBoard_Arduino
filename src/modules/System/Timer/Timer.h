#ifndef FLYBOARD_TIMER
#define FLYBOARD_TIMER

#include "../../../config.h"
#include "RBD_Timer.h"

class Timer:public RBD::Timer
{

public:

	long every_count_count;
	unsigned long every_ms_waypoint=0;


	bool every_count(long times);//每隔多少次以后执行
	void reset_count();//重置单次执行计数器
	bool every_ms(unsigned long times);//每隔多少ms后执行



};



#endif
