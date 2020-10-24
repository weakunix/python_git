from handlers import filehandler
import yaml

directory = "./QTgenerated/"

def styleMain(ui):
    defaultstyle = str(filehandler.yamlload("./data/settings.yaml")["theme"])
    a = str((filehandler.yamlload(directory+"themes.yaml")[str(defaultstyle)]["todoDiv"]).replace(" ", "").replace('"', "")).replace("\\n", "").replace("'", "")
    print(a)
    ui.todoDiv.setStyleSheet(a)
    #change later to have the 2 in settings.yaml