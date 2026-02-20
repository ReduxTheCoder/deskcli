#include "other/logging.hpp"
#include "globals.hpp"
#include "other/ansi.hpp"
#include <iostream>
#include <string_view>

namespace logging {
void log(std::string_view msg, Level level) {
    switch (level) {
    case Level::Debug: {
        if (!verbose) {
            return;
        }

        std::cout << ansi::ORANGE << msg << ansi::RESET;
        break;
    }
    case Level::Warning: {
        std::cout << ansi::YELLOW << msg << ansi::RESET;
        break;
    }
    case Level::Error: {
        std::cerr << ansi::RED << msg << ansi::RESET;
        break;
    }
    }
}
} // namespace logging
