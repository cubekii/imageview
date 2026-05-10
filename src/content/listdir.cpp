#include "listdir.h"
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

listdir::listdir(std::string file) : current_file(file) {
    path = get_current_dir(file);
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            std::string ext = entry.path().extension().string();
            if (ext == ".png" || ext == ".jpg" || ext == ".jpeg" || ext == ".webp" || ext == ".gif")
                files.push_back(entry.path().filename().string());
        }
    }
}

std::string listdir::get_current_dir(std::string file) {
    auto pos = file.rfind('\\');
    if (pos != std::string::npos) file.erase(pos);
    return file;
}

std::string listdir::get_current_file() const {
    return current_file;
}

std::string listdir::scroll_up() {
    return "";
}

std::string listdir::scroll_down() {
    return "";
}