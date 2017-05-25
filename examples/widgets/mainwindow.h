#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class QtAdMobBanner;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
protected:
    virtual void resizeEvent(QResizeEvent *event);

private:
    Ui::MainWindow *ui;
    QtAdMobBanner *banner;
};

#endif // MAINWINDOW_H
