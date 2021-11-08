/*
 * baseapi.h
 *
 *  Created on: 17.07.2015
 *      Author: Panteleymonov Aleksandr Konstantinovich  <mail@panteleymonov.ru>
 */

#pragma once
#ifndef COREAPI_H
#define COREAPI_H

#include <bt.h>

namespace csad {

void _APICALL initCore(unsigned int flagMask=0xFFFFFFFF);
void _APICALL resetCore();

}

#endif