import asyncio
import main
import character_classes
import json
import discord
import random


async def startGame(payload, client, ppl, emoji, puborpriv):
    # name   desc    day    night
    roles = character_classes.Characters.roleList
    channel = client.get_channel(payload.channel.id)
    emb = await main.embedMake(title='Starting game',
                               thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                               desc='Game starting!! Check your DM\'s!',
                               footer='The game will be played through DM\'s')
    if puborpriv:
        await channel.send(embed=emb)
    ppltoroles = [random.randint(2, len(roles) - 1) for x in range(len(ppl[str(emoji)]))]
    ppltoroles[random.randint(0, len(ppltoroles) - 1)] = 0 #change this to test
    tempcheck = random.randint(0, len(ppltoroles) - 1)
    if ppltoroles[tempcheck] != 0:
        ppltoroles[tempcheck] = 1 #change this to test
    else:
        for i in range(len(ppltoroles)):  # assigns murder to first perosn availible
            if i != tempcheck:
                ppltoroles[i] = 1
                break
    #ppltoroles[0] = 1; ppltoroles[1] = 6 #debug line
    main.jason_it(str(emoji), 'roles.json', ppltoroles)
    classes = initClasses(str(emoji))
    for i in range(len(ppl[str(emoji)])):
        emb = await main.embedMake(['You Are The', '**' + str(roles[int(ppltoroles[i])][0]) + '**' + '\n `' + str(
            roles[int(ppltoroles[i])][1]) + '`'],
                                   title='Role Reveal!',
                                   thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                                   footer='This is your role. Goodluck and have fun!!!')
        await client.get_user(int(ppl[str(emoji)][i])).send(embed=emb)
    if puborpriv:
        await client.http.delete_message(payload.channel.id, payload.id)
    await intro(emoji, client, ppl, ppltoroles)
    emb = await main.embedMake(title='a')
    arymsg = []
    for i in range(len(ppl[str(emoji)])):
        arymsg.append(await client.get_user(int(ppl[str(emoji)][i])).send(embed=emb))
    for i in range(3):
        emb = await main.embedMake(title='Game starting in:',
                                   desc=str(4 - (i + 1)),
                                   img='https://images-ext-2.discordapp.net/external/Wls1jDtGcUz3SaDbBd5_KHKTJ82Nem77ECA4Tx2Rz5g/https/media.discordapp.net/attachments/696699604003061784/747566312104001647/Screen_Shot_2020-08-24_at_5.20.21_PM.png',
                                   thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                                   footer='Tip: tip here')
        for eye in range(len(ppl[str(emoji)])):
            await arymsg[eye].edit(embed=emb)
        await asyncio.sleep(1)  # for ppl to get to their dms first
    gamething = character_classes.Game(emoji, classes)
    await gamething.startLoop(client, gamething)

def initClasses(key):  # TODO limit to only making roles for one game i gtg eat now
    with open("roles.json", 'r') as brr:
        rolestuff = json.load(brr)
    with open("games.json", 'r') as brr:
        charac = json.load(brr)
    charlist = {i: "".join('character_classes.' + str(character_classes.Characters.roleList[i][0])) + '({}, {})' for i in
                range(9)}
    listOfClasses = []
    for x in range(len(rolestuff[str(key)])):
        a = eval(str(charlist[rolestuff[str(key)][x]]).format(charac[str(key)][x], str(key)))
        listOfClasses.append(a)
    return listOfClasses


async def intro(payload, client, ppl, ppltoroles):
    for i in range(len(ppl[str(payload)])):
        if ppltoroles[i] != 0:  # isnt murder
            emb = await main.embedMake(['Remember...', 'He may be behind you'],
                                       title='It is up to you to save the town!',
                                       desc='and execute the murder...',
                                       img='https://media.discordapp.net/attachments/747186165378973796/748573847934075070/unknown.png'
                                       )
        else:
            emb = await main.embedMake(title='You have to kill them all!',
                                       desc='and use blackmail to your advantage',
                                       img='https://media.discordapp.net/attachments/747159474753503343/748632260680613919/murder_wins_1_1.png'
                                       )
        await client.get_user(int(ppl[str(payload)][i])).send(embed=emb)


async def noGame(payload, client, prefix, ppl, emoji, puborno):
    emb = await main.embedMake(
        title='Game Cancelled By Host',
        thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
        desc='use `' + str(prefix) + 'create` to host a game',
        footer='BOOOOOOOO why cancel!')
    if puborno:
        await client.http.delete_message(payload.channel.id, emoji)
        channel = client.get_channel(payload.channel.id)
        await channel.send(embed=emb)
    if str(payload.id) in ppl:
        for i in range(len(ppl[str(payload.id)])):
            if i != 0:  # not host
                try:
                    await client.get_user(int(ppl[str(payload.id)][i])).send(embed=emb)
                except:
                    break  # is host
    ppl.pop(str(emoji))
    out_file = open("games.json", "w")
    json.dump(ppl, out_file, indent=4)
    out_file.close()


async def joinGame(msgid, channelid, client):
    with open("games.json", 'r') as brr:
        gameppl = json.load(brr)
    temparraystore = gameppl[str(msgid)]
    arraynewgame = []
    arraypeople = []
    if type(temparraystore) != str:
        for i in range(len(temparraystore)):
            arraynewgame.append(temparraystore[i])
            arraypeople.append(str(client.get_user(int(temparraystore[i]))))
    else:
        arraynewgame.append(temparraystore)
    channel = client.get_channel(channelid)
    msg = await channel.fetch_message(msgid)
    emb = await main.embedMake(
        ["Game Code (for ppl in other servers): ", '\n `' + str(msgid) + "`"],
        arraytoembdtt=arraynewgame,
        valuett=arraypeople,
        title='New Room Made!',
        desc='Game type: 🔓, Public',
        thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
        footer="If you are the host, press the '☑️' to start game or '❌' to cancel!, Press '🚪' to join/leave the game")
    await msg.edit(embed=emb)


if __name__ == '__main__':
    print(
        'wrong file dude'
    )
