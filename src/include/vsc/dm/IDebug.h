

#pragma once
#include <string>

namespace vsc {
namespace dm {

class IDebug {
public:

    virtual ~IDebug() { }

    virtual bool en() const = 0;

    virtual void set_en(bool en) = 0;

    virtual const std::string &name() const = 0;

    virtual void enter(const char *fmt, ...) = 0;

    virtual void leave(const char *fmt, ...) = 0;

    virtual void debug(const char *fmt, ...) = 0;

};

}
}
