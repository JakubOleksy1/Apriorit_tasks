#include <iostream>
#include "GetFiles.h"
#include "RepFactory.h"

int main() {
    try {
        std::string folderPath;
        std::cout << "Please enter your folder path: ";
        std::cin >> folderPath;

        auto files = GetFiles::getFiles(folderPath);
        std::cout << "Number of files found: " << files.size() << std::endl;

        for (const auto& file : files) {
            std::cout << "File Name: " << file.name << std::endl;
            std::cout << "File Size: " << file.size << " bytes" << std::endl;
            std::cout << "Creation Time: " << file.creationTime << std::endl;
            std::cout << "-------------------------" << std::endl;
        }

        auto csvReport = RepFactory::createReport(RepFactory::ReportType::CSV);
        csvReport->generate(files, "output.csv");
        std::cout << "CSV report generated and saved to output.csv" << std::endl;

        auto jsonReport = RepFactory::createReport(RepFactory::ReportType::JSON);
        jsonReport->generate(files, "output.json");
        std::cout << "JSON report generated and saved to output.json" << std::endl;

        auto txtReport = RepFactory::createReport(RepFactory::ReportType::TXT);
        txtReport->generate(files, "output.txt");
        std::cout << "TXT report generated and saved to output.txt" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

//NOTE1: All .h files can be separated into .h file and .cpp file to make the code more readable but for the sake of simplicity I have kept them in the same file.
//NOTE2: They all have one function each so there is no need to separate them since in would create unnecessary files.