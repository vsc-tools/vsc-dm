#pragma once
#include <memory>

namespace vsc {
namespace dm {

template <class T> struct UPD {
    UPD() : m_owned(true) { }
    UPD(bool &owned) : m_owned(owned) { }
    void operator()(T *p) {
        if (p && m_owned) {
            delete p;
        }
    }
    bool m_owned;
};

/**
 * @brief Unique-pointer wrapper that can optionally 
 *        *not* take ownership of the pointer
 * 
 * @tparam T 
 */
template <class T> class UP : public std::unique_ptr<T,UPD<T>> {
public:
    UP() : std::unique_ptr<T,UPD<T>>() {}
    UP(T *p, bool owned=true) : std::unique_ptr<T,UPD<T>>(p, UPD<T>(owned)) {}
    bool owned() const { return std::unique_ptr<T,UPD<T>>::get_deleter().m_owned; }
};

}
}