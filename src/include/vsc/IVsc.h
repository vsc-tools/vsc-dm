/*
 * IVsc.h
 *
 *  Created on: Feb 4, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>

namespace vsc {

class IVsc;
using IVscUP=std::unique_ptr<IVsc>;
class IVsc {
public:
	virtual ~IVsc() { }

};

}

