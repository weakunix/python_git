import discord
import random
import time
import asyncio
import json
import os

client = discord.Client()
prefix = "/cow "  # default prefix
v = '1'
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
    ["kid", "costs 10k, labor 1k/month (sorry fbi)"],
    ["bot", "costs 20k, super efficient. 10k/month"],
    ["caleb", "costs 50k, makes programs for you. gives you 20k/month"],
    ["quantom pc", "costs 150k, godly fps on Minecraft, but costs a lot of power. 50k/month"],
    ["spaceship", "costs 1mil WHO TF DOESN'T WANT ONE OF THESE, advertises to aliens, 100k/Month"],
    ["script to beat chrome dinosaur game", "costs 100mil legend has it if you beat the dino game, you will cause a "
                                            "time paradox and the dinos won't be extinct which means you can "
                                            "advertise to dinos. 1mil/month"]
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
            embed.add_field(name=prefix + fieldarry[i][0], value="`" + fieldarry[i][1] + "`", inline=False)
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
            if simp != " i sad no hav":
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
                "``` " + messagestuff + "\n        \    ^__^\n         \  (oo)\_______\n            (__)\       )\/\n                ||----w |\n                ||     ||\n```")
        elif message.content.startswith(prefix + cmd[19][0]):
            try:
                howmuchbet = int(getMsg(len(prefix) + len(cmd[19][0]) + 1, message.content, True))
            except:
                await message.channel.send('AAA not integer')
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
            print(money)
            if howmuchbet <= money and str(howmuchbet)[0] != '-' and money >= 0:
                slot = []
                aaa = 0
                bbb = 0
                ccc = 0
                with open('slots.txt', 'r') as brr:
                    for line in brr:
                        slot.append(line[:-1])
                slot.pop()  # the end one is alwasy blank fsr
                id = await message.channel.send('Gambling is addiction. so feed it')
                for i in range(5):
                    await asyncio.sleep(i / 7)
                    aaa = random.randint(0, len(slot) - 1)  # 3 different slots
                    bbb = random.randint(0, len(slot) - 1)
                    ccc = random.randint(0, len(slot) - 1)
                    emb = embedMake(["Your Spin", ">:" + str(slot[aaa]) + str(slot[bbb]) + str(slot[ccc]) + ":<"],
                                    title='Moogas Cowsino', color=0x00D2FF)
                    await id.edit(embed=emb)
                if aaa == bbb and bbb == ccc:
                    await message.channel.send('YOU WON BIGGGGG \n+' + str(howmuchbet * 10))
                    jason_it(authorid, 'cowsino.json', money + howmuchbet * 10)
                elif aaa == bbb or bbb == ccc or aaa == ccc:
                    await message.channel.send('You win participation prize\n +' + str(howmuchbet * 2))
                    jason_it(authorid, 'cowsino.json', money + howmuchbet * 2)
                else:
                    await message.channel.send('lost money at cowsino\n -' + str(howmuchbet))
                    jason_it(authorid, 'cowsino.json', money - howmuchbet)
            else:
                if money < 0:
                    await message.channel.send('U BROKE BISH NO GAMBLE FOR U')
                else:
                    await message.channel.send('NO BETTING ABSURD AMOUNTS FOOL')
        elif message.content.startswith(prefix + cmd[20][0]):
            with open('cowsino.json', 'r') as countr:
                prefixes = json.load(countr)
            if str(message.author.id) in prefixes:
                mony = prefixes[str(message.author.id)]
                mony = int(mony)
            else:
                jason_it(message.author.id, 'cowsino.json', 0)
                await message.channel.send('New account made')
                return
            status = ''
            if mony < 0:
                status = 'broke'
            elif mony > 10000:
                status = 'rich'
            elif mony > 1000:
                status = 'good'
            else:
                status = 'none'
            emb = embedMake(["Your Bal:", "```$" + str(mony) + "```"], ["Your $tatus:", "```" + str(status) + "```"],
                            title='$Check How Rich You Are$', color=0x00D2FF)
            await message.channel.send(embed=emb)
        elif message.content.startswith(prefix + cmd[21][0]):
            await message.channel.send('‎‎\n'*6)
        elif message.content.startswith(prefix + cmd[22][0]):
            with open('cowsino.json', 'r') as countr:
                prefixes = json.load(countr)
            if str(message.author.id) in prefixes:
                mony = int(prefixes[str(message.author.id)])
            else:
                jason_it(message.author.id, 'cowsino.json', 0)
                await message.channel.send('New account made')
                return
            work = random.randint(100, 700)
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
        elif message.content.startswith(prefix + cmd[24][0]):
            emb = embedMake(["Prefix:", '\n `' + prefix + "buy item`"], arraytoembd=upgradesPassives, title="Buy",
                            desc="The white market for passive income",
                            color=0x00D2FF)
            await message.channel.send(embed=emb)
        elif message.content.startswith(prefix + cmd[25][0]):
            target = int(getMsg(len(prefix) + len(cmd[25][0]) + 1, message.content, True))
            with open('cowsino.json', 'r') as countr:
                prefixes = json.load(countr)
            mony = 0
            money = 0
            if str(message.author.id) in prefixes and str(target) in prefixes:
                mony = int(prefixes[str(message.author.id)])
                money = int(prefixes[str(target)])
            elif str(message.author.id) not in prefixes:
                jason_it(message.author.id, 'cowsino.json', 0)
                await message.channel.send('New account made')
                return
            elif str(target) not in prefixes:
                await message.channel.send("target is not found")
                return
            else:
                return
            if mony >= 1000:
                jason_it(message.author.id, 'cowsino.json', mony - 1000)
                jason_it(target, 'cowsino.json', money + 1000)
                await message.channel.send("Sent funds to "+str(target))
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