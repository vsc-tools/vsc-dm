/*
 * py_get_vsc.h
 *
 *  Created on: Apr 21, 2022
 *      Author: mballance
 */
#pragma once

#include "vsc/IVsc.h"

extern "C" vsc::IVsc *py_get_vsc(const char *path);
