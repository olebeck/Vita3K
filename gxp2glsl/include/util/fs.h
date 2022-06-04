#pragma once

#include <fstream>

namespace fs {
    class path {
        std::string m_path;

    public:
        path(std::string path);
        
        path filename() const;

        std::string string() const;
    };


    int file_size(const path &path);
};
