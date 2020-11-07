#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef ALARMGUI_H
#define ALARMGUI_H

#include <QMainWindow>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QTimeEdit>
#include <QListWidget>
#include <QLabel>

#include <QTime>
#include <QTimer>

#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class AlarmGUI; }
QT_END_NAMESPACE

class AlarmGUI : public QMainWindow
{
    Q_OBJECT

public:
    AlarmGUI(QWidget *parent = nullptr);
    ~AlarmGUI();

public slots:
    void timerResponse();
    void addAlarm();
    void startClock();
    void stopClock();

private:
    Ui::AlarmGUI *ui;

    void initUI();

    QVBoxLayout *centerLay;
    QHBoxLayout *hlay_edit;
    QHBoxLayout *hlay_viewer;
    QHBoxLayout *hlay_ctrlBtns;

    QLabel *lb_time;
    QTimeEdit *timeEdit;
    QPushButton *btn_Add;
    QListWidget *listWidget;
    QPushButton *btn_Start;
    QPushButton *btn_Stop;

    QList<QTime> m_alarmsList;
    QTimer *mainTimer;
    QTime lastAlarm;
};
#endif // ALARMGUI_H
