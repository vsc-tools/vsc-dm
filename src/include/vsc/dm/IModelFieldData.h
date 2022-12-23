/*
 * IModelFieldData.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>

namespace vsc {
namespace dm {

class IModelFieldData;
using IModelFieldDataUP=std::unique_ptr<IModelFieldData>;

/**
 * This class is an opaque base type for data associated
 * with a model field
 */
class IModelFieldData {
public:

	virtual ~IModelFieldData() { }

};

}
}
