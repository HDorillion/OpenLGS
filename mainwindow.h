#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// C++ libs
#include <memory>

// Qt libs
#include <QMainWindow>
#include <QGraphicsScene>
#include <QSlider>
#include <QTimer>

// cv libs
#include "opencv2/core.hpp"

// Wrapper libs
#include "camera.h"

class MatImageProcessor;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void procFrameAndRefresh();
    bool eventFilter(QObject *watched, QEvent *event);

private:
    // GUI elements
    Ui::MainWindow *ui;
    QGraphicsScene *mainframescene_;
    QImage frametodisplay_, allblack_;
    QPixmap *lastframe_;
    QColor backcolor_;

    // Camera and camera images
    cv::Mat cvimg_;
    Camera cap_;

    // Timer
    QTimer *timer_ = new QTimer(this);

    MatImageProcessor *imageprocessor_;

    bool recording_, previewing_;

private slots:
    void on_pBtn_Record_clicked();
};

#endif // MAINWINDOW_H
