#imports
import tkinter as tk, datetime as dt, random
from tkinter import messagebox

#vars
name = ''
words = set() #words
wpm = [] #words per minute
accuracy = [] #accuracy

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
        self.label = tk.Label(window, text = text, bg = '#00ffff', fg = '#000000', font = ('charter', 60, 'italic'))
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
    name = tk.Label(window, text = 'Name: ', bg = '#00ffff', fg = '#000000', font = ('charter', 20))
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
                with open(f'./wpms/{name}_wpms.txt', 'r') as wpms:
                    for i in wpms:
                        wpm.append(float(i.strip('\n')))
            except:
                pass
            try:
                with open(f'./accuracys/{name}_accuracys.txt', 'r') as accuracys:
                    for i in accuracys:
                        accuracy.append(float(i.strip('\n')))
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
        if len(wpm) >= 10:
            wpm_label = tk.Label(window, text = f'Total average WPM: {sum(wpm) / len(wpm)} | Last 10 types average WPM: {sum(wpm[-10:]) / 10} | Last type WPM: {wpm[-1]}',  bg = '#00ffff', fg = '#000000', font = ('charter', 10))
            accuracy_label = tk.Label(window, text = f'Total average accuracy: {sum(accuracy) / len(accuracy)}% | Last 10 types average accuracy: {sum(accuracy[-10:]) / 10}% | Last type accuracy: {accuracy[-1]}%',  bg = '#00ffff', fg = '#000000', font = ('charter', 10))
        else:
            wpm_label = tk.Label(window, text = f'Total average WPM: {sum(wpm) / len(wpm)} | Last 10 types average WPM: {sum(wpm[-10:]) / len(wpm)} | Last type WPM: {wpm[-1]}',  bg = '#00ffff', fg = '#000000', font = ('charter', 10))
            accuracy_label = tk.Label(window, text = f'Total average accuracy: {sum(accuracy) / len(accuracy)}% | Last 10 types average accuracy: {sum(accuracy[-10:]) / len(accuracy)}% | Last type accuracy: {accuracy[-1]}%',  bg = '#00ffff', fg = '#000000', font = ('charter', 10))
    else:
        wpm_label = tk.Label(window, text = 'Total average WPM: N/A | Last 10 types average WPM: N/A | Last type WPM: N/A', bg = '#00ffff', fg = '#000000', font = ('charter', 10))
        accuracy_label = tk.Label(window, text = 'Total average accuracy: N/A | Last 10 types average accuracy: N/A | Last type accuracy: N/A', bg = '#00ffff', fg = '#000000', font = ('charter', 10))
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
    amount = tk.Scale(window, from_ = 20, to = 100, orient = tk.HORIZONTAL, length = 120, bg = '#00ffff')
    amount.place(x = 400, y = 375, anchor = tk.CENTER)
    mode = tk.OptionMenu(window, mode_var, 'Normal', 'Sudden Death')
    mode.place(x = 525, y = 255, anchor = tk.CENTER)
    start = tk.Button(window, text = 'Start Typing', height = 3, width = 10, fg = '#000000', font = ('charter', 15), command = lambda: pre_typing())
    start.place(x = 400, y = 475, anchor = tk.CENTER)
    words_check = tk.Checkbutton(window, text = 'Words', variable = words_var, bg = '#00ffff')
    words_check.place(x = 200, y = 255, anchor = tk.CENTER)
    numbers_check = tk.Checkbutton(window, text = 'Numbers', variable = numbers_var, bg = '#00ffff')
    numbers_check.place(x = 300, y = 255, anchor = tk.CENTER)
    symbols_check = tk.Checkbutton(window, text = 'Symbols', variable = symbols_var, bg = '#00ffff')
    symbols_check.place(x = 400, y = 255, anchor = tk.CENTER)
    style = tk.OptionMenu(window, style_var, 'Paragraph', 'Quick Reaction')
    style.place(x = 675, y = 255, anchor = tk.CENTER)
    one_word_entry = tk.Entry(window)
    one_word_entry.place(x = 400, y = 325, anchor = tk.CENTER)
    one_word_label = tk.Label(window, text = 'One Word (Optional):', bg = '#00ffff', fg = '#000000', font = ('charter', 15))
    one_word_label.place(x = 225, y = 325, anchor = tk.CENTER)
    #defining typesettings widgets and settings
    typesettings.widgets += [amount, mode, start, words_check, numbers_check, symbols_check, style, one_word_entry, one_word_label]
    typesettings.settings += [mode_var, words_var, numbers_var, symbols_var, style_var]

##pre typing
def pre_typing():
    #globals
    global typesettings, words
    sd = False
    settings = [i.get() for i in typesettings.settings]
    word_amount = typesettings.widgets[2].get()
    if settings[1] == 0 and settings[2] == 0 and settings[3] == 0:
        msg = messagebox.showinfo(title = 'You can\'t type anything!', message = 'Check at least one of the boxes to start typing!')
        if msg:
            window.focus_force()
    elif settings[1] == 1 and words == set():
        msg = messagebox.showinfo(title = 'Add words!', message = 'You need to add words!')
        if msg:
            window.focus_force()
    else:
        words_to_type = generate_words(word_amount, settings, typesettings.widgets[9].get())
        typesettings.clear()
        if settings[0] == 'Sudden Death':
            sd = True
        if settings[4] == 'Paragraph':
            wtt_string = ''
            for i in words_to_type:
                wtt_string += i
            typing(words_to_type, sd, 'Paragraph', 0, set(), dt.datetime.now(), paragraph = wtt_string)
        elif settings[4] == 'Quick Reaction':
            typing(words_to_type, sd, 'Quick Reaction', 0, set(), dt.datetime.now())

##typing page
def typing(wtt, sd, style, count, wrong, start_time, **kwargs): #TODO MAKE A FORMULA TO CREATE WORDS
    #globals
    global typing_page, name, wpm, accuracy
    key_clicked = kwargs.get('key_clicked', None)
    paragraph = kwargs.get('paragraph', None)
    try:
        typed = typing_page.widgets[1].get()
    except:
        typing_page = Page()
        typed = ''
        if style == 'Paragraph':
            words_to_type = tk.Label(window, text = paragraph, font = ('charter', 15), bg = '#ffffff', fg = '#000000', wraplength = 700, justify = tk.LEFT)
            words_to_type.place(x = 50, y = 100, anchor = tk.NW)
        elif style == 'Quick Reaction':
            words_to_type = tk.Label(window, text = wtt[count], font = ('charter', 60), bg = '#ffffff', fg = '#000000')
            words_to_type.place(x = 400, y = 250, anchor = tk.CENTER)
        typing_page.widgets.append(words_to_type)
    correct = True
    for i in range(len(typed)):
        if typed[i] != wtt[count][i]:
            correct = False
            break
    if correct:
        try:
            typing_page.widgets[1].config(bg = '#00ff00')
            typing_page.widgets[1].focus()
        except:
            inpt = tk.Entry(window)
            inpt.place(x = 400, y = 450, anchor = tk.CENTER)
            inpt.focus()
            typing_page.widgets.append(inpt)
        if key_clicked == 'space':
            typing_page.widgets[1].delete(0, tk.END)
            if count == len(wtt) - 1:
                msg = messagebox.askyesno(title = 'Well done! Would you like to join our clan?', message = f'Congrats!\nYou\'ve finised typing!\n\nHere are the results:\n{typing_page.widgets[3]["text"]}\n{typing_page.widgets[4]["text"]}\n\nWould you like to type again?')
                if msg or not msg:
                    with open(f'./wpms/{name}_wpms.txt', 'a') as wpm_file:
                        wpm_file.write(f'{typing_page.widgets[3]["text"]}\n'[5:])
                    with open(f'./accuracys/{name}_accuracys.txt', 'a') as accuracy_file:
                        accuracy_file.write(f'{typing_page.widgets[4]["text"]}'[10:-1] + '\n')
                    wpm.append(float(typing_page.widgets[3]['text'][5:]))
                    accuracy.append(float(typing_page.widgets[4]['text'][10:-1]))
                    typing_page.clear()
                    if msg:
                        window.focus_force()
                        typing_settings()
                    else:
                        window.focus_force()
                        home_page()
            else:
                count += 1
                if style == 'Quick Reaction':
                    typing_page.widgets[0]['text'] = wtt[count]
                typing_page.widgets[3]['text'] = f'WPM: {60 * count / (dt.datetime.now() - start_time).total_seconds()}'
    else:
        try:
            typing_page.widgets[1].config(bg = '#ff0000')
            typing_page.widgets[1].focus()
        except:
            inpt = tk.Entry(window)
            inpt.place(x = 400, y = 450, anchor = tk.CENTER)
            inpt.focus()
            typing_page.widgets.append(inpt)
        wrong.add(count)
    if count != len(wtt) - 1:
        for i in 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ,.!?;:\'"':
            binding_key = f'<{i}>'
            if binding_key not in typing_page.binds:
                typing_page.binds.append(binding_key)
            window.bind(binding_key, lambda event: typing(wtt, sd, style, count, wrong, start_time))
        for i in range(10):
            binding_key = f'<Key-{str(i)}>'
            if binding_key not in typing_page.binds:
                typing_page.binds.append(binding_key)
            window.bind(binding_key, lambda event: typing(wtt, sd, style, count, wrong, start_time))
        for i in ['BackSpace', 'Delete']:
            binding_key = f'<{i}>'
            if binding_key not in typing_page.binds:
                typing_page.binds.append(binding_key)
            window.bind(binding_key, lambda event: typing(wtt, sd, style, count, wrong, start_time))
        window.bind(f'<space>', lambda event: typing(wtt, sd, style, count, wrong, start_time, key_clicked = 'space'))
        typing_page.binds.append('<space>')
    rage_quit = BackButton(typing_page, home_page)
    if len(typing_page.widgets) == 3:
        current_wpm = tk.Label(window, text = 'WPM: 0', bg = '#00ffff', fg = '#000000', font = ('charter', 15))
        current_wpm.place(x = 800, y = 0, anchor = tk.NE)
        current_accuracy = tk.Label(window, text = 'Accuracy: 100%', bg = '#00ffff', fg = '#000000', font = ('charter', 15))
        current_accuracy.place(x = 800, y = 25, anchor = tk.NE)
        typing_page.widgets += [current_wpm, current_accuracy]
    try:
        typing_page.widgets[4]['text'] = f'Accuracy: {(count + 1 - len(wrong)) / (count + 1) * 100}%'
    except:
        pass

##generating words
def generate_words(amount, settings, one_word):
    #globals
    global words
    if one_word == '':
        one_word = words
    else:
        one_word = {one_word}
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
            for k in range(random.randint(1, 10)):
                word += symbols[random.randint(0, 9)]
            words_to_type.append(word + ' ')
    elif nums and not symbols and not is_word:
        for i in range(amount):
            word = ''
            for k in range(random.randint(1, 10)):
                word += str(random.randint(0, 10))
            words_to_type.append(word + ' ')
    else:
        need_cap = True
        is_symbol = False
        for i in range(amount):
            word = ''
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
                    word_to_add = list(one_word)[random.randint(0, len(one_word) - 1)]
                    if need_cap:
                        word_to_add = word_to_add[0].upper() + word_to_add[1:]
                        need_cap = False
                    word += word_to_add
            elif is_word:
                word_to_add = list(one_word)[random.randint(0, len(one_word) - 1)]
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
                    if i == amount - 1:
                        if is_symbol == ')' or word[-1] == ',' or word[-1] == ';' or word[-1] == ':':
                            word = word[:-1]
                    if word[-1] == '!' or word[-1] == '?' or word[-1] == '.':
                        need_cap = True
                elif i == amount - 1 and is_symbol != ')':
                    word += '.'
            if is_symbol:
                if i == amount - 1:
                    word += is_symbol
                elif word[-1] != ',' and word[-1] != ';' and word[-1] != ':':
                    if random.randint(1, 3) == 1:
                        word += is_symbol
                        is_symbol = False
            if i == amount - 1 and symbols:
                if '!' not in word and '.' not in word and '?' not in word:
                    word += '.'
                words_to_type.append(word)
            else:
                words_to_type.append(word + ' ')
    return words_to_type

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
    add_instructions = tk.Label(window, text = 'Type the word you\nwant to add here:', bg = '#00ffff', fg = '#000000', font = ('charter', 40))
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
    elif word == '':
        msg = messagebox.showinfo(title = 'Why you add nothing?', message = 'You cannot add "" to your words')
        if msg:
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
    remove_instructions = tk.Label(window, text = 'Type the word you\nwant to remove here:', bg = '#00ffff', fg = '#000000', font = ('charter', 40))
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
    window.config(bg = '#00ffff')
    #call login or signup func
    login_or_signup()
    #mainloop
    window.mainloop()
