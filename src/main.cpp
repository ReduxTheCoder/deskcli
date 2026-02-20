#include "other/logging.hpp"
#include <classes/desktop_file.hpp>

int main(int argc, const char **argv) {
    DesktopFile desktop_file = build_desktop_file_class(argc, argv);
    logging::log("Parsing arguments...\n", logging::Level::Debug);
    try {
        desktop_file.to_filesystem();
    } catch (const std::exception &e) {
        logging::log(std::string("[ERROR]: ") + e.what() + "\n",
                     logging::Level::Error);
    }
}
