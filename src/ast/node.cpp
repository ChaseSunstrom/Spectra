#include "node.hpp"

namespace ast {

    template<typename T>
    bool node::is() {
        return typeid(*this) == typeid(T);
    }
}