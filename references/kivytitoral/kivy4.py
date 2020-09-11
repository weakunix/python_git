#use 3.5-3.7.7
import kivy
from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.gridlayout import GridLayout
from kivy.uix.textinput import TextInput
from kivy.uix.button import Button

class DZNR(GridLayout):
    pass

        

class MyApp(App):
    def build(self):
        return DZNR()
#main
if __name__ == '__main__':
    MyApp().run()
