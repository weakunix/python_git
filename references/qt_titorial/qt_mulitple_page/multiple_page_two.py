from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_page_two(object):
    def setupUi(self, page_two):
        page_two.setObjectName("page_two")
        page_two.resize(800, 600)
        self.input_label = QtWidgets.QLabel(page_two)
        self.input_label.setGeometry(QtCore.QRect(150, 175, 500, 250))
        font = QtGui.QFont()
        font.setPointSize(40)
        self.input_label.setFont(font)
        self.input_label.setAlignment(QtCore.Qt.AlignCenter)
        self.input_label.setObjectName("input_label")
        self.back_button = QtWidgets.QPushButton(page_two)
        self.back_button.setGeometry(QtCore.QRect(0, 0, 100, 60))
        self.back_button.setObjectName("back_button")

        self.retranslateUi(page_two)
        QtCore.QMetaObject.connectSlotsByName(page_two)

    def retranslateUi(self, page_two):
        _translate = QtCore.QCoreApplication.translate
        page_two.setWindowTitle(_translate("page_two", "Page 2"))
        self.input_label.setText(_translate("page_two", "TextLabel"))
        self.back_button.setText(_translate("page_two", "Back"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    page_two = QtWidgets.QWidget()
    ui = Ui_page_two()
    ui.setupUi(page_two)
    page_two.show()
    sys.exit(app.exec_())
