#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_mainframescene(new QGraphicsScene(this)),
    m_lb(cv::Scalar(100,120,100)), m_ub(cv::Scalar(255,255,255)),
    m_timer(new QTimer(this)), m_recording(false)
{
    ui->setupUi(this);

    // Setup graphic view
    m_backcolor.setRgb(0,0,0);
//    m_frametodisplay.setColor(5, m_backcolor.rgb());
    m_mainframescene->addPixmap(QPixmap::fromImage(m_frametodisplay));
    ui->graphicsView->setScene(m_mainframescene);

    // Setup cv capture
    m_cap.open(0);
    if(!m_cap.isOpened()){
        // errors
        return;
    }

    // Connect timer
    m_timer->start(30);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(procFrameAndRefresh()));

    // Connect GUI elements
    connect(ui->pBtn_Record, SIGNAL(clicked()), this, SLOT(on_pBtn_Record_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//
// Public slots
//

// procFrameAndRefresh ...
void MainWindow::procFrameAndRefresh(){
    m_cap.read(m_orig);

    if(m_orig.empty()) return;

    cv::inRange(m_orig, m_lb, m_ub, m_proc);

    // Convert cv to qt
    cv::cvtColor(m_orig, m_orig, cv::COLOR_BGR2RGB);
    m_frametodisplay = QImage(m_proc.data, m_proc.cols, m_proc.rows, m_proc.step, QImage::Format_Indexed8);

    // Display image
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
//    if(!m_recording){
//        // Connect timer
//        m_timer->start(30);
//        connect(m_timer, SIGNAL(timeout()), this, SLOT(procFrameAndRefresh()));
//    }
//    else{
//        // Disconnect timer
//        disconnect(m_timer, SIGNAL(timeout()), this, SLOT(procFrameAndRefresh()));
//        m_frametodisplay.setColor(0, m_backcolor.rgb());
//        m_timer->stop();
//    }
//    m_recording = !m_recording;
}
