#pragma once

#include <set>

#include "widen/common/fmt.hpp"
#include "widen/messages.pb.h"

// TODO: Implement own memberlist with these member functions and iterators
namespace widen
{
    typedef std::set<Identifier> Memberlist;
    static Memberlist memberlist;

    std::string memberlistDescription(const Memberlist &memberlist)
    {
        std::string s = "\n";
        for (const auto &identifier : memberlist)
        {
            s += fmt::format("Member ip: {}, initTimestamp: {}\n",
                             identifier.ip(),
                             identifier.inittimestamp());
        }
        s.pop_back();
        return s;
    }

    void memberlistUpdate(Memberlist &, const Identifier &);
}