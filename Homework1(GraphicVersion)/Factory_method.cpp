#include "GetFiles.h"
#include <iostream>
#include <vector>
#include <string>

std::vector<FileInfo> processFiles(const std::string& folderPath) {
    auto files = GetFiles::getFiles(folderPath);
    return files;
}