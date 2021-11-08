/*
 * basetimer.h
 *
 *  Created on: 15.08.2013
 *      Author: Александр
 */

#ifndef BASETIMER_H_
#define BASETIMER_H_

namespace csad {

class BaseTimer {
public:
	enum TicType {
		Begin,
		Events,
		Scene,
		Render,
		Buffer,
		End
	};

	/// времени пройдено за цикл.
	virtual double getDelta(TicType) {return 0;}
	/// кадров в секунду
	virtual double getFPS() {return 0;}
	/// устанавливает мaсштаб времени, по умолчанию 1.
	virtual void setRate(double ) {}
	virtual void tic(TicType) {}
	virtual void update() {}
};

}

#endif /* BASETIMER_H_ */
