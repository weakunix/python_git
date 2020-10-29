import main_window as mw, mwimw1 as mp1, mwimw2 as mp2, sys
from PyQt5 import QtCore, QtGui, QtWidgets

class MainWindow(mw.Ui_MainWindow):
    def __init__(self, main_window):
        self.main_window = main_window
        self.setupUi(self.main_window)
        self.main_window.show()

class PageOne(mp1.Ui_type_page):
    def __init__(self, page):
        self.page = page
        self.setupUi(self.page)
        self.go_button.clicked.connect(lambda: switch_page(self, page_two, self.input_box.text()))

class PageTwo(mp2.Ui_text_display):
    def __init__(self, page, **kwargs):
        self.page = page
        self.setupUi(self.page)
        self.back_button.clicked.connect(lambda: switch_page(self, page_one))
    
    def refresh_text(self, text):
        _translate = QtCore.QCoreApplication.translate
        self.input_text.setText(_translate("page_two", text))

def switch_page(clear, create, *args):
    clear.page.hide()
    create.page.show()
    if create == page_two:
        page_two.refresh_text(args[0])

if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    main_window = QtWidgets.QMainWindow()
    main_window = MainWindow(main_window)
    page_one = QtWidgets.QWidget(main_window.main_window)
    page_one = PageOne(page_one)
    page_two = QtWidgets.QWidget(main_window.main_window)
    page_two = PageTwo(page_two)
    page_one.page.show()
    sys.exit(app.exec_())
