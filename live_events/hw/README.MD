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

![MAC](https://i.ibb.co/44X1zzW/Screen-Shot-2020-10-06-at-10-39-48-PM.png)

![WINDOWS](https://i.ibb.co/nw03r1J/Capture.png)

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

**DISCLAIMER WE ARE NO WAY RESPONSIBLE IF YOU BREAK YOUR APPLICATION/LOSE DATA, YOU ARE RESPONSABLE FOR ALL OUTCOMES OF TAMPERING WITH FILES**

#### Modifying Handlers:

They handle all the operations done when making a change in settings or making new homework/classes
the code isn't really functional on its own. it is imported from main.py in the other folders.

##### UI HANDLER
What is it?
It handles everything about UI that is dynamic. (changed when the app is running)

Examples
* Add New button is pressed and UI handler adds a todo/class into the QScrollArea
* The topbar widget is clicked, changing the appearance from dark mode to light mode (ewww)

**If you want to change the appearance of an item add a new feature inside the QScrollArea or (display area for classes/hw) code a change in UIhandler and file a PR**

##### FILE HANDLER
What is it?
It handles everything about files.

Examples
* Add New button is pressed and File handler adds the new classes/todo.json to include the new data (yes it is also stored in the database but just in case no wifi)
* The topbar widget is clicked, changing the default always signin setting to False (writes into settings.json)

**If you need to change how data gets written/anything about local data, filehandler's where you should look**

#### Modifying Data Files:

**DO NOT MODIFY POLICY.TXT THAT IS LEGAL STUFF!!!**

**Do not modify Settings.json UNLESS YOU KNOW WHAT YOU'RE DOING ENTIRELY!!!! MODIFY AT YOUR OWN RISK**

**If adding classes/todos in the app doesn't work, you can manually add a new line of class/todos and it will work (don't forget a comma in the previous line!!)**

##### Modifying classes.json 
![classes.json image](https://i.ibb.co/gRMtm62/Screen-Shot-2020-10-07-at-10-57-14-AM.png)

Format:

```json
"class name":["timestarts-timeends (24 hour)", "block (A-z/1-10)", "classroom #", "teacher name", "class info and about"]
```

##### Modifying todos.json
![todos.json image](https://i.ibb.co/4mGGhL4/Screen-Shot-2020-10-07-at-10-57-50-AM.png)

Format:

```json
"class name":["%difficulty (0-10)", "%completion (0-100)", "due in (1d/w/m/y)", "is repeating? if so cycle listed in different thing", "homework description"]
```

#### Modifying Icons

**For whatever reason, if you want custom icons instead of the ones I drew, you can modify them (I won't take it personally). But keep a few things in mind:**

Socail icons:
50x50 downscaled to 35x35

![socials template](https://i.ibb.co/5WN31jq/rsz-1pixil-frame-0-2.png)

Pencil Icon:
193x192 upscaled to 339x326

![icon template](https://i.ibb.co/Kj853c3/testi-1-1.png)

### Pull Requests:

must be formatted like this:

## License
[MIT](https://choosealicense.com/licenses/mit/)
This project is completely open source. You are free to reuse anything as you wish. 

Founded by Mootbing and MrMoooo.

Readme made with GITHUB's readme editor and https://guides.github.com/features/mastering-markdown/

Images in this file hosted with https://imgbb.com
