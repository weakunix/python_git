# CONSOLE COWCULATOR VERSION INFO AND UPDATES

## DEPENDENCIES
* sympy (for algebra)

## VERSION 1.0
### First official working version of cowculator!
This cowculator uses the shunting yard algorithm to convert an expression into a reverse polish expression.
Then it spits out an answer.

#### Working functions:
* Basic operators
    * \+
    * \-
    * \*
    * /
    * ^ or **
    * //
    * ()
* gcd
* lcm
* max
* min

#### Functions
Functions command not working cause I am too lazy to code it.

#### Modes
Modes just shows your current mode and all modes.

#### Switch
Switch doesn't do anything cause I only coded arithmetic mode right now

#### Exit
Exit works cause it's just an exit.

#### What's this? A hidden function?
And of course for those people who actually read the readme, I will include a hidden function!
Of course it's the hidden airplane game (duh it's in every single cowculator version (actually I'm wrong because the first few versions of this cowculator won't cause I haven't coded it yet whoops)).
 
Type
```
hidden_airplane_game.launch()
```
Caps or not caps it doesn't matter.

### Things coming in version 1.1:
#### New functions:
* √ (square root)
* ! (factorial)
* !! (double factorial)
* root(x, y) (basically y to the root x (i.e. if y was 8 and x was 3 then it would be cube root y))
* floor(x) (for those people who don't know // is floor)
* ceiling(x) (celing (aka floor(x) + 1 when x is not an integer))
This is 100% coming out in version 1.1 of the Console Cowculator.

#### Ans:
I may add an ans thing which is the following

Say your previous equation you typed in was 2 + 2
The output is 4
Instead of typing 4 * 2, you could just do ans * 2

Also I want to do something where you can do ans2 * 2 which would give you the second to last answer
In the previous example your answers would be [4, 8] so ans would be 8 and ans2 would be 4

I can't guarentee this will be in the version 1.1 of the Console Cowculator.

#### Airplane Game:
I will make a new file and start working on the airplane game.
This time your progress actually saves!

I can't guarentee this will be in the version 1.1 of the Console Cowculator.

## VERSION 1.1
### What changed?
Nothing really.
All I did was fix some not big deal bugs and add new functions.

#### New funtions:
Well it's just the functions listed above in "Things coming in version 1.1" but whatever here it is again:
* √ (square root)
* ! (factorial)
* !! (double factorial)
* root(x, y) (y ** (1 / x))
* floor(x) (for those people who don't know // is floor)
* ceiling(x) (celing (aka floor(x) + 1 when x is not an integer))
(Totally didn't copy and paste that)

#### Ans:
This is added!

Everytime you get an answer it will be added to your answers list.
You can access it with the following syntax:
```
ans(x, y)
```
where x and y are optional parameters.
x and y will be defaulted to 1.
x is which answer you want (i.e. if your answer list is [1, 2, 3] ans(1) is 3 ans(2) is 2 ans(3) is 1).
y is the index of your answer.
This is only used when you have a multiple number solution (i.e. prime factor 6 = 2, 3 so your answer would be [2, 3]. if you set y to 1 it would be 2, if you set y to 2 it would be 3).

#### Bug fixes:
Before if you typed something like this:
```
exit6
```
The error would be:
```
Error: unrecognized token 'exit'
```
Now the error would be:
```
Error: unrecognized token 'exit6'
```
So you don't get confused.
Dummies be like: "But you said exit is to exit the program."
They don't notice that exit6 is not going to exit the program. 
This is what I meant by not big deal bug fixes.
Oh well.

#### Airplane Game:
Nope, sorry this isn't out yet.
I don't see this coming out anytime soon because this is really just a few if statements which is quite boring to code.
It may be coded later.

### Things coming in version 1.2:
#### New functions for arithmetic mode:
* prime_factorization(x) / pf(x) (prime factorization)
* mean(\*args) (mean of all arguments)
* median(\*args) (median of all arguments)
* mode(\*args) (mode of all arguments)
* Maybe other things that I think of later

This is 100% coming out in version 1.2 of the Console Cowculator.

#### Algebra mode:
Yep this is coming out next.
I think how it works is the user inputs x amount of equations seperated by something (maybe | or [] I have no idea) and it takes each equation and does subsitution to get the values of all variables.
This is 100% coming out in version 1.2 of the Console Cowculator.

#### Airplane game:
I'll just continue putting this here.
I have no idea when I'll code this simple and trivial console game.
I can't guarentee this will be in the version 1.2 of the Console Cowculator.
