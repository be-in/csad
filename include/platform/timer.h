/*
 * timer.h
 *
 *  Created on: 15.08.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <platform/platformapi.h>

WARNING_DISABLE;
OPTIMIZE_ON;

namespace csad {

/**
 * @class Timer
 *
 * @ingroup platform
 * @brief Timer - timer.
 *
 * @see platform
 */

class Timer {
public:
	MEMDEFAULT(Timer)

	PLATFORM_API Timer();

	enum TicType {
		Begin,
		Events,
		Scene,
		Render,
		Buffer,
		End
	};

	/// The time spent on the programme cycle, or a separate segment of work
	PLATFORM_API double getDelta(TicType tic = Begin);
	_FORCEINLINE double getFPS() { return p_avgfps;	}
	_FORCEINLINE double getLPS() { return p_avglps; }
	/// The time, in milliseconds
	PLATFORM_API _int64 getTime();
	PLATFORM_API void setRate(double rate);
	PLATFORM_API void tic(TicType tic);

	PLATFORM_API void updateLoop();
	PLATFORM_API void updateFrame();
private:
	unsigned int p_t1;
	unsigned int p_t2;

	double p_rate;
	double p_fps;
	double p_lps;
	double p_avgfps;
	double p_avglps;
	double p_tics[End];
};

}

OPTIMIZE_OFF;
WARNING_ENABLE;

#endif /* TIMER_H_ */
