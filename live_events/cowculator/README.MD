# THE COWCULATOR (console version)

## Dependencies
* sympy (for algebra)
* collections

## How it Works
This cowculator uses the shunting yard algorithm to convert an expression into a reverse polish expression.
Then it spits out an answer.

## Working Arithmetic Functions:
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
* √ (square root)
* ! (factorial)
* !! (double factorial)
* root(x, y) (basically y to the root x (i.e. if y was 8 and x was 3 then it would be cube root y))
* floor(x) (for those people who don't know // is floor)
* ceiling(x) (celing (aka floor(x) + 1 when x is not an integer))

## Ans:
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

## Functions
Functions command not working cause I am too lazy to code it.

## Modes
Modes just shows your current mode and all modes.

## Switch
Switch doesn't do anything cause I only coded arithmetic mode right now

## Exit
Exit works cause it's just an exit.

## What's this? A hidden function?
And of course for those people who actually read the readme, I will include a hidden function!
Of course it's the hidden airplane game (duh it's in every single cowculator version (actually I'm wrong because the first few versions of this cowculator won't cause I haven't coded it yet whoops)).
 
Type
```
hidden_airplane_game.launch()
```
Caps or not caps it doesn't matter.

Forgot to mention I haven't added it yet XD

