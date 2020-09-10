import actual_game
import discord
import json
import string
import random
import asyncio
import math
import os

cmd = [
    ['help',
     'usage: help [category] shows help  (this message). categories: game (commands for game creation), friend (friend requests and remove), play (how to play the actual game)'],
    ['about', 'usage: about. shows info (version... credits... desc...)'],
    ['how to play', 'usage: how to play. shows all the tips to getting started']
]
gameCmd = [
    ['create', 'usage: create [server/global (Scope)]. creates new mooder moostery game (shorthand: -mc[pu/pr])'],
    ['join', 'usage: join [true/false (Queue)]. joins game with code (use at dm), [Queue: True/False (Queues you into '
             'random '
             'available games)]'],
    ['invite', 'usage: invite [player id/mention] invites the player to a game'],
    ['kick', 'usage: kick [player id/mention] kicks person from room (if you are host)']
]

inGameCmd = [
    ['leave', 'leaves the game (in the middle of it), if you are the murder, they will auto-win'],
    ['pm', 'pm [player id], anonymously send a message to one player or `pm ALL` to send to all']
]
#    ['kill', 'kill [playerid], kills the player (if you are murder)'], ['buy', 'buy [offerid], buys offer from market'],

friendCmd = [
    ['friend list', 'usage: friend list. shows the lists of your friends'],
    ['friend request', 'usage: friend request [player id/mention]. friend requests the person (bot will dm them)'],
    ['friend remove', 'usage: friend remove [player id/mention]. removes the person from your friends list (silently)']
]

# print(os.listdir(os.getcwd()))
v = '0.1.2'
key = []
with open('key.txt', 'r') as b:
    for line in b:
        key.append(line[:-1])  # need to add a extra char
key = str("".join(key))
client = discord.Client()
prefix = '-moostery '  # default prefix


async def makeGame(pubpriv, payload):
    a = payload.id
    b = payload.author.id
    target = payload.author
    author = payload.author.id
    if pubpriv:
        # public
        emb = await embedMake(
            ["Game Code (for ppl in other servers):", '\n `' + str(a) + "`"],
            ["Users queued:", client.get_user(int(b))],
            title='New Table Created!',
            desc='Game type: 🔓, Public',
            thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
            footer="If you are the host, press the '☑️' to start game or '❌' to cancel!, Press '🚪' to join/leave the game")
        emoji = await payload.channel.send(embed=emb)
    else:
        emb = await embedMake(
            ["Game Code (for ppl in other servers): ", '\n `' + str(a) + "`"],
            ["Users queued:", client.get_user(int(b))],
            title='New Room Made!',
            desc='Game type: 🔒, Private',
            thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
            footer='Invite people to play!')
        emoji = await target.send(embed=emb)
    await emoji.add_reaction('☑️')
    await emoji.add_reaction('❌')
    if pubpriv:
        await emoji.add_reaction('🚪')
    jason_it(str(emoji.id), 'games.json', str(author))

    def check(reaction, user):
        return str(reaction.emoji) and user

    while True:
        try:
            reaction, user = await client.wait_for('reaction_add', timeout=30.0, check=check)
        except asyncio.TimeoutError:
            emb = await embedMake(
                title='The Game Has Timed Out',
                desc='This game has timed out!',
                thumbnail='https://media.discordapp.net/attachments/747159474753503343/749021318011420682/costume9.png',
                footer='use `-moostery create` to make a new game'
            )
            await emoji.edit(embed=emb)
        else:
            if str(user) == str(client.get_user(int(author))):
                if str(reaction) == '☑️' or str(reaction) == '❌':
                    with open("games.json", 'r') as brr:
                        activegames = json.load(brr)
                    if str(reaction) == '☑️':
                        if len(activegames[str(emoji.id)]) > 1 and type(
                                activegames[str(emoji.id)]) != str:
                            await actual_game.startGame(payload, client, activegames, emoji.id, pubpriv)
                            break
                        else:
                            emb = await embedMake(
                                ["You do not have enough people to start this game",
                                 "\n Invite your friends with this game code:`" + str(emoji.id) + '`'],
                                title='Invalid Request',
                                thumbnail='https://media.discordapp.net/attachments/747159474753503343/749021318011420682/costume9.png',
                                desc='Sorry!',
                                footer='Host your own game and send invites to friends!')
                            await client.get_user(int(author)).send(embed=emb)
                    elif str(reaction) == '❌':
                        await actual_game.noGame(payload, client, prefix, activegames, emoji.id, pubpriv)
                        return


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
    imgfile = kwargs.get('imgf', None)
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
    if imgfile is not None:
        a = ''.join('attachment://' + str(imgfile))
        embed.set_image(url=a)
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
        if str(message.author.id) in friend and len(friend[str(message.author.id)]) != 0:
            friendo = friend[str(message.author.id)]
            arraynewfriend = []
            if type(friendo) != str:
                for i in range(len(friendo)):
                    arraynewfriend.append(friendo[i])
            else:
                arraynewfriend.append(friendo)
            emb = await embedMake(arraytoembdt=arraynewfriend, title='Friends List',
                                  desc='All your friends here',
                                  footer='~~ still shipping until the end of time -Cowland ~~')
            await message.channel.send(embed=emb)
        else:
            emb = await embedMake(['You have no friends', 'LOL'], title='Friends List',
                                  desc='All your friend- oh wait...',
                                  footer='get rekt')
            await message.channel.send(embed=emb)
    elif message.content.startswith(prefix + friendCmd[1][0]) or message.content.startswith(prefix + friendCmd[2][0]):
        idofdmtarget = message.author.id
        if message.content.startswith(prefix + friendCmd[1][0]):
            target = getMsg(len(prefix) + len(friendCmd[1][0]) + 1, message.content, True)
        else:
            target = getMsg(len(prefix) + len(friendCmd[2][0]) + 1, message.content, True)
        target = target.replace("<", "")  # if you sent in mention
        target = target.replace(">", "")
        target = target.replace("@", "")
        target = target.replace("&", "")
        target = target.replace("!", "")
        try:
            a = client.get_user(int(target))
            if a is None:
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
            if str(a.id) not in friend[str(message.author.id)] and str(a.id) != str(
                    message.author.id):  # not self lol
                embsent = await embedMake(["To:", '\n `' + str(a) + "`"], title='Friend Request',
                                          desc='Sent Friend Request ('
                                               'You will get dm if '
                                               'they accept)',
                                          footer='always friend good players!')
                await message.author.send(embed=embsent)
                emb = await embedMake(["From:", '\n `' + str(message.author) + "`"], title='Friend Request',
                                      desc='Pending Friend '
                                           'Request (click "✅" to accept, it will expire in 3 minutes)',
                                      footer='beware of strangers online!')
                emoji = await a.send(embed=emb)
                await emoji.add_reaction("✅")
                await asyncio.sleep(1)

                def check(reaction, user):
                    return str(reaction.emoji) and user

                try:
                    reaction, user = await client.wait_for('reaction_add', timeout=180.0, check=check)
                except asyncio.TimeoutError:
                    emb = await embedMake(
                        ["This friend request from " + str(message.author) + " has timed out.",
                         "\n You can do '-moostery friend request @mention' to re-friend them`"],
                        title='Request from ' + str(client.get_user(int(idofdmtarget))),
                        desc='Sorry!',
                        thumbnail='https://media.discordapp.net/attachments/747159474753503343/749021318011420682/costume9.png',
                        footer='Friend them back! You type the cmd rn in DM!'
                    )
                    await emoji.edit(embed=emb)
                else:
                    if str(reaction) == '✅':
                        with open("friend.json", 'r') as brr:
                            friend = json.load(brr)
                        if str(idofdmtarget) in friend:
                            friendo = friend[str(idofdmtarget)]
                            arraynewfriend = []
                            if type(friendo) != str:
                                for i in range(len(friendo)):
                                    arraynewfriend.append(friendo[i])
                            else:
                                arraynewfriend.append(friendo)
                            arraynewfriend.append(str(target))
                            jason_it(str(idofdmtarget), 'friend.json', arraynewfriend)
                        else:
                            jason_it(str(idofdmtarget), 'friend.json', str(target))
                        if str(target) in friend:
                            friendt = friend[str(target)]
                            arraynewfriend = []
                            if type(friendt) != str:
                                for i in range(len(friendt)):
                                    arraynewfriend.append(friendt[i])
                            else:
                                arraynewfriend.append(friendt)
                            arraynewfriend.append(str(idofdmtarget))
                            jason_it(str(target), 'friend.json', arraynewfriend)
                        else:
                            jason_it(str(target), 'friend.json', str(idofdmtarget))
                        selfperson = client.get_user(int(target))
                        tgt = client.get_user(int(idofdmtarget))
                        emb = await embedMake(
                            ["You are now friends with:", '\n `' + str(selfperson) + "`"],
                            title='Friend Request Accepted!',
                            desc='Congratulations! ',
                            footer='I ship')
                        await tgt.send(embed=emb)
                        emb = await embedMake(
                            ["You are now friends with:", '\n `' + str(tgt) + "`"],
                            title='Friend Request Accepted!',
                            desc='Congratulations! ',
                            footer='I ship')
                        await selfperson.send(embed=emb)
            else:
                emb = await embedMake(
                    title='Friend Request - ERROR',
                    desc='Error! User is already friends with you! (or you friended yourself)',
                    footer='and I ship still...')
                await message.author.send(embed=emb)
        elif message.content.startswith(prefix + friendCmd[2][0]):
            if str(a.id) in friend[str(message.author.id)] and str(a.id) != str(
                    message.author.id):
                for i in range(len(friend[str(message.author.id)])):
                    if str(a.id) == friend[str(message.author.id)][i]:
                        friend[str(message.author.id)].pop(i)
                        break
                for i in range(len(friend[str(a.id)])):
                    if str(message.author.id) == friend[str(a.id)][i]:
                        friend[str(a.id)].pop(i)
                        break
                out_file = open("friend.json", "w")
                json.dump(friend, out_file, indent=4)
                out_file.close()
                embsent = await embedMake(
                    ["Removed:", '\n `' + str(a) + "`"],
                    title='Friend Removed',
                    desc='You have removed this person from your friends list',
                    footer='dang, my ship for you two sank')
                await message.author.send(embed=embsent)
            else:
                emb = await embedMake(
                    title='Friend Request - ERROR',
                    desc='Error! User is not friends with you! (or you tried to unfriend yourself)',
                    footer='sad...')
                await message.author.send(embed=emb)
    # elif message.content.startswith(prefix + friendCmd[1][0]):


async def isGame(message):
    if message.content.startswith(prefix + gameCmd[0][0]) or message.content.startswith("-mc"):
        if message.content.startswith(prefix):
            type = getMsg(len(prefix) + len(gameCmd[0][0]) + 1, message.content, True)
        else:
            type = getMsg(len('-mc'), message.content, True)
            type = 'public' if type == 'pu' else 'private' if type == 'pr' else 'none'
        if type == 'private' or message.guild is None:
            if message.guild is None and type == 'public':
                emb = await embedMake(title='No Public!!!!',
                                      thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                                      desc='No public games in DM. Make one in a server',
                                      footer='sorry! but... who can even join you in a dm?')
                await message.channel.send(embed=emb)
            await makeGame(False, message)
        elif type == 'public':
            await makeGame(True, message)
        else:
            personid = message.author.id
            emb = await embedMake(["Game Creation:", "Click on the reaction to make a game (times out in 30 seconds)"],
                                  title='New Moorder Moostery Game!',
                                  thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                                  desc='Find out who\'s the killer and stop them before its too late!',
                                  footer='🔒: makes a private game 🔓:makes a public game')
            emoji = await message.channel.send(embed=emb)
            await emoji.add_reaction('🔒')
            await emoji.add_reaction('🔓')
            await emoji.add_reaction('❌')
            await asyncio.sleep(1)

            def check(reaction, user):
                return str(reaction.emoji) and user

            while True:
                try:
                    reaction, user = await client.wait_for('reaction_add', timeout=30.0, check=check)
                except asyncio.TimeoutError:
                    emb = await embedMake(
                        title='The Game Has Timed Out',
                        desc='This game has timed out!',
                        thumbnail='https://media.discordapp.net/attachments/747159474753503343/749021318011420682/costume9.png',
                        footer='use `-moostery create` to make a new game'
                    )
                    await emoji.edit(embed=emb)
                else:
                    if str(user) == str(client.get_user(int(personid))):
                        if str(reaction) == '🔒':
                            await client.http.delete_message(emoji.channel.id, emoji.id)
                            await makeGame(False, message)
                        elif str(reaction) == '🔓':
                            await client.http.delete_message(emoji.channel.id, emoji.id)
                            await makeGame(True, message)
                        else:
                            emb = await embedMake(
                                title='Cancelled!',
                                desc='Game creation cancelled!',
                                thumbnail='https://media.discordapp.net/attachments/747159474753503343/749021318011420682/costume9.png',
                                footer='use `-moostery create` to make a new game'
                            )
                            await emoji.edit(embed=emb)
                        break


@client.event
async def on_raw_reaction_add(payload):
    if payload.user_id == client.user.id:
        return

    with open("games.json", 'r') as brr:
        activegames = json.load(brr)

    if payload.emoji.name == '🚪':
        if str(payload.message_id) in activegames:
            if str(payload.user_id) not in activegames[str(payload.message_id)]:
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
                values = []
                ara = []
                if type(activegames[str(payload.message_id)]) != str:
                    for i in range(len(activegames[str(payload.message_id)])):
                        ara.append(activegames[str(payload.message_id)][i])
                        values.append(str(client.get_user(int(activegames[str(payload.message_id)][i]))))
                else:
                    ara.append(activegames[str(payload.message_id)])
                    values.append(str(client.get_user(int(activegames[str(payload.message_id)]))))
                emb = await embedMake(['People sat at the table', 'Name and ID'],
                                      title='Joined Game',
                                      arraytoembdtt=ara,
                                      thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                                      valuett=values,
                                      desc='You have joined the table \n Host: ' + str(
                                          client.get_user(int(ara[0]))) + '\n Game Code: `' + str(
                                          payload.message_id) + '`',
                                      footer='YAY! Have fun!!! I can\'t... because I\'m just a footer...'
                                      )
                await client.get_user(int(payload.user_id)).send(embed=emb)


@client.event
async def on_raw_reaction_remove(payload):
    if payload.user_id == client.user.id:
        return
    if payload.emoji.name == '🚪':
        with open("games.json", 'r') as brr:
            activegames = json.load(brr)
        if str(payload.message_id) in activegames:
            if str(payload.user_id) in activegames[str(payload.message_id)]:
                if activegames[str(payload.message_id)] != str(payload.user_id) and \
                        activegames[str(payload.message_id)][0] != str(payload.user_id):  # checks for if u r room owner
                    # pr#int(activegames)
                    for i in range(len(activegames[str(payload.message_id)])):
                        if str(payload.user_id) == activegames[str(payload.message_id)][i]:
                            activegames[str(payload.message_id)].pop(i)
                            break
                    out_file = open("games.json", "w")
                    json.dump(activegames, out_file, indent=4)
                    out_file.close()
                    await actual_game.joinGame(payload, client)
                    emb = await embedMake(
                        title='Left Game',
                        thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                        desc='You have left the table. GG',
                        footer='sad. what a bummer.'
                    )
                    await client.get_user(int(payload.user_id)).send(embed=emb)


async def isOther(message):  # help and other stuff
    global prefix
    if message.content.startswith(prefix + cmd[0][0]):
        msgcontent = getMsg(len(prefix) + len(cmd[0][0]) + 1, message.content, True)
        if msgcontent == 'game':
            typea = 'Game'
            a = gameCmd
            imag = 'https://images-ext-1.discordapp.net/external/c7hVi29ta2o9hiSe9b3cwIDVklFnbtsdbUXaCh2-Obc/https/media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png'
        elif msgcontent == 'friend':
            typea = 'Friend'
            a = friendCmd
            imag = 'https://media.discordapp.net/attachments/747159474753503343/748735404810698792/unknown.png'
        elif msgcontent == 'play':
            typea = 'Play'
            a = inGameCmd
            imag = 'https://images-ext-1.discordapp.net/external/c7hVi29ta2o9hiSe9b3cwIDVklFnbtsdbUXaCh2-Obc/https/media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png'
            emb = await embedMake(['Splat!', 'There\'s a killer in this town...'],
                                  title='It was a ordinary night in the city...',
                                  thumbnail='https://media.discordapp.net/attachments/696699604003061784/748557547501256775/pfp2.png',
                                  desc='until...',
                                  img='https://media.discordapp.net/attachments/696699604003061784/748568734578376814/business_man_colored2.png'
                                  )
            await message.author.send(embed=emb)
            emb = await embedMake(
                title='How To Play',
                thumbnail='https://images-ext-2.discordapp.net/external/BAeOdPzafgkr43ervKSOByd063AO0MeENKlda4_FHW0/https/media.discordapp.net/attachments/724362941792649287/747969861061312632/mat6.png',
                desc='This G-Doc shows everything you need to get started: https://bit.ly/2ExNTIr',
                footer='i gave up on multipage and read from file'
            )
            await message.author.send(embed=emb)
        else:
            typea = 'General'
            a = cmd
            imag = 'https://cdn.discordapp.com/attachments/663150753946402820/747235632765599834/Screen_Shot_2020-08-23_at_2.52.15_PM.png'
        emb = await embedMake(["Prefix", '\n `' + prefix + "`"], arraytoembd=a,
                              img=str(imag),
                              title="Help - " + str(typea),
                              desc="Ayy... Slidin into yo dms. Here is the list of commands",
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
                                 ["Discord Invite Link:", "https://discord.gg/k2nE2u4"],
                                 ["Repo (live_events/discord_bots/moosterybot):",
                                  "https://github.com/weakunix/python_git"],
                                 title="About Murder Moostery",
                                 img='https://media.discordapp.net/attachments/696699604003061784/747566312104001647/Screen_Shot_2020-08-24_at_5.20.21_PM.png',
                                 desc="The game inspired by Town of Salem",
                                 color=0x00D2FF,
                                 footer='the pen is mightier than the sword',
                                 thumbnail='https://cdn.discordapp.com/attachments/663150753946402820/747235632765599834/Screen_Shot_2020-08-23_at_2.52.15_PM.png'
                                 )
        await message.channel.send(embed=abtemb)


async def isinGame(message):
    if message.content.startswith(prefix + inGameCmd[0][0]):
        a = getMsg(len(prefix) + len(inGameCmd[0][0]) + 1, message.content, True)
        if a == '':
            emb = await embedMake(
                title='Leaving game',
                thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                desc='Confirm Leaving Game by typing -moostery leave [gamecode]',
                footer='sad'
            )
            await message.author.send(embed=emb)
        else:
            with open("games.json", 'r') as brr:
                activegames = json.load(brr)
            with open("roles.json", 'r') as brr:
                role = json.load(brr)
            if str(a) in activegames:
                if str(message.author.id) in activegames[str(a)]:
                    for i in range(len(activegames[str(a)])):
                        if str(message.author.id) == activegames[str(a)][i]:
                            activegames[str(a)].pop(i)
                            role[str(a)].pop(i)
                            break
                else:
                    emb = await embedMake(
                        title='Check Your GameCode!',
                        thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                        desc='Doesn\'t seem like you are in this game!',
                        footer='use `-moostery create` to make a new game'
                    )
                    await message.author.send(embed=emb)
                    return
            else:
                emb = await embedMake(
                    title='Check Your Command!',
                    thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                    desc='Doesn\'t seem like you are in a game!',
                    footer='use `-moostery create` to make a new game'
                )
                await message.author.send(embed=emb)
                return
            out_file = open("games.json", "w")
            json.dump(activegames, out_file, indent=4)
            out_file.close()
            out_file = open("roles.json", "w")
            json.dump(role, out_file, indent=4)
            out_file.close()
            emb = await embedMake(
                title='Left Game',
                thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                desc='You have left the table in the middle of a game. GG',
                footer='what a bummer.'
            )
            await message.author.send(embed=emb)
    elif message.content.startswith(prefix + inGameCmd[1][0]):
        idAndMsg = getMsg(len(prefix) + len(inGameCmd[1][0]) + 1, message.content, True).split()
        if len(idAndMsg) == 1:
            emb = await embedMake(
                title="Invalid Command!",
                desc="Format: `-moostery pm [player ID] [message]`"
            )
            await message.author.send(embed=emb)
            return
        else:
            with open("games.json", 'r') as brr:
                activegames = json.load(brr)
            for i in range(len(list(activegames.values()))):
                if str(idAndMsg[0]) in list(activegames.values())[i] or str(idAndMsg[0]) == "all":
                    if str(message.author.id) in list(activegames.values())[i]:
                        a = []
                        for ii in range(1, len(idAndMsg)):
                            a.append(idAndMsg[ii])
                        a = " ".join(a)
                        emb = await embedMake(
                            title="Ahem! You've Got Mail! From Anonymous Person in your game!",
                            desc='`' + str(a) + '`',
                            footer="blackmail happens sometimes.",
                            thumbnail="https://media.discordapp.net/attachments/713115546786463784/750528205806502029/costume16.png"
                        )
                        if str(idAndMsg[0]) != "all":
                            emb2 = await embedMake(
                                title="Message Sent!",
                                desc='Sent `' + str(a) + '`\nTo: `' + str(client.get_user(int(idAndMsg[0]))) + '`',
                                thumbnail="https://media.discordapp.net/attachments/713115546786463784/750528205806502029/costume16.png"
                            )
                        else:
                            emb2 = await embedMake(
                                title="Message Sent!",
                                desc='Sent `' + str(a) + '`\nTo: `@everyone`',
                                thumbnail="https://media.discordapp.net/attachments/713115546786463784/750528205806502029/costume16.png"
                            )
                        if str(idAndMsg[0]) != "all":
                            await client.get_user(int(idAndMsg[0])).send(embed=emb)
                            await client.get_user(int(message.author.id)).send(embed=emb2)
                        else:
                            for eye in list(activegames.values())[i]:
                                if str(eye) != str(message.author.id):
                                    await client.get_user(int(eye)).send(embed=emb)
                                else:
                                    await client.get_user(int(eye)).send(embed=emb2)
                        break
                    else:
                        emb = await embedMake(
                            title="Invalid Command!",
                            desc="Target not in **your** game!"
                        )
                        await message.author.send(embed=emb)
                else:
                    emb = await embedMake(
                        title="Invalid Command!",
                        desc="Target not in game!"
                    )
                    await message.author.send(embed=emb)


@client.event
async def on_message(message):
    # await actual_game.playGame(message)
    if message.author == client.user:
        return
    if message.guild is None:  # in dm
        if not message.content.startswith(prefix):
            emb = await embedMake(["Prefix is:", '`' + str(prefix) + '`'],
                                  title='About this bot',
                                  desc='it seems like you have DM\'d the bot with a message!',
                                  footer="type '" + str(prefix) + "help' to get commands")
            await message.author.send(embed=emb)
        else:
            await isinGame(message)
    await isOther(message)  # help, meta...
    await isFriend(message)  # friend
    await isGame(message)  # game


@client.event
async def on_ready():
    print('\033[0m~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')
    print('\033[92m Logged as {0.user}'.format(client))
    print('\033[0m~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')
    await client.change_presence(
        activity=discord.Activity(name='for ' + str(prefix), type=discord.ActivityType.watching))


def clearFiles():
    os.remove('games.json')
    w = open('games.json', 'w+')
    w.write('{}')
    w.close()
    os.remove('roles.json')
    w = open('roles.json', 'w+')
    w.write('{}')
    w.close()


if __name__ == '__main__':
    clearFiles()
    client.run(key)
