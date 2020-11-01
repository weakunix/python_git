#imports
from modes import algebra, arithmetic

#vars
modes = ['algebra', 'arithmetic'] #modes
current_mode = 1 #current mode
mode_module = [algebra, arithmetic] #modules for each mode

#user def functions
def eval_input():
    global current_mode, modes, mode_module
    inpt = input('\n' + '\033[1;36;1m=' * 50 + f'\033[1;32;1m\n\nCommands:\n\n\033[1;33;1mFunctions: List functions of {modes[current_mode]} mode\n\033[1;34;1mModes: Shows your current mode and all modes of the Cowculator\n\033[1;36;1mSwitch [mode]: Switch to selected mode\n\033[1;35;1mClear: Clear all answers\n\033[1;37;1mAnswers: List of all answers\n\033[1;31;1mExit: Exit program\n\n\033[0mTo calculate just type in a valid equation:\n').strip(' ')
    if inpt.lower() == 'exit':
        inpt = input('\n' + '\033[1;36;1m=' * 50 + '\033[1;31;1m\n\nAre you sure you want to exit?\n\033[0m')
        try:
            inpt = inpt[0].lower()
        except:
            inpt = None
        if inpt == 'y':
            with open('./answers.txt', 'w') as answers:
                answers.write('')
            raise SystemExit('\033[0m')
    elif 'switch' in inpt.lower():
        switchable = True
        try:
            inpt = inpt.lower().split(' ')[1]
            if inpt in modes:
                current_mode = modes.index(inpt)
            else:
                print(f'\033[1;31;1mError: mode {inpt} not found')
                switchable = False
        except:
            print(f'\033[1;31;1mError: unspecified mode to switch to')
            switchable = False
        if switchable:
            print('\n' + '\033[1;36;1m=' * 50 + f'\n\nSwitched to {modes[current_mode]} mode')
    elif inpt.lower() == 'functions':
        try:
            with open(f'./tutorials/{modes[current_mode]}.txt', 'r') as function_file:
                for line in function_file:
                    line = line.strip('\n')
                    print(f'\033[1;33;1m{line}')
        except:
            print(f'\033[1;33;1mToo lazy, haven\'t written the list of functions yet')
    elif inpt.lower() == 'modes':
        print('\n' + '\033[1;36;1m=' * 50 + f'\033[1;34;1m\n\nCurrent mode: {modes[current_mode]}\n\nAll modes:')
        for i in range(len(modes)):
            print(modes[i][0].upper() + modes[i][1:])
    elif inpt.lower() == 'clear':
        inpt = input('\n' + '\033[1;36;1m=' * 50 + '\n\n\033[1;35;1mAre you sure you want to clear all of your answers?\033[0m\n')
        try:
            inpt = inpt.lower()[0]
        except:
            inpt = None
        if inpt == 'y':
            with open('./answers.txt', 'w') as answers:
                answers.write('')
            print('\n' + '\033[1;36;1m=' * 50 + '\n\n\033[1;35;1mAll answers cleared')
    elif inpt.lower() == 'answers':
        print('\n' + '\033[1;36;1m=' * 50 + '\n\033[1;37;1m')
        are_answers = False
        with open('./answers.txt', 'r') as answers:
            for line in answers:
                are_answers = True
                line = line.strip('\n')
                for i in line:
                    if i == ' ':
                        print(', ', end = '')
                    else:
                        print(i, end = '')
                print('')
        if not are_answers:
            print('None')
    else:
        answer = mode_module[current_mode].tokenize(inpt)
        if answer != None:
            answer = mode_module[current_mode].shunting(answer)
            if answer != None:
                answer = mode_module[current_mode].eval_rp(answer)
                if answer != None:
                    print(f'\033[1;32;1m{answer}')
                    write_answer = ''
                    if type(answer) == int or type(answer) == float:
                        write_answer = str(answer)
                    else:
                        for k, i in enumerate(answer):
                            write_answer += str(i)
                            if k != len(answer) - 1:
                                write_answer += ' '
                    with open('./answers.txt', 'a') as answers:
                        answers.write(write_answer + '\n')

#main
if __name__ == '__main__':
    with open('./answers.txt', 'w') as answers:
        answers.write('')
    print(f'\033[1;32;1mWelcome to the Cowculator!')
    while True:
        eval_input()
