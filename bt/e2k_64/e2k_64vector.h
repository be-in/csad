/*
 * e2k_64vector.h
 *
 *  Created on: 18.09.2013
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#ifndef E2K_64VECTOR_H_
#define E2K_64VECTOR_H_

#include <bt.h>

#ifdef CPU_E2K_64

namespace bt {

	void _APICALL _V2FAddE2K(float *,float *,float *);
	void _APICALL _V3FAddE2K(float *,float *,float *);
	void _APICALL _V4FAddE2K(float *,float *,float *);
	void _APICALL _V2DAddE2K(double *,double *,double *);
	void _APICALL _V3DAddE2K(double *,double *,double *);
	void _APICALL _V4DAddE2K(double *,double *,double *);

	void _APICALL _V2FSubE2K(float *,float *,float *);
	void _APICALL _V3FSubE2K(float *,float *,float *);
	void _APICALL _V4FSubE2K(float *,float *,float *);
	void _APICALL _V2DSubE2K(double *,double *,double *);
	void _APICALL _V3DSubE2K(double *,double *,double *);
	void _APICALL _V4DSubE2K(double *,double *,double *);

	float _APICALL _V2FDotE2K(float *a,float *b);
	float _APICALL _V4FDotE2K(float *a,float *b);
	double _APICALL _V4DDotE2K(double *a,double *b);

	void _APICALL _V2FNormalE2K(float *,float *);
	void _APICALL _V3FNormalE2K(float *,float *);
	void _APICALL _V4FNormalE2K(float *,float *);
	void _APICALL _V2DNormalE2K(double *,double *);
	void _APICALL _V3DNormalE2K(double *,double *);
	void _APICALL _V4DNormalE2K(double *,double *);
}

#endif

#endif /* E2K_64VECTOR_H_ */
