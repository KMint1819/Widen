#include "widen/node/memberlist.hpp"
#include "widen/common/exception.hpp"

namespace widen
{
    Memberlist memberlist;

    Member::Member() {}

    Member::Member(const std::string &addrString, int64_t timestamp)
        : Member(address_v4::from_string(addrString), timestamp) {}

    Member::Member(const address_v4 &addr, int64_t timestamp)
        : ip(addr), initTime(timestamp) {}

    asio::ip::address_v4 Member::getIp() const { return ip; }
    int64_t Member::getInitTime() const { return initTime; }

    std::string memberlistDescription(const Memberlist &memberlist)
    {
        std::stringstream ss;
        for (const auto &member : memberlist)
        {
            ss << fmt::format("\nMember ip: {}, initTimestamp: {}",
                              member.getIp().to_string(),
                              member.getInitTime());
        }
        return ss.str();
    }
    void memberlistUpdate(Memberlist &memberlist, const Member &member)
    {
        throw NotImplementedError();
    }
}