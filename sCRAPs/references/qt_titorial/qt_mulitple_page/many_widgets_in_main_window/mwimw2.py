# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'mwimw2.ui'
#
# Created by: PyQt5 UI code generator 5.15.1
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_text_display(object):
    def setupUi(self, text_display):
        text_display.setObjectName("text_display")
        text_display.resize(800, 600)
        self.input_text = QtWidgets.QLabel(text_display)
        self.input_text.setGeometry(QtCore.QRect(310, 220, 181, 101))
        self.input_text.setText("")
        self.input_text.setAlignment(QtCore.Qt.AlignCenter)
        self.input_text.setObjectName("input_text")
        self.back_button = QtWidgets.QPushButton(text_display)
        self.back_button.setGeometry(QtCore.QRect(0, 0, 121, 81))
        self.back_button.setObjectName("back_button")

        self.retranslateUi(text_display)
        QtCore.QMetaObject.connectSlotsByName(text_display)

    def retranslateUi(self, text_display):
        _translate = QtCore.QCoreApplication.translate
        text_display.setWindowTitle(_translate("text_display", "Text Display"))
        self.back_button.setText(_translate("text_display", "Back"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    text_display = QtWidgets.QWidget()
    ui = Ui_text_display()
    ui.setupUi(text_display)
    text_display.show()
    sys.exit(app.exec_())
