#include <util/fs.h>

namespace fs {
    path::path(std::string _path) : m_path(std::move(_path)) {}
    
    path path::filename() const {
        return path(m_path.substr(m_path.find_last_of("/\\") + 1));
    }

    std::string path::string() const {
        return m_path;
    }


    int file_size(const path &path) {
        std::ifstream file(path.string(), std::ios::binary | std::ios::ate);
        if (!file.is_open())
            return -1;
        return static_cast<int>(file.tellg());
    }
}
