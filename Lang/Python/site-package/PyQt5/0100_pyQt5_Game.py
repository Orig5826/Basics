
import sys
import time
from PyQt5.QtWidgets import (QApplication, QWidget, QFrame, QGridLayout,
                             QProgressBar, QPushButton, QCalendarWidget,
                             QLabel)
from PyQt5.QtGui import QIcon, QFont, QColor
from PyQt5.QtCore import Qt, QBasicTimer, QDate


from Game_Run import Person, Game


class Windows(QWidget):
    def __init__(self):
        super().__init__()

        self.game = Game()

        self.initUI()
        self.finished = False

    def initUI(self):
        self.setWindowTitle('汤姆 vs 托尼')
        self.setWindowIcon(QIcon('./res/apaki.ico'))
        self.setGeometry(400, 300, 400, 300)

        self.pbar = QProgressBar(self)
        self.pbar2 = QProgressBar(self)
        self.pbar.setValue(100)
        self.pbar2.setValue(100)

        self.btn = QPushButton("开始游戏", self)
        self.btn.clicked.connect(self.doAction)

        self.timer = QBasicTimer()

        # 标签
        self.label = QLabel(self)
        self.label.setText('汤姆')
        self.label.setFont(QFont('华文行楷', 14))

        self.label2 = QLabel(self)
        self.label2.setText('托尼')
        self.label2.setFont(QFont('华文行楷', 14))

        self.label3 = QLabel(self)
        self.label3.setText('战斗情报')
        self.label3.setFont(QFont('宋体', 12))

        # -------------------------------------------------

        grid = QGridLayout(self)
        grid.addWidget(self.label, 0, 0, 1, 1)
        grid.addWidget(self.pbar, 0, 1, 1, 4)

        grid.addWidget(self.label3, 1, 1, 1, 1)
        grid.addWidget(self.btn, 1, 4, 1, 1)

        grid.addWidget(self.label2, 2, 0, 1, 1)
        grid.addWidget(self.pbar2, 2, 1, 1, 4)
        self.setLayout(grid)

    def timerEvent(self, event):
        if self.game.isgame_over():
            self.timer.stop()
            self.finished = True
            if self.game.who_win() == 'Tom':
                self.label3.setText('托尼死亡 -- 汤姆胜利')
            else:
                self.label3.setText('汤姆死亡 -- 托尼胜利')

            # self.btn.setText('游戏结束')
            self.btn.setText('重新开始')
            return

        ret = self.game.run()
        if 0 == ret:
            self.label3.setText('攻击：汤姆 ->  托尼')
        else:
            self.label3.setText('攻击：汤姆 <-  托尼')

        hp1 = self.game.get_blood('Tom')
        hp2 = self.game.get_blood('Tony')

        self.pbar.setValue(hp1)
        self.pbar2.setValue(hp2)

    def doAction(self):
        if self.finished is not True:
            if self.timer.isActive():
                self.timer.stop()
                self.btn.setText('继续')
            else:
                self.timer.start(500, self)
                self.btn.setText('进行中')
        else:
            self.label3.setText('战斗情报')
            self.pbar.setValue(100)
            self.pbar2.setValue(100)

            del self.game
            self.game = Game()

            self.finished = False
            self.timer.start(500, self)


    def showData(self, date):
        self.label.setText(date.toString())


if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = Windows()
    w.show()

    sys.exit(app.exec_())
