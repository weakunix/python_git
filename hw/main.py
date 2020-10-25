#System imports
import sys
import webbrowser

#PYQT5 imports
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QMessageBox

#import files
from handlers import filehandler, newhandler, sqlhandler, themeshandler
from QTgenerated import application, hw_main_window as mw, login


class hwMainWindow(mw.Ui_MainWindow):
    def __init__(self, main_window):
        self.main_window = main_window
        self.setupUi(self.main_window)
        self.main_window.show()

    #TODO JASON: ADD MAIN WINDOW TOOLBAR LINKING IN __init__ METHOD


class loginPage(login.Ui_Form):
    def __init__(self, ui):
        #human stuff now
        self.ui = ui
        self.setupUi(self.ui)

        iconSizer = 35

        #manually making buttons (bc path doesnt work)
        self.ICONPNG.setPixmap(QtGui.QPixmap("./icons/ICON.png"))
        self.ICONPNG.setAlignment(QtCore.Qt.AlignCenter)

        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap("./icons/INSTA.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.insta.setIcon(icon)
        self.insta.setIconSize(QtCore.QSize(iconSizer, iconSizer))

        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap("./icons/YOUTUBE.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.youtube.setIcon(icon1)
        self.youtube.setIconSize(QtCore.QSize(iconSizer, iconSizer))

        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap("./icons/GITHUB.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.github.setIcon(icon2)
        self.github.setIconSize(QtCore.QSize(iconSizer, iconSizer))

        #open sites when clicked
        self.github.pressed.connect(lambda : webbrowser.open("https://github.com/weakunix/python_git")) 
        self.youtube.pressed.connect(lambda: webbrowser.open("https://www.youtube.com/c/cowland"))
        self.insta.pressed.connect(lambda:  webbrowser.open("https://instagram.com"))

        #link buttons clicked to open locally or validate with (later) database

        self.signinLocalButton.pressed.connect(lambda: [self.openApp(False)]) # "signs in" with only data from device
        self.submitcredentials.pressed.connect(self.validate) #submit credentials for validations
        self.registercredentials.pressed.connect(self.register) #registers account

        
    
    def validate(self):
        password = self.PasswordInputS.text()
        username = self.UsernameInputS.text() #idk how the fuck I flipepd these
        keepSignedIn = self.keepsignin.isChecked()
        #temp = filehandler.checkForUserInDatabase(username, password) #is valid name and password combo
        if temp == "True":
            def yes(selection):
                if selection.text() == "&Yes":
                    filehandler.yaml_it("settings.yaml", "autolog", "True")
                else:
                    filehandler.yaml_it("settings.yaml", "autolog", "False")
            if keepSignedIn:
                KeepSignedInConfirm = QMessageBox()
                KeepSignedInConfirm.setText("Confirm to keep yourself signed in automatically?")
                KeepSignedInConfirm.setInformativeText("Don't do this on shared devices to prevent theft!")
                KeepSignedInConfirm.setIcon(QMessageBox.Critical)
                KeepSignedInConfirm.setStandardButtons(QMessageBox.Yes|QMessageBox.No)
                KeepSignedInConfirm.setDefaultButton(QMessageBox.No)
                KeepSignedInConfirm.buttonClicked.connect(yes)

                KeepSignedInConfirm.exec()
            #self.app.quit()
            self.openApp(True)
        else:
            MAKE_A_DAMN_ACCOUNT = QMessageBox()
            if temp == "False":
                MAKE_A_DAMN_ACCOUNT.setText("Error: You do not have an account made! Head over to the 'Register' tab and create an account on us. Free of charge! Or, you can continue as a guest. But be wary! Your data will be gone if you delete this app!")
            else:
                MAKE_A_DAMN_ACCOUNT.setText("Error: Wrong Password!")
            MAKE_A_DAMN_ACCOUNT.setIcon(QMessageBox.Critical)
            MAKE_A_DAMN_ACCOUNT.setStandardButtons(QMessageBox.Ok)
            MAKE_A_DAMN_ACCOUNT.setDefaultButton(QMessageBox.Ok)

            MAKE_A_DAMN_ACCOUNT.exec()

    def register(self):
        username = self.UsernameInputR.text()
        password = self.passwordInputR.text()
        passwordConfirm = self.passwordInputConfirmR.text()

        '''if password == passwordConfirm:
            if not filehandler.checkForUserAlreadyExists(str(username)):
                def start(e):
                    if e.text() == "&Yes":
                        # change this to sql access later
                        accountMadeSuccess = QMessageBox()
                        accountMadeSuccess.setText("The account '" + str(username) + "' has been created!")
                        accountMadeSuccess.setIcon(QMessageBox.Information)
                        accountMadeSuccess.setStandardButtons(QMessageBox.Ok)
                        accountMadeSuccess.setDefaultButton(QMessageBox.Ok)

                        accountMadeSuccess.exec()
                with open("./data/policy.txt") as f:
                    policy = f.read()
                readTerms = QMessageBox()
                readTerms.setText("ACCEPT OUR TERMS AND POLICIES TO CONTINUE (CLICK YES IF YOU ACCEPT)")
                readTerms.setInformativeText(policy)
                readTerms.setIcon(QMessageBox.Information)
                readTerms.setStandardButtons(QMessageBox.Yes|QMessageBox.No)
                readTerms.setDefaultButton(QMessageBox.No)
                readTerms.buttonClicked.connect(start)

                readTerms.exec() 
            else:
                errorUserAlreadyExists = QMessageBox()
                errorUserAlreadyExists.setText("The username '" + str(username) + "' is already in use!")
                errorUserAlreadyExists.setIcon(QMessageBox.Critical)
                errorUserAlreadyExists.setStandardButtons(QMessageBox.Ok)
                errorUserAlreadyExists.setDefaultButton(QMessageBox.Ok)

                errorUserAlreadyExists.exec()
        else:
            errorNotSamePassword = QMessageBox()
            errorNotSamePassword.setText("The passwords do not match!")
            errorNotSamePassword.setIcon(QMessageBox.Critical)
            errorNotSamePassword.setStandardButtons(QMessageBox.Ok)
            errorNotSamePassword.setDefaultButton(QMessageBox.Ok)

            errorNotSamePassword.exec()
        '''
        
        self.UsernameInputR.clear()
        self.passwordInputR.clear()
        self.passwordInputConfirmR.clear()

        self.tabWidget.setCurrentIndex(0)

    def openApp(self, isOnline):
        self.ui.hide()
        app_page.ui.show()

class App(application.Ui_Form):
    def __init__(self, ui):
        self.ui = ui
        self.setupUi(self.ui)

        themeshandler.styleMain(self)

        #more code here later
        '''self.newAdd.pressed.connect(lambda: [newhandler.newSomething.newHomework(self, [])])
        self.newAddS.pressed.connect(lambda: [newhandler.newSomething.newClass(self, [])])'''


if __name__ == "__main__": 
    app = QtWidgets.QApplication(sys.argv)
    main_window = QtWidgets.QMainWindow()
    main_window = hwMainWindow(main_window)
    login_page = QtWidgets.QWidget(main_window.main_window)
    login_page = loginPage(login_page)
    app_page = QtWidgets.QWidget(main_window.main_window)
    app_page = App(app_page)
    login_page.ui.show()
    sys.exit(app.exec_())
