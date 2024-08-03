#ifndef FILEINFO_H
#define FILEINFO_H

#include <string>
#include <cstdint>

struct FileInfo {
    std::string name;
    uintmax_t size;
    std::string creationTime;
};

#endif // FILEINFO_H