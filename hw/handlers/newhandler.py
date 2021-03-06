from PyQt5 import QtCore, QtGui, QtWidgets
#import filehandler

translate = QtCore.QCoreApplication.translate

class newSomething:
    @staticmethod
    def newClass(ui, arrayOfClassesAlready):
        
        className = ui.newClassName_2.toPlainText()
        timeStarts = ui.starts.dateTime()
        timeEnds = ui.done.dateTime()
        blockName = ui.newBlock.toPlainText()
        classRoomNumber = ui.newClassroomNum.toPlainText()

        #
        
        ui.time.setText(ui._translate("Form", "11:45-12:01"))
        ui.classBlockTextSched.setText(ui._translate("Form", "A"))
        ui.classNumberNameSched.setText(ui._translate("Form", "LC 7"))
        ui.classNameSched.setText(ui._translate("Form", "AP Computer Science"))
        ui.showExtra.setText(ui._translate("Form", "..."))

    @staticmethod
    def newHomework(ui, arrayOfTodosAlready):
        homeworkInfo = ui.newHWText.toPlainText()
        dueDate = ui.newDueTime.dateTime().toSecsSinceEpoch()
        isRepeating = ui.radioButton.isDown() #Ruoyu for you bc your dumb shitqing
        difficulty = ui.newDifficultySlider.value()
        fromClass = ui.newClassToHW.currentText()

        dueIn = (dueDate - QtCore.QDateTime().currentDateTime().toSecsSinceEpoch())

        if dueIn < 0: 
            return #can't be already due lmao
        
        #calculates when assignment is due
        dueDays = (dueIn // 86400)
        temp = dueIn % 86400
        dueHours = temp // 3600
        dueMinutes = temp % 3600 // 60

        if homeworkInfo.replace(" ", "") == "":
            return #not good!!! don't put JUST SPACE as hw name 

        #add to file

        newSomething.todos(ui)

        ui.blockName.setText(ui._translate("Form", "")) # get block from class info
        ui.classname.setText(ui._translate("Form", str(fromClass)))
        ui.diffrating.setText(ui._translate("Form", f"{str(difficulty)}/10"))
        ui.dueinName.setText(ui._translate("Form", str(dueDays)))
        ui.extrabtn.setText(ui._translate("Form", "..."))

    @staticmethod
    def todos(ui):
        ui.horizontalLayout_14 = QtWidgets.QHBoxLayout(ui.classSubject)
        ui.horizontalLayout_14.setObjectName("horizontalLayout_14")
        ui.ifDone = QtWidgets.QCheckBox(ui.classSubject)
        ui.ifDone.setMaximumSize(QtCore.QSize(20, 16777215))
        ui.ifDone.setCursor(QtGui.QCursor(QtCore.Qt.OpenHandCursor))
        ui.ifDone.setText("")
        ui.ifDone.setObjectName("ifDone")
        ui.horizontalLayout_14.addWidget(ui.ifDone)
        ui.block = QtWidgets.QGroupBox(ui.classSubject)
        ui.block.setMaximumSize(QtCore.QSize(39, 16777215))
        ui.block.setTitle("")
        ui.block.setObjectName("block")
        ui.horizontalLayout_11 = QtWidgets.QHBoxLayout(ui.block)
        ui.horizontalLayout_11.setObjectName("horizontalLayout_11")
        ui.blockName = QtWidgets.QLabel(ui.block)
        ui.blockName.setAlignment(QtCore.Qt.AlignCenter)
        ui.blockName.setObjectName("blockName")
        ui.horizontalLayout_11.addWidget(ui.blockName)
        ui.horizontalLayout_14.addWidget(ui.block)
        ui.classinside = QtWidgets.QGroupBox(ui.classSubject)
        ui.classinside.setTitle("")
        ui.classinside.setObjectName("classinside")
        ui.horizontalLayout_10 = QtWidgets.QHBoxLayout(ui.classinside)
        ui.horizontalLayout_10.setObjectName("horizontalLayout_10")
        ui.classname = QtWidgets.QLabel(ui.classinside)
        ui.classname.setAlignment(QtCore.Qt.AlignCenter)
        ui.classname.setObjectName("classname")
        ui.horizontalLayout_10.addWidget(ui.classname)
        ui.horizontalLayout_14.addWidget(ui.classinside)
        ui.diff = QtWidgets.QGroupBox(ui.classSubject)
        ui.diff.setMaximumSize(QtCore.QSize(57, 16777215))
        ui.diff.setTitle("")
        ui.diff.setObjectName("diff")
        ui.horizontalLayout_9 = QtWidgets.QHBoxLayout(ui.diff)
        ui.horizontalLayout_9.setObjectName("horizontalLayout_9")
        ui.diffrating = QtWidgets.QLabel(ui.diff)
        ui.diffrating.setAlignment(QtCore.Qt.AlignCenter)
        ui.diffrating.setObjectName("diffrating")
        ui.horizontalLayout_9.addWidget(ui.diffrating)
        ui.horizontalLayout_14.addWidget(ui.diff)
        ui.progress = QtWidgets.QGroupBox(ui.classSubject)
        ui.progress.setMaximumSize(QtCore.QSize(50, 71))
        ui.progress.setTitle("")
        ui.progress.setObjectName("progress")
        ui.horizontalLayout_12 = QtWidgets.QHBoxLayout(ui.progress)
        ui.horizontalLayout_12.setObjectName("horizontalLayout_12")
        ui.progressBar = QtWidgets.QProgressBar(ui.progress)
        ui.progressBar.setMaximumSize(QtCore.QSize(95, 16777215))
        ui.progressBar.setStyleSheet("")
        ui.progressBar.setProperty("value", 24)
        ui.progressBar.setObjectName("progressBar")
        ui.horizontalLayout_12.addWidget(ui.progressBar)
        ui.horizontalLayout_14.addWidget(ui.progress)
        ui.duein = QtWidgets.QGroupBox(ui.classSubject)
        ui.duein.setMaximumSize(QtCore.QSize(50, 71))
        ui.duein.setTitle("")
        ui.duein.setObjectName("duein")
        ui.horizontalLayout_13 = QtWidgets.QHBoxLayout(ui.duein)
        ui.horizontalLayout_13.setObjectName("horizontalLayout_13")
        ui.dueinName = QtWidgets.QLabel(ui.duein)
        ui.dueinName.setLayoutDirection(QtCore.Qt.LeftToRight)
        ui.dueinName.setAlignment(QtCore.Qt.AlignCenter)
        ui.dueinName.setObjectName("dueinName")
        ui.horizontalLayout_13.addWidget(ui.dueinName)
        ui.horizontalLayout_14.addWidget(ui.duein)
        ui.extrainfo = QtWidgets.QFrame(ui.classSubject)
        ui.extrainfo.setMaximumSize(QtCore.QSize(51, 16777215))
        ui.extrainfo.setObjectName("extrainfo")
        ui.extrabtn = QtWidgets.QPushButton(ui.extrainfo)
        ui.extrabtn.setGeometry(QtCore.QRect(0, 0, 40, 38))
        ui.extrabtn.setMinimumSize(QtCore.QSize(40, 38))
        ui.extrabtn.setMaximumSize(QtCore.QSize(40, 38))
        ui.extrabtn.setObjectName("extrabtn")
        ui.horizontalLayout_14.addWidget(ui.extrainfo)
        ui.verticalLayout_2.addWidget(ui.classSubject)
        ui.scrollableHomeworkDisplay.setWidget(ui.scrollHomework)
        ui.verticalLayout.addWidget(ui.scrollableHomeworkDisplay)
    
    @staticmethod
    def classs(ui):
        ui.horizontalLayout_33 = QtWidgets.QHBoxLayout(ui.timeclassstartend)
        ui.horizontalLayout_33.setObjectName("horizontalLayout_33")
        ui.time = QtWidgets.QLabel(ui.timeclassstartend)
        ui.time.setMinimumSize(QtCore.QSize(0, 20))
        ui.time.setAlignment(QtCore.Qt.AlignCenter)
        ui.time.setObjectName("time")
        ui.horizontalLayout_33.addWidget(ui.time)
        ui.horizontalLayout_16.addWidget(ui.timeclassstartend)
        ui.classBlockSched = QtWidgets.QGroupBox(ui.classItem)
        ui.classBlockSched.setMaximumSize(QtCore.QSize(50, 71))
        ui.classBlockSched.setTitle("")
        ui.classBlockSched.setObjectName("classBlockSched")
        ui.horizontalLayout_29 = QtWidgets.QHBoxLayout(ui.classBlockSched)
        ui.horizontalLayout_29.setObjectName("horizontalLayout_29")
        ui.classBlockTextSched = QtWidgets.QLabel(ui.classBlockSched)
        ui.classBlockTextSched.setMinimumSize(QtCore.QSize(0, 20))
        ui.classBlockTextSched.setAlignment(QtCore.Qt.AlignCenter)
        ui.classBlockTextSched.setObjectName("classBlockTextSched")
        ui.horizontalLayout_29.addWidget(ui.classBlockTextSched)
        ui.horizontalLayout_16.addWidget(ui.classBlockSched)
        ui.classNumberSched = QtWidgets.QGroupBox(ui.classItem)
        ui.classNumberSched.setTitle("")
        ui.classNumberSched.setObjectName("classNumberSched")
        ui.horizontalLayout_30 = QtWidgets.QHBoxLayout(ui.classNumberSched)
        ui.horizontalLayout_30.setObjectName("horizontalLayout_30")
        ui.classNumberNameSched = QtWidgets.QLabel(ui.classNumberSched)
        ui.classNumberNameSched.setMinimumSize(QtCore.QSize(0, 20))
        ui.classNumberNameSched.setAlignment(QtCore.Qt.AlignCenter)
        ui.classNumberNameSched.setObjectName("classNumberNameSched")
        ui.horizontalLayout_30.addWidget(ui.classNumberNameSched)
        ui.horizontalLayout_16.addWidget(ui.classNumberSched)
        ui.classNameSched_2 = QtWidgets.QGroupBox(ui.classItem)
        ui.classNameSched_2.setTitle("")
        ui.classNameSched_2.setObjectName("classNameSched_2")
        ui.horizontalLayout_31 = QtWidgets.QHBoxLayout(ui.classNameSched_2)
        ui.horizontalLayout_31.setObjectName("horizontalLayout_31")
        ui.classNameSched = QtWidgets.QLabel(ui.classNameSched_2)
        ui.classNameSched.setMinimumSize(QtCore.QSize(0, 20))
        ui.classNameSched.setAlignment(QtCore.Qt.AlignCenter)
        ui.classNameSched.setObjectName("classNameSched")
        ui.horizontalLayout_31.addWidget(ui.classNameSched)
        ui.horizontalLayout_16.addWidget(ui.classNameSched_2)
        ui.showExtra = QtWidgets.QPushButton(ui.classItem)
        ui.showExtra.setMinimumSize(QtCore.QSize(40, 38))
        ui.showExtra.setMaximumSize(QtCore.QSize(40, 38))
        ui.showExtra.setObjectName("showExtra")
        ui.horizontalLayout_16.addWidget(ui.showExtra)
        ui.verticalLayout_3.addWidget(ui.classItem)
        ui.scrollableClassesDisplay.setWidget(ui.scrollClass)