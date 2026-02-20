#include "other/logging.hpp"
#include "globals.hpp"
#include "other/ansi.hpp"
#include <iostream>
#include <string_view>

namespace logging {
void log(std::string_view msg, Level level) {
    if (verbose && level == Level::Debug) {
        return;
    }

    switch (level) {
    case Level::Debug: {
        if (verbose)
            return;

        std::cout << ansi::ORANGE << msg << ansi::RESET;
    }
    case Level::Warning: {
        if (verbose)
            return;

        std::cout << ansi::YELLOW << msg << ansi::RESET;
    }
    case Level::Error: {
        if (verbose)
            return;

        std::cout << ansi::RED << msg << ansi::RESET;
    }
    }
}
} // namespace logging
