#pragma once
#include <string>
#include <vector>

class listdir {
private:
    uint32_t current_file;
    std::string path;
    std::vector<std::string> files;

public:
    listdir(std::string file);
    std::string get_current_file() const;
    std::string scroll_up();
    std::string scroll_down();
private:
    std::string get_current_dir(std::string file);
};