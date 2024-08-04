#ifndef TXTREP_H
#define TXTREP_H

#include "IRep.h"
#include <fstream>

class TxtRep : public IRep {
public:
    void generate(const std::vector<FileInfo>& files, const std::string& outputPath) const override {
        std::ofstream outFile(outputPath);
        for (const auto& file : files) {
            outFile << "File: " << file.name << "\n";
            outFile << "Size: " << file.size << " bytes\n";
            outFile << "Creation Time: " << file.creationTime << "\n";
            outFile << "--------------------------\n";
        }
    }
};

#endif // TXTREP_H