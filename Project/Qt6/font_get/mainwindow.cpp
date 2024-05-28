#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPainter>
#include <QTimer>


#include <QApplication>
#include <QFontDatabase>
#include <QPainter>
#include <QImage>
#include <QDebug>
#include <QFontMetrics>

#include <QByteArray>

#define FONT_SIZE          16 // 16/64

// #define FONT_TEXT       "好"
// #define FONT_TEXT       "美"
#define FONT_TEXT          "\u54c8"     //哈 -> unicode


// #define FONT_NAME       "华文琥珀"
// #define FONT_NAME       "微软雅黑"
//#define FONT_NAME       "华文行楷"
// #define FONT_NAME       "新宋体"
// #define FONT_NAME       "黑体"
// #define FONT_NAME       "等线 Blod"

#define FONT_NAME       "宋体"
// #define FONT_NAME       ""



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::timer_update);
    // timer->start(200);  // ms
    timer->start(10);  // ms
}

MainWindow::~MainWindow()
{
    delete timer;

    delete ui;
}

void MainWindow::timer_update(void)
{
    this->update();
}

void MainWindow::draw_point(QPainter &painter,int i, int j, QColor color, bool fill)
{
    painter.setPen(color);
    // painter.drawPoint(x, y);

    int width = 10;
    int height = 10;
    int x = this->x0 + i * width;
    int y = this->y0 + j * height;

    if(fill)
    {
        painter.fillRect(x, y, width, height, color);
    }
    else
    {
        painter.drawRect(x, y, width, height);
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    // window
    QPainter painter(this);

    painter.drawRect(0, 0, FONT_SIZE, FONT_SIZE);
    // painter.fillRect(240,240,240,240,QColor(255,0,0,255));
    // painter.fillRect(this->rect(), QColor(255,255,255,255));

    static uint32_t count = this->unicode;
    count++;

    QString str = QString(QChar(count));

    QFont font(FONT_NAME);
    font.setPixelSize(FONT_SIZE);
    // font.setPointSize(FONT_SIZE);

    // QFontMetrics font_metrics(font);
    // int font_height = font_metrics.height();

    //windows
    painter.setPen(QColor("black"));
    painter.setFont(font);
    painter.drawText(QRect(0,0,FONT_SIZE,FONT_SIZE),Qt::AlignCenter, str);
    QString str3 = QString::number(count, 16);
    painter.drawText(QRect(100, 0, FONT_SIZE*5, FONT_SIZE),Qt::AlignCenter, str3);

    // image
    QImage image(FONT_SIZE, FONT_SIZE, QImage::Format_RGB32);
    image.fill(Qt::white);

    QPainter painter2(&image);
    painter2.setPen(QColor("black"));
    painter2.setFont(font);
    painter2.drawText(QRect(0,0,FONT_SIZE, FONT_SIZE),Qt::AlignCenter, str);
    // image.save("output.bmp");

    for(uint32_t i = 0; i < image.width(); i++)
    {
        for(uint32_t j = 0; j < image.height(); j++)
        {
            QColor color = image.pixelColor(i,j);
            if(color == "black")
            {
                this->draw_point(painter, i, j, QColor("blue"), true);
            }
            else
            {
                this->draw_point(painter, i, j, QColor("red"), false);
            }
        }
    }
}
