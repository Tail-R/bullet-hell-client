#pragma once

#include "../socket/socket.hpp"
#include "../frame/frame_template.hpp"
#include "../frame/frame_serializer.hpp"

/*
    To-Do: Optimize the part of finding a magic number
*/

class PacketStreamClient {
public:
    PacketStreamClient(std::string_view server_addr, uint16_t server_port, uint32_t magic_number, uint32_t max_packet_size);
    ~PacketStreamClient();

    bool connect_to_server();
    void disconnect();

    std::optional<Frame> retrieve_frame(size_t max_attempts = 10);
    std::vector<Frame> retrieve_all_frames(size_t max_attempts = 10);

private:
    bool refill_buffer();
    void consume_buffer(size_t size);
    std::optional<PacketHeader> try_extract_packet_header();
    std::optional<Frame> try_extract_frame(const PacketHeader& packet_header);
    bool is_valid_packet_size(const PacketHeader& packet_header);

    ClientSocket            m_client_socket;
    bool                    m_server_connected;

    /*
        This is used to detect the start of a packet
        and is fixed at 4 bytes so should not be changed
    */
    uint32_t                m_magic_number;
    uint32_t                m_max_packet_size;
    std::vector<std::byte>  m_buffer;
};

// class PacketStreamServer {
// public:

// private:
// };