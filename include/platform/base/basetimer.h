/*
 * basetimer.h
 *
 *  Created on: 15.08.2013
 *      Author: ���������
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

	/// ������� �������� �� ����.
	virtual double getDelta(TicType) {return 0;}
	/// ������ � �������
	virtual double getFPS() {return 0;}
	/// ������������� �a����� �������, �� ��������� 1.
	virtual void setRate(double ) {}
	virtual void tic(TicType) {}
	virtual void update() {}
};

}

#endif /* BASETIMER_H_ */
