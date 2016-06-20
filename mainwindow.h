#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimerEvent>
#include "httprequestworker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_actionAbout_triggered();

public Q_SLOTS:
    void handleResponse(HttpRequestWorker *worker);

private:
    Ui::MainWindow *ui;
    int timerID;
    void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H
