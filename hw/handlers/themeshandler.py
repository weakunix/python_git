from handlers import filehandler
import yaml

directory = "./QTgenerated/"
defaultstyle = str(filehandler.yamlload("./data/settings.yaml")["theme"])

def styleMain(ui):
    for objs in filehandler.yamlload(directory+"themes.yaml")[str(defaultstyle)]:
        try:
            exec(f"ui.{str(objs)}.setStyleSheet(styleGetter(str(objs)))")
        except Exception:
            print(Exception)

def styleGetter(obj):
    return str((filehandler.yamlload(directory+"themes.yaml")[str(defaultstyle)][str(obj)]).replace(" ", "").replace('"', "")).replace("\\n", "")