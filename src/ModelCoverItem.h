
#pragma once
#include "vsc/dm/IModelCoverItem.h"
#include "ModelCoverOpts.h"

namespace vsc {
namespace dm {

class ModelCoverItem : public virtual IModelCoverItem {
public:

    ModelCoverItem(const std::string &name);

    virtual ~ModelCoverItem();

	virtual const std::string &name() const override { return m_name; }

	virtual IModelCoverOpts *getOptions() override {
        return &m_options;
    }
    

protected:
    std::string                     m_name;
    ModelCoverOpts                  m_options;

};


}
}
