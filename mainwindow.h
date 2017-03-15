#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt libs
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>

// cv libs
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

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
    QGraphicsScene *m_mainframescene;
    QImage m_frametodisplay, m_allblack;
    QPixmap *m_lastframe;
    QColor m_backcolor;
    // cv vars
    cv::VideoCapture m_cap;
    cv::Mat m_orig, m_proc, m_blackmat;

    // Timer
    QTimer *m_timer;

    MatImageProcessor *m_imageprocessor;

    bool m_recording, m_previewing;

private slots:
    void on_pBtn_Record_clicked();
};

#endif // MAINWINDOW_H
