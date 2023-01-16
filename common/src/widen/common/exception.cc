#include "widen/common/exception.hpp"

namespace widen
{
    NotImplementedError::NotImplementedError()
        : std::logic_error("Function not yet implemented"){};

}