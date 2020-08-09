# Wormy (a Nibbles clone)
# By Al Sweigart al@inventwithpython.com
# http://inventwithpython.com/pygame
# Released under a "Simplified BSD" license
 
import random, pygame, sys
from pygame.locals import *
WINNER = 0
FPS = 10
WINDOWWIDTH = 660 #1280
WINDOWHEIGHT = 600
CELLSIZE = 30
assert WINDOWWIDTH % CELLSIZE == 0, "Window width must be a multiple of cell size."
assert WINDOWHEIGHT % CELLSIZE == 0, "Window height must be a multiple of cell size."
CELLWIDTH = int(WINDOWWIDTH / CELLSIZE)
CELLHEIGHT = int(WINDOWHEIGHT / CELLSIZE)
 
#             R    G    B
WHITE     = (255, 255, 255)
BLACK     = (  0,   0,   0)
RED       = (255,   0,   0)
GREEN     = (  0, 255,   0)
DARKGREEN = (  0, 155,   0)
DARKGRAY  = ( 40,  40,  40)
GOLDENYELLOW = (255, 223, 0)
VENOMGREEN = (158, 242, 130)
BGCOLOR = BLACK
APPLETYPE = ['normal', 'venom']
APPLECOLOR = ['RED','VENOMGREEN']
UP = 'up'
DOWN = 'down'
LEFT = 'left'
RIGHT = 'right'
 
HEAD = 0 # syntactic sugar: index of the worm's head
 
def main():
    global FPSCLOCK, DISPLAYSURF, BASICFONT, WINNER
 
    pygame.init()
    FPSCLOCK = pygame.time.Clock()
    DISPLAYSURF = pygame.display.set_mode((WINDOWWIDTH, WINDOWHEIGHT))
    BASICFONT = pygame.font.Font('freesansbold.ttf', 18)
    pygame.display.set_caption('Wormy')
 
    showStartScreen()
    while True:
        runGame()
        showWINNERscreen(WINNER)
 
 
def runGame():
    global WINNER
    # Set a random start point.
    appletype = 'normal'
    startx = random.randint(5, CELLWIDTH - 6)
    starty = random.randint(5, CELLHEIGHT - 6)
    startx2 = random.randint(5, CELLWIDTH -6)
    starty2 = random.randint(5, CELLHEIGHT - 6)
    wormCoords = [{'x': startx,     'y': starty},
                  {'x': startx - 1, 'y': starty},
                  {'x': startx - 2, 'y': starty}]
    wormCoords2 = [{'x': startx2,   'y': starty2},
                  {'x': startx2 + 1, 'y': starty2},
                  {'x': startx2 + 2, 'y': starty2}]
    direction = RIGHT
    direction2 = LEFT
 
    # Start the apple in a random place.
    apple = getRandomLocation()
 
    while True: # main game loop
        for event in pygame.event.get(): # event handling loop
            if event.type == QUIT:
                terminate()
            elif event.type == KEYDOWN:
                if (event.key == K_LEFT) and direction != RIGHT:
                    direction = LEFT
                elif (event.key == K_a) and direction2 != RIGHT:
                    direction2 = LEFT
                elif (event.key == K_RIGHT) and direction != LEFT:
                    direction = RIGHT
                elif (event.key == K_d) and direction2 != LEFT:
                    direction2 = RIGHT
                elif (event.key == K_UP) and direction != DOWN:
                    direction = UP
                elif (event.key == K_w) and direction2 != DOWN:
                    direction2 = UP
                elif (event.key == K_DOWN) and direction != UP:
                    direction = DOWN
                elif (event.key == K_s) and direction2 != UP:
                    direction2 = DOWN
                elif event.key == K_ESCAPE:
                    terminate()
 
        # check if the worm has hit the edge
        if wormCoords[HEAD]['x'] == -1 or wormCoords[HEAD]['x'] == CELLWIDTH: 
            wormCoords[HEAD]['x'] = wormCoords[HEAD]['x'] %CELLWIDTH
        if wormCoords[HEAD]['y'] == -1 or wormCoords[HEAD]['y'] == CELLHEIGHT:
            wormCoords[HEAD]['y'] = wormCoords[HEAD]['y'] %CELLHEIGHT
        # check if worm2 has hit the edge
        if wormCoords2[HEAD]['x'] == -1 or wormCoords2[HEAD]['x'] == CELLWIDTH: 
            wormCoords2[HEAD]['x'] = wormCoords2[HEAD]['x'] %CELLWIDTH
        if wormCoords2[HEAD]['y'] == -1 or wormCoords2[HEAD]['y'] == CELLHEIGHT:
            wormCoords2[HEAD]['y'] = wormCoords2[HEAD]['y'] %CELLHEIGHT
            #return # game over
         
        #if worm1 hits itself
        for wormBody in wormCoords[1:]:
            if wormBody['x'] == wormCoords[HEAD]['x'] and wormBody['y'] == wormCoords[HEAD]['y']:
                WINNER = 2
                return # game over
        #if worm2 hits itself
        for wormBody in wormCoords2[1:]:
            if wormBody['x'] == wormCoords2[HEAD]['x'] and wormBody['y'] == wormCoords2[HEAD]['y']:
                WINNER = 1
                return # game over
        #if worm1 hits worm2
        for wormBody in wormCoords2[1:]:
            if wormBody['x'] == wormCoords[HEAD]['x'] and wormBody['y'] == wormCoords[HEAD]['y']:
                WINNER = 2
                return # game over
        #if worm2 hits worm1
        for wormBody in wormCoords[1:]:
            if wormBody['x'] == wormCoords2[HEAD]['x'] and wormBody['y'] == wormCoords2[HEAD]['y']:
                WINNER = 1
                return # game over
 
 
        # check if worm has eaten an apple
        if wormCoords[HEAD]['x'] == apple['x'] and wormCoords[HEAD]['y'] == apple['y']:
            # don't remove worm's tail segment
            apple = getRandomLocation() # set a new apple somewhere
            appletype = getRandomAppleType()
        else:
            del wormCoords[-1] # remove worm's tail segment
        # check if worm2 has eaten an apple
        if wormCoords2[HEAD]['x'] == apple['x'] and wormCoords2[HEAD]['y'] == apple['y']:
            # don't remove worm's tail segment
            apple = getRandomLocation()# set a new apple somewhere
            appletype = getRandomAppleType()#set a new apple type
        else:
            del wormCoords2[-1] # remove worm 2's tail segment
        # move the worm by adding a segment in the direction it is moving
        if direction == UP:
            newHead = {'x': wormCoords[HEAD]['x'], 'y': wormCoords[HEAD]['y'] - 1}
        elif direction == DOWN:
            newHead = {'x': wormCoords[HEAD]['x'], 'y': wormCoords[HEAD]['y'] + 1}
        elif direction == LEFT:
            newHead = {'x': wormCoords[HEAD]['x'] - 1, 'y': wormCoords[HEAD]['y']}
        elif direction == RIGHT:
            newHead = {'x': wormCoords[HEAD]['x'] + 1, 'y': wormCoords[HEAD]['y']}
        wormCoords.insert(0, newHead)
        if direction2 == UP:
            newHead2 = {'x': wormCoords2[HEAD]['x'], 'y': wormCoords2[HEAD]['y'] - 1}
        elif direction2 == DOWN:
            newHead2 = {'x': wormCoords2[HEAD]['x'], 'y': wormCoords2[HEAD]['y'] + 1}
        elif direction2 == LEFT:
            newHead2 = {'x': wormCoords2[HEAD]['x'] - 1, 'y': wormCoords2[HEAD]['y']}
        elif direction2 == RIGHT:
            newHead2 = {'x': wormCoords2[HEAD]['x'] + 1, 'y': wormCoords2[HEAD]['y']}
        wormCoords2.insert(0, newHead2)
        DISPLAYSURF.fill(BGCOLOR)
        drawGrid()
        drawWorm(wormCoords, GOLDENYELLOW)
        drawWorm(wormCoords2, GREEN)
        drawApple(apple, appletype)
        drawScore(len(wormCoords) - 3, GOLDENYELLOW, WINDOWWIDTH -120)
        drawScore(len(wormCoords2) - 3, GREEN, 120)
        pygame.display.update()
        FPSCLOCK.tick(FPS)
 
def drawPressKeyMsg():
    pressKeySurf = BASICFONT.render('Press a key to play.', True, DARKGRAY)
    pressKeyRect = pressKeySurf.get_rect()
    pressKeyRect.topleft = (WINDOWWIDTH - 200, WINDOWHEIGHT - 30)
    DISPLAYSURF.blit(pressKeySurf, pressKeyRect)
 
 
def checkForKeyPress():
    if len(pygame.event.get(QUIT)) > 0:
        terminate()
 
    keyUpEvents = pygame.event.get(KEYUP)
    if len(keyUpEvents) == 0:
        return None
    if keyUpEvents[0].key == K_ESCAPE:
        terminate()
    return keyUpEvents[0].key
 
 
def showStartScreen():
    titleFont = pygame.font.Font('freesansbold.ttf', 100)
    titleSurf1 = titleFont.render('Wormy!', True, WHITE, DARKGREEN)
    titleSurf2 = titleFont.render('Wormy!', True, GREEN)
 
    degrees1 = 0
    degrees2 = 0
    while True:
        DISPLAYSURF.fill(BGCOLOR)
        rotatedSurf1 = pygame.transform.rotate(titleSurf1, degrees1)
        rotatedRect1 = rotatedSurf1.get_rect()
        rotatedRect1.center = (WINDOWWIDTH / 2, WINDOWHEIGHT / 2)
        DISPLAYSURF.blit(rotatedSurf1, rotatedRect1)
 
        rotatedSurf2 = pygame.transform.rotate(titleSurf2, degrees2)
        rotatedRect2 = rotatedSurf2.get_rect()
        rotatedRect2.center = (WINDOWWIDTH / 2, WINDOWHEIGHT / 2)
        DISPLAYSURF.blit(rotatedSurf2, rotatedRect2)
 
        drawPressKeyMsg()
 
        if checkForKeyPress():
            pygame.event.get() # clear event queue
            return
        pygame.display.update()
        FPSCLOCK.tick(FPS)
        degrees1 += 3 # rotate by 3 degrees each frame
        degrees2 += 7 # rotate by 7 degrees each frame
 
 
def terminate():
    pygame.quit()
    sys.exit()
 
 
def getRandomLocation():
    return {'x': random.randint(0, CELLWIDTH - 1), 'y': random.randint(0, CELLHEIGHT - 1)}
 
def getRandomAppleType():
    pick = random.randint(1,5)
    if pick == 5:
        return APPLETYPE[1]
    else:
        return APPLETYPE[0]
 
def showGameOverScreen():
    gameOverFont = pygame.font.Font('freesansbold.ttf', 150)
    gameSurf = gameOverFont.render('Game', True, WHITE)
    overSurf = gameOverFont.render('Over', True, WHITE)
    gameRect = gameSurf.get_rect()
    overRect = overSurf.get_rect()
    gameRect.midtop = (WINDOWWIDTH / 2, 10)
    overRect.midtop = (WINDOWWIDTH / 2, gameRect.height + 10 + 25)
 
    DISPLAYSURF.blit(gameSurf, gameRect)
    DISPLAYSURF.blit(overSurf, overRect)
    drawPressKeyMsg()
    pygame.display.update()
    pygame.time.wait(500)
    checkForKeyPress() # clear out any key presses in the event queue
 
    while True:
        if checkForKeyPress():
            pygame.event.get() # clear event queue
            return
 
def showWINNERscreen(WINNER):
    gameOverFont = pygame.font.Font('freesansbold.ttf', 150)
    gameSurf = gameOverFont.render('Winner: ', True, WHITE)
    WINNER = str(WINNER)
    overSurf = gameOverFont.render('Player '+WINNER, True, WHITE)
    gameRect = gameSurf.get_rect()
    overRect = overSurf.get_rect()
    gameRect.midtop = (WINDOWWIDTH / 2, 10)
    overRect.midtop = (WINDOWWIDTH / 2, gameRect.height + 10 + 25)
 
    DISPLAYSURF.blit(gameSurf, gameRect)
    DISPLAYSURF.blit(overSurf, overRect)
    drawPressKeyMsg()
    pygame.display.update()
    pygame.time.wait(500)
    checkForKeyPress() # clear out any key presses in the event queue
 
    while True:
        if checkForKeyPress():
            pygame.event.get() # clear event queue
            return
 
def drawScore(score, color, offset):
    scoreSurf = BASICFONT.render('Score: %s' % (score), True, color)
    scoreRect = scoreSurf.get_rect()
    scoreRect.topleft = (WINDOWWIDTH - offset, 10)
    DISPLAYSURF.blit(scoreSurf, scoreRect)
 
 
 
def drawWorm(wormCoords, wcolor):
    for coord in wormCoords:
        x = coord['x'] * CELLSIZE
        y = coord['y'] * CELLSIZE
        wormSegmentRect = pygame.Rect(x, y, CELLSIZE, CELLSIZE)
        pygame.draw.rect(DISPLAYSURF, wcolor, wormSegmentRect)
        wormInnerSegmentRect = pygame.Rect(x + 4, y + 4, CELLSIZE - 8, CELLSIZE - 8)
        pygame.draw.rect(DISPLAYSURF, wcolor, wormInnerSegmentRect)
 
 
def drawApple(coord, appletype):
    x = coord['x'] * CELLSIZE
    y = coord['y'] * CELLSIZE
    appleRect = pygame.Rect(x, y, CELLSIZE, CELLSIZE)
    location = APPLETYPE.index(appletype)
    color = APPLECOLOR[location]
    color = eval(color)
    pygame.draw.rect(DISPLAYSURF, color, appleRect)
 
 
def drawGrid():
    for x in range(0, WINDOWWIDTH, CELLSIZE): # draw vertical lines
        pygame.draw.line(DISPLAYSURF, DARKGRAY, (x, 0), (x, WINDOWHEIGHT))
    for y in range(0, WINDOWHEIGHT, CELLSIZE): # draw horizontal lines
        pygame.draw.line(DISPLAYSURF, DARKGRAY, (0, y), (WINDOWWIDTH, y))
 
 
if __name__ == '__main__':
    main()
