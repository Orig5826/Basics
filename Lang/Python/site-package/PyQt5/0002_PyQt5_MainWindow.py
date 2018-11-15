
import sys
from PyQt5.QtWidgets import (QMainWindow, QApplication, QAction, qApp,
                             QTextEdit)
from PyQt5.QtGui import QIcon


icon_exit = './images/exit.png'


class Windows(QMainWindow):
    def __init__(self):
        super().__init__()

        self.statusBar().showMessage('欢迎来到英雄联盟...(^.^)')
        self.initUI()

    def initUI(self):
        self.setWindowTitle('Apaki示例')
        self.setWindowIcon(QIcon('./res/apaki.ico'))
        self.setGeometry(400, 300, 800, 600)

        # 没有可用图标，就临时顶上了(^.^)
        exitAction = QAction(QIcon(icon_exit), '&退出', self)
        exitAction.setShortcut('Ctrl+Q')
        exitAction.setStatusTip('退出程序')
        # 信号触发
        exitAction.triggered.connect(qApp.quit)

        # 菜单栏
        menubar = self.menuBar()
        menubar.setStatusTip('菜单栏')
        fileMenu = menubar.addMenu('&文件')
        fileMenu.addAction(exitAction)

        # 工具栏
        toolbar = self.addToolBar('Exit')
        toolbar.setStatusTip('工具栏')
        toolbar.setWindowIcon(QIcon(icon_exit))
        toolbar.addAction(exitAction)

        # 添加文本框组件，将其配置为QMainWindow的中心组件
        textEdit = QTextEdit()
        textEdit.setStatusTip('文本框')
        self.setCentralWidget(textEdit)


if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = Windows()
    w.show()

    sys.exit(app.exec_())
