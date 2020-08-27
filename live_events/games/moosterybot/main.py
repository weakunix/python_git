import actual_game
import discord
import json
import string
import random
import asyncio
import math

cmd = [
    ['help', 'usage: help [category] shows help  (this message). categories: game, friend'],
    ['about', 'usage: about. shows info (version... credits... desc...)'],
    ['meta', 'usage: meta [gun]. shows meta of weapons/items. use "meta list" for a list of weapons'],
    ['prefix', 'usage: -moostery prefix [new prefix]. sets new prefix (always -moostery as prefix for this)']
]
gameCmd = [
    ['create', 'usage: create. creates new mooder moostery game'],
    ['join', 'usage: join. joins game with code (use at dm)'],
    ['invite', 'usage: invite [player id/mention] invites the player to a game'],
    ['kick', 'usage: kick [player id/mention] kicks person from room (if you are host)'],
    ['how to play', 'usage: how to play. shows all the tips to getting started']
]

friendCmd = [
    ['friend list', 'usage: friend list. shows the lists of your friends'],
    ['friend request', 'usage: friend request [player id/mention]. friend requests the person (bot will dm them)'],
    ['friend remove', 'usage: friend remove [player id/mention]. removes the person from your friends list (silently)']
]

roles = [
    ["killer", ""],
    ["detective", ""],
    ["medic", ""],
    ["dash the deer hunter", ""],
    ["workhorse parents", "choose a person to stay up all night"],
    ["cupid man the stupid man", ""],
    ["", ""]
]

v = '0.0.3'
key = []
with open('key.txt', 'r') as b:
    for line in b:
        key.append(line[:-1])  # need to add a extra char
key = str("".join(key))
client = discord.Client()
prefix = '-moostery '  # default prefix


async def makeGame(pubpriv, payload, fromline):
    gamecode = ''.join(random.choice(string.ascii_letters) for i in range(5))  # 5 number game code
    emoji = ''
    if pubpriv:
        # public
        emb = await embedMake(
            ["Game Code (for ppl in other servers):", '\n `' + str(gamecode) + "`"],
            title='New Room Made!',
            desc='Game type: 🔓, Public',
            thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
            footer="If you are the host, press the '☑️' to start game or '❌' to cancel!, Press '🚪' to join/leave the game")
        if not fromline:
            await client.http.delete_message(payload.channel_id, payload.message_id)
            wheretosend = client.get_channel(int(payload.channel_id))
            emoji = await wheretosend.send(embed=emb)  # def bugged here
            author = int(payload.user_id)
            ids = payload.message_id
        else:
            emoji = await payload.channel.send(embed=emb)
            author = payload.author.id
            ids = payload.id
        await emoji.add_reaction('☑️')
        await emoji.add_reaction('❌')
        await emoji.add_reaction('🚪')
    else:
        emb = await embedMake(
            ["Game Code:", '\n `' + str(gamecode) + "`"],
            title='New Room Made!',
            desc='Game type: 🔒, Private',
            thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
            footer='Invite people to play!')
        if not fromline:
            target = client.get_user(payload.user_id)
            ids = payload.message_id
            author = client.get_user(int(payload.user_id))
        else:
            target = payload.author
            author = payload.author.id
            ids = payload.id
        await target.send(embed=emb)
        # jason_it(emoji)
    '''game = json.load(open("games.json"))
    new = [obj for obj in game if [str(id)] != str(author)]
    with open('games.json', 'w') as brrr:
        json.dump(new, brrr, indent=4)'''
    jason_it(str(emoji.id), 'games.json', str(author))


def jason_it(whatindex, filename, msg):
    with open(filename, 'r') as brr:
        prefixes = json.load(brr)
    prefixes[str(whatindex)] = msg
    with open(filename, 'w') as brrr:
        json.dump(prefixes, brrr, indent=4)


async def embedMake(*args, **kwargs):  # makes an embedded element
    title = kwargs.get('title', None)
    desc = kwargs.get('desc', None)
    footer = kwargs.get('footer', None)
    img = kwargs.get('img', None)
    thumbnail = kwargs.get('thumbnail', None)
    author = kwargs.get('author', None)
    fieldarry = kwargs.get('arraytoembd', None)
    fieldarryt = kwargs.get('arraytoembdt', None)
    fieldarrytt = kwargs.get('arraytoembdtt', None)
    fieldarryttt = kwargs.get('valuett', None)

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
    if img is not None:
        embed.set_image(url=img)
    if fieldarry is not None:
        for i in range(len(fieldarry)):
            embed.add_field(name=prefix + str(fieldarry[i][0]), value="`" + str(fieldarry[i][1]) + "`", inline=False)
    if fieldarryt is not None:
        for i in range(len(fieldarryt)):
            username = client.get_user(int(fieldarryt[i]))
            embed.add_field(name='Name: ** ' + str(username) + ' **',
                            value="id: `" + str(fieldarryt[i]) + "`", inline=False)
    if fieldarrytt is not None and fieldarryttt:
        for i in range(len(fieldarrytt)):
            embed.add_field(name='Name: ** ' + str(fieldarryttt[i]) + ' **',
                            value="id: `" + str(fieldarrytt[i]) + "`", inline=True)
    if footer is not None:
        embed.set_footer(text=footer)
    if author is not None:
        embed.set_author(name=author)
    if thumbnail is not None:
        embed.set_thumbnail(url=thumbnail)
    return embed


def getMsg(lenpfx, msg, string):
    ret = []
    for i in range(lenpfx, len(msg)):
        ret.append(str(msg[i]))
    if string:
        ret = "".join(ret)
    return ret


async def isFriend(message):
    if message.content.startswith(prefix + friendCmd[0][0]):  # firend list
        with open("friend.json", 'r') as brr:
            friend = json.load(brr)
        if str(message.author.id) in friend:
            friendo = friend[str(message.author.id)]
            arraynewfriend = []
            if type(friendo) != str:
                for i in range(len(friendo)):
                    arraynewfriend.append(friendo[i])
                emb = await embedMake(arraytoembdt=arraynewfriend, title='Friends List',
                                      desc='All your friends here \n========================',
                                      footer='~~ still shipping until the end of time -Cowland ~~')
            else:
                arraynewfriend.append(friendo)
                emb = await embedMake(['.', arraynewfriend], title='Friends List',
                                      desc='All your friends here \n========================',
                                      footer='~~ still shipping until the end of time -Cowland ~~')
            await message.channel.send(embed=emb)
        else:
            emb = await embedMake(['You have no friends', 'LOL'], title='Friends List',
                                  desc='All your friend- oh wait... \n========================',
                                  footer='get rekt')
            await message.channel.send(embed=emb)
    elif message.content.startswith(prefix + friendCmd[1][0]) or message.content.startswith(prefix + friendCmd[2][0]):
        idofdmtarget = message.author.id
        target = getMsg(len(prefix) + len(friendCmd[1][0]) + 1, message.content, True)
        target = target.replace("<", "")
        target = target.replace(">", "")
        target = target.replace("@", "")
        target = target.replace("&", "")
        target = target.replace("!", "")
        try:
            target = client.get_user(int(target))
            if target is None:
                embedurbad = await embedMake(title='Friend Request - ERROR',
                                             desc='`Error! No person found by that alias! Check the ID again!`',
                                             footer='Bad ID!')
                await message.author.send(embed=embedurbad)
                return
        except:
            embedurbad = await embedMake(title='Friend Request - ERROR',
                                         desc='`Error! No person found by that alias! Check the ID again!`',
                                         footer='You typed a string for the ID mate')
            await message.author.send(embed=embedurbad)
            return
        with open("friend.json", 'r') as brr:
            friend = json.load(brr)
        if message.content.startswith(prefix + friendCmd[1][0]):
            if str(target.id) not in friend[str(message.author.id)] and str(target.id) != str(
                    message.author.id):  # not self lol
                embsent = await embedMake(["To:", '\n `' + str(target) + "`"], title='Friend Request',
                                          desc='Sent Friend Request ('
                                               'You will get dm if '
                                               'they accept)',
                                          footer='always friend good players!')
                await message.author.send(embed=embsent)
                emb = await embedMake(["From:", '\n `' + str(message.author) + "`"], title='Friend Request',
                                      desc='Pending Friend '
                                           'Request (click "✅" to accept, ignore to ignore)',
                                      footer='beware of strangers online!')
                emoji = await target.send(embed=emb)
                jason_it(str(emoji.id), 'pending_requests.json', str(idofdmtarget))
                await emoji.add_reaction("✅")
            else:
                emb = await embedMake(
                    title='Friend Request - ERROR',
                    desc='Error! User is already friends with you! (or you friended yourself)',
                    footer='and I ship still...')
                await message.author.send(embed=emb)
        else:
            if str(target.id) in friend[str(message.author.id)] and str(target.id) != str(
                    message.author.id):  # not self lol
                embsent = await embedMake(["Removed:", '\n `' + str(target) + "`"],
                                          title='Friend Removed',
                                          desc='You have removed this person from your friends list',
                                          footer='dang, my ship for you two sank')
                await message.author.send(embed=embsent)
            else:
                emb = await embedMake(
                    title='Friend Request - ERROR',
                    desc='Error! User is not friends with you! (or you unfriended yourself)',
                    footer='sad...')
                await message.author.send(embed=emb)
    # elif message.content.startswith(prefix + friendCmd[1][0]):


async def isGame(message):
    if message.content.startswith(prefix + gameCmd[0][0]):
        type = getMsg(len(prefix) + len(gameCmd[0][0]) + 1, message.content, True)
        if type == 'private':
            await makeGame(False, message, True)
        elif type == 'public':
            await makeGame(True, message, True)
        else:
            personid = message.author.id
            emb = await embedMake(["Game Creation:", "Click on the reaction to make a game"],
                                  title='New Moorder Moostery Game!',
                                  thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                                  desc='Find out who\'s the killer and stop them before its too late!',
                                  footer='🔒: makes a private game 🔓:makes a public game')
            emoji = await message.channel.send(embed=emb)
            await emoji.add_reaction('🔒')
            await emoji.add_reaction('🔓')
            jason_it(str(emoji.id), 'games.json', str(personid))
    elif message.content.startswith(prefix + gameCmd[4][0]):
        emb = await embedMake(
            title='How To Play',
            thumbnail='https://images-ext-2.discordapp.net/external/BAeOdPzafgkr43ervKSOByd063AO0MeENKlda4_FHW0/https/media.discordapp.net/attachments/724362941792649287/747969861061312632/mat6.png',
            desc='This G-Doc shows everything you need to get started: https://bit.ly/2ExNTIr',
            footer='i gave up on multipage and read from file'
        )
        await message.channel.send(embed=emb)
    elif message.content.startswith(prefix + 'roles'):
        pass
        '''roles = []
        messages = []
        messagecountperln = []
        message_send = []
        with open('./files/roles.txt', 'r') as b:
            for line in b:
                roles.append(line[:-1])  # need to add a extra char#roles =
                messagecountperln.append(len(b.readline()))
        brek = False
        for x in range(len(messagecountperln)):
            for y in range(len(roles[x])):
                message_send.append(roles[x][y])
        message_send = "".join(message_send)
        '# under is bugged
        divisible = math.ceil(len(message_send) / 1990)
        messagePart = []
        countr = 1990
        cc = 0
        c = 0
        for i in range(divisible):
            while countr > 0:
                if countr - int(messagecountperln[c]) >= 0 and c < len(messagecountperln) - 1:
                    messagePart.append(roles[c])
                    countr -= int(messagecountperln[c])
                    c += 1
                else:
                    countr = 0
            else:
                countr = 1990
                await message.channel.send(str(str("".join(messagePart)).replace('==', '\n')))
                messagePart = []'''


@client.event
async def on_raw_reaction_add(payload):
    if payload.user_id == client.user.id:
        return
    if payload.guild_id is None and payload.emoji.name == "✅":  # in dm
        with open("pending_requests.json", 'r') as brr:
            acceptreq = json.load(brr)
        if str(payload.message_id) in acceptreq:
            target = acceptreq[str(payload.message_id)]
            with open("friend.json", 'r') as brr:
                friend = json.load(brr)
            if str(target) in friend:
                friendo = friend[str(target)]
                arraynewfriend = []
                if type(friendo) != str:
                    for i in range(len(friendo)):
                        arraynewfriend.append(friendo[i])
                else:
                    arraynewfriend.append(friendo)
                arraynewfriend.append(str(payload.user_id))
                jason_it(str(target), 'friend.json', arraynewfriend)
            else:
                jason_it(str(target), 'friend.json', str(payload.user_id))
            if str(payload.user_id) in friend:
                friendt = friend[str(payload.user_id)]
                arraynewfriend = []
                if type(friendt) != str:
                    for i in range(len(friendt)):
                        arraynewfriend.append(friendt[i])
                else:
                    arraynewfriend.append(friendt)
                arraynewfriend.append(str(target))
                jason_it(str(payload.user_id), 'friend.json', arraynewfriend)
            else:
                jason_it(str(payload.user_id), 'friend.json', str(target))
            target = client.get_user(int(target))
            selfperson = client.get_user(int(payload.user_id))
            emb = await embedMake(
                ["You are now friends with:", '\n `' + str(client.get_user(int(payload.user_id))) + "`"],
                title='Friend Request Accepted!',
                desc='Congratulations! ',
                footer='I ship')
            await client.http.delete_message(payload.channel_id, payload.message_id)
            await target.send(embed=emb)
            await selfperson.send(embed=emb)
    else:
        if payload.emoji.name == '🔒' or payload.emoji.name == '🔓':
            with open("games.json", 'r') as brr:
                activegames = json.load(brr)
            if str(payload.message_id) in activegames:
                if str(payload.user_id) == activegames[str(payload.message_id)]:
                    if payload.emoji.name == '🔒':
                        await makeGame(False, payload, False)
                    else:
                        await makeGame(True, payload, False)
        elif payload.emoji.name == '☑️' or payload.emoji.name == '❌' or payload.emoji.name == '🚪':
            with open("games.json", 'r') as brr:
                activegames = json.load(brr)
            if str(payload.message_id) in activegames:
                if str(payload.user_id) == activegames[str(payload.message_id)][0] or str(payload.user_id) == \
                        activegames[str(payload.message_id)]:  # if is host
                    if payload.emoji.name == '☑️':
                        await actual_game.startGame(payload, client)
                    elif payload.emoji.name == '❌':
                        await actual_game.noGame(payload, client, prefix)
                elif payload.emoji.name == '🚪':
                    gamestuff = activegames[str(payload.message_id)]
                    arraynewgames = []
                    if type(gamestuff) != str:
                        for i in range(len(gamestuff)):
                            arraynewgames.append(gamestuff[i])
                    else:
                        arraynewgames.append(gamestuff)
                    arraynewgames.append(str(payload.user_id))
                    jason_it(str(payload.message_id), 'games.json', arraynewgames)
                    await actual_game.joinGame(payload, client)


async def isOther(message):  # help and other stuff
    global prefix
    if message.content.startswith(prefix + cmd[0][0]):
        msgcontent = getMsg(len(prefix) + len(cmd[0][0]) + 1, message.content, True)
        if msgcontent == 'game':
            emb = await embedMake(["Prefix", '\n `' + prefix + "`"], arraytoembd=gameCmd,
                                  img='https://cdn.discordapp.com/attachments/663150753946402820/747235632765599834/Screen_Shot_2020-08-23_at_2.52.15_PM.png',
                                  title="Help - Game",
                                  thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                                  desc="Ayy... Slidin into yo dms. Here is the list of commands about the game",
                                  footer='the "blood" on sword is actually ketchup',
                                  color=0x00D2FF)
        elif msgcontent == 'friend':
            emb = await embedMake(["Prefix", '\n `' + prefix + "`"], arraytoembd=gameCmd,
                                  img='https://cdn.discordapp.com/attachments/663150753946402820/747235632765599834/Screen_Shot_2020-08-23_at_2.52.15_PM.png',
                                  title="Help - Friend",
                                  desc="Ayy... Slidin into yo dms. Here is the list of commands about friends",
                                  footer='the "blood" on sword is actually ketchup',
                                  thumbnail='https://media.discordapp.net/attachments/747159474753503343/747595752141881393/unknown.png',
                                  color=0x00D2FF)
        else:
            emb = await embedMake(["Prefix", '\n `' + prefix + "`"], arraytoembd=cmd,
                                  img='https://cdn.discordapp.com/attachments/663150753946402820/747235632765599834/Screen_Shot_2020-08-23_at_2.52.15_PM.png',
                                  title="Help - General",
                                  desc="Ayy... Slidin into yo dms. Here is the list of commands in general",
                                  footer='the "blood" on sword is actually ketchup',
                                  color=0x00D2FF)
        await message.author.send(embed=emb)
        await message.channel.send("> Help sent to " + message.author.mention + "'s DM. Please Check. ")
    elif message.content.startswith(prefix + cmd[1][0]):
        abtemb = await embedMake(["Version: ", '`' + str(v) + '`'],
                                 ["Developed by",
                                  '`' + str(client.get_user(369652997308809226)) + "` with help from `" + str(
                                      client.get_user(583755143074283531)) + "`"],
                                 ["Artwork by", '`' + str(client.get_user(369652997308809226)) + "` and `" + str(
                                     client.get_user(605125493120827413)) + '`'],
                                 ["Special Thanks To", '`' + str(client.get_user(333398956958810114)) + "` and `" + str(
                                     client.get_user(149491899240153088)) + '` for letting me "borrow" ideas'],
                                 title="About Murder Moostery",
                                 img='https://media.discordapp.net/attachments/696699604003061784/747566312104001647/Screen_Shot_2020-08-24_at_5.20.21_PM.png',
                                 desc="The game inspired by Town of Salem",
                                 color=0x00D2FF,
                                 footer='the pen is mightier than the sword',
                                 thumbnail='https://cdn.discordapp.com/attachments/663150753946402820/747235632765599834/Screen_Shot_2020-08-23_at_2.52.15_PM.png'
                                 )
        await message.channel.send(embed=abtemb)
    elif message.content.startswith(prefix + cmd[2][0]):
        pass
    elif message.content.startswith("-moostery " + cmd[3][0]):
        newPFX = getMsg(len("-moostery ") + len(cmd[3][0]) + 1, message.content, True)
        if newPFX != "default" and newPFX != '':
            prefix = newPFX + " "
        else:
            prefix = "-moostery "
        emb = await embedMake(
            title='Prefix Change',
            desc="New prefix: `" + str(prefix) + "`",
            color=0x00D2FF,
            footer='the command to change prefix is always `-moostery prefix [new prefix]`'
        )
        await message.channel.send(embed=emb)


@client.event
async def on_raw_reaction_remove(payload):
    pass


@client.event
async def on_message(message):
    if message.author == client.user:
        return
    if message.guild is None:  # in dm
        if not message.content.startswith(prefix):
            emb = await embedMake(["Prefix is:", '`' + str(prefix) + '`'],
                                  title='About this bot',
                                  desc='it seems like you have DM\'d the bot with a message!',
                                  footer="type '" + str(prefix) + "help' to get commands")
            await message.author.send(embed=emb)
    await isOther(message)  # help, meta...
    await isFriend(message)  # friend
    await isGame(message)  # game


@client.event
async def on_ready():
    print('\033[92m Logged as {0.user}'.format(client))
    await client.change_presence(
        activity=discord.Activity(name='for ' + str(prefix), type=discord.ActivityType.watching))


if __name__ == '__main__':
    client.run(key)
