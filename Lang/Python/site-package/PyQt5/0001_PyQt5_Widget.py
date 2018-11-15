
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
from PyQt5.QtWidgets import QApplication, QWidget
from PyQt5.QtGui import QIcon


class Windows(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        self.setGeometry(300, 300, 300, 200)
        self.setWindowTitle('Apaki示例')
        self.setWindowIcon(QIcon('./res/apaki.ico'))


if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = Windows()
    w.show()

    sys.exit(app.exec_())
