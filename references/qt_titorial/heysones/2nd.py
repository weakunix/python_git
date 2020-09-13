from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QApplication, QMainWindow
import sys


class Windomino(QMainWindow):

    def __init__(self):
        super(Windomino, self).__init__()
        self.setGeometry(200, 200, 300, 300)
        self.setWindowTitle("2nd QT program")
        self.initUI()
    
    def initUI(self):
        self.label = QtWidgets.QLabel(self)
        self.label.setText("First labll")
        self.label.move(50, 50)

        self.b1 = QtWidgets.QPushButton(self)
        self.b1.setText(" CLICK THIS")
        self.b1.clicked.connect(self.clicks)


    def clicks(self):
        self.label.setText("You press button very very very guudly")
        self.update()
        self.label.repaint()

    def update(self):
        self.label.adjustSize()



def window():
    app = QApplication(sys.argv)
    win = Windomino()

    win.show()
    sys.exit(app.exec_())

window()