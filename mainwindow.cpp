#include "mainwindow.h"
#include "ui_mainwindow.h"

// Std libs
#include <iostream>

// Qt libs
#include <QSignalBlocker>

// Image processor
#include "matimageprocessor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mainframescene_(new QGraphicsScene(this)),
    imageprocessor_(new MatImageProcessor()),
    recording_(false), previewing_(false)
{
    ui->setupUi(this);

    // Apply the black screen
    ui->graphicsView->setScene(mainframescene_);
    ui->graphicsView->show();

    // Connect timer
    timer_->start(30);
    connect(timer_, SIGNAL(timeout()), this, SLOT(procFrameAndRefresh()));
}

MainWindow::~MainWindow()
{
    cap_.release();
    delete ui;
}

//
// Public slots
//

// procFrameAndRefresh ...
void MainWindow::procFrameAndRefresh(){
    // Display image if previewing
    if(!previewing_){
        frametodisplay_ = allblack_;
    }
    else{
        // Process image
        cap_.getFrame(cvimg_);
        imageprocessor_->processImage(cvimg_, frametodisplay_);
    }
    // Display new image
    mainframescene_->addPixmap(QPixmap::fromImage(frametodisplay_));
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
    if(recording_){
        cap_.release();
        recording_ = previewing_ = false;
        std::cout << "Stopped recording\n";
    }
    else{
        if(!cap_.open(0)){
            // Failure to open
            return;
        }
        cap_.getEmptyFrame(cvimg_);
        if(!cvimg_.empty()){
            cap_.open(0);
            MatImageProcessor::Mat2QImage(cvimg_, allblack_);
            recording_ = previewing_ = true;
            std::cout << "Started recording\n";
        }
    }
}

