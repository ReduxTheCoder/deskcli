#ifndef DESKTOP_FILE_HPP
#define DESKTOP_FILE_HPP

#include <string>

class DesktopFile {
  private:
    std::string name;
    std::string comment;
    std::string exec_path;
    std::string icon_path;
    bool is_terminal = false;
    std::string categories;
    bool system_wide = false;

  public:
    DesktopFile(std::string name, std::string comment = "Program description",
                std::string exec_path = "", std::string icon_path = "",
                bool is_terminal = false, std::string categories = "",
                bool system_wide = false)
        : name(name), comment(comment), exec_path(exec_path),
          icon_path(icon_path), is_terminal(is_terminal),
          categories(categories), system_wide(system_wide) {}

    void to_filesystem() const;
};

DesktopFile build_desktop_file_class(int argc, const char **argv);

#endif
