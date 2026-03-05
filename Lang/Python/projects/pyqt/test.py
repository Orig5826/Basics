"""
import sys
from PyQt6 import QtWidgets

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = QtWidgets.QMainWindow()
    window.show()
    exit_code = app.exec()
    sys.exit(exit_code)
"""

import sys
from PyQt6 import QtWidgets

import main_ui

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = QtWidgets.QMainWindow()
    ui = main_ui.Ui_MainWindow()
    ui.setupUi(window)
    window.show()
    exit_code = app.exec()
    sys.exit(exit_code)
