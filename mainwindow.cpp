#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <zlib.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("All Files (*)"));

    if (!filePath.isEmpty()) {
        ui->lineEdit->setText(filePath); // Set the selected file path to QLineEdit
    }
}


void MainWindow::on_pushButton_clicked()
{
    QString filePath = ui->lineEdit->text();

    if (!filePath.isEmpty()) {
        // Read the file
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly)) {
            QByteArray data = file.readAll();
            file.close();

            // Compress the data using zlib
            QByteArray compressedData;
            // (Insert zlib compression code here)

            // Save the compressed data to a new file
            QFile compressedFile(filePath + ".gz");
            if (compressedFile.open(QIODevice::WriteOnly)) {
                compressedFile.write(compressedData);
                compressedFile.close();
            }
        }
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QString filePath = ui->lineEdit->text();

    if (!filePath.isEmpty()) {
        // Read the compressed file
        QFile compressedFile(filePath);
        if (compressedFile.open(QIODevice::ReadOnly)) {
            QByteArray compressedData = compressedFile.readAll();
            compressedFile.close();

            // Decompress the data using zlib
            QByteArray decompressedData;
            // (Insert zlib decompression code here)

            // Save the decompressed data to a new file
            QFile decompressedFile(filePath + ".decompressed");
            if (decompressedFile.open(QIODevice::WriteOnly)) {
                decompressedFile.write(decompressedData);
                decompressedFile.close();
            }
        }
    }
}

