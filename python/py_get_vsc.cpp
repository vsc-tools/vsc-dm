/*
 * py_get_vsc.cpp
 *
 *  Created on: Apr 21, 2022
 *      Author: mballance
 */
#include "py_get_vsc.h"
#include "vsc/loader.h"

vsc::IVsc *py_get_vsc(const char *path) {
	return get_vsc(path);
}



