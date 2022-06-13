#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Maze.h"
#include <QColor>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QList<Maze*> data;

public slots:
    void blockInterface();      // блокирование интерфейса для того что бы можно было нажать сгенерировать лабиринт, только после завершения
                                // передыдущей генерации
    void unBlockInterface();    // разблокирование интерфейса

private slots:
    void on_pushButton_clicked();

    void on_spinBox_valueChanged();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
