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

    /// @brief Pick n random members from the memberlist using Fisher-Yates shuffle.
    /// Reference: https://stackoverflow.com/questions/9345087/choose-m-elements-randomly-from-a-vector-containing-n-elements
    /// @param memberlist
    /// @param n
    /// @return
    Memberlist randomPickMembers(const Memberlist &memberlist, const int n);

    void memberlistUpdate(Memberlist &, const Member &);
}