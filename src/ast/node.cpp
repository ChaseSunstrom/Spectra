#include "node.hpp"

namespace ast {

template <typename T>
bool Node::is() {
    return typeid(*this) == typeid(T);
}
}