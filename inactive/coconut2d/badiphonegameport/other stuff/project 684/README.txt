ruoyu. this is your thing. u must do something about pj684 in which u can make an algorithem that works with match3 games

here is what i am thinking

array = [

[][][][][]
[][][][][]
[][][][][]
[][][][][]
[][][][][]

]
randomly generaate the array above so each cell contains numbers 0-3 (we are gonna have 4 different types)

so, the result would be:
>>>
[1][2][3][0][1]
[3][1][0][1][3]
[0][3][1][0][0]
[3][0][2][1][2]
[2][1][3][1][3]
but here arises a problem: it is unsolvable. so we need another algorithem that makes it solveable by 
replacing one of the things with something that makes it solvable. <here> is the one taken out and replaced

so, the result would be:
>>>
[1][2][3][0][1]
[3][1][0][1][3]
[0][3][1][0][0]
[3][0][2]<2>[2]
[2][1][3][1][3]

and the algorithem would also have to be able to generate new rows that also can be tapped in 3
(here) is the one generated 

so, the result would be:
>>>
[1][2][3](0)[1]
[3][1][0][0][3]
[0][3][1][1][0]
[3][0][2][0][2]
[2][1][3][1][3]

treat this like an euler project

also after that it would need to regenerate 3. but you need to do it so that it could be tapped again. else the game would just end
in /here/ is the things generated
btw, in /n/ is ones that can be random generated because there was already one that would work

so, the result would be:
>>>
[1][2]/n//n/[1]
[3][1][3]/1/[3]
[0][3][1][1][0]
[3][0][2][0][2]
[2][1][3][1][3]

anyways you get the point.
so. get to working

anyways the result would be me stitching each of the array element to an image
0 could be a hexigon
1 could be a star
2 could be a circle
3 could be a square

anyways don't worry too much about the front end. I'll work with that