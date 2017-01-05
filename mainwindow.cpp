#include "mainwindow.h"
#include "ui_mainwindow.h"

// Std libs
#include "iostream"

// Qt libs
#include <QSignalBlocker>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_mainframescene(new QGraphicsScene(this)),
    m_lb(cv::Scalar(20,60,60)), m_ub(cv::Scalar(255,90,255)), m_black(cv::Scalar(0,0,0)),
    m_timer(new QTimer(this)), m_recording(false), m_previewing(false)
{
    ui->setupUi(this);

    // Setup cv capture
    m_cap.open(0);
    if(!m_cap.isOpened()){
        // errors
        return;
    }

    // Store blank frame
    m_cap.read(m_orig);
    if(m_orig.empty()) exit(EXIT_FAILURE);
    cv::Mat imgtemp(ui->graphicsView->height(), ui->graphicsView->width(), m_orig.type(), m_black);
    imgtemp.convertTo(m_blackmat, cv::COLOR_BGR2RGB);
    m_allblack = QImage((uchar*) m_blackmat.data, m_blackmat.cols, m_blackmat.rows, m_blackmat.step, QImage::Format_Indexed8);

    // Apply the black screen
    ui->graphicsView->setScene(m_mainframescene);
    m_mainframescene->addPixmap(QPixmap::fromImage(m_allblack));
    ui->graphicsView->show();

    // Connect timer
    m_timer->start(60);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(procFrameAndRefresh()));
}

MainWindow::~MainWindow()
{
    m_cap.release();
    delete ui;
}

//
// Public slots
//

// procFrameAndRefresh ...
void MainWindow::procFrameAndRefresh(){
    // Display image if previewing
    if(!m_previewing){
        m_frametodisplay = m_allblack;
    }
    else{
        m_cap.read(m_orig);

        if(m_orig.empty()) exit(EXIT_SUCCESS);

        // Process image
//        cv::Mat mask;
        inRange(m_orig, m_lb, m_ub, mask);
//        m_proc = cv::Mat()

        // Convert cv to qt
        cv::Mat imgtemp = cv::Mat(m_proc.rows, m_proc.cols, m_proc.type(), m_proc.data, m_proc.step);
        cv::cvtColor(imgtemp, imgtemp, cv::COLOR_GRAY2RGB);
        m_frametodisplay = QImage(m_proc.data, m_proc.cols, m_proc.rows, m_proc.step, QImage::Format_Indexed8);
    }
    // Display new image
    m_mainframescene->addPixmap(QPixmap::fromImage(m_frametodisplay));
}

// eventFilter ...
bool MainWindow::eventFilter(QObject *watched, QEvent *event){
    // Maybe do things?
    return QMainWindow::eventFilter(watched, event);
}

//
// Private slots
//

// on_pBtn_Record_clicked starts or stops recording
void MainWindow::on_pBtn_Record_clicked(){
    QSignalBlocker blocker(this);
    m_recording = !m_recording;
    m_previewing = !m_previewing;
    if(m_recording) std::cout << "Started recording\n";
    else std::cout << "Stopped recording\n";
}
