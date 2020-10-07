# HWorker

HWorker/HWTracker (we haven't decided yet) is an app used to manage your schoolwork. It doesn't matter if you are in Colledge or in Elementary School. You'll still have one thing in common; homework! With our app, you can track all your assignments with push notifications before they are due. 

## Usage

tba

## Downloads

Download the app version here on [our website]()/[AppStore](). 

## Contributor:
### Install:

1. Make sure you have Python 3.8.5 installed! If not, you can go [here](https://www.python.org/downloads/).

2. To run with source code and modifiable files, clone this repository using console command:

    ```bash
    git clone https://github.com/weakunix/python_git.git
    ```

3. Then, pip install PyQt5 (if you haven't done so already)

    ```bash
    pip3 install PyQt5
    ```

4. Use your file browser to locate where 'main.py' is (it should be in the first folder) 

![MAC](https://raw.githubusercontent.com/weakunix/python_git/master/live_events/hw/icons/support/macHelp.PNG)

![WINDOWS](https://raw.githubusercontent.com/weakunix/python_git/master/live_events/hw/icons/support/windowshelp.PNG)

5. Right click on 'main.py' then RUN with Python 3.8.5. or open with your favorite code editor (notepad for the win!)

CMD/Terminal:

4. You want to 'cd' to main.py's dir (./HWTracker)

    ```bash
    cd ./HWTracker/
    ```

5. Then run it with 'python3'

    ```bash
    python3 main.py
    ```
    
### File Modifications:

#### Modifying Data Files:

**NOTICE**
**Do not modify policy.txt!!! THAT IS LEGAL STUFF!!!**

**Do not modify Settings.json UNLESS YOU KNOW WHAT YOU'RE DOING ENTIRELY!!!! IF YOUR FILE BREAKS!!! RECLONE**

* modifying classes.json
** Layout: 
> "class name":["timestarts-timeends (24 hour)", "block (A-z/1-10)", "classroom #", "teacher name", "class info and about"]
> "English":["13:50-14:05", "B", "LC9", "Garrow", "journals"]
* modifying todos.json
> "class name":["%difficulty (0-10)", "%completion (0-100)", "due in (1d/w/m/y)", "is repeating? if so cycle listed in different thing", "homework description"]
> "Computer Science":["6", "50%", "1d", "True", "finish java stuff"]

### Pull Requests:

must be formatted like this:

## License
[MIT](https://choosealicense.com/licenses/mit/)
This project is completely open source. You are free to reuse anything as you wish. 

Founded by Mootbing and MrMoooo.
