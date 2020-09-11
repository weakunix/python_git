#use 3.5-3.7.7
import kivy
from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.gridlayout import GridLayout
from kivy.uix.textinput import TextInput
from kivy.uix.button import Button

class DZNR(GridLayout):
    def __init__(self, **kwargs):
        super(DZNR, self).__init__(**kwargs)
        self.cols = 1
        self.add_widget(Label(text="Username: "))
        self.name = TextInput(multiline=False)
        self.add_widget(self.name)
        self.add_widget(Label(text="Pissword: "))
        self.name = TextInput(multiline=False)
        self.add_widget(self.name)
        self.add_widget(Label(text="Email: "))
        self.name = TextInput(multiline=False)
        self.add_widget(self.name)

class MyApp(App):
    def build(self):
        return DZNR()
#main
if __name__ == '__main__':
    MyApp().run()
