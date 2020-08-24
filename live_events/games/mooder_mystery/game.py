import discord
import json

cmd = [
    ['help', 'usage: help [category] shows help  (this message). categories: game, friend'],
    ['about', 'usage: about. shows info (version... credits... desc...)'],
    ['meta', 'usage: meta [gun]. shows meta of weapons/items. use "meta list" for a list of weapons'],
]
gameCmd = [
    ['create', 'usage: create. creates new mooder moostery game'],
    ['abandon', 'usage: abandon. you abandons ship this game'],
    ['invite', 'usage: invite [player id] invites the player to a game'],
    ['kick', 'kicks person from room (if you are host)']
]

friendCmd = [
    ['friend list', 'usage: friend list. shows the lists of your friends'],
    ['friend request', 'usage: friend request [player id]. friend requests the person (bot will dm them)']
]
v = '0.1'
key = []
with open('key.txt', 'r') as b:
    for line in b:
        key.append(line[:-1])  # need to add a extra char
key = str("".join(key))
client = discord.Client()
prefix = '-moostery '  # default prefix


def jason_it(whatindex, filename, msg):
    with open(filename, 'r') as brr:
        prefixes = json.load(brr)
    prefixes[str(whatindex)] = msg
    with open(filename, 'w') as brrr:
        json.dump(prefixes, brrr, indent=4)


def embedMake(*args, **kwargs):  # makes an embedded element
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
    if img is not None:
        embed.set_image(url=img)
    if fieldarry is not None:
        for i in range(len(fieldarry)):
            embed.add_field(name=prefix + str(fieldarry[i][0]), value="`" + str(fieldarry[i][1]) + "`", inline=False)
    if fieldarryt is not None:
        for i in range(len(fieldarryt)):
            embed.add_field(name='Name: **' + str(client.get_user(int(fieldarryt[i]))) + '**',
                            value="id: `" + str(fieldarryt[i]) + "`", inline=False)
    if footer is not None:
        embed.set_footer(text=footer)
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
                emb = embedMake(arraytoembdt=arraynewfriend, title='Friends List',
                                desc='All your friends here \n========================',
                                footer='~~ still shipping until the end of time -Cowland ~~')
            else:
                arraynewfriend.append(friendo)
                emb = embedMake(['.', arraynewfriend], title='Friends List',
                                desc='All your friends here \n========================',
                                footer='~~ still shipping until the end of time -Cowland ~~')
            await message.channel.send(embed=emb)
        else:
            emb = embedMake(['You have no friends', 'LOL'], title='Friends List',
                            desc='All your friend- oh wait... \n========================',
                            footer='get rekt')
            await message.channel.send(embed=emb)
    elif message.content.startswith(prefix + friendCmd[1][0]):
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
                embedurbad = embedMake(title='Friend Request - ERROR',
                                       desc='`Error! No person found by that alias! Check the ID again!`',
                                       footer='Bad ID!')
                await message.author.send(embed=embedurbad)
                return
        except:
            embedurbad = embedMake(title='Friend Request - ERROR',
                                   desc='`Error! No person found by that alias! Check the ID again!`',
                                   footer='You typed a string for the ID mate')
            await message.author.send(embed=embedurbad)
            return
        embsent = embedMake(["To:", '\n `' + str(target) + "`"], title='Friend Request', desc='Sent Friend Request ('
                                                                                              'You will get dm if '
                                                                                              'they accept)',
                            footer='always friend good players!')
        await message.author.send(embed=embsent)
        emb = embedMake(["From:", '\n `' + str(message.author) + "`"], title='Friend Request', desc='Pending Friend '
                                                                                                    'Request (click "✅" to accept, ignore to ignore)',
                        footer='beware of strangers online!')
        emoji = await target.send(embed=emb)
        jason_it(str(emoji.id), 'pending_requests.json', str(idofdmtarget))
        await emoji.add_reaction("✅")
        '''else:
            emb = embedMake(
                            title='Friend Request',
                            desc='User is already friends with you! ',
                            footer='I ship still...')
            await message.author.send(embed=emb)'''


async def isGame(message):
    if message.content.startswith(prefix + gameCmd[0][0]):
        emb = embedMake(["Game Creation:", "Click on the reaction to make a game"], title='New Moorder Moostery Game!',
                            desc='Find out who\'s the killer and stop them before its too late!',
                            footer='🔒: makes a private game 🔓:makes a public game')
        emoji = await message.channel.send(embed=emb)
        await emoji.add_reaction('🔒')
        await emoji.add_reaction('🔓')


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
            emb = embedMake(["You are now friends with:", '\n `' + str(client.get_user(int(payload.user_id))) + "`"],
                            title='Friend Request Accepted!',
                            desc='Congratulations! ',
                            footer='I ship')
            await client.http.delete_message(payload.channel_id, payload.message_id)
            await target.send(embed=emb)
            await selfperson.send(embed=emb)
    else:
        return


async def isOther(message):  # help and other stuff
    if message.content.startswith(prefix + cmd[0][0]):
        msgcontent = getMsg(len(prefix) + len(cmd[0][0]) + 1, message.content, True)
        if msgcontent == 'game':
            emb = embedMake(["Prefix", '\n `' + prefix + "`"], arraytoembd=gameCmd,
                            img='https://cdn.discordapp.com/attachments/663150753946402820/747235632765599834/Screen_Shot_2020-08-23_at_2.52.15_PM.png',
                            title="Help - Game",
                            desc="Ayy... Slidin into yo dms. Here is the list of commands about the game",
                            footer='the blood on sword is actually ketchup',
                            color=0x00D2FF)
        elif msgcontent == 'friend':
            emb = embedMake(["Prefix", '\n `' + prefix + "`"], arraytoembd=gameCmd,
                            img='https://cdn.discordapp.com/attachments/663150753946402820/747235632765599834/Screen_Shot_2020-08-23_at_2.52.15_PM.png',
                            title="Help - Friend",
                            desc="Ayy... Slidin into yo dms. Here is the list of commands about friends",
                            footer='the blood on sword is actually ketchup',
                            color=0x00D2FF)
        else:
            emb = embedMake(["Prefix", '\n `' + prefix + "`"], arraytoembd=cmd,
                            img='https://cdn.discordapp.com/attachments/663150753946402820/747235632765599834/Screen_Shot_2020-08-23_at_2.52.15_PM.png',
                            title="Help - General",
                            desc="Ayy... Slidin into yo dms. Here is the list of commands in general",
                            footer='the blood on sword is actually ketchup',
                            color=0x00D2FF)
        await message.author.send(embed=emb)
        await message.channel.send("> Help sent to " + message.author.mention + "'s DM. Please Check. ")
    elif message.content.startswith(prefix + cmd[1][0]):
        abtemb = embedMake(["Developed by", '`' + str(client.get_user(369652997308809226)) + "`"],
                           ["Version: ", '`' + str(v) + '`'], title="About Murder Moostery",
                           img='https://cdn.discordapp.com/attachments/663150753946402820/747235632765599834/Screen_Shot_2020-08-23_at_2.52.15_PM.png',
                           desc="The game inspired by Town of Salem",
                           color=0x00D2FF,
                           footer='the pen is mightier than the sword'
                           )
        await message.channel.send(embed=abtemb)


@client.event
async def on_raw_reaction_remove(payload):
    pass


@client.event
async def on_ready():
    print('\033[92m Logged as {0.user}'.format(client))
    await client.change_presence(
        activity=discord.Activity(name='for ' + str(prefix), type=discord.ActivityType.watching))


@client.event
async def on_message(message):
    if message.author == client.user:
        return
    await isOther(message)  # help, meta...
    await isFriend(message)  # friend
    await isGame(message)  # game


client.run(key)
