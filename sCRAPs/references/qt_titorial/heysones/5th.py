from PyQt5 import QtWidgets, QtGui, QtCore
from PyQt5.QtWidgets import QApplication, QMainWindow, QMessageBox, QProgressBar
import sys


class Windomino(QMainWindow):

    def __init__(self):
        super(Windomino, self).__init__()
        self.setGeometry(300, 100, 300, 100)
        self.setWindowTitle("Among us FREE HACKED")
        self.initUI()
    
    def initUI(self):
        self.label = QtWidgets.QLabel(self)
        self.label.setText("Click to download/patch")
        self.label.move(50, 50)

        self.b1 = QtWidgets.QPushButton(self)
        self.b1.setText("[DOWNLOAD]")
        self.b1.clicked.connect(self.clicks)


    def clicks(self):
        messagee = QMessageBox()
        messagee.setWindowTitle("Uh oh, no bueno pinto")
        messagee.setText("You got virus on mac. Congrats, you won lottery")
        messagee.setIcon(QMessageBox.Critical)
        messagee.setStandardButtons(QMessageBox.Ok|QMessageBox.Cancel|QMessageBox.Close|QMessageBox.Ignore|QMessageBox.Yes|QMessageBox.No)
        messagee.setDefaultButton(QMessageBox.Ok)
        messagee.setInformativeText("Lol free stuff is never free kid")
        messagee.setDetailedText("loris epslalidsfhadsjkadshjklhsahadshadsjasdhjdashjklasjkh")
        messagee.buttonClicked.connect(self.clickmessagebox)
        
        messagee.exec()

    def clickmessagebox(self, i):
        print(i.text())

    def update(self):
        self.label.adjustSize()



def window():
    app = QApplication(sys.argv)
    win = Windomino()

    win.show()
    sys.exit(app.exec_())

window()