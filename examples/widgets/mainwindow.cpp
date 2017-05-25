#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qtfirebase.h"
#include "qtadmobbanner.h"
#include "qtadmmobinterstitial.h"
#include "qtanalytics.h"
#include <QResizeEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QtFirebase::instance()->setAdmobAppId("ca-app-pub-7485900711629006~3592060658");
    
    banner = new QtAdMobBanner();
    banner->setUnitId("ca-app-pub-7485900711629006/5068793852");
    banner->setSize(QSize(320, 50));
    banner->setVisible(true);

    QtAdmMobInterstitial *interstitial = new QtAdmMobInterstitial();
    interstitial->setUnitId("ca-app-pub-7485900711629006/2878880251");
    //interstitial->show();

    QtAnalytics *analytics = new QtAnalytics();
    analytics->logEvent("Hello!");
    analytics->logEvent("Hello!", "Value", "World!");
    analytics->logEvent("Hello!", "Integer", 1);
    analytics->logEvent("Hello!", "Double", 2.0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    qDebug() << event->size().width() << ", " << event->size().height();
    QPoint position((event->size().width() - banner->size().width()) * 0.5f, 0.0f);
    banner->setPosition(position);
}
