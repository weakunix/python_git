#imports
import tkinter as tk, time, random
from tkinter import messagebox

#vars
name = ''
words = set() #words
wpm = [] #words per minute
accuracy = [] #accuracy
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
        self.button = tk.Button(window, text = 'Back', height = 3, width = 8, fg = '#000000', font = ('charter', 15), command = lambda: [clear.clear(), create()])
        self.button.place(x = 0, y = 0, anchor = tk.NW)
        #append into its page's widgets
        clear.widgets.append(self.button)

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
    window.title('Login / Signup')
    #making widgets
    start_title = Title('Type Training', loginorsignup)
    login = tk.Button(window, text = 'Login', height = 3, width = 8, fg = '#000000', font = ('charter', 15), command = lambda: [loginorsignup.clear(), login_signup_page('Login')])
    login.place(x = 350, y = 400, anchor = tk.CENTER)
    signup = tk.Button(window, text = 'Signup', height = 3, width = 8, fg = '#000000', font = ('charter', 15), command = lambda: [loginorsignup.clear(), login_signup_page('Signup')])
    signup.place(x = 450, y = 400, anchor = tk.CENTER)
    #loginorsignup widgets defined
    loginorsignup.widgets += [login, signup]

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
    name_input.focus()
    loginsignup_button = tk.Button(window, text = logorsign, height = 3, width = 10, fg = '#000000', font = ('charter', 15), command = lambda: get_account(logorsign))
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
    name = loginsignup.widgets[3].get().strip(' ')
    is_account = False #signup is if the account is taken, log in is if the account is stored
    with open('names.txt', 'r') as names:
        for i in names:
            if i.strip('\n') == name:
                is_account = True
                break
    if logorsign == 'Login':
        if is_account:
            try:
                with open('./wpms/{name}_wpms.txt', 'r') as wpms:
                    for i in wpms:
                        wpm.append(int(i.strip('\n')))
            except:
                pass
            try:
                with open('./wpms/{name}_accuracys.txt', 'r') as accuracys:
                    for i in accuracys:
                        accuracy.append(int(i.strip('\n')))
            except:
                pass
            try:
                with open(f'./words/{name}_words.txt', 'r') as word_file:
                    for i in word_file:
                        words.add(line.strip('\n'))
            except:
                pass
            loginsignup.clear()
            login_success(logorsign)
        else:
            account_fail('Account not found!')
    else:
        if not is_account:
            if ' ' not in name:
                with open('names.txt', 'a') as names:
                    names.write(f'{name}\n')
                loginsignup.clear()
                login_success(logorsign)
            else:
                account_fail('Your name cannot contain spaces!')
        else:
            account_fail('This name has already been taken!')

#account name not valid
def account_fail(text):
    #globals
    global loginsignup
    try:
        loginsignup.widgets[5].destroy()
        loginsignup.widgets[5] = tk.Label(window, text = text, bg = '#00FFFF', fg = '#FF0000', font = ('charter', 10))
        loginsignup.widgets[5].place(x = 400, y = 550, anchor = tk.CENTER)
    except:
        not_found = tk.Label(window, text = text, bg = '#00FFFF', fg = '#FF0000', font = ('charter', 10))
        not_found.place(x = 400, y = 550, anchor = tk.CENTER)
        loginsignup.widgets.append(not_found)
    loginsignup.widgets[3].selection_range(0, tk.END)

#login / sign up successful
def login_success(logorsign):
    #page class instance login success page
    loginsuccess = Page()
    #window title
    window.title(f'{logorsign} Success')
    #making widgets
    all_set = Title('You\'re all set!', loginsuccess)
    if logorsign == 'Login':
        text = 'Login success! Hopefully you got all of your stats recovered correctly...'
    else:
        text = 'Signup success! Don\'t forget your account. There isn\'t any account recovery...'
    details = tk.Label(window, text = text, bg = '#00FFFF', fg = '#000000', font = ('charter', 20))
    details.place(x = 400, y = 300, anchor = tk.CENTER)
    start_type = tk.Button(window, text = 'Continue', height = 3, width = 8, fg = '#000000', font = ('charter', 15), command = lambda: [loginsuccess.clear(), home_page()])
    start_type.place(x = 400, y = 450, anchor = tk.CENTER)
    #loginsuccess widgets defined
    loginsuccess.widgets += [details, start_type]
     
##home page
def home_page():
    #globals
    global wpm, accuracy
    #Page class instance home page
    homepage = Page()
    #window title
    window.title('Home')
    #making widgets
    home_title = Title('Typing Training', homepage)
    type_button = tk.Button(window, text = 'Type', height = 3, width = 8, fg = '#000000', font = ('charter', 15), command = lambda: [homepage.clear(), typing_settings()])
    type_button.place(x = 300, y = 450, anchor = tk.CENTER)
    add_word_button = tk.Button(window, text = 'Add\nWord', height = 3, width = 8, fg = '#000000', font = ('charter', 15), command = lambda: [homepage.clear(), add_word()])
    add_word_button.place(x = 400, y = 450, anchor = tk.CENTER)
    remove_word_button = tk.Button(window, text = 'Remove\nWord', height = 3, width = 8, fg = '#000000', font = ('charter', 15), command = lambda: [homepage.clear(), remove_word()])
    remove_word_button.place(x = 500, y = 450, anchor = tk.CENTER)
    if len(wpm) != 0:
        wpm_label = tk.Label(window, text = f'Total average WPM: {sum(wpm) / len(wpm)} | Last 10 types average WPM: {sum(wpm[-10:]) / 10} | Last type WPM: {wpm[-1]}',  bg = '#00FFFF', fg = '#000000', font = ('charter', 20))
        accuracy_label = tk.Label(window, text = f'Total average accuracy: {sum(accuracy) / len(accuracy)} | Last 10 types average accuracy: {sum(accuracy[-10:]) / 10} | Last type accuracy: {accuracy[-1]}',  bg = '#00FFFF', fg = '#000000', font = ('charter', 20))
    else:
        wpm_label = tk.Label(window, text = 'Total average WPM: N/A | Last 10 types average WPM: N/A | Last type WPM: N/A', bg = '#00FFFF', fg = '#000000', font = ('charter', 10))
        accuracy_label = tk.Label(window, text = 'Total average accuracy: N/A | Last 10 types average accuracy: N/A | Last type accuracy: N/A', bg = '#00FFFF', fg = '#000000', font = ('charter', 10))
    wpm_label.place(x = 400, y = 525, anchor = tk.CENTER)
    accuracy_label.place(x = 400, y = 550, anchor = tk.CENTER)
    #homepage widgets defined
    homepage.widgets += [type_button, add_word_button, remove_word_button, wpm_label, accuracy_label]

##word amount page
def typing_settings():
    #Page class instance typesettings page
    typesettings = Page()
    #window title
    window.title('Typing Settings')
    #checkbox and option menu variables
    mode_var = tk.StringVar()
    mode_var.set('Normal')
    #making widgets
    back_to_home = BackButton(typesettings, home_page)
    amount = tk.Scale(window, from_ = 20, to = 200, orient = tk.HORIZONTAL, length = 180, bg = '#00FFFF')
    amount.place(x = 500, y = 350, anchor = tk.CENTER)
    mode = tk.OptionMenu(window, mode_var, 'Normal', 'Sudden Death')
    mode.place(x = 300, y = 358, anchor = tk.CENTER)
    start = tk.Button(window, text = 'Start Typing', height = 3, width = 10, fg = '#000000', font = ('charter', 15))
    start.place(x = 400, y = 450, anchor = tk.CENTER)
    #defining typesettings widgets
    typesettings.widgets = [amount, mode, start]

##adding a word
def add_word():
    #globals
    global addword
    #Page class instance addword page
    addword = Page()
    #window title
    window.title('Add Word')
    #making widgets
    back_to_home = BackButton(addword, home_page)
    word = tk.Entry(window)
    word.place(x = 400, y = 350, anchor = tk.CENTER)
    word.focus()
    add_button = tk.Button(window, text = 'Add Word', height = 3, width = 15, fg = '#000000', font = ('charter', 15), command = lambda: get_add_word())
    add_button.place(x = 400, y = 450, anchor = tk.CENTER)
    add_instructions = tk.Label(window, text = 'Type the word you\nwant to add here:', bg = '#00FFFF', fg = '#000000', font = ('charter', 40))
    add_instructions.place(x = 400, y = 150, anchor = tk.CENTER)
    #binding keys
    window.bind('<Return>', lambda event: get_add_word())
    #defining addword widgets and binds
    addword.widgets += [word, add_button, add_instructions]
    addword.binds += ['<Return>']

##getting the added word
def get_add_word(): 
    #globals
    global addword, name, words
    word = addword.widgets[1].get().strip(' ')
    already_in = False
    for i in words:
        if word == i.strip('\n'):
            already_in = True
    if already_in:
        msg = messagebox.showinfo(title = 'No Duplicates!', message = f'You already have {word} added to your words!')
        if msg:
            addword.widgets[1].selection_range(0, tk.END)
            window.focus()
            addword.widgets[1].focus()
    else:
        msg = messagebox.askyesno(title = 'Did you spell correctly?', message = f'Are you sure you want to add {word} into your words?')
        if msg:
            with open(f'./words/{name}_words.txt', 'a') as all_words:
                all_words.write(f'{word}\n')
            words.add(word)
            msg = messagebox.showinfo(title = 'Adding Complete!', message = f'Successfully added {word} to your words!')
            if msg:
                addword.widgets[1].delete(0, tk.END)
                window.focus()
                addword.widgets[1].focus()
        else:
            addword.widgets[1].selection_range(0, tk.END)
            window.focus()
            addword.widgets[1].focus()

#removing a word
def remove_word():
    #globals
    global removeword
    #Page class instance removeword page
    removeword = Page()
    #window title
    window.title('Remove Word')
    #making widgets
    back_to_home = BackButton(removeword, home_page)
    word = tk.Entry(window)
    word.place(x = 400, y = 350, anchor = tk.CENTER)
    word.focus()
    remove_button = tk.Button(window, text = 'Remove Word', height = 3, width = 15, fg = '#000000', font = ('charter', 15), command = lambda: get_remove_word())
    remove_button.place(x = 400, y = 450, anchor = tk.CENTER)
    remove_instructions = tk.Label(window, text = 'Type the word you\nwant to remove here:', bg = '#00FFFF', fg = '#000000', font = ('charter', 40))
    remove_instructions.place(x = 400, y = 150, anchor = tk.CENTER)
    #binding keys
    window.bind('<Return>', lambda event: get_remove_word())
    #defining removeword widgets and binds
    removeword.widgets += [word, remove_button, remove_instructions]
    removeword.binds += ['<Return>']

#getting the removed word
def get_remove_word():
    #globals
    global removeword, name, words
    word = removeword.widgets[1].get().strip(' ')
    already_in = False
    for i in words:
        if word == i.strip('\n'):
            already_in = True
    if not already_in:
        msg = messagebox.showinfo(title = 'No can remove!', message = f'You don\'t have {word} added to your words!')
        if msg:
            removeword.widgets[1].selection_range(0, tk.END)
            window.focus()
            removeword.widgets[1].focus()
    else:
        msg = messagebox.askyesno(title = 'It\'ll be gone forever!!! (Unless you add it back)', message = f'Are you sure you want to remove {word} frome your words?')
        if msg:
            words.remove(word)
            with open(f'./words/{name}_words.txt', 'w') as all_words:
                for i in words:
                    all_words.write(f'{i}\n')
            msg = messagebox.showinfo(title = 'Removing Complete!', message = f'Successfully removed {word} from your words!')
            if msg:
                removeword.widgets[1].delete(0, tk.END)
                window.focus()
                removeword.widgets[1].focus()
        else:
            removeword.widgets[1].selection_range(0, tk.END)
            window.focus()
            removeword.widgets[1].focus()

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
