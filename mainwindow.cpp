#include "mainwindow.h"
#include "ui_mainwindow.h"

// Std libs
#include "iostream"

// Qt libs
#include <QSignalBlocker>

// Image processor
#include "matimageprocessor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_mainframescene(new QGraphicsScene(this)),
    m_timer(new QTimer(this)), m_imageprocessor(new MatImageProcessor()),
    m_recording(false), m_previewing(false)
{
    ui->setupUi(this);

    // Setup cv capture
    m_cap.open(0);
    if(!m_cap.isOpened()){
        // errors
        return;
    }

    cv::Scalar blanket = cv::Scalar(0,0,0);

    // Store blank frame
    m_cap.read(m_orig);
    m_cap.release();
    if(m_orig.empty()) exit(EXIT_FAILURE);
    cv::Mat imgtemp(ui->graphicsView->height(), ui->graphicsView->width(), m_orig.type(), blanket);
    MatImageProcessor::Mat2QImage(imgtemp, m_allblack);

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
    delete m_imageprocessor;
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
         m_imageprocessor->processImage(m_orig, m_frametodisplay);
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
    if(m_recording){
        m_cap.release();
        m_recording = m_previewing = false;
        std::cout << "Stopped recording\n";
    }
    else{
        if(!m_cap.open(0)){
            // Failure to open
            return;
        }
        m_recording = m_previewing = true;
        std::cout << "Started recording\n";
    }
}

