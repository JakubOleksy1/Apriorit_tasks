#ifndef GETFILES_H
#define GETFILES_H

#include "FileInfo.h"
#include <vector>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>

class GetFiles {
public:
    static std::vector<FileInfo> getFiles(const std::string& folderPath) {
        std::vector<FileInfo> files;
        for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
            FileInfo fileInfo;
            fileInfo.name = entry.path().filename().string();
            fileInfo.size = entry.file_size();
            
            // Retrieve and format the creation time
            auto ftime = std::filesystem::last_write_time(entry);
            auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(ftime - decltype(ftime)::clock::now() + std::chrono::system_clock::now());
            std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);
            fileInfo.creationTime = std::asctime(std::localtime(&cftime));
            fileInfo.creationTime.pop_back(); // Remove the newline character

            files.push_back(fileInfo);
        }
        return files;
    }
};

#endif // GETFILES_H