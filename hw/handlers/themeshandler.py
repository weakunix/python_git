from handlers import filehandler
import yaml

directory = "./QTgenerated/"

def styleMain(ui):
    defaultstyle = str(filehandler.yamlload("./data/settings.yaml")["theme"])
    ui.todoDiv.setStyleSheet(str(filehandler.yamlload(directory+"themes.yaml")[str(defaultstyle)]["todoDiv"]))
    #change later to have the 2 in settings.yaml


