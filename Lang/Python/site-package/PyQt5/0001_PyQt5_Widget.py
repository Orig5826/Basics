
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
from PyQt5.QtWidgets import QApplication, QWidget, QToolTip, QPushButton, QMessageBox
from PyQt5.QtGui import QIcon, QFont
from PyQt5.QtCore import QCoreApplication


class Windows(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        self.setGeometry(400, 300, 400, 300)
        self.setWindowTitle('Apaki示例')
        self.setWindowIcon(QIcon('./res/apaki.ico'))

        QToolTip.setFont(QFont('宋体', 10))
        self.setToolTip('Apaki界面示例')

        exitBt = QPushButton('退出', self)
        exitBt.setFont(QFont('华文行楷', 12))
        exitBt.setToolTip('按下按键，退出程序')
        exitBt.resize(exitBt.sizeHint())
        exitBt.move(300, 250)
        # 信号槽：退出
        exitBt.clicked.connect(QCoreApplication.instance().quit)

        font = QFont('华文行楷', 12)
        confirmBt = QPushButton("确认", self)
        confirmBt.setFont(font)
        confirmBt.setToolTip('按下按键，显示确认提示')
        confirmBt.move(300, 200)

        aboutBt = QPushButton("关于", self)
        aboutBt.setFont(font)
        aboutBt.setToolTip('2018.11.15 by jianfeng')
        aboutBt.move(300, 150)

    def closeEvent(self, event):
        """
            通过窗口右上角进行关闭时
        """
        reply = QMessageBox.question(self, '请确认',
                                     '请确认是否退出？', QMessageBox.Yes | QMessageBox.No)
        if reply == QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()


if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = Windows()
    w.show()

    sys.exit(app.exec_())
