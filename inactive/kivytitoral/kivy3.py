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

        self.inside = GridLayout()
        self.inside.cols = 2

        self.cols = 1
        self.inside.add_widget(Label(text="Username: "))
        self.name = TextInput(multiline=False)
        self.inside.add_widget(self.name)
        self.inside.add_widget(Label(text="Pissword: "))
        self.pwd = TextInput(multiline=False)
        self.inside.add_widget(self.pwd)
        self.inside.add_widget(Label(text="Email: "))
        self.mail = TextInput(multiline=False)
        self.inside.add_widget(self.mail)

        self.add_widget(self.inside)

        self.submit = Button(text = "Submit", font_size=40)
        self.submit.bind(on_press=self.pressed)
        self.add_widget(self.submit)

    def pressed(self, instance):
        print("Name: "+str(self.name.text)+"\nPassword: "+str(self.pwd.text)+"\nEmail: "+str(self.mail.text))
        self.name.text = ""
        self.pwd.text = ""
        self.mail.text = ""

        

class MyApp(App):
    def build(self):
        return DZNR()
#main
if __name__ == '__main__':
    MyApp().run()
