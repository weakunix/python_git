import tkinter as tk

def destroyBTN(*args, **kwargs):
    arry = kwargs.get("arry", None)
    for i in args:
        try:
            i.destroy()
        except:
            print("oopsies")
    if type(arry) == list:
        for ii in range(len(arry)):
            arry[ii].destroy()