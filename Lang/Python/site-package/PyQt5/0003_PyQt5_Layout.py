
import sys
from PyQt5.QtWidgets import (QApplication, QWidget, QToolTip, QPushButton,
                             QMessageBox, QDesktopWidget, QVBoxLayout,
                             QHBoxLayout)
from PyQt5.QtGui import QIcon, QFont
from PyQt5.QtCore import QCoreApplication

"""
    箱布局
"""
class Windows(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        self.setWindowTitle('Apaki示例')
        self.setWindowIcon(QIcon('./res/apaki.ico'))
        self.setGeometry(400, 300, 400, 300)
        font = QFont('华文行楷', 12)

        QToolTip.setFont(QFont('楷体', 10))
        self.setToolTip('Apaki界面示例')

        # 退出Button
        exitBt = QPushButton('退出', self)
        exitBt.setFont(font)
        exitBt.setToolTip('按下按键，退出程序')
        exitBt.resize(exitBt.sizeHint())
        exitBt.clicked.connect(QCoreApplication.instance().quit)

        # 确认Button
        confirmBt = QPushButton("确认", self)
        confirmBt.setFont(font)
        confirmBt.setToolTip('按下按键，暂时无效')

        # 关于Button
        aboutBt = QPushButton("关于", self)
        aboutBt.setFont(font)
        aboutBt.setToolTip('显示程序相关信息')
        aboutBt.clicked.connect(self.aboutEvent)


        # 0003_PyQt5_Layout.py重点
        hbox = QHBoxLayout()
        # 我的理解2018.11.06
        # 添加拉伸因子，若没有addStretch，则横向均分空白
        # 若添加拉伸因子，其参数表示空白区域均分占比
        hbox.addStretch(9)
        hbox.addWidget(aboutBt)
        hbox.addWidget(confirmBt)
        hbox.addWidget(exitBt)
        hbox.addStretch(1)    #2.1

        # 将水平布局箱放在垂直布局内，从而实现整个我们想要的右下脚效果
        vbox = QVBoxLayout()
        vbox.addStretch(1)
        vbox.addItem(hbox)

        # 配置“箱布局”
        self.setLayout(vbox)

    def aboutEvent(self, event):
        QMessageBox.about(self, '关于',
                                '时间：2018.11.15\n作者：jianfeng\n'
                                '版本：v1.0.00')

if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = Windows()
    w.show()

    sys.exit(app.exec_())
