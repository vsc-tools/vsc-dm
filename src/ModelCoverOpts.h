/*
 * ModelCoverOpts.h
 *
 *  Created on: Nov 25, 2021
 *      Author: mballance
 */

#pragma once
#include <stdint.h>
#include <string>

namespace vsc {

class ModelCoverOpts {
public:
	ModelCoverOpts();

	virtual ~ModelCoverOpts();

	/**
	 * Propagates relevant options from the parent scope
	 */
	void propagate(const ModelCoverOpts &opts);

	uint32_t weight() const { return m_weight; }

	void weight(uint32_t w) { m_weight = w; }

	uint32_t goal() const { return m_goal; }

	void goal(uint32_t g) { m_goal = g; }

	const std::string &comment() const { return m_comment; }

	void comment(const std::string &c) { m_comment = c; }

	uint32_t at_least() const { return m_at_least; }

	void at_least(uint32_t a) { m_at_least = a; }

	uint32_t auto_bin_max() const { return m_auto_bin_max; }

	void auto_bin_max(uint32_t m) { m_auto_bin_max = m; }

private:
	uint32_t			m_weight;
	uint32_t			m_goal;
	std::string			m_comment;
	uint32_t			m_at_least;
	uint32_t			m_auto_bin_max;
};

} /* namespace vsc */

