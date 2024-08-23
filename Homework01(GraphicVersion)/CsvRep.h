#ifndef CSVREP_H
#define CSVREP_H

#include "IRep.h"
#include <fstream>

class CsvRep : public IRep {
public:
    void generate(const std::vector<FileInfo>& files, const std::string& outputPath) const override {
        std::ofstream outFile(outputPath);
        outFile << "File,Size,Creation Time\n";
        for (const auto& file : files) {
            outFile << file.name << "," << file.size << "," << file.creationTime << "\n";
        }
    }
};

#endif // CSVREP_H