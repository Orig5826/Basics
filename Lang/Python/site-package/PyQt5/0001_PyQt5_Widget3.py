
import sys
from PyQt5.QtWidgets import (QApplication, QWidget, QFrame, QGridLayout,
                             QProgressBar, QPushButton)
from PyQt5.QtGui import QIcon, QFont, QColor
from PyQt5.QtCore import Qt, QBasicTimer

"""
    进度条的应用
    感谢：Archi - 高手成长之路
    参考来源：https://www.cnblogs.com/archisama/p/5465104.html
"""


class Windows(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()
        self.finished = False

    def initUI(self):
        self.setWindowTitle('进度条示例')
        self.setWindowIcon(QIcon('./res/apaki.ico'))
        self.setGeometry(400, 300, 400, 300)

        self.pbar = QProgressBar(self)
        self.btn = QPushButton("开始", self)
        self.btn.clicked.connect(self.doAction)

        self.timer = QBasicTimer()
        self.step = 0

        grid = QGridLayout(self)
        grid.addWidget(self.pbar, 0, 0, 1, 3)
        grid.addWidget(self.btn, 1, 1, 1, 1)
        self.setLayout(grid)

    def timerEvent(self, event):
        if self.step >= 100:
            self.timer.stop()
            self.btn.setText('下载完成')
            self.finished = True
            return

        self.step += 1
        self.pbar.setValue(self.step)

    def doAction(self):
        if self.finished is not True:
            if self.timer.isActive():
                self.timer.stop()
                self.btn.setText('开始')
            else:
                self.timer.start(100, self)
                self.btn.setText('停止')


if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = Windows()
    w.show()

    sys.exit(app.exec_())
