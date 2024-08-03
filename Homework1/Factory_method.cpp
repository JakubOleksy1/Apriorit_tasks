#include <stdio.h>
#include <iostream>
#include "GetFiles.h"

int main() {
    try {
        std::string folderPath;
        std::cout << "Please enter you folder path: ";
        std::cin >> folderPath;

        auto files = GetFiles::getFiles(folderPath);
        std::cout << "Number of files found: " << files.size() << std::endl;

        for (const auto& file : files) {
            std::cout << "File Name: " << file.name << std::endl;
            std::cout << "File Size: " << file.size << " bytes" << std::endl;
            std::cout << "Creation Time: " << file.creationTime << std::endl;
            std::cout << "-------------------------" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}