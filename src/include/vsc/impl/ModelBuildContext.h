/*
 * ModelBuildContext.h
 *
 *  Created on: Jun 12, 2022
 *      Author: mballance
 */

#pragma once
#include <stdio.h>
#include <vector>
#include "vsc/IModelBuildContext.h"

namespace vsc {

class ModelBuildContext : public virtual IModelBuildContext {
public:

	ModelBuildContext(IContext *ctxt) : m_ctxt(ctxt) { }

	virtual ~ModelBuildContext() { }

	virtual IContext *ctxt() const override { return m_ctxt; }

	virtual void pushTopDownScope(IModelField *f) override {
		fprintf(stdout, "ModelBuildContext::pushTopDownScope %s => %d\n", 
			f->name().c_str(),
			m_top_down_s.size()+1);
		fflush(stdout);
		m_top_down_s.push_back(TopDownScopeT{f});
	}

	virtual IModelField *getTopDownScope() const override {
		return (m_top_down_s.size())?m_top_down_s.back().scope:0;
	}

	virtual void popTopDownScope() override {
		if (m_top_down_s.size()) {
			fprintf(stdout, "ModelBuildContext::popTopDownScope %s => %d\n", 
				m_top_down_s.back().scope->name().c_str(),
				m_top_down_s.size()-1);
		    fflush(stdout);
			m_top_down_s.pop_back();
		} else {
			fprintf(stdout, "ModelBuildContext::Error - pop from empty stack\n");
		    fflush(stdout);
		}
	}

	virtual void pushBottomUpScope(IModelField *f) override {
		fprintf(stdout, "ModelBuildContext::pushBottomUpScope %s\n", f->name().c_str());
		fflush(stdout);
		m_top_down_s.back().bottom_up_s.push_back(f);
	}

	virtual IModelField *getBottomUpScope(int32_t offset=-1) const override {
		if (offset < 0) {
			return m_top_down_s.back().bottom_up_s.at(
				m_top_down_s.back().bottom_up_s.size()+offset
			);
		} else {
			return m_top_down_s.back().bottom_up_s.at(offset);
		}
	}

	virtual void popBottomUpScope() override {
		fprintf(stdout, "ModelBuildContext::popBottomUpScope %s\n", 
			m_top_down_s.back().bottom_up_s.back()->name().c_str());
		fflush(stdout);
		m_top_down_s.back().bottom_up_s.pop_back();
	}

	virtual IModelField *getScope() const override {
		if (m_top_down_s.size()) {
			if (m_top_down_s.back().bottom_up_s.size()) {
				return m_top_down_s.back().bottom_up_s.back();
			} else {
				return m_top_down_s.back().scope;
			}
		} else {
			return 0;
		}
	}

protected:
	struct TopDownScopeT {
		IModelField						*scope;
		std::vector<IModelField *>		bottom_up_s;
	};

protected:
	IContext							*m_ctxt;
	std::vector<TopDownScopeT>			m_top_down_s;

};

}
