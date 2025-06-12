#pragma once

#include <string>
#include "frame_template_enums.hpp"
#include "frame_template_structs.hpp"

std::string frame_to_json_str(const Frame& frame);
void print_frame(const Frame& frame);