from handlers import filehandler
import yaml

directory = "./QTgenerated/"
defaultstyle = str(filehandler.yamlload("./data/settings.yaml")["theme"])

def styleMain(ui):
    
    ui.todoDiv.setStyleSheet(styleGetter("todoDiv"))
    #change later to have the 2 in settings.

def styleGetter(obj):
    return str((filehandler.yamlload(directory+"themes.yaml")[str(defaultstyle)][str(obj)]).replace(" ", "").replace('"', "")).replace("\\n", "")