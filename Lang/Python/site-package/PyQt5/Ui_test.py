# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'f:\Orig5826\Basics\Lang\Python\site-package\PyQt5\test.ui'
#
# Created by: PyQt5 UI code generator 5.11.3
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_Apaki(object):
    def setupUi(self, Apaki):
        Apaki.setObjectName("Apaki")
        Apaki.resize(400, 300)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap("res/apaki.ico"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        Apaki.setWindowIcon(icon)
        self.tabWidget = QtWidgets.QTabWidget(Apaki)
        self.tabWidget.setGeometry(QtCore.QRect(-4, -1, 411, 301))
        self.tabWidget.setObjectName("tabWidget")
        self.tab_hash = QtWidgets.QWidget()
        self.tab_hash.setObjectName("tab_hash")
        self.tabWidget.addTab(self.tab_hash, "")
        self.tab_aes = QtWidgets.QWidget()
        self.tab_aes.setObjectName("tab_aes")
        self.tabWidget.addTab(self.tab_aes, "")

        self.retranslateUi(Apaki)
        self.tabWidget.setCurrentIndex(1)
        QtCore.QMetaObject.connectSlotsByName(Apaki)

    def retranslateUi(self, Apaki):
        _translate = QtCore.QCoreApplication.translate
        Apaki.setWindowTitle(_translate("Apaki", "Apaki Crypto"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_hash), _translate("Apaki", "hash"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_aes), _translate("Apaki", "aes"))

