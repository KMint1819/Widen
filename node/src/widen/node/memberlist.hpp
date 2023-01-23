#pragma once

#include <deque>
#include <asio.hpp>

#include "widen/common/fmt.hpp"

// TODO: Implement own singleton memberlist with these member functions and iterators
namespace widen
{
    class Member
    {
        using address_v4 = asio::ip::address_v4;

    public:
        Member();
        Member(const std::string &addrString, int64_t timestamp);
        Member(const address_v4 &addr, int64_t timestamp);
        address_v4 getIp() const;
        int64_t getInitTime() const;

    private:
        asio::ip::address_v4 ip;
        int64_t initTime = 0;
    };
    using Memberlist = std::deque<Member>;
    extern Memberlist memberlist;

    std::string memberlistDescription(const Memberlist &memberlist);

    void memberlistUpdate(Memberlist &, const Member &);
}