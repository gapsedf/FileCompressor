#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QByteArray>
#include <QMessageBox>
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
            uLongf compressedSize = compressBound(data.size());
            QByteArray compressedData(compressedSize, 0);
            int result = compress(reinterpret_cast<Bytef*>(compressedData.data()), &compressedSize, reinterpret_cast<const Bytef*>(data.data()), data.size());

            if (result != Z_OK) {
                QMessageBox::warning(this, tr("Error"), tr("Compression failed!"));
                return;
            }

            compressedData.resize(compressedSize);

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
            uLongf decompressedSize = compressedData.size() * 4; // Estimate decompressed size
            QByteArray decompressedData(decompressedSize, 0);
            int result = uncompress(reinterpret_cast<Bytef*>(decompressedData.data()), &decompressedSize, reinterpret_cast<const Bytef*>(compressedData.data()), compressedData.size());

            if (result != Z_OK) {
                QMessageBox::warning(this, tr("Error"), tr("Decompression failed!"));
                return;
            }

            decompressedData.resize(decompressedSize);

            // Save the decompressed data to a new file
            QFile decompressedFile(filePath + ".decompressed");
            if (decompressedFile.open(QIODevice::WriteOnly)) {
                decompressedFile.write(decompressedData);
                decompressedFile.close();
            }
        }
    }
}

