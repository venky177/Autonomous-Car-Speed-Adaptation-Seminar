#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int x,y,di,myx[1000],myy[1000],count;
    float mya[1000];
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void draw();
    void on_pushButton_clicked();
    void mh();
    void md();
    void mv();
    void anticipation();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
