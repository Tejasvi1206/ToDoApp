#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QStandardPaths>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);


    QFile file(path);

    if(!file.open(QIODevice::ReadWrite)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);
    while(!in.atEnd()) {
        QListWidgetItem* item = new QListWidgetItem(in.readLine(), ui->listWidget);
        ui->listWidget->addItem(item);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }

    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;

    QFile file(path);

    if(!file.open(QIODevice::ReadWrite)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream out(&file);

    for (int i = 0; i < ui->listWidget->count(); ++i) {
        out<<ui->listWidget->item(i)->text()<<"\n";
    }

    file.close();
}

void MainWindow::on_AddBtn_clicked()
{
    QString taskText = ui->txtTask->text().trimmed();
    if (taskText.isEmpty()) {
        QMessageBox::warning(this, "Empty Task", "Please enter a task before adding.");
        return;
    }
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem* existingItem = ui->listWidget->item(i);
        if (existingItem->text().compare(taskText, Qt::CaseInsensitive) == 0) {
            QMessageBox::information(this, "Duplicate Task", "This task already exists.");
            return;
        }
    }
    QListWidgetItem* item = new QListWidgetItem(ui->txtTask->text(), ui->listWidget);
    ui->listWidget->addItem(item);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    ui->txtTask->clear();
    ui->txtTask->setFocus();


}


void MainWindow::on_removebtn_clicked()
{
    QListWidgetItem* item = ui->listWidget->takeItem(ui->listWidget->currentRow());
    delete item;
}


void MainWindow::on_RemoveallBtn_clicked()
{
    ui->listWidget->clear();
}

