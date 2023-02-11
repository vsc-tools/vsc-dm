/*
 * VscTestBase.h
 *
 *  Created on: Oct 6, 2021
 *      Author: mballance
 */

#pragma once
#include "gtest/gtest.h"
#include "vsc/dm/IContext.h"
#include "vsc/dm/IFactory.h"

namespace vsc {
namespace dm {

class VscTestBase : public ::testing::Test {
public:
	VscTestBase();

	virtual ~VscTestBase();

	virtual void SetUp() override;

	virtual void TearDown() override;

    void enableDebug(bool en);

protected:
    IFactory                    *m_factory;
    IContextUP                  m_ctxt;

};

}
} /* namespace vsc */

