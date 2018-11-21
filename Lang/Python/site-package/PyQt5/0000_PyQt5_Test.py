
from PyQt5 import QtCore, QtGui, QtWidgets
from Ui_apaki_crypto import Ui_Apaki

# ----------------------------------------
# test.ui时Designer配置好的
# 这仅仅是个框架，有些功能其实未实现
if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    widget = QtWidgets.QWidget(None)
    Ui_Apaki().setupUi(widget)
    widget.show()
    sys.exit(app.exec_())
    pass
