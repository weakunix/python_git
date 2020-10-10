# CONTRIBUTION TO THE PROJECT
We appreciate your kindness to contribute! Here are some guidelines and tips to get you started!

## File Modifications:

**DISCLAIMER WE ARE NO WAY RESPONSIBLE IF YOU BREAK YOUR APPLICATION/LOSE DATA, YOU ARE RESPONSABLE FOR ALL OUTCOMES OF TAMPERING WITH FILES**

### Modifying Handlers:

#### Modifying newhandler
What is it?
It handles everything about UI that is dynamic. (UI that is changed when the app is running)

like adding classes

![eg. adding classes img](https://i.ibb.co/CW8MMdg/Screen-Shot-2020-10-07-at-12-06-17-PM.png)

Examples
* Add New button is pressed and UI handler adds a todo/class into the QScrollArea
* The topbar widget is clicked, changing the appearance from dark mode to light mode (ewww)

**If you want to change the appearance of an item add a new feature inside the QScrollArea or (display area for classes/hw) code a change in UIhandler and file a PR**

#### Modifying filehandler
What is it?
It handles everything about files.

Examples
* Add New button is pressed and File handler adds the new classes/todo.json to include the new data (yes it is also stored in the database but just in case no wifi)
* The topbar widget is clicked, changing the default always signin setting to False (writes into settings.json)

**If you need to change how data gets written/anything about local data, filehandler's where you should look**

### Modifying Data Files:

**DO NOT MODIFY POLICY.TXT THAT IS LEGAL STUFF!!!**

**Do not modify Settings.json UNLESS YOU KNOW WHAT YOU'RE DOING ENTIRELY!!!! MODIFY AT YOUR OWN RISK**

**If adding classes/todos in the app doesn't work, you can manually add a new line of class/todos and it will work (don't forget a comma in the previous line!!)**

#### Modifying classes.json 
![classes.json image](https://i.ibb.co/gRMtm62/Screen-Shot-2020-10-07-at-10-57-14-AM.png)

Format:

```json
"class name":["timestarts-timeends (24 hour)", "block (A-z/1-10)", "classroom #", "teacher name", "class info and about"]
```

#### Modifying todos.json
![todos.json image](https://i.ibb.co/4mGGhL4/Screen-Shot-2020-10-07-at-10-57-50-AM.png)

Format:

```json
"class name":["%difficulty (0-10)", "%completion (0-100)", "due in (1d/w/m/y)", "is repeating? if so cycle listed in different thing", "homework description"]
```

## Modifying Icons

**For whatever reason, if you want custom icons instead of the ones I drew, you can modify them (I won't take it personally). But keep a few things in mind:**

Socail icons (base template):

![socials template](https://i.ibb.co/5WN31jq/rsz-1pixil-frame-0-2.png)

50x50 downscaled to 35x35

Pencil Icon (base template):

![icon template](https://i.ibb.co/Kj853c3/testi-1-1.png)

193x192 upscaled to 339x326

## Pull Requests:

### must be formatted like this:

<details><summary><b>Show Code Format</b></summary>
    
old code
    
```python
def bot():
    print("hi")
```

new code

```python
#Added a parameter slot
def bot(yes):
    print(str(yes)) #replaced "hi" to yes so it prints whatever is passed through
```

</details>

<details><summary><b>Checklist</b></summary>

- [ ] My code follows the style guidelines of this project
- [ ] I have performed a self-review of my own code
- [ ] I have commented my code, particularly in hard-to-understand areas
- [ ] I have made corresponding changes to the documentation
- [ ] My changes generate no new warnings
- [ ] I have added tests that prove my fix is effective or that my feature works
- [ ] New and existing unit tests pass locally with my changes
- [ ] Any dependent changes have been merged and published in downstream modules
- [ ] I have checked my code and corrected any misspellings

checklist from https://guides.github.com/features/mastering-markdown/

</details>

## License
[MIT License. ](https://choosealicense.com/licenses/mit/)
This project is completely open source. You are free to reuse anything as you wish. 

Founded by Mootbing and MrMoooo.

![Company icon](https://i.ibb.co/rxd0Txc/image0-png.jpg)
