
"""
# 方式1
import sys
from PyQt5.QtWidgets import QApplication,QWidget


if __name__ == '__main__':
    # 必须创建应用对象
    app = QApplication(sys.argv)

    # QWidget是PyQt5所有界面类的基础类
    w = QWidget()
    w.setWindowTitle('QWidget')
    w.resize(400, 300)
    w.show()

    sys.exit(app.exec_())
"""


import sys
from PyQt5.QtWidgets import (QApplication, QWidget, QToolTip, QPushButton,
                             QMessageBox, QDesktopWidget, QFrame)
from PyQt5.QtGui import QIcon, QFont, QColor
from PyQt5.QtCore import QCoreApplication, qrand, qsrand, QTime


class Windows(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()
        time = QTime(0, 0, 0).secsTo(QTime.currentTime())
        qsrand(time)

    def initUI(self):
        self.setWindowTitle('Apaki示例')
        self.setWindowIcon(QIcon('./res/apaki.ico'))
        self.setGeometry(400, 300, 400, 300)
        # 设置窗口居中显示到屏幕中心处
        # self.center()

        QToolTip.setFont(QFont('宋体', 10))
        self.setToolTip('Apaki界面示例')

        exitBt = QPushButton('退出', self)
        exitBt.setFont(QFont('华文行楷', 12))
        exitBt.setToolTip('按下按键，退出程序')
        exitBt.resize(exitBt.sizeHint())
        exitBt.move(300, 250)
        # 信号槽：退出
        exitBt.clicked.connect(QCoreApplication.instance().quit)

        self.font = QFont('华文行楷', 12)
        confirmBt = QPushButton("确认", self)
        confirmBt.setFont(self.font)
        confirmBt.setToolTip('按下随机，弹起黑色')
        confirmBt.move(300, 200)

        confirmBt.setCheckable(True)
        confirmBt.clicked[bool].connect(self.confirmBtEvent)

        aboutBt = QPushButton("关于", self)
        aboutBt.setFont(self.font)
        aboutBt.setToolTip('显示程序相关信息')
        aboutBt.move(300, 150)
        aboutBt.clicked.connect(self.aboutEvent)

        self.color = QColor(0, 0, 0)
        self.frame = QFrame(self)
        self.frame.setGeometry(30, 30, 200, 200)
        self.frame.setStyleSheet("QWidget { background-color: %s }" %
                                 self.color.name())

    def aboutEvent(self, event):
        QMessageBox.about(self, '关于',
                                '时间：2018.11.15\n作者：jianfeng\n'
                                '版本：v1.0.00')

    def center(self):
        """
            将窗口放置在屏幕正中央的一种方式
        """
        # 获取主窗口的一个特定矩形
        qr = self.frameGeometry()
        # 计算出显示器的绝对值并从这个绝对值中我们获得屏幕的中心点
        cp = QDesktopWidget().availableGeometry().center()
        # 将矩形的中心设置到屏幕中心处。
        qr.moveCenter(cp)
        # 移动了应用窗口的左上方的点到qr矩形的左上方的点
        self.move(qr.topLeft())

    def closeEvent(self, event):
        """
            通过窗口右上角进行关闭时
        """
        reply = QMessageBox.question(self, '退出程序',
                                     '请确认是否退出？',
                                     QMessageBox.Yes | QMessageBox.No,
                                     # 最后这个参数表示是初始焦点位置(若无该参数，则默认是Yes)
                                     QMessageBox.Yes)
        if reply == QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()

    def confirmBtEvent(self, pressed):
        # print('pressed', pressed)
        if not pressed:
            value = 0
            self.color.setRgb(value, value, value)
        else:
            r = qrand() % 256
            g = qrand() % 256
            b = qrand() % 256
            self.color.setRgb(r, g, b)

        self.frame.setStyleSheet("QWidget { background-color: %s }" %
                                 self.color.name())


if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = Windows()
    w.show()

    sys.exit(app.exec_())
