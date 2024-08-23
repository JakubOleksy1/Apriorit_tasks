#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Factory_method.h"
#include "RepFactory.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_browseButton_clicked() {
    QString folderPath = QFileDialog::getExistingDirectory(this, "Select Folder");
    if (folderPath.isEmpty()) {
        return;
    }

    ui->folderPathLineEdit->setText(folderPath);

    try {
        auto files = processFiles(folderPath.toStdString());
        QString result;
        result += "Number of files found: " + QString::number(files.size()) + "\n";

        for (const auto& file : files) {
            result += "File Name: " + QString::fromStdString(file.name) + "\n";
            result += "File Size: " + QString::number(file.size) + " bytes\n";
            result += "Creation Time: " + QString::fromStdString(file.creationTime) + "\n";
            result += "-------------------------\n";
        }

        ui->resultTextEdit->setPlainText(result);

        auto csvReport = RepFactory::createReport(RepFactory::ReportType::CSV);
        csvReport->generate(files, "output.csv");

        auto jsonReport = RepFactory::createReport(RepFactory::ReportType::JSON);
        jsonReport->generate(files, "output.json");

        auto txtReport = RepFactory::createReport(RepFactory::ReportType::TXT);
        txtReport->generate(files, "output.txt");

        QMessageBox::information(this, "Success", "Reports generated and saved to output.csv, output.json, and output.txt");

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}