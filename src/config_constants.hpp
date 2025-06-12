#pragma once

#include <cstdint>
#include <string_view>

namespace general_constants {

}

namespace logger_constants {
    constexpr std::string_view LOG_FILE_NAME = "app.log";
}

namespace render_constants {
    constexpr std::string_view  WINDOW_NAME     = "bullet_hell";
    constexpr size_t            WINDOW_WIDTH    = 600;
    constexpr size_t            WINDOW_HEIGHT   = 800;
}

namespace socket_constants {
    constexpr std::string_view  SERVER_ADDR             = "150.42.11.6";
    constexpr uint16_t          SERVER_PORT             = 6198;
    constexpr uint32_t          SERVER_MAGIC_NUMBER     = 0x7F3B29D1;
    constexpr uint32_t          SERVER_MAX_PACKET_SIZE  = 10 * 1024 * 1024; // 10MB
}