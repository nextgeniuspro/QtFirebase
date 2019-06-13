#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "firebase.h"
#include "admobbanner.h"
#include "admmobinterstitial.h"
#include "analytics.h"
#include "adrequest.h"
#include "authentification.h"
#include "user.h"
#include "platform.h"
#include <QFile>
#include <QTextStream>

using namespace qfb;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QtFirebase::instance()->setAdmobAppId("ca-app-pub-7485900711629006~3592060658");
    Firebase::instance()->setAdmobAppId("ca-app-pub-7485900711629006~7644692161");
    
    m_Banner = new AdMobBanner();
    m_Banner->setUnitId("ca-app-pub-7485900711629006/5760764857");
    m_Banner->setSize(QSize(320, 50));
    m_Banner->setVisible(true);
    m_Banner->adRequest()->setBirthday(9, 11, 2010);
    m_Banner->adRequest()->addTestDevice("820ec31e0fb17c012b6d63ad7380e17f");

    m_Interstitial = new AdmMobInterstitial();
    m_Interstitial->setUnitId("ca-app-pub-7485900711629006/9596724620");
    m_Interstitial->adRequest()->addTestDevice("820ec31e0fb17c012b6d63ad7380e17f");

    m_Analytics = new Analytics();
    m_Analytics->logEvent("Hello");
    m_Analytics->logEvent("Hello", "Value", "World!");
    m_Analytics->logEvent("Hello", "Integer", 1);
    m_Analytics->logEvent("Hello", "Double", 2.0);

    m_Auth = new Auth();
    
    connect(m_Banner, SIGNAL(loaded()), this, SLOT(onBannerLoaded()));
    connect(m_Banner, SIGNAL(loading()), this, SLOT(onBannerLoading()));
    
    connect(m_Interstitial, SIGNAL(loaded()), this, SLOT(onInterstitialLoaded()));
    connect(m_Interstitial, SIGNAL(loading()), this, SLOT(onInterstitialLoading()));
    
    connect(m_Auth, SIGNAL(signInCompleted(qfb::User*)), this, SLOT(onSignIn(qfb::User*)));
    
    connect(ui->bannerButton, SIGNAL(clicked()), this, SLOT(onButtonBannerClicked()));
    connect(ui->interstitialButton, SIGNAL(clicked()), this, SLOT(onButtonInterstitialClicked()));
    connect(ui->signUpButton, SIGNAL(clicked()), this, SLOT(onButtonSignUpClicked()));
    connect(ui->signInButton, SIGNAL(clicked()), this, SLOT(onButtonSignInClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    centerBanner();
}

void MainWindow::centerBanner()
{
    QPoint position((width() - m_Banner->size().width()) * 0.5f, 0.0f);
    m_Banner->setPosition(position);
}

void MainWindow::updateBannerButtonText()
{
    bool isVisible = m_Banner->visible();
    if (isVisible)
    {
        ui->bannerButton->setText("Hide Banner");
    }
    else
    {
        ui->bannerButton->setText("Show Banner");
    }
}

void MainWindow::onBannerLoaded()
{
    updateBannerButtonText();
    ui->bannerButton->setEnabled(true);
    
    centerBanner();
}

void MainWindow::onBannerLoading()
{
    ui->bannerButton->setText("Loading..");
    ui->bannerButton->setEnabled(false);
}

void MainWindow::onButtonBannerClicked()
{
    bool isVisible = m_Banner->visible();
    m_Banner->setVisible(!isVisible);
    updateBannerButtonText();
}

void MainWindow::onButtonInterstitialClicked()
{
    if (m_Interstitial->isLoaded())
    {
        m_Interstitial->show();
        m_Interstitial->setUnitId("ca-app-pub-7485900711629006/9596724620");
    }
}

void MainWindow::onButtonSignUpClicked()
{
    m_Auth->signUp(ui->emailEdit->text(), ui->passwordEdit->text());
}

void MainWindow::onButtonSignInClicked()
{
    if (m_Auth->user()) {
        m_Auth->signOut();
    } else {
        m_Auth->signIn(ui->emailEdit->text(), ui->passwordEdit->text());
    }
}

void MainWindow::onSignIn(qfb::User* user)
{
    ui->signInButton->setText(user ? "OK" : "FAIL");
}

void MainWindow::onInterstitialLoaded()
{
    ui->interstitialButton->setText("Show Interstitial");
    ui->interstitialButton->setEnabled(true);
}

void MainWindow::onInterstitialLoading()
{
    ui->interstitialButton->setText("Loading..");
    ui->interstitialButton->setEnabled(false);
}
