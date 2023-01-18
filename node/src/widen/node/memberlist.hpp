#pragma once

#include <deque>

#include "widen/common/proto_wrapper/identifier.hpp"
#include "widen/common/fmt.hpp"

// TODO: Implement own singleton memberlist with these member functions and iterators
namespace widen
{
    using Member = Identifier;
    using Memberlist = std::deque<Member>;
    Memberlist memberlist;

    std::string memberlistDescription(const Memberlist &memberlist)
    {
        std::string s = "\n";
        for (const auto &identifier : memberlist)
        {
            s += fmt::format("Member ip: {}, initTimestamp: {}\n",
                             identifier.ip(),
                             identifier.initTimestamp());
        }
        s.pop_back();
        return s;
    }

    void memberlistUpdate(Memberlist &, const Identifier &);
}