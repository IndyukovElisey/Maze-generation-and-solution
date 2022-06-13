#ifndef MAZE_H
#define MAZE_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <cmath>
#include <QTime>
#include <QColor>
#include <QVector>


struct pair
{
    int y;
    int x;
};

class Maze: public QWidget
{
    Q_OBJECT

    const int height;
    const int width;
    bool** matrix;
    QVector <pair> solution;

    int timeGeneration;
    int timePathfind;

    QTime time;
    void clearCells();  // очистка поля лабиринта

public:
    int path_found;

    explicit Maze(int a, int b, QWidget *parent = 0);

    virtual void paintEvent(QPaintEvent * event);   // обработчик события отрисовки

public slots:

    void generate1();
    void generate2();
    void solve1();
    void solve2();

    int getTimeGeneration() { return timeGeneration;}
    int getTimePathfind() { return timePathfind;}

};


#endif // MAZE_H
