/*
 * FieldBoundPropagator.h
 *
 *  Created on: Jul 8, 2020
 *      Author: ballance
 */

#pragma once
#include <memory>

namespace vsc {

class FieldBoundInfo;

class FieldBoundPropagator {
public:

	FieldBoundPropagator(FieldBoundInfo *info);

	virtual ~FieldBoundPropagator();

	virtual void propagate() = 0;

protected:
	FieldBoundInfo					*m_info;

};

typedef std::unique_ptr<FieldBoundPropagator> FieldBoundPropagatorUP;

} /* namespace vsc */

