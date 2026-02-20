#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <string_view>

namespace logging {
enum class Level {
    Debug,
    Warning,
    Error,
};

void log(std::string_view msg, Level level);
} // namespace logging

#endif
