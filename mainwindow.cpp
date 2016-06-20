#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->statusBar()->setSizeGripEnabled(false);
    this->setFixedSize(this->maximumSize());

    ui->setupUi(this);

    timerID = startTimer(900); // set less than 1 sec
}

MainWindow::~MainWindow()
{
    killTimer(timerID);
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event){
    if(event->timerId() == timerID){
        QTime time = QTime::currentTime();
        QString text = time.toString("hh:mm:ss");
        if ((time.second() % 2) == 0){
            text[5] = ' ';
        }
        ui->lcdNumber->display(text);
    }
}

void MainWindow::handleResponse(HttpRequestWorker *worker){
    if (worker->error_type == QNetworkReply::NoError) {
        // communication was successful
        // we got a JSON response, let's parse it
        QJsonDocument json = QJsonDocument::fromJson(worker->response);
        QJsonObject jobj = json.object();
        QJsonValue value = jobj.value("message");
        if(value.toString() == "success"){
            value = jobj.value("md5");
            ui->lineEdit_2->setText(value.toString().toUpper());
        }else{
            QMessageBox::information(this,"Error", value.toString());
        }
    }
    else {
        // an error occurred
        QString msg = "Error: " + worker->error_str;
        QMessageBox::information(this, "", msg);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QString url_str = "http://localhost/rest_example.php";

    HttpRequestInput input(url_str, "POST");

    QString text = ui->lineEdit->text();

    input.add_var("id", text);

    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker, SIGNAL(on_execution_finished(HttpRequestWorker*)), this, SLOT(handleResponse(HttpRequestWorker*)));
    worker->execute(&input);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgbox;
    msgbox.setWindowTitle("About");
    msgbox.setText("This is a simple MD5 calculator\n\nUsing QT5 and RESTFul service\nCoded by: Tejashwi Kalp Taru\n\n\nDo you want to visit his page?");
    msgbox.setStandardButtons(QMessageBox::Yes);
    msgbox.addButton(QMessageBox::No);

    if(msgbox.exec() == QMessageBox::Yes){
        QString link = "https://www.facebook.com/tejashwikalptaru";
        QDesktopServices::openUrl(QUrl(link));
    }
}
