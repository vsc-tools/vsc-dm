/*
 * IModelCoverpoint.h
 *
 *  Created on: Feb 3, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <string>
#include <vector>
#include "vsc/IAccept.h"
#include "vsc/IModelCoverBin.h"
#include "vsc/IModelCoverItem.h"
#include "vsc/IModelCoverpointIff.h"
#include "vsc/IModelCoverpointTarget.h"
#include "vsc/IModelExpr.h"

namespace vsc {

class IModelCovergroup;

class IModelCoverpoint;
using IModelCoverpointUP=std::unique_ptr<IModelCoverpoint>;
class IModelCoverpoint : public virtual IModelCoverItem {
public:

	virtual ~IModelCoverpoint() { }

	virtual void setCovergroup(IModelCovergroup *cg) = 0;

	virtual IModelCovergroup *getCovergroup() const = 0;

	virtual IModelCoverpointTarget *getTarget() const = 0;

	virtual IModelCoverpointIff *getIff() const = 0;

	virtual void addBin(IModelCoverBin *bin) = 0;

	virtual uint32_t getNumBins(ModelCoverBinType type) const = 0;

	virtual std::string getBinName(ModelCoverBinType type, int32_t bin_idx) = 0;

	virtual int32_t getBinHits(ModelCoverBinType type, int32_t bin_idx) = 0;

	virtual const std::vector<int32_t> &getHitIdx(ModelCoverBinType type) = 0;

	virtual const IModelVal *getVal() = 0;

	virtual void setVal(const IModelVal *v) = 0;

	/**
	 * @brief Called by coverpoint bins to increment hit counts
	 * 
	 * @param index 
	 */
	virtual void coverageEvent(ModelCoverBinType type, int32_t index) = 0;


};

}

