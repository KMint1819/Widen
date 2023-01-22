#include "widen/node/memberlist.hpp"
#include "widen/common/exception.hpp"

namespace widen
{
    Memberlist memberlist;
    std::string memberlistDescription(const Memberlist &memberlist)
    {
        std::string s = "\n";
        for (const auto &identifier : memberlist)
        {
            s += fmt::format("Member ip: {}, initTimestamp: {}\n",
                             identifier.getIp(),
                             identifier.getInitTimestamp());
        }
        s.pop_back();
        return s;
    }
    void memberlistUpdate(Memberlist &memberlist, const Identifier &identifier)
    {
        throw NotImplementedError();
    }
}