#include <iostream>

#include "config_constants.hpp"
#include "logger/logger.hpp"
#include "packet_stream/packet_stream.hpp"


int main(int argc, char* argv[]) {
    start_async_logger(logger_constants::LOG_FILE_NAME.data());

    PacketStreamClient psc(
        socket_constants::SERVER_ADDR,
        socket_constants::SERVER_PORT,
        socket_constants::SERVER_MAGIC_NUMBER,
        socket_constants::SERVER_MAX_PACKET_SIZE
    );

    if (!psc.connect_to_server())
    {
        std::cerr << "Failed to connect to server" << "\n";

        return 1;
    }

    for (int i = 0; i < 600; i++)
    {
        auto frames = psc.retrieve_all_frames();
        
        for (Frame f : frames)
        {
            async_log(LogLevel::Debug, frame_to_json_str(f));
        }   
    }

    stop_async_logger();

    return 0;
}