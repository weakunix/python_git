#use 3.5-3.7.7
import kivy
from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.gridlayout import GridLayout
from kivy.uix.textinput import TextInput
from kivy.uix.button import Button
from kivy.uix.widget import Widget
from kivy.properties import ObjectProperty

class DZNR(Widget):
    name = ObjectProperty(None)
    email = ObjectProperty(None)
     #used in kv file
    def press(self):
        print("Name: "+str(self.name.text)+"\nEmail: "+str(self.email.text))

class MyApp(App):
    def build(self):
        return DZNR()
#main
if __name__ == '__main__':
    MyApp().run()
