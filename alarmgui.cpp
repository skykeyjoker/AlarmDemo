#include "alarmgui.h"
#include "ui_alarmgui.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

AlarmGUI::AlarmGUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AlarmGUI)
{
    ui->setupUi(this);

    // Init UI
    initUI();

    // Init Timer
    mainTimer = new QTimer(this);

    // Bind signals and slots
    connect(btn_Add, &QPushButton::clicked, this, &AlarmGUI::addAlarm);
    connect(btn_Start,&QPushButton::clicked, this, &AlarmGUI::startClock);
    connect(btn_Stop,&QPushButton::clicked, this, &AlarmGUI::stopClock);
    connect(mainTimer, &QTimer::timeout, this, &AlarmGUI::timerResponse);
}

AlarmGUI::~AlarmGUI()
{
    delete ui;
}

void AlarmGUI::timerResponse()
{
    QTime currentTime = QTime::currentTime();
    qDebug()<<"Timer timeout"<<QTime::currentTime().toString("HH:mm:ss");
    for(int i=0; i<m_alarmsList.size(); ++i)
    {
        QTime alarm = m_alarmsList.at(i);
        //qDebug()<<alarm<<lastAlarm;
        if (alarm.hour() == currentTime.hour() && alarm.minute() == currentTime.minute() && (alarm.hour()!=lastAlarm.hour() || alarm.minute()!=lastAlarm.minute()))
        {
            //qDebug()<<lastAlarm;
            lastAlarm = alarm;
            //qDebug()<<lastAlarm;
            qDebug()<<"Ding Ding Ding!"<<alarm;
        }
        //qDebug()<<i;
    }
    //qDebug()<<lastAlarm;
}

void AlarmGUI::addAlarm()
{
    m_alarmsList.push_back(timeEdit->time());
    listWidget->addItem(timeEdit->time().toString("HH:mm:ss"));

    qDebug()<<"Add alarm:"<<timeEdit->time();
    qDebug()<<m_alarmsList.size();
//    for(auto alarm : m_alarmsList)
//    {
//        qDebug()<<alarm;
//    }
}

void AlarmGUI::startClock()
{
    mainTimer->start(500);
    qDebug()<<"Timer Started";
}

void AlarmGUI::stopClock()
{
    mainTimer->stop();
    qDebug()<<"Timer stopped";
}

void AlarmGUI::initUI()
{
    centerLay = new QVBoxLayout(centralWidget());

    // Hlay_edit
    hlay_edit = new QHBoxLayout;
    lb_time = new QLabel("时间：");
    timeEdit = new QTimeEdit;
    btn_Add = new QPushButton("添加");

    hlay_edit->addStretch();
    hlay_edit->addWidget(lb_time);
    hlay_edit->addStretch();
    hlay_edit->addWidget(timeEdit);
    hlay_edit->addStretch();
    hlay_edit->addWidget(btn_Add);
    hlay_edit->addStretch();
//    hlay_edit->setStretchFactor(lb_time,1);
//    hlay_edit->setStretchFactor(timeEdit,2);
//    hlay_edit->setStretchFactor(btn_Add,1);

    // Hlay_viewer
    hlay_viewer = new QHBoxLayout;
    listWidget = new QListWidget;

    hlay_viewer->addWidget(listWidget);

    // Hlay_crtlBtns
    hlay_ctrlBtns = new QHBoxLayout;
    btn_Start = new QPushButton("启动闹钟");
    btn_Stop = new QPushButton("停止闹钟");

    hlay_ctrlBtns->addStretch();
    hlay_ctrlBtns->addWidget(btn_Start);
    hlay_ctrlBtns->addStretch();
    hlay_ctrlBtns->addWidget(btn_Stop);
    hlay_ctrlBtns->addStretch();

    centerLay->addLayout(hlay_edit);
    centerLay->addLayout(hlay_viewer);
    centerLay->addLayout(hlay_ctrlBtns);
}

