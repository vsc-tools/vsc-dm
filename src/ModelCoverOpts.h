/*
 * ModelCoverOpts.h
 *
 *  Created on: Nov 25, 2021
 *      Author: mballance
 */

#pragma once
#include <stdint.h>
#include <string>
#include "vsc/dm/IModelCoverOpts.h"

namespace vsc {
namespace dm {

class ModelCoverOpts : public virtual IModelCoverOpts {
public:
	ModelCoverOpts();

	virtual ~ModelCoverOpts();

	/**
	 * Propagates relevant options from the parent scope
	 */
	virtual void init(const IModelCoverOpts *opts) override;

	virtual uint32_t getWeight() const override { return m_weight; }

	virtual void setWeight(uint32_t w) override { m_weight = w; }

	virtual uint32_t getGoal() const override { return m_goal; }

	virtual void setGoal(uint32_t g) override { m_goal = g; }

	virtual const std::string &getComment() const override { return m_comment; }

	virtual void setComment(const std::string &c) override { m_comment = c; }

	virtual uint32_t getAtLeast() const override { return m_at_least; }

	virtual void setAtLeast(uint32_t a) override { m_at_least = a; }

	virtual uint32_t getAutoBinMax() const override { return m_auto_bin_max; }

	virtual void setAutoBinMax(uint32_t m) override { m_auto_bin_max = m; }

private:
	uint32_t			m_weight;
	uint32_t			m_goal;
	std::string			m_comment;
	uint32_t			m_at_least;
	uint32_t			m_auto_bin_max;
};

}
} /* namespace vsc */

