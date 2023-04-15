/*
 * ModelBuildContext.h
 *
 *  Created on: Jun 12, 2022
 *      Author: mballance
 * 
 * Copyright 2019-2023 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include "vsc/dm/IModelBuildContext.h"
#include "vsc/dm/IModelField.h"

namespace vsc {
namespace dm {

class ModelBuildContext : public virtual IModelBuildContext {
public:

	ModelBuildContext(IContext *ctxt) : m_ctxt(ctxt) { }

	virtual ~ModelBuildContext() { }

	virtual IContext *ctxt() const override { return m_ctxt; }

	virtual void pushTopDownScope(IModelField *f) override {
		m_top_down_s.push_back(TopDownScopeT{f});
	}

	virtual IModelField *getTopDownScope() const override {
		return (m_top_down_s.size())?m_top_down_s.back().scope:0;
	}

	virtual void popTopDownScope() override {
		if (m_top_down_s.size()) {
			m_top_down_s.pop_back();
		} else {
			fprintf(stdout, "ModelBuildContext::Error - pop from empty stack\n");
		    fflush(stdout);
		}
	}

	virtual void pushBottomUpScope(IModelField *f) override {
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
}
