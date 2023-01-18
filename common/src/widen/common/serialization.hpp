#pragma once

#include <string>
#include "widen/common/fmt.hpp"

// TODO: be aware of endianess
namespace widen
{
    // template <typename T>
    inline std::string serialize4BytesNumber(uint32_t number)
    {
        u_char *bytePointer = reinterpret_cast<u_char *>(&number);

        return {bytePointer, bytePointer + sizeof(uint32_t)};
    }

    template <typename T>
    T deserializeNumber(const std::string &byteString)
    {
        if (byteString.length() != sizeof(T))
            throw std::out_of_range(fmt::format("Byte string length {} does not match data length {}",
                                                byteString.length(),
                                                sizeof(T)));
        T value;
        std::memcpy(&value, byteString.data(), sizeof(T));

        return value;
    }
}