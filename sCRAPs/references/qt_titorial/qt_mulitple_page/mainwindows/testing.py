import many_mainwindow_one as mp1, many_mainwindow_two as mp2, sys
from PyQt5 import QtCore, QtGui, QtWidgets

class PageOne(mp1.Ui_MainWindow):
    def __init__(self, page):
        self.page = page
        self.setupUi(self.page)
        self.continue_button.clicked.connect(lambda: switch_page(self, page_two, self.lineEdit.text()))

class PageTwo(mp2.Ui_MainWindow):
    def __init__(self, page, **kwargs):
        self.page = page
        self.setupUi(self.page)
        self.back_button.clicked.connect(lambda: switch_page(self, page_one))
    
    def refresh_text(self, text):
        _translate = QtCore.QCoreApplication.translate
        self.input_label.setText(_translate("page_two", text))

def switch_page(clear, create, *args):
    clear.page.hide()
    create.page.show()
    if create == page_two:
        page_two.refresh_text(args[0])

if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    page_one = QtWidgets.QMainWindow()
    page_one = PageOne(page_one)
    page_one.page.show()
    page_two = QtWidgets.QMainWindow()
    page_two = PageTwo(page_two)
    sys.exit(app.exec_())
