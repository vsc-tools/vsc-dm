/*
 * DataType.h
 *
 *  Created on: Sep 23, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/dm/IContext.h"
#include "vsc/dm/IDataType.h"
#include "vsc/dm/IModelBuildContext.h"
#include "ModelVal.h"

namespace vsc {
namespace dm {

class DataType;
typedef std::unique_ptr<DataType> DataTypeUP;
class DataType : 
    public virtual IDataType {
public:
	DataType();

	virtual ~DataType();

    virtual void finalize(IContext *ctxt) override { 
        m_ctxt = ctxt;
    }

    virtual int32_t getByteSize() const { return m_bytesz; }

/*
    virtual void initVal(ValRef &v) override { }

    virtual void finiVal(ValRef &v) override { }

    virtual ValRef &&copyVal(const ValRef &src) override { }
 */

    virtual void setAssociatedData(IAssociatedData *data) override {
        m_associated_data = IAssociatedDataUP(data);
    }

    virtual IAssociatedData *getAssociatedData() const override {
        return m_associated_data.get();
    }

protected:
    IContext                    *m_ctxt;
    int32_t                     m_bytesz;
    IAssociatedDataUP           m_associated_data;

};

}
} /* namespace vsc */

