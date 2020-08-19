import discord
import random
import time
import math as albreto
import asyncio

client = discord.Client()
prefix = "/cow "
v = '0.8'
stopTimer = False

key = []
with open('key.txt', 'r') as b:
    for line in b:
        key.append(line[:-1])  # need to add a extra char
key = "".join(key)

fortune = []
with open('fortune.txt', 'r') as b:
    for line in b:
        fortune.append(line[:-1])  # need to add a extra char

cmd = [
    ["help", "help: This command"],
    ["simp", "simp: Simp for your girl,"],
    ["prefix", "prefix []: change prefix to [], (it is always __/cow prefix []__ just in case your friend changes it "
               "to smt you don't know)additionall command(s): /cow prefix 'default' resets prefix"],
    ["moo", "moo: joins your voice channel and moos, if you are not in vc, it'll send you a MooTube video and a joke"],
    ["version", "version: checks version of this bot and github"],
    ["timer", "timer: format is(timer h and m and s), example: prefix timer 1h and 4m and 30s, additional commands: "
              "timer show (shows all timers and their channels) timer stop (stops all timers)"],
    ["dznr", "dznr: Louis Vuitton, Gucci, Vercase"],
    ["yessir", "yessir: Spamms YESSIRRRRRR (ferg style)"],
    ["bug", "bug: uh oh, theres a bug? let pdb and pushorca help!"],
    ["spam", "spam: spam [message] spams the message (can be mentions too ;))"],
    ["lecture", "lecture: Ruoyu popping off af"],
    ["pushorca", "pushorca: Shows Pushorca for good luck"],
    ["internet", "internet: Checks for ping and (later) IP..."],
    ["fortune cookie", "fortune cookie: tells you your fortune!"],
    ["clean", "clean: clean [number of messages], clean less than 5 at a time because safety"]
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
        ret.append(str(msg[i]))
    if string:
        ret = "".join(ret)
    return ret


def embedMake(**kwargs):
    title = kwargs.get('title', None)
    desc = kwargs.get('desc', None)
    footer = kwargs.get('footer', None)
    img = kwargs.get('img', None)
    thumbnail = kwargs.get('thumbnail', None)
    author = kwargs.get('author', None)
    field = kwargs.get('field', None)
    fieldt = kwargs.get('fieldt', None)
    color = kwargs.get('color', None)
    embed = discord.Embed(
        title=title,
        description=desc,
        color=color
    )
    embed.add_field(name=field[0], value=field[1], inline=True)
    embed.add_field(name=fieldt[0], value=fieldt[1], inline=True)
    return embed


@client.event
async def on_ready():
    print('Logged as {0.user}'.format(client))
    await client.change_presence(activity=discord.Activity(name='for /cow help', type=discord.ActivityType.watching))


@client.event
async def on_message(message):
    global prefix
    global stopTimer
    if message.author == client.user:
        return
    if message.content.startswith(prefix + cmd[0]):
        #a = "\n".join(cmd)
        emb = embedMake(title="Help", desc="MOO? You need halp? Here is the list of commands", color=0x00D2FF,
                        field=["Prefix", '\n' + prefix], fieldt=["Commands", ' ```' + a + '```'])
        await message.channel.send(embed=emb)
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
        if newPFX != "'default'":
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
        user = message.author
        timeslep = getMsg(len(prefix) + len(cmd[5]) + 1, message.content, False)
        slp = 0
        if "show" in message.content:
            for i in range(len(timerslist)):
                await message.channel.send(timerslist[i])
            if len(timerslist) == 0:
                await message.channel.send("no timers running, set one with ```" + prefix + "timer```")
        elif "stop" in message.content:
            stopTimer = True
            await message.channel.send("Cleared Timers, use ```" + prefix + "timer``` to set one")
            # timerslist.clear()
        else:
            stopTimer = False
            stuff = [["s", 1], ["m", 60], ["h", 3600], ['a', 0], ['n', 0], ['d', 0]]
            for i in range(len(timeslep)):
                for x in range(len(stuff)):
                    if stuff[x][0] == timeslep[i]:
                        timeslep[i] = ""
            timeslep = "".join(timeslep)
            arry = timeslep.split(" ")
            hr = int(arry[0])
            minu = int(arry[1])
            sec = int(arry[2])
            slp = hr * 3600
            slp += minu * 60
            slp += sec
            ak = await message.channel.send("Timer set")
            timerslist.append("o")
            brr = len(timerslist)
            display = [0, 0, 0]
            for i in range(0, slp):
                if not stopTimer:
                    time.sleep(1)
                    display[0] = 0
                    display[1] = 0
                    display[2] = 0
                    if slp < 60:
                        display[2] = slp
                    elif slp <= 3600:
                        display[1] = slp // 60
                        display[2] = slp % 60
                    else:
                        display[0] = slp // 3600
                        display[1] = (slp % 3600) // 60
                        display[2] = (slp % 3600) % 60
                    # display = slp if slp < 60 else slp / 60 if slp < 3600 else slp / 3600
                    timerslist[brr - 1] = (
                            '> timer set: ' + str(display[0]) + 'h ' + str(display[1]) + 'm ' + str(
                        display[2]) + 's ' + " #" + str(message.channel.mention))
                    await ak.edit(content="> Timer set for ```" + str(display[0]) + 'h ' + str(display[1]) + 'm ' + str(
                        display[2]) + 's ' + "```")
                    slp -= 1
            if not stopTimer:
                bss = '> Timer done! : ' + str(user.mention)
                await ak.edit(content=bss)
                await message.author.send(bss)
                timerslist.pop(brr - 1)
            else:
                bss = '> Timer Cancelled! : '
                await ak.edit(content=bss)
                await message.channel.send(bss + str(user.mention))
            # except ValueError:
            #    await message.channel.send('> Failed to set timer\n Make it like this  ```h and m and s```')
    elif message.content.startswith(prefix + cmd[6]):
        await message.channel.send('> https://media.discordapp.net/attachments/730581364675575858/744609727752962185'
                                   '/image0.jpg?width=1248&height=936')
    elif message.content.startswith(prefix + cmd[7]):
        yay = ("YESSIRRRRR " * 5)
        for i in range(5):
            await message.channel.send(yay)
        await message.channel.send("https://www.youtube.com/watch?v=3xsZnMLrH2U")
    elif message.content.startswith(prefix + cmd[8]):
        await message.channel.send(":bug: ```import pdb;pdb.set_trace()```")
    elif message.content.startswith(prefix + cmd[9]):
        spam = getMsg(len(prefix) + len(cmd[9]), message.content, True) + ""
        spam = message.author.mention * 5 if spam == "" else spam * 5
        for i in range(0, 5):
            await message.channel.send(spam)
    elif message.content.startswith(prefix + cmd[10]):
        await message.channel.send(
            'https://media.discordapp.net/attachments/663150753946402820/745720458174922823/unknown.png')
    elif message.content.startswith(prefix + cmd[11]):
        pushorcas = [
            'https://media.discordapp.net/attachments/663150753946402820/738870510708064286/image0.jpg?width=1248&height=936',
            'https://cdn.discordapp.com/emojis/720706354154569808.png?v=1']
        await message.channel.send(pushorcas[random.randint(0, 1)])
    elif message.content.startswith(prefix + cmd[12]):
        await message.channel.send("> Your Ping(ms) :" + str(round(client.latency * 1000)))
    elif message.content.startswith(prefix + cmd[13]):
        await message.channel.send(fortune[random.randint(0, len(fortune))])
    elif message.content.startswith(prefix + cmd[14]):
        howMuchToPurge = 0
        try:
            howMuchToPurge = int(getMsg(len(prefix) + len(cmd[14]) + 1, message.content, True))
        except:
            await message.channel.send("NOT A INTEGER U DOOFUS :RAAAA: ")
        if howMuchToPurge > 5:
            await message.channel.send("For safety reasons, do not clear more than 5 messages")
        elif 0 < howMuchToPurge <= 5:
            await message.channel.purge(limit=howMuchToPurge + 1)
            await message.channel.send("~Cleared " + str(howMuchToPurge) + " messages and command~")
            time.sleep(1)
            await message.channel.purge(limit=1)


client.run(key)
