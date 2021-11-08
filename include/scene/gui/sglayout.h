/*
 * sglayout.h
 *
 *  Created on: 10.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef SGLAYOUT_H_
#define SGLAYOUT_H_

#include <scene/scenecomponent.h>
#include <bt.h>

namespace csad {

using namespace bt;

class SGLayout: public SceneComponent {
public:
	MEMDEFAULT(SGLayout)

	CSAD_API SGLayout();

	enum Mode {
		FIXED,
		MIN,
		MAX
	};

	enum Orientation {
		Gorizontal,
		Vertical,
		Skip
	};

//	void setMode(unsigned int mode);
	CSAD_API void setSize(double x,double y,double z);

private:

	///
	vector3d p_size;
	unsigned int p_mode;

	///

};

}

#endif /* SGLAYOUT_H_ */
