#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStandardPaths>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_AddBtn_clicked();

    void on_removebtn_clicked();

    void on_RemoveallBtn_clicked();

private:
    Ui::MainWindow *ui;

    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "\\ToDoListApp.txt";
};
#endif // MAINWINDOW_H
