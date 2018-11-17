
import os
import sys
from PyQt5.QtWidgets import (QApplication, QWidget, QPushButton, QFileDialog,
                             QVBoxLayout, QHBoxLayout, QLineEdit, QLabel)
from PyQt5.QtGui import QIcon, QPixmap
from PyQt5.QtCore import Qt

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
        self.setWindowTitle('图像显示示例')
        self.setWindowIcon(QIcon('./res/apaki.ico'))
        self.setGeometry(400, 300, 400, 300)

        # 打开按键
        self.fileBtn = QPushButton('打开图像', self)
        self.fileBtn.clicked.connect(self.showfileDialog)

        # 路径显示
        self.lineEidt = QLineEdit(self)

        # 图像显示
        self.label = QLabel(self)

        hbox = QHBoxLayout()
        hbox.addWidget(self.fileBtn)
        hbox.addWidget(self.lineEidt)
        vbox = QVBoxLayout()
        vbox.addItem(hbox)
        vbox.addWidget(self.label)
        self.setLayout(vbox)

    def showfileDialog(self):
        # 弹出文本框选择框
        imagefname = QFileDialog.getOpenFileName(self,
                                                 '选择文件',
                                                 './',
                                                 filter='图像 (*.jpg *.png *.bmp)')
        file_path = imagefname[0]
        self.lineEidt.setText(file_path)
        pixmap = QPixmap(file_path)
        self.label.setPixmap(pixmap)

    def keyPressEvent(self, event):
        if event.key() == Qt.Key_Return:
            file_path = self.lineEidt.text()
            if os.path.exists(file_path):
                # print(file_path)
                pixmap = QPixmap(file_path)
                self.label.setPixmap(pixmap)
            else:
                self.label.setText('文件不存在')


if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = Windows()
    w.show()

    sys.exit(app.exec_())
