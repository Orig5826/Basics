# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'f:\Orig5826\Basics\Lang\Python\site-package\PyQt5\test.ui'
#
# Created by: PyQt5 UI code generator 5.11.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_Test(object):
    def setupUi(self, Test):
        Test.setObjectName("Test")
        Test.resize(400, 300)
        self.textBrowser = QtWidgets.QTextBrowser(Test)
        self.textBrowser.setGeometry(QtCore.QRect(60, 40, 256, 192))
        self.textBrowser.setObjectName("textBrowser")

        self.retranslateUi(Test)
        QtCore.QMetaObject.connectSlotsByName(Test)

    def retranslateUi(self, Test):
        _translate = QtCore.QCoreApplication.translate
        Test.setWindowTitle(_translate("Test", "Hello World"))
        self.textBrowser.setHtml(_translate("Test", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'SimSun\'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a href=\"https://www.baidu.com/\"><span style=\" font-size:18pt; text-decoration: underline; color:#0000ff;\">百度一下</span></a></p></body></html>"))

