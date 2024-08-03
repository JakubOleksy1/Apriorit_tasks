#ifndef IREP_H
#define IREP_H

#include <vector>
#include <string>
#include "FileInfo.h"

class IRep {
public:
    virtual ~IRep() = default;
    virtual void generate(const std::vector<FileInfo>& files, const std::string& outputPath) const = 0;
};

#endif // IREP_H