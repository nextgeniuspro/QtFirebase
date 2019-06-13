#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

namespace qfb {
    class AdMobBanner;
    class AdmMobInterstitial;
    class Analytics;
    class Auth;
    class User;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event);
    void centerBanner();
    void updateBannerButtonText();
    
public slots:
    void onBannerLoaded();
    void onBannerLoading();
    void onInterstitialLoaded();
    void onInterstitialLoading();
    void onSignIn(qfb::User* user);

    void onButtonBannerClicked();
    void onButtonInterstitialClicked();
    void onButtonSignInClicked();
    void onButtonSignUpClicked();
    
private:
    Ui::MainWindow *ui;
    
    qfb::AdMobBanner *m_Banner;
    qfb::AdmMobInterstitial *m_Interstitial;
    qfb::Analytics *m_Analytics;
    qfb::Auth *m_Auth;

};

#endif // MAINWINDOW_H
