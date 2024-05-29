#include "mainwindow.h"

#include <QApplication>

#if 1
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
#else

#include <QApplication>
#include <QFontDatabase>
#include <QPainter>
#include <QImage>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 加载字体
    QFontDatabase fontDb;
    int fontId = fontDb.addApplicationFont("./STXINGKA.TTF"); // 替换为你的ttf文件路径
    if (fontId < 0) {
        qDebug() << "Failed to load font.";
        return -1;
    }

    // 创建一个QImage来绘制字模
    QImage image(256, 256, QImage::Format_Mono);
    image.fill(Qt::white);

    QPainter painter;
    painter.begin(&image);
    // painter.setFont(QFont("YourFontName", 20)); // 替换为你的字体名称和大小
    painter.setPen(Qt::black);

    // 绘制字符'A'
    painter.drawText(10, 150, "A");

    painter.end();

    // 保存图像
    image.save("output.png");

    return app.exec();
}

#endif
