
#pragma once
#include <string>
#include "vsc/IAccept.h"
#include "vsc/IModelCoverOpts.h"

namespace vsc {

class IModelCoverItem : public virtual IAccept {
public:

    virtual ~IModelCoverItem() { }

	virtual const std::string &name() const = 0;

	virtual void finalize() = 0;

	virtual void sample() = 0;

	virtual double getCoverage() = 0;

	virtual IModelCoverOpts *getOptions() = 0;

};

}