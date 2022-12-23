
#pragma once
#include <string>
#include "vsc/dm/IAccept.h"
#include "vsc/dm/IModelCoverOpts.h"

namespace vsc {
namespace dm {

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
}
