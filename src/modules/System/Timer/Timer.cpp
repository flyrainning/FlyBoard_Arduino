#include "Timer.h"



	bool Timer::every_count(long times)//每隔多少次以后执行
	{
		every_count_count++;
		if (every_count_count>=times)
		{
			every_count_count=0;
			return true;
		}else{
			return false;
		}
	}

	bool Timer::every_ms(unsigned long times)//每隔多少ms后执行
	{
		unsigned long now=millis();
		unsigned long td= now - every_ms_waypoint;

		if (td>=times){
			every_ms_waypoint=now;
			return true;
		}else{
			return false;
		}

	}

	void Timer::reset_count()//重置单次执行计数器
	{
		every_count_count=0;
	}
