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
        self.settings = []
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
    def __init__(self, text, clear, **kwargs):
        #kwargs
        self.y = kwargs.get('y', 175)
        #create title
        self.label = tk.Label(window, text = text, bg = '#00FFFF', fg = '#000000', font = ('charter', 60, 'italic'))
        self.label.place(x = 400, y = self.y, anchor = tk.CENTER)
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
                        words.add(i.strip('\n'))
            except:
                pass
            msg = messagebox.showinfo(title = 'Stats recovered correctly?', message = 'Login Successful')
            if msg:
                loginsignup.clear()
                window.focus_force()
                home_page()
        else:
            msg = messagebox.showinfo(title = 'You spelling right?', message = 'Account not found!')
            if msg:
                loginsignup.widgets[3].selection_range(0, tk.END)
                window.focus_force()
                loginsignup.widgets[3].focus()
    else:
        if not is_account:
            if ' ' not in name:
                with open('names.txt', 'a') as names:
                    names.write(f'{name}\n')
                msg = messagebox.showinfo(title = 'Don\'t forget your account!', message = 'Signup Sucessful!')
                if msg:
                    loginsignup.clear()
                    window.focus_force()
                    home_page()
            else:
                msg = messagebox.showinfo(title = 'Why spaces huh?', message = 'Your name cannot contain spaces!')
                if msg:
                    loginsignup.widgets[3].selection_range(0, tk.END)
                    window.focus_force()
                    loginsignup.widgets[3].focus()
        else:
            msg = messagebox.showinfo(title = 'Bummer. Who stole your name?', message = 'This name has already been taken!')
            if msg:
                loginsignup.widgets[3].selection_range(0, tk.END)
                window.focus_force()
                loginsignup.widgets[3].focus()

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
    #globals
    global typesettings
    #Page class instance typesettings page
    typesettings = Page()
    #window title
    window.title('Typing Settings')
    #checkbox and option menu variables
    mode_var = tk.StringVar()
    mode_var.set('Normal')
    words_var = tk.IntVar()
    numbers_var = tk.IntVar()
    symbols_var = tk.IntVar()
    style_var = tk.StringVar()
    style_var.set('Paragraph')
    #making widgets
    settings_title = Title('Typing Settings', typesettings, y = 125)
    back_to_home = BackButton(typesettings, home_page)
    amount = tk.Scale(window, from_ = 20, to = 200, orient = tk.HORIZONTAL, length = 180, bg = '#00FFFF')
    amount.place(x = 400, y = 375, anchor = tk.CENTER)
    mode = tk.OptionMenu(window, mode_var, 'Normal', 'Sudden Death')
    mode.place(x = 300, y = 308, anchor = tk.CENTER)
    start = tk.Button(window, text = 'Start Typing', height = 3, width = 10, fg = '#000000', font = ('charter', 15), command = lambda: typing())
    start.place(x = 400, y = 475, anchor = tk.CENTER)
    words_check = tk.Checkbutton(window, text = 'Words', variable = words_var, bg = '#00FFFF')
    words_check.place(x = 300, y = 250, anchor = tk.CENTER)
    numbers_check = tk.Checkbutton(window, text = 'Numbers', variable = numbers_var, bg = '#00FFFF')
    numbers_check.place(x = 400, y = 250, anchor = tk.CENTER)
    symbols_check = tk.Checkbutton(window, text = 'Symbols', variable = symbols_var, bg = '#00FFFF')
    symbols_check.place(x = 500, y = 250, anchor = tk.CENTER)
    style = tk.OptionMenu(window, style_var, 'Paragraph', 'Quick Reaction')
    style.place(x = 500, y = 308, anchor = tk.CENTER)
    #defining typesettings widgets and settings
    typesettings.widgets += [amount, mode, start, words_check, numbers_check, symbols_check, style]
    typesettings.settings += [mode_var, words_var, numbers_var, symbols_var, style_var]

##typing
def typing():
    #globals
    global typesettings, words
    settings = [i.get() for i in typesettings.settings]
    word_amount = typesettings.widgets[2].get()
    if settings[1] == 0 and settings[2] == 0 and settings[3] == 0:
        msg = messagebox.showinfo(title = 'You can\'t type anything!', message = 'Check at least one of the boxes to start typing!')
        if msg:
            window.focus_force()
    elif settings[1] == 1 and words == []:
        msg = messagebox.showinfo(title = 'Add words!', message = 'You need to add words!')
        import pdb;pdb.set_trace()
        if msg:
            window.focus_force()
    else:
        word_to_type = generate_words(word_amount, settings)
        typesettings.clear()

##generating words
def generate_words(amount, settings):
    #globals
    global words
    words_to_type = []
    if settings[3] == 1:
        symbols = ['\'', '"', '(', ')', '.', ',', '!', '?', ':', ';']
    else:
        symbols = False
    if settings[2] == 1:
        nums = True
    else:
        nums = False
    if settings[1] == 1:
        is_word = True
    else:
        is_word = False
    if symbols and not nums and not is_word:
        for i in range(amount):
            word = ''
            for k in range(random.randint(1, 9)):
                word += symbols[random.randint(0, 10)]
            words_to_type.append(word + ' ')
    if nums and not symbols and not is_word:
        for i in range(amount):
            word = ''
            for k in range(random.randint(1, 10)):
                word += str(random.randint(0, 10))
            words_to_type.append(word + ' ')
    else:
        need_cap = True
        for i in range(amount):
            word = ''
            is_symbol = False
            #starting symbol
            if symbols and not is_symbol:
                if random.randint(1, 10) == 1:
                    is_symbol = symbols[random.randint(0, 2)]
                    word += is_symbol
                    if is_symbol == '(':
                        is_symbol = ')'
                    else:
                        need_cap = True
            #number or word
            if is_word and nums:
                if random.randint(1, 6) == 1:
                    for k in range(random.randint(1, 10)):
                        word += str(random.randint(0, 10))
                else:
                    word_to_add = list(words)[random.randint(0, len(words) - 1)]
                    if need_cap:
                        word_to_add = word_to_add[0].upper() + word_to_add[1:]
                        need_cap = False
                    word += word_to_add
            elif is_word:
                word_to_add = list(words)[random.randint(0, len(words) - 1)]
                if need_cap:
                    word_to_add = word_to_add[0].upper() + word_to_add[1:]
                    need_cap = False
                word += word_to_add
            else:
                for k in range(random.randint(1, 10)):
                    word += str(random.randint(0, 10))
            if symbols:
                if random.randint(1, 7) == 1:
                    word += symbols[random.randint(4, 9)]
                    if word[-1] == '!' or word[-1] == '?' or word[-1] == '.':
                        need_cap = True
            if is_symbol:
                if i == amount - 1:
                    word += is_symbol
                else:
                    if random.randint(1, 3) == 1:
                        word += is_symbol
                        is_symbol = False
            words_to_type.append(word + ' ')
    for i in words_to_type:
        print(i, end = '')
    print('\n')

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
            window.focus_force()
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
                window.focus_force()
                addword.widgets[1].focus()
        else:
            addword.widgets[1].selection_range(0, tk.END)
            window.focus_force()
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
            window.focus_force()
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
                window.focus_force()
                removeword.widgets[1].focus()
        else:
            removeword.widgets[1].selection_range(0, tk.END)
            window.focus_force()
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
