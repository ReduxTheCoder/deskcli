#include "classes/desktop_file.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <vector>

using path = std::filesystem::path;

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

    std::ofstream file(target_path);
    if (!file) {
        throw std::runtime_error("Failed to create " + target_path.string() +
                                 " file.");
    }

    file << "[Desktop Entry]\nName=" << name << "\nComment=" << comment
         << "\nExec=" << exec_path << "\nIcon=" << icon_path
         << "\nTerminal=" << bool_to_string(is_terminal)
         << "\nType=Application\nCategories=" << categories << "\n";
}

DesktopFile build_desktop_file_class(int argc, const char **argv) {
    std::string name, comment, exec_path, icon_path, categories;
    bool is_terminal = false, system_wide = false;

    std::vector<std::string> positionals;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-t" || arg == "--terminal") {
            is_terminal = true;
        } else if (arg == "-s" || arg == "--system-wide") {
            system_wide = true;
        } else {
            positionals.push_back(arg);
        }
    }

    if (positionals.size() > 0)
        name = positionals[0];
    if (positionals.size() > 1)
        comment = positionals[1];
    if (positionals.size() > 2)
        exec_path = positionals[2];
    if (positionals.size() > 3)
        icon_path = positionals[3];
    if (positionals.size() > 4)
        categories = positionals[4];

    return DesktopFile(name, comment, exec_path, icon_path, is_terminal,
                       categories, system_wide);
}
