#include <util/log.h>

namespace fmt {
    std::string format(std::string fmt, ...) {
        static char buffer[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buffer, sizeof(buffer), fmt.c_str(), args);
        va_end(args);
        return buffer;
    }
}
