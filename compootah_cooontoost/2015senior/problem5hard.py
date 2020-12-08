a = 2
b = 1
c = 1
d = 1
assyemilyblee = 0

while True:
    assyemilyblee = b #load b
    assyemilyblee = assyemilyblee * a #multi a
    b = assyemilyblee #store b
    assyemilyblee = c
    assyemilyblee += b
    c = assyemilyblee
    assyemilyblee = d
    assyemilyblee += 1
    d = assyemilyblee
    assyemilyblee = c
    assyemilyblee -= 100
    if assyemilyblee >= 0:
        break 

print(d)
