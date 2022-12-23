/*
 * ModelValRangelist.cpp
 *
 *  Created on: Nov 21, 2021
 *      Author: mballance
 */

#include "ModelValRangelist.h"

namespace vsc {
namespace dm {

ModelValRangelist::ModelValRangelist(bool is_signed)
		: m_is_signed(is_signed) {

}

ModelValRangelist::~ModelValRangelist() {
	// TODO Auto-generated destructor stub
}

void ModelValRangelist::push_back(const IModelValRange *v) {
	m_values.push_back(ModelValRange(v));
	m_values_p.push_back(&m_values.back());
}

void ModelValRangelist::push_back(const IModelValRange &v) {
	m_values.push_back(ModelValRange(&v));
	m_values_p.push_back(&m_values.back());
}

void ModelValRangelist::clear() {
	m_values.clear();
	m_values_p.clear();
}

const IModelValRange *ModelValRangelist::at(uint32_t i) const {
	return &m_values.at(i);
}

IModelValRange *ModelValRangelist::at(uint32_t i) {
	return &m_values.at(i);
}


}
} /* namespace vsc */

