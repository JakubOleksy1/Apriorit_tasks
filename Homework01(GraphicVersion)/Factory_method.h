#ifndef FACTORY_METHOD_H
#define FACTORY_METHOD_H

#include <vector>
#include <string>
#include "FileInfo.h" 

std::vector<FileInfo> processFiles(const std::string& folderPath);

#endif // FACTORY_METHOD_H