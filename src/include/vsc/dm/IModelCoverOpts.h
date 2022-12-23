
#pragma once
#include <stdint.h>
#include <string>

namespace vsc {
namespace dm {

class IModelCoverOpts {
public:

    virtual ~IModelCoverOpts() { }

	virtual void init(const IModelCoverOpts *opts) = 0;

	virtual uint32_t getWeight() const = 0;

	virtual void setWeight(uint32_t w) = 0;

	virtual uint32_t getGoal() const = 0;

	virtual void setGoal(uint32_t g) = 0;

	virtual const std::string &getComment() const = 0;

	virtual void setComment(const std::string &c) = 0;

	virtual uint32_t getAtLeast() const = 0;

	virtual void setAtLeast(uint32_t a) = 0;

	virtual uint32_t getAutoBinMax() const = 0;

	virtual void setAutoBinMax(uint32_t m) = 0;

};

}
}
