import discord
import random
import time
import asyncio
import json
import os

client = discord.Client()
prefix = "/cow "  # default prefix
v = '1.3'
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
    ["random", "random: random from 1 to [number]"],
    ["bug", "bug: uh oh, theres a bug? let pdb and pushorca help!"],
    ["spam", "spam: spam [message] spams the message (can be mentions too ;))"],
    ["lecture", "lecture: Ruoyu popping off af"],
    ["pushorca", "pushorca: Shows Pushorca for good luck"],
    ["internet", "internet: Checks for ping and (later) IP..."],
    ["fortune cookie", "fortune cookie: tells you your fortune!"],
    ["clean", "clean: clean [number of messages], clean less than 5 at a time!"],
    ["bounce", "bounce: BOUNCE IT"],
    ["emojirole", "emojirole: gives roles according to reactions"],
    ["purge channel", "purge channel: COMPLETELY CLEANS THE CHANNEL. BE CAREFUL!!!"],
    ["say", "say: cowsay from linux! (except no cow figure ;( )"],
    ["gamble", "gamble: economy, play slots"],
    ["bal", "bal: economy, checks your ballence"],
    ["invis", "invis: you cant see this"],
    ["work", "work: economy, work for dat paper"],
    ["scratch", "scratch: economy, buy yourself a scratch-off ticket"],
    ["buy upgrade", "buy upgrade: economy, passive income"],
    ["transfer", "transfer: economy, transfer funds to [user id]"]
]

upgradesPassives = [
    ["kid", "costs 10k, labor +1k/work (sorry fbi)"],
    ["bot", "costs 20k, super efficient. 5k/work"],
    ["caleb", "costs 50k, makes programs for you. gives you 10k/work"],
    ["quantum", "costs 150k, godly fps on Minecraft, but costs a lot of power. 75k/work"],
    ["spaceship", "costs 1mil WHO TF DOESN'T WANT ONE OF THESE, advertises to aliens, 125k/work"],
    ["dino", "costs 100mil legend has it if you beat the dino game, you will cause a "
                                            "time paradox and the dinos won't be extinct which means you can "
                                            "advertise to dinos. 1mil/work"]
]

cowpun = []

with open('cowpuns.txt', 'r') as b:
    for line in b:
        cowpun.append(line[:-1])


def jason_it(whatindex, filename, msg):
    with open(filename, 'r') as brr:
        prefixes = json.load(brr)
    prefixes[str(whatindex)] = msg
    with open(filename, 'w') as brrr:
        json.dump(prefixes, brrr, indent=4)


timerslist = []
messageid = 0
messagerole = ""
roleset = False
deletion = False


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
    fieldarryt = kwargs.get('arraytoembdt', None)
    color = kwargs.get('color', None)
    if color is None:
        color = 0x00D2FF
    embed = discord.Embed(
        title=title,
        description=desc,
        color=color
    )
    for arg in args:
        embed.add_field(name=arg[0], value=arg[1], inline=False)
    if fieldarry is not None:
        for i in range(len(fieldarry)):
            embed.add_field(name=prefix + str(fieldarry[i][0]), value="`" + str(fieldarry[i][1]) + "`", inline=False)
    if fieldarryt is not None:
        for i in range(len(fieldarryt)):
            embed.add_field(name=".", value="`" + str(fieldarryt[i][1]) + "`", inline=True)
    if footer is not None:
        embed.set_footer(text=footer)
    return embed


async def timer(message):
    try:
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
                if message.channel.id == 745753093915934772:
                    await message.channel.purge(limit=2)
                bss = '> Timer Cancelled! : '
                await message.channel.send(bss + str(user.mention))
    except:
        await message.channel.send("Timer Failed To Start. Check that it is in the format: h m s")
        if message.channel.id == 745753093915934772:
            time.sleep(1)
            await message.channel.purge(limit=2)


@client.event
async def on_ready():
    print('Logged as {0.user}'.format(client))
    await client.change_presence(activity=discord.Activity(name='for /cow help', type=discord.ActivityType.watching))


@client.event
async def on_voice_state_update(member, before, after):
    if after.channel is not None:
        if before.channel is None and after.channel.id == 746126673761534023:
            await member.add_roles(discord.utils.get(member.guild.roles, name="moosicow"))
            await member.move_to(client.get_channel(711999517184098436))
        elif before.channel is not None and after.channel.id == 712350731751129158:
            await member.move_to(None)
        elif after.channel.id == 731188789254553632:
            await member.remove_roles(discord.utils.get(member.guild.roles, name="moosicow"))
    elif before.channel is not None:
        if before.channel.id == 746174850858614835 or before.channel.id == 711999517184098436 or before.channel.id == 712350731751129158:
            await member.remove_roles(discord.utils.get(member.guild.roles, name="moosicow"))


@client.event
async def on_raw_reaction_add(payload):
    emojirole = {}
    if payload.user_id == client.user:
        return
    if payload.guild_id is None:
        return
    else:
        with open("reactionmsg.json", 'r') as brr:
            emojirole = json.load(brr)
        if str(payload.message_id) in emojirole:
            await client.get_guild(payload.guild_id).get_member(payload.user_id).add_roles(
                discord.utils.get(client.get_guild(payload.guild_id).roles, name=emojirole[str(payload.message_id)]))


@client.event
async def on_raw_reaction_remove(payload):
    emojirole = {}
    if payload.user_id == client.user:
        return
    if payload.guild_id is None:
        return
    else:
        with open("reactionmsg.json", 'r') as brr:
            emojirole = json.load(brr)
        if str(payload.message_id) in emojirole:
            await client.get_guild(payload.guild_id).get_member(payload.user_id).remove_roles(
                discord.utils.get(client.get_guild(payload.guild_id).roles, name=emojirole[str(payload.message_id)]))


@client.event
async def on_guild_join(guild):
    jason_it(guild.id, 'prefixes.json', "/moo ")


@client.event
async def on_message(message):
    global prefix
    global roleset
    global stopTimer
    global messageid
    global messagerole
    global deletion
    if message.author == client.user:
        return
    if message.channel.id != 745753093915934772 and message.channel.id != 725404488030224616:  # the channels #at the same clock and talk and announcements
        if message.content.startswith(prefix + cmd[0][0]) or message.content.startswith(prefix + "halp"):
            emb = embedMake(["Prefix", '\n `' + prefix + "`"], arraytoembd=cmd, title="Help",
                            desc="Ayy... Slidin into yo dms. MOO? You need halp? Here is the list of commands",
                            color=0x00D2FF)
            await message.author.send(embed=emb)
            await message.channel.send("> Help sent to " + message.author.mention + "'s DM. Please Check. ")
        elif message.content.startswith(prefix + cmd[1][0]):
            simp = "you have no gf"
            simp = getMsg(len(prefix) + len(cmd[1][0]) + 1, message.content, True)
            if '@' in simp:
                simp = simp.replace("<", "")
                simp = simp.replace(">", "")
                simp = simp.replace("@", "")
                simp = simp.replace("&", "")
                simp = simp.replace("!", "")
                try:
                    simpname = client.get_user(int(simp))
                except:
                    await message.channel.send('person no exist')
                    return
                if simpname is not None:
                    with open('cowsino.json', 'r') as countr:
                        prefixes = json.load(countr)
                    if str(message.author.id) in prefixes and str(simp) in prefixes:
                        mony = int(prefixes[str(message.author.id)])
                        money = int(prefixes[str(simp)])
                    elif str(message.author.id) not in prefixes:
                        jason_it(message.author.id, 'cowsino.json', 0)
                        await message.channel.send('New account made')
                        return
                    else:
                        return
                    jason_it(message.author.id, 'cowsino.json', 0)
                    jason_it(simp, 'cowsino.json', money + mony)
                    await message.channel.send("Sent *donations* to " + str(simpname))
                    emb = embedMake(['SIMP', 'How much? ```$' + str(mony) + '```'],
                                    ['From', str(message.author)], title="Someone's simping for ya", desc='😘',
                                    footer='girls with kaboobs are theives i know')
                    await simpname.send(embed=emb)
                    simp = (":heart:" + str(simpname)) * 5
            elif simp != " i sad no hav":
                simp = (":heart:" + simp) * 5
            else:
                simp = "me too its fine ;("
            for i in range(0, 5):
                await message.channel.send(simp)
        elif message.content.startswith("/cow " + cmd[2][0]):
            newPFX = getMsg(len("/cow ") + len(cmd[2][0]) + 1, message.content, True)
            if newPFX != "'default'" and newPFX != '':
                prefix = newPFX + " "
            else:
                prefix = "/cow "
            jason_it(message.guild.id, 'prefixes.json', prefix)
            await message.channel.send("> Prefix Successfully Changed To:\n```" + prefix + "```")
        elif message.content.startswith(prefix + cmd[3][0]):
            # if message.author.voice != None:
            # await play(message, 'https://www.youtube.com/watch?v=J0HgEEY2jts')
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
            await message.channel.send("STAWP GAMBLING LIKE A GATBING")
            spam = getMsg(len(prefix) + len(cmd[7][0]), message.content, True) + ""
            try:
                spam = int(spam)
            except:
                await message.channel.send('aint a integer lmao')
                return
            id = await message.channel.send('```' + str(random.randint(1, spam)) + '```')
            await id.edit(content='You Won: ```' + str(random.randint(1, spam)) + '```')

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
            if message.guild is None:
                return
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
            if message.guild is None:
                return
            messagestuff = getMsg(len(prefix) + len(cmd[16][0]) + 1, message.content, True)
            if messagestuff != '':
                a = await message.channel.send(messagestuff)
            else:
                a = await message.channel.send("example text")
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
                jason_it(messageid, "reactionmsg.json", messagerole)
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
        elif message.content.startswith(prefix + cmd[17][0]):
            if message.guild is None:
                return
            deletion = True
            await message.channel.send(
                "Are moo sure about that? \n WARNING: you can't retrieve the messages back... \n Confirm With:```" + prefix + "DELETE MOO IS SURE```")
        elif message.content.startswith(prefix + "DELETE MOO IS SURE") and deletion:
            if message.channel.name == '🤭qmbo-time' or message.guild.id != 663150753946402817:
                a = message.channel
                await discord.TextChannel.clone(self=a)
                await discord.TextChannel.delete(self=a)
        elif message.content.startswith(prefix + cmd[18][0]):
            messagestuff = getMsg(len(prefix) + len(cmd[18][0]) + 1, message.content, True)
            await message.channel.send(
                "``` " + messagestuff + "\n        \    ^__^\n         \  (oo)\_______\n            (__)\       )\/\n "
                                        "               ||----w |\n                ||     ||\n```")
        elif message.content.startswith(prefix + cmd[19][0]) or message.content.startswith('/cowsino'):
            msgtemp = ''
            if message.content.startswith(prefix + cmd[19][0]):
                stufflen = len(prefix) + len(cmd[19][0]) + 1
            else:
                stufflen = 8
            try:
                howmuchbet = int(getMsg(stufflen, message.content, True))
            except:
                await message.channel.send('Gamble not integer')
                return
            authorid = message.author.id
            num = len(str(howmuchbet)) + 1
            with open('cowsino.json', 'r') as countr:
                prefixes = json.load(countr)
            if str(authorid) in prefixes:
                money = prefixes[str(message.author.id)]
            else:
                jason_it(authorid, 'cowsino.json', 0)
                return
            if howmuchbet <= money and str(howmuchbet)[0] != '-' and money >= 0:
                slot = []
                arraytemp = []
                aaa = 0
                bbb = 0
                ccc = 0
                arrayofgambles = [0 for asdf in range(num)]
                with open('slots.txt', 'r', encoding="utf8") as brr:
                    for line in brr:
                        slot.append(line[:-1])
                slot.pop()  # the end one is alwasy blank fsr
                id = await message.channel.send('.')
                for ii in range(5):
                    arraytemp = []
                    await asyncio.sleep(ii / 7)
                    for i in range(num):
                        arrayofgambles[i] = random.randint(0, num)
                        arraytemp.append(str(slot[arrayofgambles[i]]))
                    msgtemp = "".join(arraytemp)
                    emb = embedMake(["Your Spin", str(msgtemp)],
                                    title='Moogas Cowsino', color=0x00D2FF, footer='Gambling is addiction. so feed it')
                    await id.edit(embed=emb)
                arrayofgambles.sort()
                if all(ele == arrayofgambles[0] for ele in arrayofgambles):
                    emb = embedMake(["Your Spin", str(msgtemp)],
                                    ['Result', '**YOU WON BIGGGGG** \n+' + str(howmuchbet * 10)],
                                    title='Moogas Cowsino', color=0x00D2FF, footer='Gambling is addiction. so feed it')
                    await id.edit(embed=emb)
                    jason_it(authorid, 'cowsino.json', money + howmuchbet * 10)
                else:
                    seen = []
                    contr = 0
                    for xi in range(len(arrayofgambles) - 1):
                        if arrayofgambles[xi] == arrayofgambles[xi + 1]:
                            contr += 1
                    if contr >= num // 2:
                        emb = embedMake(
                            ["Your Spin", str(msgtemp)],
                            ['Result', '**Ayy some colors match**\n +' + str(howmuchbet * 2)],
                            title='Moogas Cowsino', color=0x00D2FF, footer='Gambling is addiction. so feed it')
                        await id.edit(embed=emb)
                        jason_it(authorid, 'cowsino.json', money + howmuchbet * 2)
                    else:
                        emb = embedMake(["Your Spin", str(msgtemp)],
                                        ['Result', '**lost money at cowsino**\n -' + str(howmuchbet)],
                                        title='Moogas Cowsino', color=0x00D2FF,
                                        footer='Gambling is addiction. so feed it')
                        await id.edit(embed=emb)
                        jason_it(authorid, 'cowsino.json', money - howmuchbet)
            else:
                if money < 0:
                    await message.channel.send('U BROKE BISH NO GAMBLE FOR U')
                else:
                    await message.channel.send('NO BETTING ABSURD AMOUNTS FOOL')
        elif message.content.startswith(prefix + cmd[20][0]):
            whotocheck = getMsg(len(prefix) + len(cmd[20][0]) + 1, message.content, True)
            if whotocheck == '' or whotocheck == 'self':
                whotocheck = message.author.id
            with open('cowsino.json', 'r') as countr:
                prefixes = json.load(countr)
            if str(whotocheck) in prefixes:
                mony = int(prefixes[str(whotocheck)])
            else:
                jason_it(message.author.id, 'cowsino.json', 0)
                await message.channel.send('New account made')
                return
            if mony <= 0:
                status = 'broke'
            elif mony > 1000000:
                status = 'business man'
            elif mony > 10000:
                status = 'rich'
            elif mony > 1000:
                status = 'good'
            else:
                status = 'none'
            username = str(client.get_user(int(whotocheck)))
            emb = embedMake(["Bal:", "```$" + str(mony) + "```"], ["$tatus:", "```" + str(status) + "```"],
                            title='How Rich i$ $omeone ', desc='```' + username + '```', color=0x00D2FF)
            await message.channel.send(embed=emb)
        elif message.content.startswith(prefix + cmd[21][0]):
            await message.channel.send('‎‎\n' * 6)
        elif message.content.startswith(prefix + cmd[22][0]):
            with open('cowsino.json', 'r') as countr:
                prefixes = json.load(countr)
            if str(message.author.id) in prefixes:
                mony = int(prefixes[str(message.author.id)])
            else:
                jason_it(message.author.id, 'cowsino.json', 0)
                await message.channel.send('New account made')
                return
            with open('boosts.json', 'r') as contr:
                boosts = json.load(contr)
            if str(message.author.id) in boosts:
                moneey = int(boosts[str(message.author.id)])
            else:
                moneey = 0
            work = random.randint(100, 500 + moneey)
            jason_it(message.author.id, 'cowsino.json', work + mony)
            emb = embedMake(["You Earned", "```" + str(work) + "```"],
                            title='$Work Slav Work!$', color=0x00D2FF)
            await message.channel.send(embed=emb)
        elif message.content.startswith(prefix + cmd[23][0]):
            with open('cowsino.json', 'r') as countr:
                prefixes = json.load(countr)
            if str(message.author.id) in prefixes:
                mony = int(prefixes[str(message.author.id)])
            else:
                jason_it(message.author.id, 'cowsino.json', 0)
                await message.channel.send('New account made')
                return
            win = random.randint(1, 1000)
            if win <= random.randint(1, 1000):
                addmany = win
                jason_it(message.author.id, 'cowsino.json', addmany + mony)
                emb = embedMake(["You Earned", "|| $" + str(addmany) + "||"],
                                title='$Scratch off$', color=0x00D2FF)
            else:
                jason_it(message.author.id, 'cowsino.json', mony - 20)
                emb = embedMake(["You Earned", "|| $0 LOL ||"],
                                title='$Scratch off$', color=0x00D2FF)
            await message.channel.send(embed=emb)
        elif message.content.startswith(prefix + cmd[24][0]) or message.content.startswith(prefix + 'buy'):
            if message.content.startswith(prefix + cmd[24][0]):
                item = getMsg(len(prefix) + len(cmd[24][0]) + 1, message.content, True)
            else:
                item = getMsg(len(prefix+"buy") + 1, message.content, True)
            if item == 'list':
                emb = embedMake(["Prefix:", '\n `' + prefix + "buy item`"], arraytoembd=upgradesPassives, title="Buy",
                                desc="The white market for passive income",
                                color=0x00D2FF)
                await message.channel.send(embed=emb)
                return
            item = item.split()
            with open('cowsino.json', 'r') as contr:
                money = json.load(contr)
            with open('boosts.json', 'r') as countr:
                boosts = json.load(countr)
            if str(message.author.id) in money:
                money = int(money[str(message.author.id)])
                if str(message.author.id) in boosts:
                    moneystuff = int(boosts[str(message.author.id)])
                else:
                    moneystuff = 0
            else:
                jason_it(message.author.id, 'cowsino.json', 0)
                await message.channel.send('New account made')
                return
            moneyarray = [ #work boosts, cost
                [1000, 10000],
                [5000, 20000],
                [10000, 50000],
                [75000, 150000],
                [125000, 1000000],
                [1000000, 100000000]
            ]
            ugh = 0
            for y in range(len(upgradesPassives)):
                if item[0] == upgradesPassives[y][0]:
                    ugh = y
            for i in range(len(moneyarray)):
                if i == ugh:
                    if money >= (moneyarray[i][1] * int(item[1])):
                        if item[0] == upgradesPassives[i][0]:
                            jason_it(message.author.id, 'boosts.json', moneystuff + (moneyarray[i][0] * int(item[1])))
                            jason_it(message.author.id, 'cowsino.json', money - (moneyarray[i][1] * int(item[1])))
                            await message.channel.send('Buy '+str(item[1])+' '+str(item[0]))
                    else:
                        await message.channel.send('Costs too much!!!!')
        elif message.content.startswith(prefix + cmd[25][0]):
            user = message.author.mention
            target = getMsg(len(prefix) + len(cmd[25][0]) + 1, message.content, True)
            target = target.split()
            a = target[0]
            bb = target[0]
            a = a.replace("<", "")
            a = a.replace(">", "")
            a = a.replace("@", "")
            a = a.replace("&", "")
            a = a.replace("!", "")
            target[0] = a
            if str(target[0]) == str(message.author.id):
                await message.channel.send("dont send to urself")
                return
            try:
                b = int(target[0])
                c = int(target[1])
            except:
                if target[1] != 'all':
                    await message.channel.send("something is no integer")
                    return
            with open('cowsino.json', 'r') as countr:
                prefixes = json.load(countr)
            if str(message.author.id) in prefixes and str(target[0]) in prefixes:
                if target[1] == 'all':
                    target[1] = str(prefixes[str(message.author.id)])  # send all da money
                mony = int(prefixes[str(message.author.id)])
                money = int(prefixes[str(target[0])])
            elif str(message.author.id) not in prefixes:
                jason_it(message.author.id, 'cowsino.json', 0)
                await message.channel.send('New account made')
                return
            elif str(target[0]) not in prefixes:
                await message.channel.send("target is not found")
                return
            else:
                return
            if mony >= int(target[1]):
                jason_it(message.author.id, 'cowsino.json', mony - int(target[1]))
                jason_it(target[0], 'cowsino.json', money + int(target[1]))
                await message.channel.send("Sent funds to " + str(bb))
                reciever = client.get_user(int(target[0]))
                emb = embedMake(['Mooney transfer', 'How much? ```$' + str(target[1]) + '```'], ['From', str(user)],
                                title='Money Transfer', desc='WeChatPay', footer='credit card fraud happens sometimes')
                await reciever.send(embed=emb)
            else:
                await message.channel.send("U BROKE BOI NO MANEY SEND")
        # end here ^^^^
        elif message.content.startswith(prefix):
            await message.channel.send("moo? That's not a cow command. Type " + prefix + "help")
    else:
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