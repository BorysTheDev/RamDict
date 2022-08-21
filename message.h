#pragma once

#include <cstdint>
#include <vector>
#include <span>
#include <cstring>

struct msg_header { // TODO add serialization
    enum Msg_types : std::uint32_t {
        SET,
        GET
    } msg_type;
    std::uint32_t msg_size;
};
static_assert(sizeof(msg_header) == (sizeof(msg_header::msg_type) + sizeof(msg_header::msg_size)));

struct message {
    std::vector<char> buf;
    void fill(msg_header::Msg_types type, std::span<const char> data) {
        msg_header header{type, (std::uint32_t)data.size()};
        buf.resize(sizeof(msg_header) + data.size());
        std::memcpy(buf.data(), &header, sizeof(header));
        std::memcpy(buf.data() + sizeof(header), data.data(), data.size());
    }
};
