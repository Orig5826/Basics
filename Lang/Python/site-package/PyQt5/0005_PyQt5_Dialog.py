
import sys
from PyQt5.QtWidgets import (QApplication, QWidget, QPushButton, QInputDialog,
                             QLineEdit, QGridLayout,
                             QColorDialog, QFrame, QFontDialog, QFileDialog,
                             QTextEdit, QCheckBox, QComboBox, QLabel)
from PyQt5.QtGui import QIcon, QFont, QColor
from PyQt5.QtCore import QCoreApplication, Qt


class Windows(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        self.setWindowTitle('Apaki示例')
        self.setWindowIcon(QIcon('./res/apaki.ico'))
        self.setGeometry(400, 300, 400, 300)

        # ---------------------------------------------------
        self.DialogBtn = QPushButton('输入对话框', self)
        self.DialogBtn.clicked.connect(self.showDialog)

        self.lineEdit = QLineEdit(self)
        self.lineEdit.setAlignment(Qt.AlignRight)

        # ---------------------------------------------------
        self.colorBtn = QPushButton('颜色对话框', self)
        self.colorBtn.clicked.connect(self.showcolorDialog)

        # QFrame组件的背景设置为黑色
        color = QColor(0, 0, 0)
        self.frm = QFrame(self)
        self.frm.setStyleSheet(
            'QWidget { background-color: %s}' % color.name())

        # --------------------------------------------------
        self.fontBtn = QPushButton('字体对话框', self)
        self.fontBtn.clicked.connect(self.showfontDialog)

        # --------------------------------------------------
        self.fileBtn = QPushButton('文件对话框', self)
        self.fileBtn.clicked.connect(self.showfileDialog)

        self.textEdit = QTextEdit(self)

        # --------------------------------------------------
        checkbox = QCheckBox('切换标题', self)
        checkbox.stateChanged.connect(self.changeTitle)

        # --------------------------------------------------
        combo = QComboBox(self)
        cars = ['雷克萨斯', '宝马', '梅赛德斯', '宾利', '保时捷', '玛莎拉蒂', '兰博基尼', '法拉利',
                '凯迪拉克', '别克', '劳斯莱斯', '大众', '奥迪', '名爵', '铃木', '本田', '现代',
                '丰田', '欧宝', '悍马', '吉普', '布加迪', '红旗', '五菱', '双环', '水星',
                '福特', '通用', '吉利', '雪佛兰', '斯巴鲁', '捷豹', '道奇', '日产', '马自达',
                '雪铁龙', '英菲尼迪', '全球鹰', '林肯']
        cars.sort()
        for car in cars:
            combo.addItem(car)
        combo.activated[str].connect(self.onActived)
        self.label = QLabel(self)
        self.label.setText(combo.itemText(0))
        self.label.setFont(QFont('华文行楷', 14))

        # 布局
        grid = QGridLayout()
        self.setLayout(grid)
        grid.addWidget(self.DialogBtn, 0, 0)
        grid.addWidget(self.lineEdit, 0, 1)
        grid.addWidget(self.colorBtn, 1, 0)
        grid.addWidget(self.frm, 1, 1)
        grid.addWidget(self.fontBtn, 2, 0)
        grid.addWidget(self.fileBtn, 3, 0)
        grid.addWidget(self.textEdit, 3, 1, 10, 1)
        grid.addWidget(checkbox, 5, 0)
        grid.addWidget(combo, 7, 0)
        grid.addWidget(self.label, 10, 0)

    def showDialog(self):
        text, ok = QInputDialog.getText(self, '对话框', '请输入你的名字')
        if ok:
            self.lineEdit.setText(str(text))

    def showcolorDialog(self):
        # 弹出颜色选择框
        color = QColorDialog.getColor()

        if color.isValid():
            self.frm.setStyleSheet(
                'QWidget { background-color: %s}' % color.name())

    def showfontDialog(self):
        # 弹出字体选择框
        font, ok = QFontDialog.getFont()
        if ok:
            self.lineEdit.setFont(font)
            self.textEdit.setFont(font)

    def showfileDialog(self):
        # 弹出文本框选择框
        fname = QFileDialog.getOpenFileName(
            self, '打开文件', filter='Markdown(*.md);;Text(*.txt);;All(*.*)')
        if fname[0]:
            f = open(fname[0], 'r', encoding='utf-8')
            with f:
                data = f.read()
                self.textEdit.setText(data)

    def changeTitle(self, status):
        if status == Qt.Checked:
            self.setWindowTitle('复选框选中')
        else:
            self.setWindowTitle('Apaki示例')

    def onActived(self, text):
        self.label.setText(text)
        self.label.adjustSize()


if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = Windows()
    w.show()

    sys.exit(app.exec_())
