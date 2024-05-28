#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *event);

    QTimer *timer = NULL;
    uint32_t unicode = 0x4E00;  //unicode 汉字起始

    int32_t x0 = 120;
    int32_t y0 = 120;

    void draw_point(QPainter &painter,int x, int y, QColor color, bool fill);
    void timer_update(void);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
