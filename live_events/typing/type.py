#imports
import tkinter as tk, time, pandas as pd
from tkinter import messagebox

#vars
name = ''
words = [] #words
wpm = 0 #words per minute
accuracy = 0 #accuracy
mode = 0 #typing mode

#classes
##class page 
class Page:
    #init
    def __init__(self):
        #setting its widgets and binds to []
        self.widgets = []
        self.binds = []
    def clear(self):
        for i in self.widgets:
            i.destroy()
        for i in self.binds:
            window.unbind(i)

#class back button 
class BackButton:
    #init
    def __init__(self, clear, create):
        #create back button
        self.button = tk.Button(window, text = 'Back(X)', height = 3, width = 8, fg = '#000000', font = ('charter', 15), command = lambda: [clear.clear(), create()])
        self.button.place(x = 0, y = 0, anchor = tk.NW)
        #bind to back button
        window.bind('<x>', lambda event: [clear.clear(), create()])
        #append into its page's widgets
        clear.widgets.append(self.button)
        #append into its page's binds
        clear.binds.append('<x>')

#class title
class Title:
    #init
    def __init__(self, text, clear):
        #create title
        self.label = tk.Label(window, text = text, bg = '#00FFFF', fg = '#000000', font = ('charter', 60, 'italic'))
        self.label.place(x = 400, y = 175, anchor = tk.CENTER)
        #append into its page's widgets
        clear.widgets.append(self.label)

#user def functions
##login or signup
def login_or_signup():
    #Page class instance login or signup page
    loginorsignup = Page()
    #window title
    window.title('Login / Sign Up')
    #making widgets
    start_title = Title('Type Training', loginorsignup)
    login = tk.Button(window, text = 'Login(L)', height = 3, width = 8, fg = '#000000', font = ('charter', 15), command = lambda: [loginorsignup.clear(), login_signup_page('Login')])
    login.place(x = 350, y = 400, anchor = tk.CENTER)
    signup = tk.Button(window, text = 'Sign Up(S)', height = 3, width = 8, fg = '#000000', font = ('charter', 15), command = lambda: [loginorsignup.clear(), login_signup_page('Sign Up')])
    signup.place(x = 450, y = 400, anchor = tk.CENTER)
    #binding keys
    window.bind('<l>', lambda event: [loginorsignup.clear(), login_signup_page('Login')])
    window.bind('<s>', lambda event: [loginorsignup.clear(), login_signup_page('Sign Up')])
    #loginorsignup widgets and binds defined
    loginorsignup.widgets += [login, signup]
    loginorsignup.binds += ['<l>', '<s>']

##login page / signup page (they are the same format)
def login_signup_page(logorsign):
    #globals
    global loginsignup
    #Page class instance login signup page
    loginsignup = Page()
    #window title
    window.title(logorsign)
    #making widgets
    loginsignup_title = Title(f'{logorsign}:', loginsignup)
    back_button = BackButton(loginsignup, login_or_signup)
    name = tk.Label(window, text = 'Name: ', bg = '#00FFFF', fg = '#000000', font = ('charter', 20))
    name.place(x = 260, y = 375, anchor = tk.CENTER)
    name_input = tk.Entry(window, font = ('charter', 15))
    name_input.place(x = 400, y = 375, anchor = tk.CENTER)
    loginsignup_button = tk.Button(window, text = f'{logorsign}(Enter)', height = 3, width = 15, fg = '#000000', font = ('charter', 15), command = lambda: get_account(logorsign))
    loginsignup_button.place(x = 400, y = 450, anchor = tk.CENTER)
    #binding keys
    window.bind('<Return>', lambda event: get_account(logorsign))
    #loginsignup widgets and binds defined
    loginsignup.widgets += [name, name_input, loginsignup_button]
    loginsignup.binds += ['<Return>']

##getting account (logging in or signing up)
def get_account(logorsign):
    #globals
    global loginsignup, name, words, wpm, accuracy
    #getting account 
    name = loginsignup.widgets[3].get()
    is_account = False #sign up is if the account is taken, log in is if the account is stored
    #try to read
    try:
        accounts = pd.read_csv('accounts.txt', index_col = 'name')
    #else create data frame
    except:
        accounts = pd.DataFrame({'name': [], 'wpm': [], 'accuracy': []})
    for i in range(len(accounts)):
        if accounts.index[i] == name:
            is_account = True
            break
    if logorsign == 'Login':
        if is_account:
            wpm = accounts.loc[name, 'wpm']
            accuracy = accounts.loc[name, 'accuracy']
            words = []
            try:
                with open(f'./words/{name}_words.txt', 'r') as word_file:
                    for line in word_file:
                        words.append(line.strip('\n'))
            except:
                pass
            loginsignup.clear()
            login_success(logorsign)
        else:
            not_found = tk.Label(window, text = 'Account not found!', bg = '#00FFFF', fg = '#FF0000', font = ('charter', 10))
            not_found.place(x = 400, y = 550, anchor = tk.CENTER)
            loginsignup.widgets.append(not_found)
            loginsignup.widgets[3].selection_range(0, tk.END)
    else:
        if not is_account:
            wpm = 'N/A'
            accuracy = 'N/A'
            words = []
            all_names = [accounts.index[i] for i in range(len(accounts))] + [name]
            all_wpm = [accounts.loc[all_names[i], 'wpm'] for i in range(len(all_names) - 1)] + [0]
            all_accuracy = [accounts.loc[all_names[i], 'accuracy'] for i in range(len(all_names) - 1)] + [0]
            accounts = pd.DataFrame({'name': all_names, 'wpm': all_wpm, 'accuracy': all_accuracy})
            accounts.to_csv('accounts.txt', index = False)
            loginsignup.clear()
            login_success(logorsign)
        else:
            not_found = tk.Label(window, text = 'This name has already been taken!', bg = '#00FFFF', fg = '#FF0000', font = ('charter', 10))
            not_found.place(x = 400, y = 550, anchor = tk.CENTER)
            loginsignup.widgets.append(not_found)
            loginsignup.widgets[3].selection_range(0, tk.END)

#login / sign up successful
def login_success(logorsign):
    pass
                
#TODO FINISH PARTS PAST THESE LATER!!!!!! DO NOT WORK ON THEM NOW OR YOUR EFFECIENCY WILL GO DOWN!!!!
##home page
def home_page():
    #Page class instance home page
    homepage = Page()
    #making widgets
    home_title = tk.Label(window, text = 'Typing Training', bg = '#00FFFF', fg = '#000000', font = ('charter', 60, 'italic'))
    home_title.place(x = 400, y = 175, anchor = tk.CENTER)
    type_button = tk.Button(window, text = 'Type(T)', height = 3, width = 8, fg = '#000000', font = ('charter', 15), command = lambda: [homepage.clear(), word_amount()])
    type_button.place(x = 200, y = 450, anchor = tk.CENTER)
    add_word_button = tk.Button(window, text = 'Add\nWord(A)', height = 3, width = 8, fg = '#000000', font = ('charter', 15), command = lambda: [homepage.clear(), add_word()])
    add_word_button.place(x = 300, y = 450, anchor = tk.CENTER)
    remove_word = tk.Button(window, text = 'Remove\nWord(D)', height = 3, width = 8, fg = '#000000', font = ('charter', 15))
    remove_word.place(x = 400, y = 450, anchor = tk.CENTER)
    all_word = tk.Button(window, text = 'Words(W)', height = 3, width = 8, fg = '#000000', font = ('charter', 15))
    all_word.place(x = 500, y = 450, anchor = tk.CENTER)
    stats = tk.Button(window, text = 'Profile(P)', height = 3, width = 8, fg = '#000000', font = ('charter', 15))
    stats.place(x = 600, y = 450, anchor = tk.CENTER)
    #binding keys
    window.bind('<r>', lambda event: [homepage.clear(), word_amount()])
    window.bind('<a>', lambda event: [homepage.clear(), add_word()])
    #homepage widgets and binds defined
    homepage.widgets = [home_title, type_button, add_word_button, remove_word, all_word, stats]
    homepage.binds = ['<r>', '<a>']

##word amount page
def word_amount():
    wordamount = Page()
    amount = tk.Scale(window, from_ = 20, to = 200, orient = tk.HORIZONTAL, length = 600, bg = '#00FFFF')
    amount.place(x = 400, y = 350, anchor = tk.CENTER)
    start = tk.Button(window, text = 'Start Typing(Enter)', height = 3, width = 15, fg = '#000000', font = ('charter', 15))
    start.place(x = 400, y = 450, anchor = tk.CENTER)
    instructions = tk.Label(window, text = 'Select the number of\nwords you want to type:', bg = '#00FFFF', fg = '#000000', font = ('charter', 40))
    instructions.place(x = 400, y = 150, anchor = tk.CENTER)

##adding a word
def add_word():
    #globals
    global addword
    #Page class instance addword page
    addword = Page()
    #making widgets
    word = tk.Entry(window)
    word.place(x = 400, y = 350, anchor = tk.CENTER)
    add_button = tk.Button(window, text = 'Add Word(Enter)', height = 3, width = 15, fg = '#000000', font = ('charter', 15), command = lambda: get_add_word())
    add_button.place(x = 400, y = 450, anchor = tk.CENTER)
    add_instructions = tk.Label(window, text = 'Type the word you\nwant to add here:', bg = '#00FFFF', fg = '#000000', font = ('charter', 40))
    add_instructions.place(x = 400, y = 150, anchor = tk.CENTER)
    #binding keys
    window.bind('<Return>', lambda event: get_add_word())
    addword.widgets = [word, add_button, add_instructions]
    addword.binds = ['<Return>']

##getting the added word
def get_add_word():
    #globals
    global addword
    word = addword.widgets[0].get()
    print(word)

#main
if __name__ == '__main__':
    #window set up
    window = tk.Tk()
    window.geometry('800x600')
    window.config(bg = '#00FFFF')
    #call login or signup func
    login_or_signup()
    #mainloop
    window.mainloop()
