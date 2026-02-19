#include <exception>
#include <iostream>
#include <classes/desktop_file.hpp>

int main(int argc, const char **argv) {
    std::cout << "Parsing given parameters...\n";

    DesktopFile desktop_file = build_desktop_file_class(argc, argv);
    try { desktop_file.to_filesystem(); }
    catch (const std::exception& e) {
        std::cerr << "[ERROR]: " << e.what() << "\n";
    }
}
