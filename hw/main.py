#IMPORT FILES
from QTgenerated import hw_main_window as mw, application, login
from handlers import filehandler, newhandler

#other python imports
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QMessageBox
import webbrowser, sys

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
        self.ui.ICONPNG.setPixmap(QtGui.QPixmap("./icons/ICON.png"))

        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap("./icons/INSTA.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.ui.insta.setIcon(icon)
        self.ui.insta.setIconSize(QtCore.QSize(iconSizer, iconSizer))

        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap("./icons/YOUTUBE.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.ui.youtube.setIcon(icon1)
        self.ui.youtube.setIconSize(QtCore.QSize(iconSizer, iconSizer))

        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap("./icons/GITHUB.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.ui.github.setIcon(icon2)
        self.ui.github.setIconSize(QtCore.QSize(iconSizer, iconSizer))

        #open sites when clicked

        self.ui.github.clicked.connect(lambda : webbrowser.open("https://github.com/weakunix/python_git")) 
        self.ui.youtube.clicked.connect(lambda: webbrowser.open("https://www.youtube.com/c/cowland"))
        self.ui.insta.clicked.connect(lambda:  webbrowser.open("https://instagram.com"))

        #link buttons clicked to open locally or validate with (later) database

        self.ui.signinLocalButton.clicked.connect(lambda: [self.app.quit(), self.openApp(False)]) # "signs in" with only data from device
        self.ui.submitcredentials.clicked.connect(self.validate) #submit credentials for validations
        self.ui.registercredentials.clicked.connect(self.register) #registers account

        #put at end
        self.Login.show()
        sys.exit(self.app.exec_())
    
    def validate(self):
        password = self.ui.PasswordInputS.text()
        username = self.ui.UsernameInputS.text() #idk how the fuck I flipepd these
        keepSignedIn = self.ui.keepsignin.isChecked()
        temp = filehandler.File.checkForUserInDatabase(username, password) #is valid name and password combo
        if temp == "True":
            def yes(selection):
                if selection.text() == "&Yes":
                    filehandler.File.jason_it("settings.json", "autoLogIn", "True")
                else:
                    filehandler.File.jason_it("settings.json", "autoLogIn", "False")
            if keepSignedIn:
                KeepSignedInConfirm = QMessageBox()
                KeepSignedInConfirm.setText("Confirm to keep yourself signed in automatically?")
                KeepSignedInConfirm.setInformativeText("Don't do this on shared devices to prevent theft!")
                KeepSignedInConfirm.setIcon(QMessageBox.Critical)
                KeepSignedInConfirm.setStandardButtons(QMessageBox.Yes|QMessageBox.No)
                KeepSignedInConfirm.setDefaultButton(QMessageBox.No)
                KeepSignedInConfirm.buttonClicked.connect(yes)

                KeepSignedInConfirm.exec()
            self.app.quit()
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
        username = self.ui.UsernameInputR.text()
        password = self.ui.passwordInputR.text()
        passwordConfirm = self.ui.passwordInputConfirmR.text()

        if password == passwordConfirm:
            if not filehandler.File.checkForUserAlreadyExists(str(username)):
                def start(e):
                    if e.text() == "&Yes":
                        filehandler.File.jason_it("logininfo.json", str(username), [str(password)]) #register and log to logininfo.json
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
        
        self.ui.UsernameInputR.clear()
        self.ui.passwordInputR.clear()
        self.ui.passwordInputConfirmR.clear()

        self.ui.tabWidget.setCurrentIndex(0)

    def openApp(self, isOnline):
       self.Login.hide()
       app = App() 

class App(application.Ui_Form):
    def __init__(self, ui):
        self.ui = ui

        #more code here later
        self.ui.newAdd.clicked.connect(lambda: [newhandler.newSomething.newHomework(self.ui), self.HWTracker.repaint()])
        self.ui.newAddS.clicked.connect(lambda: [newhandler.newSomething.newClass(self.ui), self.HWTracker.repaint()])


if __name__ == "__main__": 
    app = QtWidgets.QApplication(sys.argv)
    main_window = QtWidgets.QMainWindow()
    main_window = hwMainWindow(main_window)
    login_page = QtWidgets.QWidget(main_window.main_window)
    login_page = loginPage(login_page)
    app_page = QtWidgets.QWidget(main_window.main_window)
    app_page = App(app_page)
    login_page.show()
    sys.exit(app.exec_())
