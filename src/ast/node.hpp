#ifndef SPECTRA_NODE_HPP
#define SPECTRA_NODE_HPP

#include <lexer/token.hpp>

#include "token_stream.hpp"

namespace ast {

class Node {
   public:
    template <typename T>
    bool is();
};

}  // namespace ast

#endif  // SPECTRA_SCANNER_HPP
