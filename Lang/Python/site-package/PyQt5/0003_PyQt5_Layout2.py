
import sys
from PyQt5.QtWidgets import (QApplication, QWidget, QGridLayout, QPushButton,
                             QLineEdit)
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import Qt

"""
    网络布局
"""


class Windows(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle('Apaki计算器框架')
        self.setWindowIcon(QIcon('./res/apaki.ico'))
        self.setGeometry(400, 300, 400, 300)

        grid = QGridLayout()
        self.setLayout(grid)

        LineEdit = QLineEdit(self)
        LineEdit.setAlignment(Qt.AlignRight)
        grid.setSpacing(10)
        grid.addWidget(LineEdit, 0, 0, 1, 4)

        names = ['C', 'DEL', '', '=',
                 '7', '8', '9', '/',
                 '4', '5', '6', '*',
                 '1', '2', '3', '-',
                 '±', '0', '.', '+']
        positions = [(i, j) for i in range(1, 6) for j in range(4)]

        for position, name in zip(positions, names):
            if name == '':
                continue
            button = QPushButton(name)
            grid.addWidget(button, *position)


if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = Windows()
    w.show()

    sys.exit(app.exec_())
