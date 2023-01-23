#pragma once

#include "widen/common/serialization.hpp"
#include "widen/general.pb.h"

#include <asio.hpp>
#include <google/protobuf/message.h>

namespace widen
{
    int64_t getTimestamp();
    asio::ip::address_v4 getSelfIp(const std::string &interface = "eth0");

    // /// @brief Taking a pointer to pb::Message for polymorphism
    // /// @param req
    // /// @param type
    // /// @return
    // void sendRequest(
    //     google::protobuf::Message *req,
    //     const std::string &type,
    //     asio::ip::tcp::socket &socket,
    //     std::optional<std::function<void(asio::error_code, std::size_t)>> callback = std::nullopt)
    // {
    //     std::string headerStr, bodyStr;
    //     req->SerializeToString(&bodyStr);

    //     proto::Header header;
    //     header.set_type(type);
    //     header.set_body_length(bodyStr.length());

    //     header.SerializeToString(&headerStr);

    //     asio::streambuf buf;
    //     std::ostream os(&buf);
    //     os << serializeUInt32(headerStr.length()) << headerStr << bodyStr;
    //     os.flush();

    //     if (callback)
    //         asio::async_write(socket, buf, callback.value());
    //     else
    //         asio::write(socket, buf);
    // }

    // void recvHeader(
    //     google::protobuf::Message *res,
    //     asio::ip::tcp::socket &socket,
    //     std::optional<std::function<void(asio::error_code, std::size_t)>> callback = std::nullopt)
    // {
    //     static std::array<char, 8192> buf;

    //     // asio::async_read(socket, asio::buffer(buf, 4), )
    // }
}