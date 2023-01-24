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

    Memberlist randomPickMembers(const Memberlist &memberlist, const int n)
    {
        auto begin = memberlist.begin();
        auto end = memberlist.end();
        size_t left = std::distance(begin, end);
        for (int i = 0; i < n; i++)
        {
            auto r = begin;
            std::advance(r, rand() % left);
            std::swap(begin, r);
            ++begin;
            --left;
        }
        return begin;
    }

    void memberlistUpdate(Memberlist &memberlist, const Member &member)
    {
        throw NotImplementedError();
    }
}