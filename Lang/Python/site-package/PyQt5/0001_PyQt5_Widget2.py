
import sys
from PyQt5.QtWidgets import (QApplication, QWidget, QFrame, QGridLayout,
                             QSlider, QHBoxLayout, QVBoxLayout, QSplitter)
from PyQt5.QtGui import QIcon, QFont, QColor
from PyQt5.QtCore import Qt

"""
    其他组件的示例
    其中：复选框组件，不再列举，因为其已经0005_PyQt5_Dialog.py中实现过
"""


class Windows(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        self.setWindowTitle('RGB控制示例')
        self.setWindowIcon(QIcon('./res/apaki.ico'))
        self.setGeometry(400, 300, 400, 300)

        self.color = QColor(0, 0, 0)
        self.frame = QFrame(self)
        self.frame.setStyleSheet("QWidget { background-color: %s }" %
                                 self.color.name())
        self.frame.setFrameShape(QFrame.StyledPanel)
        # ---------------------------------------------------------------
        self.redSlider = QSlider(Qt.Horizontal, self)
        self.greenSlider = QSlider(Qt.Horizontal, self)  # 默认纵向
        self.blueSlider = QSlider(Qt.Horizontal, self)
        # 配置范围
        self.redSlider.setMaximum(255)
        self.greenSlider.setMaximum(255)
        self.blueSlider.setMaximum(255)
        # 信号
        self.redSlider.valueChanged[int].connect(self.changeValue)
        self.greenSlider.valueChanged[int].connect(self.changeValue)
        self.blueSlider.valueChanged[int].connect(self.changeValue)

        splitter = QSplitter(self)
        splitter.addWidget(self.frame)

        vbox = QVBoxLayout()
        vbox.addWidget(self.redSlider)
        vbox.addWidget(self.greenSlider)
        vbox.addWidget(self.blueSlider)
        hbox = QHBoxLayout()
        hbox.addWidget(splitter)
        hbox.addItem(vbox)
        self.setLayout(hbox)

    def changeValue(self, value):
        sender = self.sender()
        if sender == self.redSlider:
            self.color.setRed(sender.value())
        elif sender == self.greenSlider:
            self.color.setGreen(sender.value())
        elif sender == self.blueSlider:
            self.color.setBlue(sender.value())
        else:
            pass
        self.frame.setStyleSheet("QWidget { background-color: %s }" %
                                 self.color.name())


if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = Windows()
    w.show()

    sys.exit(app.exec_())
