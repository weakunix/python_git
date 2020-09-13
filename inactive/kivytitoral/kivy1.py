#use 3.5-3.7.7
import kivy
from kivy.app import App
from kivy.uix.label import Label

class MyApp(App):
    def build(self):
        return Label(text="Hello MOOrld")
#main
if __name__ == '__main__':
    MyApp().run()

