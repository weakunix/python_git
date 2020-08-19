import discord
import random
import time
import math as albreto
import asyncio

client = discord.Client()
prefix = "/cow "
v = '0.6'

key = []
with open('key.txt', 'r') as b:
    for line in b:
        key.append(line[:-1])  # need to add a extra char
key = "".join(key)

cmd = [
    "help",
    "simp",
    "prefix",
    "moo",
    "version",
    "timer",
    "timers"
]

cowpun = [
    "What is a happy cowboy?\n> A jolly rancher",
    "What's a pampered cow?\n> Spoiled Milk",
    "Who did the cow call to relocate?\n> the MOOVING company",
    "What do you call a scardycow?\n> a coward",
    "Who is MrMoooo?\n> a business cow",
    "What did the cow say to the spilled milk?\n> udder cowtastrophe",
    "What does cows drive into war?\n> milk TANKERS"
]

timerslist = []


def getMsg(lenpfx, msg, string):
    ret = []
    for i in range(lenpfx, len(msg)):
        ret.append(msg[i])
    print(ret)
    if string:
        ret = "".join(ret)
    return ret


@client.event
async def on_ready():
    print('Logged as {0.user}'.format(client))
    await client.change_presence(activity=discord.Activity(name='for /cow help', type=discord.ActivityType.watching))


@client.event
async def on_message(message):
    global prefix
    if message.author == client.user:
        return
    if message.content.startswith(prefix + cmd[0]):
        await message.channel.send('> MOO? You need halp? Here is the list of commands: \n ```/cow prefix [] ('
                                   'change prefix [itll always be /cow prefix to change]) \n' + prefix + 'moo (play cow moo sound) \n' + prefix + 'simp [girlfriend (i sad no '
                                                                                                                                                  'hav)] (cow spams her name and hearts)\n' + prefix + 'moo```')
    elif message.content.startswith(prefix + cmd[1]):

        simp = getMsg(len(prefix) + len(cmd[1]) + 1, message.content, True)
        if simp != " i sad no hav":
            simp = (":heart:" + simp) * 5
        else:
            simp = "me too its fine ;("
        for i in range(0, 5):
            await message.channel.send(simp)
    elif message.content.startswith("/cow " + cmd[2]):
        newPFX = getMsg(len("/cow ") + len(cmd[2]) + 1, message.content, True)
        if newPFX != "default":
            prefix = newPFX + " "
        else:
            prefix = "/cow "
        await message.channel.send("> Prefix Successfully Changed To:\n```" + prefix + "```")
    elif message.content.startswith(prefix + cmd[3]):
        await message.channel.send(
            "> " + cowpun[random.randint(0, 6)] + "\n https://www.youtube.com/watch?v=J0HgEEY2jts")
    elif message.content.startswith("/bing"):
        prefix = "moo "
        await message.channel.send("> ```Dev Cheats Activated```")
    elif message.content.startswith(prefix + cmd[4]):
        await message.channel.send("> BingBingBot Version: ```Version: " + v + "```> github repo here:\n "
                                                                               "> ```https://github.com/weakunix/python_git```")
    elif message.content.startswith(prefix + cmd[5]):
        timeslep = getMsg(len(prefix) + len(cmd[5]) + 1, message.content, False)
        slp = 0
        if "show" in message.content:
            for i in range(len(timerslist)):
                await message.channel.send(timerslist[i])
            if len(timerslist) == 0:
                await message.channel.send("no timers running, set one with ```" + prefix + "timer```")
        else:
            for i in range(len(timeslep)):
                if "s" == timeslep[i]:
                    timeslep[i] = ""
                    slp = 1
                elif "m" == timeslep[i]:
                    timeslep[i] = ""
                    slp = 60
                elif "h" == timeslep[i]:
                    timeslep[i] = ""
                    slp = 3600
            timeslep = "".join(timeslep)
            try:
                timeslep = int(timeslep)
                slp *= timeslep
                ak = await message.channel.send("Timer set")
                timerslist.append("o")
                brr = len(timerslist)
                print(brr)
                for i in range(0, slp):
                    await asyncio.sleep(1)
                    a = "s" if slp < 60 else "m" if slp <= 3600 else "h"
                    display = slp if slp < 60 else slp / 60 if slp < 3600 else slp / 3600
                    timerslist[brr - 1] = (
                                '> timer set: ' + str(albreto.floor(display)) + a + " #" + str(message.channel))
                    await ak.edit(content="> Timer set for ```" + str(albreto.floor(display)) + a + "```")
                    slp -= 1
                await message.channel.send('> Timer done! : {} '.format(message.author))  # '''
                await message.author.send('Your timer is done!')
                timerslist[brr-1].pop()
            except ValueError:
                await message.channel.send('> Failed to set timer\n Make it like this  ```1h```,```1m```,```1s```')


client.run(key)
