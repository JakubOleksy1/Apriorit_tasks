#ifndef JSONREP_H
#define JSONREP_H

#include "IRep.h"
#include <fstream>
#include "json.hpp"

class JsonRep : public IRep {
public:
    void generate(const std::vector<FileInfo>& files, const std::string& outputPath) const override {
        nlohmann::json j;
        for (const auto& file : files) {
            j.push_back({{"name", file.name}, {"size", file.size}, {"creationTime", file.creationTime}});
        }
        std::ofstream outFile(outputPath);
        outFile << j.dump(4);
    }
};

#endif // JSONREP_H