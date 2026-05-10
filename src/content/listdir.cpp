#include "listdir.h"
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

listdir::listdir(std::string file){
    path = get_current_dir(file);
    int32_t i = 0;
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            std::string ext = entry.path().extension().string();
            if (ext == ".png" || ext == ".jpg" || ext == ".jpeg" || ext == ".webp" || ext == ".gif") {
                files.push_back(entry.path().filename().string());
                if (path + files.back()==file)
                    current_file = i;
                i++;
            }
        }
    }
}

std::string listdir::get_current_dir(std::string file) {
    auto pos = file.rfind('\\');
    if (pos != std::string::npos) file.erase(pos + 1);
    return file;
}

std::string listdir::get_current_file() const {
    return path + files[current_file];
}

std::string listdir::scroll_up() {
    if (current_file + 1 < files.size())
        current_file++;
    else
        current_file = 0;
    return get_current_file();
}

std::string listdir::scroll_down() {
    if (current_file == 0)
        current_file = files.size() - 1;
    else
        current_file--;
    return get_current_file();
}