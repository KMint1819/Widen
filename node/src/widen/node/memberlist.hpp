#pragma once

#include <deque>

#include "widen/common/proto_wrapper/identifier.hpp"
#include "widen/common/fmt.hpp"

// TODO: Implement own singleton memberlist with these member functions and iterators
namespace widen
{
    using Member = Identifier;
    using Memberlist = std::deque<Member>;
    extern Memberlist memberlist;

    std::string memberlistDescription(const Memberlist &memberlist);

    void memberlistUpdate(Memberlist &, const Identifier &);
}