#include "classes/desktop_file.hpp"
#include "globals.hpp"
#include "other/logging.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

using path = std::filesystem::path;

static void display_help() {
    std::cout << "Usage:\n";
    std::cout << "  deskcli name comment exec_path icon_path categories\n";
    std::cout << "Flags:\n";
    std::cout << "  -t, --terminal: should the app the .desktop file points to "
                 "be a terminal app?\n";
    std::cout << "  -s, --system-wide: should the .desktop file be usable by "
                 "all users?\n";
    std::cout << "  --verbose: verbose mode\n";
    std::cout << "  -h, --help: display this help message\n";
}

static std::string get_home_path() {
    const char *home = std::getenv("HOME");

    if (!home)
        throw std::runtime_error("HOME environment variable is not set");

    return std::string(home);
}

static std::string bool_to_string(bool b) { return b ? "true" : "false"; }

void DesktopFile::to_filesystem() const {
    path base = (system_wide ? "/usr/share/applications/"
                             : get_home_path() + "/.local/share/applications/");

    path target_path = base / (name + ".desktop");

    logging::log("Target path: " + target_path.string() + "\n", logging::Level::Debug);

    if (std::filesystem::exists(target_path)) {
        std::string file_type;
        std::string command;

        (std::filesystem::is_regular_file(target_path))
            // Not sure this works
            ? file_type = "file",
              command = "rm" : file_type = "directory", command = "rm -r";

        throw std::runtime_error(file_type +
                                 " with the same name was found\nHINT: run `" +
                                 command + " " + target_path.string() + "`\n");
    }

    logging::log("Creating .desktop file\n", logging::Level::Debug);
    std::ofstream file(target_path);

    if (!file) {
        throw std::runtime_error("Failed to create " + target_path.string() +
                                 " file.");
    }

    logging::log("Writing to .desktop file\n", logging::Level::Debug);
    logging::log("[Desktop Entry]\nName=" + name + "\nComment=" + comment +
                     "\nExec=" + exec_path + "\nIcon=" + icon_path +
                     "\nTerminal=" + bool_to_string(is_terminal) +
                     "\nType=Application\nCategories=" + categories + "\n",
                 logging::Level::Debug);

    file << "[Desktop Entry]\nName=" << name << "\nComment=" << comment
         << "\nExec=" << exec_path << "\nIcon=" << icon_path
         << "\nTerminal=" << bool_to_string(is_terminal)
         << "\nType=Application\nCategories=" << categories << "\n";
}

DesktopFile build_desktop_file_class(int argc, const char **argv) {
    std::string name, comment, exec_path, icon_path, categories;
    bool is_terminal = false, system_wide = false;

    std::vector<std::string> arguments;
    std::vector<std::string> flags;

    // Starts the vectors
    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);

        (arg.starts_with("--") || arg.starts_with("-"))
            ? flags.push_back(arg)
            : arguments.push_back(arg);
    }

    for (size_t i = 0; i < flags.size(); ++i) {
        std::string flag = flags.at(i);

        if (flag == "-t" || flag == "--terminal")
            is_terminal = true;
        if (flag == "-s" || flag == "--system-wide")
            system_wide = true;
        if (flag == "-h" || flag == "--help") {
            display_help();
            std::exit(0);
        };
        if (flag == "--verbose")
            verbose = true;
    }

    if (arguments.size() > 0)
        name = arguments[0];
    if (arguments.size() > 1)
        comment = arguments[1];
    if (arguments.size() > 2)
        exec_path = arguments[2];
    if (arguments.size() > 3)
        icon_path = arguments[3];
    if (arguments.size() > 4)
        categories = arguments[4];

    return DesktopFile(name, comment, exec_path, icon_path, is_terminal,
                       categories, system_wide);
}
