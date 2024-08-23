#ifndef REPFACTORY_H
#define REPFACTORY_H

#include "IRep.h"
#include "TxtRep.h"
#include "CsvRep.h"
#include "JsonRep.h"
#include <memory>
#include <string>

class RepFactory {
public:
    enum class ReportType { TXT, CSV, JSON };

    static std::unique_ptr<IRep> createReport(ReportType type) {
        switch (type) {
            case ReportType::TXT:
                return std::make_unique<TxtRep>();
            case ReportType::CSV:
                return std::make_unique<CsvRep>();
            case ReportType::JSON:
                return std::make_unique<JsonRep>();
            default:
                throw std::invalid_argument("Unknown report type");
        }
    }
};

#endif // REPFACTORY_H