from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("Moooo")
        MainWindow.resize(800, 600)
        MainWindow.setStyleSheet('background-color: #00FFFF')
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.push_orca = QtWidgets.QPushButton(self.centralwidget)
        self.push_orca.setGeometry(QtCore.QRect(350, 310, 100, 32))
        self.push_orca.setObjectName("push_orca")
        self.push_orca.setStyleSheet('background-color: #00FF00')
        self.mootbing = QtWidgets.QLabel(self.centralwidget)
        self.mootbing.setGeometry(QtCore.QRect(300, 110, 200, 151))
        self.mootbing.setAutoFillBackground(False)
        self.mootbing.setAlignment(QtCore.Qt.AlignCenter)
        self.mootbing.setObjectName("mootbing")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 800, 22))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Moooo"))
        self.push_orca.setText(_translate("MainWindow", "Push Orca"))
        self.mootbing.setText(_translate("MainWindow", "Mootbing"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
