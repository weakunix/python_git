# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'loginaswidget.ui'
#
# Created by: PyQt5 UI code generator 5.15.0
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(962, 703)
        self.leftSide = QtWidgets.QWidget(Form)
        self.leftSide.setGeometry(QtCore.QRect(10, 10, 200, 681))
        self.leftSide.setMinimumSize(QtCore.QSize(200, 0))
        self.leftSide.setMaximumSize(QtCore.QSize(200, 16777215))
        self.leftSide.setStyleSheet("QWidget{\n"
"    background:rgb(66, 64, 66);\n"
"    border-radius: 10px;\n"
"}\n"
"QPushButton{\n"
"    color:rgb(255, 255, 255);\n"
"    background: rgb(50, 50, 54);\n"
"    border-radius:3px;\n"
"    border: 1px solid rgb(27, 129, 255);\n"
"}\n"
"QPushButton:hover{\n"
"    border:1px solid rgb(213, 214, 146);\n"
"}\n"
"QLineEdit{\n"
"    font-size:18px;\n"
"    background: rgb(50, 50, 54);\n"
"    color: rgb(255, 255, 255);\n"
"    border-radius:3px;\n"
"    border: 1px solid rgb(27, 129, 255);\n"
"    padding-left:2px;\n"
"    padding-right:2px;\n"
"}\n"
"QLineEdit:hover{\n"
"    border:1px solid rgb(213, 214, 146);\n"
"}\n"
"QCheckBox{\n"
"    background: rgb(66, 64, 66);\n"
"    border: 1px solid rgb(27, 129, 255);\n"
"    color:rgb(255, 255, 255);\n"
"    border-radius:3px;\n"
"}\n"
"QCheckBox:hover{\n"
"    border:1px solid rgb(213, 214, 146);\n"
"}\n"
"QLabel{\n"
"    color:rgb(255, 255, 255);\n"
"}")
        self.leftSide.setObjectName("leftSide")
        self.verticalLayout_7 = QtWidgets.QVBoxLayout(self.leftSide)
        self.verticalLayout_7.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_7.setObjectName("verticalLayout_7")
        self.changableFrame = QtWidgets.QFrame(self.leftSide)
        self.changableFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.changableFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.changableFrame.setObjectName("changableFrame")
        self.verticalLayout_15 = QtWidgets.QVBoxLayout(self.changableFrame)
        self.verticalLayout_15.setObjectName("verticalLayout_15")
        self.tabWidget = QtWidgets.QTabWidget(self.changableFrame)
        self.tabWidget.setObjectName("tabWidget")
        self.login = QtWidgets.QWidget()
        self.login.setObjectName("login")
        self.LoginFrame = QtWidgets.QFrame(self.login)
        self.LoginFrame.setGeometry(QtCore.QRect(0, 10, 151, 241))
        self.LoginFrame.setMinimumSize(QtCore.QSize(0, 240))
        self.LoginFrame.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.LoginFrame.setStyleSheet("QFrame{\n"
"    background:rgb(83, 82, 84);\n"
"}")
        self.LoginFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.LoginFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.LoginFrame.setObjectName("LoginFrame")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.LoginFrame)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.logintext = QtWidgets.QLabel(self.LoginFrame)
        self.logintext.setMaximumSize(QtCore.QSize(16777215, 40))
        font = QtGui.QFont()
        font.setFamily("Arial")
        font.setPointSize(23)
        self.logintext.setFont(font)
        self.logintext.setAlignment(QtCore.Qt.AlignCenter)
        self.logintext.setObjectName("logintext")
        self.verticalLayout_2.addWidget(self.logintext)
        self.loginFrame = QtWidgets.QFrame(self.LoginFrame)
        self.loginFrame.setMinimumSize(QtCore.QSize(0, 140))
        self.loginFrame.setMaximumSize(QtCore.QSize(16777215, 100))
        font = QtGui.QFont()
        font.setFamily("Arial")
        font.setPointSize(24)
        font.setBold(True)
        font.setWeight(75)
        self.loginFrame.setFont(font)
        self.loginFrame.setCursor(QtGui.QCursor(QtCore.Qt.ArrowCursor))
        self.loginFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.loginFrame.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.loginFrame.setObjectName("loginFrame")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.loginFrame)
        self.verticalLayout.setObjectName("verticalLayout")
        self.UsernameInputS = QtWidgets.QLineEdit(self.loginFrame)
        self.UsernameInputS.setObjectName("UsernameInputS")
        self.verticalLayout.addWidget(self.UsernameInputS)
        self.PasswordInputS = QtWidgets.QLineEdit(self.loginFrame)
        font = QtGui.QFont()
        font.setPointSize(-1)
        self.PasswordInputS.setFont(font)
        self.PasswordInputS.setText("")
        self.PasswordInputS.setEchoMode(QtWidgets.QLineEdit.Password)
        self.PasswordInputS.setObjectName("PasswordInputS")
        self.verticalLayout.addWidget(self.PasswordInputS)
        self.keepsignin = QtWidgets.QCheckBox(self.loginFrame)
        self.keepsignin.setMinimumSize(QtCore.QSize(0, 30))
        self.keepsignin.setCursor(QtGui.QCursor(QtCore.Qt.OpenHandCursor))
        self.keepsignin.setObjectName("keepsignin")
        self.verticalLayout.addWidget(self.keepsignin)
        self.verticalLayout_2.addWidget(self.loginFrame)
        self.submitcredentials = QtWidgets.QPushButton(self.LoginFrame)
        self.submitcredentials.setMinimumSize(QtCore.QSize(0, 20))
        self.submitcredentials.setCursor(QtGui.QCursor(QtCore.Qt.OpenHandCursor))
        self.submitcredentials.setObjectName("submitcredentials")
        self.verticalLayout_2.addWidget(self.submitcredentials)
        self.tabWidget.addTab(self.login, "")
        self.signup = QtWidgets.QWidget()
        self.signup.setObjectName("signup")
        self.registerbox = QtWidgets.QFrame(self.signup)
        self.registerbox.setGeometry(QtCore.QRect(0, 10, 151, 240))
        self.registerbox.setMinimumSize(QtCore.QSize(0, 240))
        self.registerbox.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.registerbox.setStyleSheet("QFrame{\n"
"    background:rgb(83, 82, 84);\n"
"}")
        self.registerbox.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.registerbox.setFrameShadow(QtWidgets.QFrame.Raised)
        self.registerbox.setObjectName("registerbox")
        self.verticalLayout_10 = QtWidgets.QVBoxLayout(self.registerbox)
        self.verticalLayout_10.setObjectName("verticalLayout_10")
        self.registerlable = QtWidgets.QLabel(self.registerbox)
        self.registerlable.setMaximumSize(QtCore.QSize(16777215, 40))
        font = QtGui.QFont()
        font.setFamily("Arial")
        font.setPointSize(23)
        self.registerlable.setFont(font)
        self.registerlable.setAlignment(QtCore.Qt.AlignCenter)
        self.registerlable.setObjectName("registerlable")
        self.verticalLayout_10.addWidget(self.registerlable)
        self.registerFrame = QtWidgets.QFrame(self.registerbox)
        self.registerFrame.setMaximumSize(QtCore.QSize(16777215, 16777215))
        font = QtGui.QFont()
        font.setFamily("Arial")
        font.setPointSize(24)
        font.setBold(True)
        font.setWeight(75)
        self.registerFrame.setFont(font)
        self.registerFrame.setCursor(QtGui.QCursor(QtCore.Qt.ArrowCursor))
        self.registerFrame.setStyleSheet("")
        self.registerFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.registerFrame.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.registerFrame.setObjectName("registerFrame")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout(self.registerFrame)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.UsernameInputR = QtWidgets.QLineEdit(self.registerFrame)
        self.UsernameInputR.setObjectName("UsernameInputR")
        self.verticalLayout_3.addWidget(self.UsernameInputR)
        self.passwordInputR = QtWidgets.QLineEdit(self.registerFrame)
        font = QtGui.QFont()
        font.setPointSize(-1)
        self.passwordInputR.setFont(font)
        self.passwordInputR.setText("")
        self.passwordInputR.setEchoMode(QtWidgets.QLineEdit.Password)
        self.passwordInputR.setObjectName("passwordInputR")
        self.verticalLayout_3.addWidget(self.passwordInputR)
        self.passwordInputConfirmR = QtWidgets.QLineEdit(self.registerFrame)
        font = QtGui.QFont()
        font.setPointSize(-1)
        self.passwordInputConfirmR.setFont(font)
        self.passwordInputConfirmR.setText("")
        self.passwordInputConfirmR.setEchoMode(QtWidgets.QLineEdit.Password)
        self.passwordInputConfirmR.setObjectName("passwordInputConfirmR")
        self.verticalLayout_3.addWidget(self.passwordInputConfirmR)
        self.verticalLayout_10.addWidget(self.registerFrame)
        self.registercredentials = QtWidgets.QPushButton(self.registerbox)
        self.registercredentials.setMinimumSize(QtCore.QSize(0, 20))
        self.registercredentials.setCursor(QtGui.QCursor(QtCore.Qt.OpenHandCursor))
        self.registercredentials.setObjectName("registercredentials")
        self.verticalLayout_10.addWidget(self.registercredentials)
        self.tabWidget.addTab(self.signup, "")
        self.verticalLayout_15.addWidget(self.tabWidget)
        self.verticalLayout_7.addWidget(self.changableFrame)
        self.staticFrame = QtWidgets.QFrame(self.leftSide)
        self.staticFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.staticFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.staticFrame.setObjectName("staticFrame")
        self.verticalLayout_4 = QtWidgets.QVBoxLayout(self.staticFrame)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.signinLocal = QtWidgets.QFrame(self.staticFrame)
        self.signinLocal.setStyleSheet("QFrame{\n"
"    background:rgb(83, 82, 84);\n"
"}")
        self.signinLocal.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.signinLocal.setFrameShadow(QtWidgets.QFrame.Raised)
        self.signinLocal.setObjectName("signinLocal")
        self.verticalLayout_14 = QtWidgets.QVBoxLayout(self.signinLocal)
        self.verticalLayout_14.setObjectName("verticalLayout_14")
        self.signinLocalText = QtWidgets.QLabel(self.signinLocal)
        self.signinLocalText.setObjectName("signinLocalText")
        self.verticalLayout_14.addWidget(self.signinLocalText)
        self.signinLocalButton = QtWidgets.QPushButton(self.signinLocal)
        self.signinLocalButton.setCursor(QtGui.QCursor(QtCore.Qt.OpenHandCursor))
        self.signinLocalButton.setObjectName("signinLocalButton")
        self.verticalLayout_14.addWidget(self.signinLocalButton)
        self.verticalLayout_4.addWidget(self.signinLocal)
        self.socials = QtWidgets.QFrame(self.staticFrame)
        self.socials.setMaximumSize(QtCore.QSize(16777215, 100))
        self.socials.setStyleSheet("QPushButton{\n"
"    background:rgb(255, 255, 255);\n"
"}\n"
"QFrame{\n"
"    background:rgb(83, 82, 84);\n"
"}")
        self.socials.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.socials.setFrameShadow(QtWidgets.QFrame.Plain)
        self.socials.setObjectName("socials")
        self.gridLayout_2 = QtWidgets.QGridLayout(self.socials)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.checkusout = QtWidgets.QLabel(self.socials)
        self.checkusout.setAlignment(QtCore.Qt.AlignCenter)
        self.checkusout.setObjectName("checkusout")
        self.gridLayout_2.addWidget(self.checkusout, 0, 0, 1, 3)
        self.insta = QtWidgets.QPushButton(self.socials)
        self.insta.setCursor(QtGui.QCursor(QtCore.Qt.OpenHandCursor))
        self.insta.setText("")
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap("../../Downloads/output-onlinepngtools-removebg-preview-2.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.insta.setIcon(icon)
        self.insta.setIconSize(QtCore.QSize(40, 40))
        self.insta.setObjectName("insta")
        self.gridLayout_2.addWidget(self.insta, 1, 0, 1, 1)
        self.youtube = QtWidgets.QPushButton(self.socials)
        font = QtGui.QFont()
        font.setKerning(False)
        self.youtube.setFont(font)
        self.youtube.setCursor(QtGui.QCursor(QtCore.Qt.OpenHandCursor))
        self.youtube.setText("")
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap("../../Downloads/youtube_PNG12.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.youtube.setIcon(icon1)
        self.youtube.setIconSize(QtCore.QSize(40, 40))
        self.youtube.setObjectName("youtube")
        self.gridLayout_2.addWidget(self.youtube, 1, 1, 1, 1)
        self.github = QtWidgets.QPushButton(self.socials)
        font = QtGui.QFont()
        font.setKerning(False)
        self.github.setFont(font)
        self.github.setCursor(QtGui.QCursor(QtCore.Qt.OpenHandCursor))
        self.github.setText("")
        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap("../../Downloads/github-153-675523.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.github.setIcon(icon2)
        self.github.setIconSize(QtCore.QSize(40, 40))
        self.github.setObjectName("github")
        self.gridLayout_2.addWidget(self.github, 1, 2, 1, 1)
        self.verticalLayout_4.addWidget(self.socials)
        self.verticalLayout_7.addWidget(self.staticFrame)
        self.rightSide = QtWidgets.QWidget(Form)
        self.rightSide.setGeometry(QtCore.QRect(220, 10, 733, 681))
        self.rightSide.setStyleSheet("QWidget{\n"
"    background:rgb(66, 64, 66);\n"
"    border-radius: 10px;\n"
"}")
        self.rightSide.setObjectName("rightSide")
        self.verticalLayout_5 = QtWidgets.QVBoxLayout(self.rightSide)
        self.verticalLayout_5.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_5.setObjectName("verticalLayout_5")
        self.ICONFRAME = QtWidgets.QFrame(self.rightSide)
        self.ICONFRAME.setMinimumSize(QtCore.QSize(0, 350))
        self.ICONFRAME.setStyleSheet("QFrame{\n"
"    border-radius:10px;\n"
"    background:rgb(0, 85, 216)\n"
"}")
        self.ICONFRAME.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.ICONFRAME.setFrameShadow(QtWidgets.QFrame.Raised)
        self.ICONFRAME.setObjectName("ICONFRAME")
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout(self.ICONFRAME)
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.ICONPNG = QtWidgets.QLabel(self.ICONFRAME)
        self.ICONPNG.setMinimumSize(QtCore.QSize(0, 250))
        self.ICONPNG.setMaximumSize(QtCore.QSize(16777215, 16777215))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.ICONPNG.setFont(font)
        self.ICONPNG.setText("")
        self.ICONPNG.setPixmap(QtGui.QPixmap(":/ICON/icon.png"))
        self.ICONPNG.setAlignment(QtCore.Qt.AlignCenter)
        self.ICONPNG.setObjectName("ICONPNG")
        self.horizontalLayout_3.addWidget(self.ICONPNG)
        self.HWTRACKERLABEL = QtWidgets.QLabel(self.ICONFRAME)
        font = QtGui.QFont()
        font.setFamily("Arial")
        font.setPointSize(50)
        self.HWTRACKERLABEL.setFont(font)
        self.HWTRACKERLABEL.setAlignment(QtCore.Qt.AlignCenter)
        self.HWTRACKERLABEL.setObjectName("HWTRACKERLABEL")
        self.horizontalLayout_3.addWidget(self.HWTRACKERLABEL)
        self.verticalLayout_5.addWidget(self.ICONFRAME)
        self.BOTTOMCONTAINER = QtWidgets.QGroupBox(self.rightSide)
        font = QtGui.QFont()
        font.setPointSize(24)
        self.BOTTOMCONTAINER.setFont(font)
        self.BOTTOMCONTAINER.setAutoFillBackground(False)
        self.BOTTOMCONTAINER.setStyleSheet("QGroupBox{\n"
"    border: 2px solid rgb(50, 50, 54);\n"
"}\n"
"QLabel{\n"
"    background:rgb(50, 50, 54);\n"
"    border-radius:5px;\n"
"    border: 2px solid rgb(27, 129, 255);\n"
"    padding:2px;\n"
"    color:rgb(255, 255, 255);\n"
"}")
        self.BOTTOMCONTAINER.setObjectName("BOTTOMCONTAINER")
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout(self.BOTTOMCONTAINER)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.TODOS = QtWidgets.QScrollArea(self.BOTTOMCONTAINER)
        self.TODOS.setStyleSheet("QGroupBox{\n"
"    border: 1px solid rgb(27, 129, 255);\n"
"}")
        self.TODOS.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        self.TODOS.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        self.TODOS.setWidgetResizable(True)
        self.TODOS.setObjectName("TODOS")
        self.TODOSSCROLLABLE = QtWidgets.QWidget()
        self.TODOSSCROLLABLE.setGeometry(QtCore.QRect(0, 0, 222, 267))
        self.TODOSSCROLLABLE.setObjectName("TODOSSCROLLABLE")
        self.verticalLayout_27 = QtWidgets.QVBoxLayout(self.TODOSSCROLLABLE)
        self.verticalLayout_27.setObjectName("verticalLayout_27")
        self.todoBox = QtWidgets.QGroupBox(self.TODOSSCROLLABLE)
        self.todoBox.setMinimumSize(QtCore.QSize(0, 170))
        self.todoBox.setObjectName("todoBox")
        self.verticalLayout_28 = QtWidgets.QVBoxLayout(self.todoBox)
        self.verticalLayout_28.setObjectName("verticalLayout_28")
        self.TBtitleFrame = QtWidgets.QFrame(self.todoBox)
        self.TBtitleFrame.setMaximumSize(QtCore.QSize(16777215, 50))
        self.TBtitleFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.TBtitleFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.TBtitleFrame.setObjectName("TBtitleFrame")
        self.verticalLayout_29 = QtWidgets.QVBoxLayout(self.TBtitleFrame)
        self.verticalLayout_29.setObjectName("verticalLayout_29")
        self.TBtitle = QtWidgets.QLabel(self.TBtitleFrame)
        self.TBtitle.setObjectName("TBtitle")
        self.verticalLayout_29.addWidget(self.TBtitle)
        self.verticalLayout_28.addWidget(self.TBtitleFrame)
        self.TBdescFrame = QtWidgets.QFrame(self.todoBox)
        self.TBdescFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.TBdescFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.TBdescFrame.setObjectName("TBdescFrame")
        self.verticalLayout_30 = QtWidgets.QVBoxLayout(self.TBdescFrame)
        self.verticalLayout_30.setObjectName("verticalLayout_30")
        self.TBdesc = QtWidgets.QLabel(self.TBdescFrame)
        self.TBdesc.setAlignment(QtCore.Qt.AlignCenter)
        self.TBdesc.setObjectName("TBdesc")
        self.verticalLayout_30.addWidget(self.TBdesc)
        self.verticalLayout_28.addWidget(self.TBdescFrame)
        self.verticalLayout_27.addWidget(self.todoBox)
        self.TODOS.setWidget(self.TODOSSCROLLABLE)
        self.horizontalLayout_2.addWidget(self.TODOS)
        self.SCHEDULE = QtWidgets.QScrollArea(self.BOTTOMCONTAINER)
        self.SCHEDULE.setStyleSheet("QGroupBox{\n"
"    border: 1px solid rgb(27, 129, 255);\n"
"}")
        self.SCHEDULE.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        self.SCHEDULE.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        self.SCHEDULE.setWidgetResizable(True)
        self.SCHEDULE.setObjectName("SCHEDULE")
        self.SCHEDULESCROLLABLE = QtWidgets.QWidget()
        self.SCHEDULESCROLLABLE.setGeometry(QtCore.QRect(0, 0, 221, 267))
        self.SCHEDULESCROLLABLE.setObjectName("SCHEDULESCROLLABLE")
        self.verticalLayout_23 = QtWidgets.QVBoxLayout(self.SCHEDULESCROLLABLE)
        self.verticalLayout_23.setObjectName("verticalLayout_23")
        self.scheduleBox = QtWidgets.QGroupBox(self.SCHEDULESCROLLABLE)
        self.scheduleBox.setMinimumSize(QtCore.QSize(0, 170))
        self.scheduleBox.setObjectName("scheduleBox")
        self.verticalLayout_24 = QtWidgets.QVBoxLayout(self.scheduleBox)
        self.verticalLayout_24.setObjectName("verticalLayout_24")
        self.SBtimeFrame = QtWidgets.QFrame(self.scheduleBox)
        self.SBtimeFrame.setMaximumSize(QtCore.QSize(16777215, 50))
        self.SBtimeFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.SBtimeFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.SBtimeFrame.setObjectName("SBtimeFrame")
        self.verticalLayout_25 = QtWidgets.QVBoxLayout(self.SBtimeFrame)
        self.verticalLayout_25.setObjectName("verticalLayout_25")
        self.SBtime = QtWidgets.QLabel(self.SBtimeFrame)
        self.SBtime.setObjectName("SBtime")
        self.verticalLayout_25.addWidget(self.SBtime)
        self.verticalLayout_24.addWidget(self.SBtimeFrame)
        self.SBdescFrame = QtWidgets.QFrame(self.scheduleBox)
        self.SBdescFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.SBdescFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.SBdescFrame.setObjectName("SBdescFrame")
        self.verticalLayout_26 = QtWidgets.QVBoxLayout(self.SBdescFrame)
        self.verticalLayout_26.setObjectName("verticalLayout_26")
        self.SBdesc = QtWidgets.QLabel(self.SBdescFrame)
        self.SBdesc.setAlignment(QtCore.Qt.AlignCenter)
        self.SBdesc.setObjectName("SBdesc")
        self.verticalLayout_26.addWidget(self.SBdesc)
        self.verticalLayout_24.addWidget(self.SBdescFrame)
        self.verticalLayout_23.addWidget(self.scheduleBox)
        self.SCHEDULE.setWidget(self.SCHEDULESCROLLABLE)
        self.horizontalLayout_2.addWidget(self.SCHEDULE)
        self.NEWS = QtWidgets.QScrollArea(self.BOTTOMCONTAINER)
        self.NEWS.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        self.NEWS.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        self.NEWS.setWidgetResizable(True)
        self.NEWS.setObjectName("NEWS")
        self.NEWSSCROLLABLE = QtWidgets.QWidget()
        self.NEWSSCROLLABLE.setGeometry(QtCore.QRect(0, 0, 222, 267))
        self.NEWSSCROLLABLE.setObjectName("NEWSSCROLLABLE")
        self.verticalLayout_12 = QtWidgets.QVBoxLayout(self.NEWSSCROLLABLE)
        self.verticalLayout_12.setObjectName("verticalLayout_12")
        self.NewsBox = QtWidgets.QGroupBox(self.NEWSSCROLLABLE)
        self.NewsBox.setMinimumSize(QtCore.QSize(0, 170))
        self.NewsBox.setStyleSheet("QGroupBox{\n"
"    border: 1px solid rgb(27, 129, 255);\n"
"}")
        self.NewsBox.setObjectName("NewsBox")
        self.verticalLayout_6 = QtWidgets.QVBoxLayout(self.NewsBox)
        self.verticalLayout_6.setObjectName("verticalLayout_6")
        self.NBtitleBox = QtWidgets.QFrame(self.NewsBox)
        self.NBtitleBox.setMaximumSize(QtCore.QSize(16777215, 50))
        self.NBtitleBox.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.NBtitleBox.setFrameShadow(QtWidgets.QFrame.Raised)
        self.NBtitleBox.setObjectName("NBtitleBox")
        self.verticalLayout_9 = QtWidgets.QVBoxLayout(self.NBtitleBox)
        self.verticalLayout_9.setObjectName("verticalLayout_9")
        self.NBtitle = QtWidgets.QLabel(self.NBtitleBox)
        self.NBtitle.setMaximumSize(QtCore.QSize(16777215, 50))
        self.NBtitle.setObjectName("NBtitle")
        self.verticalLayout_9.addWidget(self.NBtitle)
        self.verticalLayout_6.addWidget(self.NBtitleBox)
        self.NBdescBox = QtWidgets.QFrame(self.NewsBox)
        self.NBdescBox.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.NBdescBox.setFrameShadow(QtWidgets.QFrame.Raised)
        self.NBdescBox.setObjectName("NBdescBox")
        self.verticalLayout_8 = QtWidgets.QVBoxLayout(self.NBdescBox)
        self.verticalLayout_8.setObjectName("verticalLayout_8")
        self.NBdesc = QtWidgets.QLabel(self.NBdescBox)
        self.NBdesc.setAlignment(QtCore.Qt.AlignCenter)
        self.NBdesc.setObjectName("NBdesc")
        self.verticalLayout_8.addWidget(self.NBdesc)
        self.verticalLayout_6.addWidget(self.NBdescBox)
        self.verticalLayout_12.addWidget(self.NewsBox)
        self.NEWS.setWidget(self.NEWSSCROLLABLE)
        self.horizontalLayout_2.addWidget(self.NEWS)
        self.verticalLayout_5.addWidget(self.BOTTOMCONTAINER)

        self.retranslateUi(Form)
        self.tabWidget.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.logintext.setText(_translate("Form", "Login"))
        self.UsernameInputS.setPlaceholderText(_translate("Form", "Username"))
        self.PasswordInputS.setPlaceholderText(_translate("Form", "Password"))
        self.keepsignin.setText(_translate("Form", "Keep me\n"
" signed in"))
        self.submitcredentials.setText(_translate("Form", "Sign In"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.login), _translate("Form", "Login"))
        self.registerlable.setText(_translate("Form", "Register"))
        self.UsernameInputR.setPlaceholderText(_translate("Form", "Username"))
        self.passwordInputR.setPlaceholderText(_translate("Form", "Password"))
        self.passwordInputConfirmR.setPlaceholderText(_translate("Form", "Pass again"))
        self.registercredentials.setText(_translate("Form", "Sign Up"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.signup), _translate("Form", "Register"))
        self.signinLocalText.setText(_translate("Form", "Make an account to \n"
" save your classes\n"
" and schoolwork \n"
" into our database\n"
" however if you are\n"
" offline, click \n"
" \"continue from\n"
" device\""))
        self.signinLocalButton.setText(_translate("Form", "Continue From \n"
"Device"))
        self.checkusout.setText(_translate("Form", "<html><head/><body><p>Visit us <br/></p></body></html>"))
        self.HWTRACKERLABEL.setText(_translate("Form", "<html><head/><body><p><span style=\" font-weight:600; color:#fbfbfb;\">HW</span><span style=\" color:#fbfbfb;\">Tracker</span></p></body></html>"))
        self.TBtitle.setText(_translate("Form", "TODO"))
        self.TBdesc.setText(_translate("Form", "Geometry stuff"))
        self.SBtime.setText(_translate("Form", "10:01-12:34"))
        self.SBdesc.setText(_translate("Form", "Math"))
        self.NBtitle.setText(_translate("Form", "New as of v1.0"))
        self.NBdesc.setText(_translate("Form", "daksjlflllfa"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Form = QtWidgets.QWidget()
    ui = Ui_Form()
    ui.setupUi(Form)
    Form.show()
    sys.exit(app.exec_())