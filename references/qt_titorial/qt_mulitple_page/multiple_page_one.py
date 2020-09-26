from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_page_one(object):
    def setupUi(self, page_one):
        page_one.setObjectName("page_one")
        page_one.resize(800, 600)
        self.start_label = QtWidgets.QLabel(page_one)
        self.start_label.setGeometry(QtCore.QRect(250, 130, 300, 120))
        self.start_label.setAlignment(QtCore.Qt.AlignCenter)
        self.start_label.setObjectName("start_label")
        self.input_box = QtWidgets.QLineEdit(page_one)
        self.input_box.setGeometry(QtCore.QRect(350, 350, 113, 21))
        self.input_box.setObjectName("input_box")
        self.go = QtWidgets.QPushButton(page_one)
        self.go.setGeometry(QtCore.QRect(350, 400, 113, 32))
        self.go.setObjectName("go")

        self.retranslateUi(page_one)
        QtCore.QMetaObject.connectSlotsByName(page_one)

    def retranslateUi(self, page_one):
        _translate = QtCore.QCoreApplication.translate
        page_one.setWindowTitle(_translate("page_one", "Page 1"))
        self.start_label.setText(_translate("page_one", "Mootbing"))
        self.go.setText(_translate("page_one", "Go!"))

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    page_one = QtWidgets.QWidget()
    ui = Ui_page_one()
    ui.setupUi(page_one)
    page_one.show()
    sys.exit(app.exec_())
