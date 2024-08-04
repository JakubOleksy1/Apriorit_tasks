#ifndef FACTORY_METHOD_H
#define FACTORY_METHOD_H

#include <vector>
#include <string>
#include "FileInfo.h" // Include the definition of the File structure

std::vector<FileInfo> processFiles(const std::string& folderPath);

#endif // FACTORY_METHOD_H