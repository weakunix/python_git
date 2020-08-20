import discord
import random
import time
import math as albreto
import asyncio

client = discord.Client()
prefix = "/cow "  # default prefix
v = '0.9'
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
    ["help", "help: This"],
    ["simp", "simp: simp [girl name (default to you have no girlfriend)] Simp for your girl,"],
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
    ["clean", "clean: clean [number of messages], clean less than 5 at a time!"],
    ["bounce", "bounce: BOUNCE IT"],
    ["emojirole", "gives roles according to reactions"],
]

cowpun = [
    "What is a happy cowboy?\n> A jolly rancher",
    "What's a pampered cow?\n> Spoiled Milk",
    "Who did the cow call to relocate?\n> the MOOVING company",
    "What do you call a scardycow?\n> a coward",
    "Who is MrMoooo?\n> a business cow",
    "What did the cow say to the spilled milk?\n> udder cowtastrophe",
    "What does cows drive into war?\n> milk TANKERS",
    "What did the cow say at the Mexican Restaurant?\n MOOchas gracias!"
]

emojirole = []

timerslist = []
messageid = 0
messagerole = ""
roleset = False


def getMsg(lenpfx, msg, string):
    ret = []
    for i in range(lenpfx, len(msg)):
        ret.append(str(msg[i]))
    if string:
        ret = "".join(ret)
    return ret


def embedMake(*args, **kwargs):
    title = kwargs.get('title', None)
    desc = kwargs.get('desc', None)
    footer = kwargs.get('footer', None)
    img = kwargs.get('img', None)
    thumbnail = kwargs.get('thumbnail', None)
    author = kwargs.get('author', None)
    fieldarry = kwargs.get('arraytoembd', None)
    color = kwargs.get('color', None)
    embed = discord.Embed(
        title=title,
        description=desc,
        color=color
    )
    for arg in args:
        embed.add_field(name=arg[0], value=arg[1], inline=False)
    for i in range(len(fieldarry)):
        embed.add_field(name=prefix + fieldarry[i][0], value="`" + fieldarry[i][1] + "`", inline=False)
    return embed


async def timer(message):
    user = message.author
    timeslep = getMsg(len(prefix) + len(cmd[5][0]) + 1, message.content, False)
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
            if message.channel.id == 745753093915934772:
                await message.channel.purge(limit=2)
            bss = '> Timer done! : ' + str(user.mention)
            time.sleep(1)
            await message.author.send(bss)
            timerslist.pop(brr - 1)
        else:
            await message.channel.purge(limit=2)
            bss = '> Timer Cancelled! : '
            await message.channel.send(bss + str(user.mention))


@client.event
async def on_ready():
    print('Logged as {0.user}'.format(client))
    await client.change_presence(activity=discord.Activity(name='for /cow help', type=discord.ActivityType.watching))


@client.event
async def on_reaction_add(reaction, user):
    global emojirole
    try:
        num = -1
        for i in range(len(emojirole)):
            if emojirole[i][1] == reaction.message.id:
                num = i
        if num != -1:
            await user.add_roles(discord.utils.get(user.guild.roles, name=emojirole[num][0]))
        # await reaction.message.channel.send("added " + emojirole[num][0] + " to " + user.mention)
    except:
        return 0


@client.event
async def on_reaction_remove(reaction, user):
    global emojirole
    try:
        num = -1
        for i in range(len(emojirole)):
            if emojirole[i][1] == reaction.message.id:
                num = i
        if num != -1:
            await user.remove_roles(discord.utils.get(user.guild.roles, name=emojirole[num][0]))
        # await reaction.message.channel.send("removed " + emojirole[num][0] + " to " + user.mention)
    except:
        return 0


@client.event
async def on_message(message):
    global prefix
    global roleset
    global stopTimer
    global messageid
    global messagerole
    if message.author == client.user:
        return
    if message.channel.id != 745753093915934772 and message.channel.id != 725404488030224616: #the channels #at the same clock and talk and announcements
        if message.content.startswith(prefix + cmd[0][0]) or message.content.startswith(prefix + "halp"):
            emb = embedMake(["Prefix", '\n `' + prefix + "`"], arraytoembd=cmd, title="Help",
                            desc="Ayy... Slidin into yo dms. MOO? You need halp? Here is the list of commands",
                            color=0x00D2FF)
            await message.author.send(embed=emb)
            await message.channel.send("> Help sent to " + message.author.mention + "'s DM. Please Check. ")
        elif message.content.startswith(prefix + cmd[1][0]):
            simp = "you have no gf"
            simp = getMsg(len(prefix) + len(cmd[1][0]) + 1, message.content, True)
            if simp != " i sad no hav":
                simp = (":heart:" + simp) * 5
            else:
                simp = "me too its fine ;("
            for i in range(0, 5):
                await message.channel.send(simp)
        elif message.content.startswith("/cow " + cmd[2][0]):
            newPFX = getMsg(len("/cow ") + len(cmd[2][0]) + 1, message.content, True)
            if newPFX != "'default'":
                prefix = newPFX + " "
            else:
                prefix = "/cow "
            await message.channel.send("> Prefix Successfully Changed To:\n```" + prefix + "```")
        elif message.content.startswith(prefix + cmd[3][0]):
            await message.channel.send(
                "> " + cowpun[random.randint(0, 6)] + "\n https://www.youtube.com/watch?v=J0HgEEY2jts")
        elif message.content.startswith("/bing"):
            prefix = "moo "
            await message.channel.send("> ```Dev Cheats Activated```")
        elif message.content.startswith(prefix + cmd[4][0]):
            await message.channel.send("> BingBingBot Version: ```Version: " + v + "```> github repo here:\n "
                                                                                   "> ```https://github.com/weakunix/python_git```")
        elif message.content.startswith(prefix + cmd[5][0]):
            await timer(message)
            # except ValueError:
            #    await message.channel.send('> Failed to set timer\n Make it like this  ```h and m and s```')
        elif message.content.startswith(prefix + cmd[6][0]):
            await message.channel.send(
                '> https://media.discordapp.net/attachments/730581364675575858/744609727752962185'
                '/image0.jpg?width=1248&height=936')
        elif message.content.startswith(prefix + cmd[7][0]):
            yay = ("YESSIRRRRR " * 5)
            for i in range(5):
                await message.channel.send(yay)
            await message.channel.send("https://www.youtube.com/watch?v=3xsZnMLrH2U")
        elif message.content.startswith(prefix + cmd[8][0]):
            await message.channel.send(":bug: ```import pdb;pdb.set_trace()```")
        elif message.content.startswith(prefix + cmd[9][0]):
            spam = getMsg(len(prefix) + len(cmd[9][0]), message.content, True) + ""
            spam = message.author.mention * 5 if spam == "" else spam * 5
            for i in range(0, 5):
                await message.channel.send(spam)
        elif message.content.startswith(prefix + cmd[10][0]):
            await message.channel.send(
                'https://media.discordapp.net/attachments/663150753946402820/745720458174922823/unknown.png')
        elif message.content.startswith(prefix + cmd[11][0]):
            pushorcas = [
                'https://media.discordapp.net/attachments/663150753946402820/738870510708064286/image0.jpg?width=1248&height=936',
                'https://cdn.discordapp.com/emojis/720706354154569808.png?v=1']
            await message.channel.send(pushorcas[random.randint(0, 1)])
        elif message.content.startswith(prefix + cmd[12][0]):
            await message.channel.send("> Your Ping(ms) :" + str(round(client.latency * 1000)))
        elif message.content.startswith(prefix + cmd[13][0]):
            await message.channel.send(fortune[random.randint(0, len(fortune))])
        elif message.content.startswith(prefix + cmd[14][0]):
            howMuchToPurge = 0
            try:
                howMuchToPurge = int(getMsg(len(prefix) + len(cmd[14][0]) + 1, message.content, True))
            except:
                await message.channel.send("NOT A INTEGER U DOOFUS :RAAAA: ")
            if howMuchToPurge > 5:
                await message.channel.send("For safety reasons, do not clear more than 5 messages")
            elif 0 < howMuchToPurge <= 5:
                await message.channel.purge(limit=howMuchToPurge + 1)
                await message.channel.send("~Cleared " + str(howMuchToPurge) + " messages and command~")
                time.sleep(1)
                await message.channel.purge(limit=1)
        elif message.content.startswith(prefix + cmd[15][0]):
            await message.channel.send("bounce!!\n https://images-ext-2.discordapp.net/external/_e-mp-bsozl"
                                       "-BZDp2dPhJ9uExzpf6T6rFNgCXob-mzo/%3Fw%3D640/https/kmccready.files.wordpress.com"
                                       "/2009/04/bouncing-cow.gif")
        elif message.content.startswith(prefix + cmd[16][0]):
            messagestuff = getMsg(len(prefix) + len(cmd[16][0]) + 1, message.content, True)
            a = await message.channel.send(messagestuff)
            await a.add_reaction("🐮")
            messageid = a.id
            await message.channel.send("Continue setup with /setrole [role to add with emoji]")
            roleset = True
        elif message.content.startswith("/setrole") and roleset:
            messagerole = getMsg(len("/setrole") + 1, message.content, True)
            try:
                await message.author.add_roles(discord.utils.get(message.author.guild.roles, name=messagerole))
                await message.author.remove_roles(discord.utils.get(message.author.guild.roles, name=messagerole))
                await message.channel.send("role assigned to emoji:" + str(messagerole))
                roleset = False
                emojirole.append([messagerole, messageid])
            except AttributeError:
                await message.channel.send("Not a role, setup cancelled")
                roleset = False
                msg = await message.channel.fetch_message(messageid)
                await msg.delete()
            except discord.errors.Forbidden:
                await message.channel.send("Can't set a role higher than yourself lol. Ha! No admin for you ;)")
                roleset = False
                msg = await message.channel.fetch_message(messageid)
                await msg.delete()
        elif message.content.startswith(prefix):
            await message.channel.send("moo? That's not a cow command. Type "+prefix+"help")
    else:
        '''if message.channel.id == 663150753946402820:
            if message.content.startswith(prefix):
                await message.channel.purge(limit=1)
                await message.channel.send("In order to not clog up "+str(message.channel.mention)+", Please move to "
                                                                                                   "the bot "
                                                                                                   "channel"+str(
                    message.author.mention))
                time.sleep(1)
                await message.channel.purge(limit=1)'''
        if message.channel.id == 725404488030224616:
            if not message.content.startswith("[ANNOUNCEMENT]"):
                await message.channel.purge(limit=1)
                await message.author.send("dont small talk in " + str(message.channel.mention) + "Use [ANNOUNCEMENT] "
                                                                                                "message as a prefix.")
        else:
            if message.content.startswith(prefix + cmd[5][0]):
                await timer(message)
            else:
                await message.channel.purge(limit=1)
                await message.author.send("not a timer command, use " + prefix + "timer h m s")


client.run(key)
