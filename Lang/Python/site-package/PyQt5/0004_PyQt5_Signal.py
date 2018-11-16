
import sys
from PyQt5.QtWidgets import (QApplication, QWidget, QLCDNumber,
                             QSlider, QVBoxLayout, QHBoxLayout,
                             QPushButton)
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import Qt, QObject, pyqtSignal

"""
    信号
"""


class Communicate(QObject):
    """
        创建一个新的信号叫做closeApp
        信号使用了pyqtSignal()方法创建，并且成为外部类Communicate类的属性。
    """
    closeApp = pyqtSignal()


class Windows(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle('Apaki 显示进度')
        self.setWindowIcon(QIcon('./res/apaki.ico'))
        self.setGeometry(400, 300, 300, 200)

        lcd = QLCDNumber(self)
        lcd.setDigitCount(3)

        self.max_num = 255
        self.slider = QSlider(Qt.Horizontal, self)
        self.slider.setMaximum(self.max_num)

        maxBt = QPushButton('最大值', self)
        minBt = QPushButton("最小值", self)
        # 两个按钮连接到同一个事件
        maxBt.clicked.connect(self.buttonClicked)
        minBt.clicked.connect(self.buttonClicked)

        hbox = QHBoxLayout()
        hbox.addWidget(minBt)
        hbox.addWidget(maxBt)

        vbox = QVBoxLayout()
        vbox.addWidget(lcd)
        vbox.addWidget(self.slider)
        vbox.addLayout(hbox)
        self.setLayout(vbox)

        self.slider.valueChanged.connect(lcd.display)

        # 把自定义的closeApp信号连接到QMainWindow的close()槽上。
        self.custom = Communicate()
        self.custom.closeApp.connect(self.close)

    def keyPressEvent(self, event):
        """
            重写事件函数
        """
        if event.key() == Qt.Key_Escape:
            self.close()

    def buttonClicked(self):
        """
            事件发送者
        """
        sender = self.sender()
        if sender.text() == '最大值':
            self.slider.setValue(self.max_num)
        elif sender.text() == '最小值':
            self.slider.setValue(0)
        else:
            pass

    def mousePressEvent(self, event):
        """
            触发鼠标点击事件时，自定义信号closeApp会被发射
            现在在窗口非点击组件上单击一下，则会退出
        """
        self.custom.closeApp.emit()


if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = Windows()
    w.show()

    sys.exit(app.exec_())
