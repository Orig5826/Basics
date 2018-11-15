
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
from PyQt5.QtWidgets import QApplication, QWidget, QToolTip, QPushButton
from PyQt5.QtGui import QIcon, QFont


class Windows(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        self.setGeometry(400, 300, 400, 300)
        self.setWindowTitle('Apaki示例')
        self.setWindowIcon(QIcon('./res/apaki.ico'))

        QToolTip.setFont(QFont('行楷', 10))
        self.setToolTip('Apaki界面示例')

        exitBt = QPushButton('退出', self)
        exitBt.setToolTip('按下按键，退出程序')
        exitBt.resize(exitBt.sizeHint())
        exitBt.move(300, 250)


if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = Windows()
    w.show()

    sys.exit(app.exec_())
