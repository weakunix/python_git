import asyncio

import main
import json
import discord
import random


async def startGame(payload, client, ppl):
    #name   desc    day    night
    roles = [
        ["murder", "**KILL EVERYONE!**"],
        ["detective", "Find out who the **murder** is!"],
        ["hacker", "Spy that the market! Control it!"],
        ["hunter", "Find the murder's weapons and avenge yourself!"],
        ["millionaire", "Use your influence to manipulate the votes!"],
        ["overprotective_mom", "Stall and distract!"],
        ["scientist", "Find out who is lying and who is truthful!"],
        ["witch", "Medicate and protect the city!"],
        ["workhorse_dad", "Stall and distract v2!"]
    ]
    play = True
    channel = client.get_channel(payload.channel_id)
    emb = await main.embedMake(title='Starting game',
                               thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                               desc='Game starting!! Check your DM\'s! \n If you need to leave, this is the gamecode: `'+str(payload.message_id)+'`',
                               footer='The game will be played through DM\'s')
    await channel.send(embed=emb)
    ppltoroles = [random.randint(2, len(roles) - 1) for x in range(len(ppl[str(payload.message_id)]))]
    ppltoroles[random.randint(0, len(ppltoroles) - 1)] = 0
    tempcheck = random.randint(0, len(ppltoroles) - 1)
    if ppltoroles[tempcheck] != 0:
        ppltoroles[tempcheck] = 1
    else:
        for i in range(len(ppltoroles)): #assigns murder to first perosn availible
            if i != tempcheck:
                ppltoroles[i] = 1
                break
    main.jason_it(str(payload.message_id), 'roles.json', ppltoroles)
    for i in range(len(ppl[str(payload.message_id)])):
        emb = await main.embedMake(['You Are The', '**' + str(roles[int(ppltoroles[i])][0]) + '**' + '\n `' + str(roles[int(ppltoroles[i])][1]) + '`'],
                                   title='Role Reveal!',
                                   thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                                   desc='If you need to leave, this is the gamecode: `'+str(payload.message_id)+'`',
                                   footer='This is your role. Goodluck and have fun!!!')
        await client.get_user(int(ppl[str(payload.message_id)][i])).send(embed=emb)
    await client.http.delete_message(payload.channel_id, payload.message_id)
    await intro(payload, client, ppl, ppltoroles)
    emb = await main.embedMake(title='a')
    arymsg = []
    for i in range(len(ppl[str(payload.message_id)])):
        arymsg.append(await client.get_user(int(ppl[str(payload.message_id)][i])).send(embed=emb))
    for i in range(10):
        if i < 9:
            emb = await main.embedMake(title='Game starting in:',
                                       desc=str(10-(i+1)),
                                       img='https://images-ext-2.discordapp.net/external/Wls1jDtGcUz3SaDbBd5_KHKTJ82Nem77ECA4Tx2Rz5g/https/media.discordapp.net/attachments/696699604003061784/747566312104001647/Screen_Shot_2020-08-24_at_5.20.21_PM.png',
                                       thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                                       footer='Tip: tip here')
        else:
            emb = await main.embedMake(
                ['Day one', 'First day after the murder, it is on the local news\n Everyone saw the grusome scene on camera and wonders...\n Who did this? \n \n **Claim your role right now by typing** `-moostery claim [role]` (obviously if you are murderer you have to fake lol)'],
                title='Welcome to Murder Moostery...',
                img='https://media.discordapp.net/attachments/747159474753503343/748641985241415721/costume8_2_1.png',
                desc='Hopefully 10 seconds was enough time',
                                       )
        for eye in range(len(ppl[str(payload.message_id)])):
            await arymsg[eye].edit(embed=emb)
        await asyncio.sleep(1) #for ppl to get to their dms first
    #while play:
    #    await day()
    #    await night()


async def day():
    pass


async def night():
    pass


async def initClasses():
    import character_class
    pass


async def intro(payload, client, ppl, ppltoroles):
    for i in range(len(ppl[str(payload.message_id)])):
        if ppltoroles[i] != 0: #isnt murder
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
        await client.get_user(int(ppl[str(payload.message_id)][i])).send(embed=emb)


async def noGame(payload, client, prefix, ppl):
    await client.http.delete_message(payload.channel_id, payload.message_id)
    channel = client.get_channel(payload.channel_id)
    emb = await main.embedMake(
        title='Game Cancelled By Host',
        thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
        desc='use `' + str(prefix) + 'create` to host a game',
        footer='BOOOOOOOO why cancel!')
    await channel.send(embed=emb)
    if str(payload.message_id) in ppl:
        for i in range(len(ppl[str(payload.message_id)])):
            if i != 0:  # not host
                try:
                    await client.get_user(int(ppl[str(payload.message_id)][i])).send(embed=emb)
                except:
                    break #is host
    ppl.pop(str(payload.message_id))
    out_file = open("games.json", "w")
    json.dump(ppl, out_file, indent=4)
    out_file.close()


async def joinGame(payload, client):
    with open("games.json", 'r') as brr:
        gameppl = json.load(brr)
    temparraystore = gameppl[str(payload.message_id)]
    arraynewgame = []
    arraypeople = []
    if type(temparraystore) != str:
        for i in range(len(temparraystore)):
            arraynewgame.append(temparraystore[i])
            arraypeople.append(str(client.get_user(int(temparraystore[i]))))
    else:
        arraynewgame.append(temparraystore)
    channel = client.get_channel(payload.channel_id)
    msg = await channel.fetch_message(payload.message_id)
    emb = await main.embedMake(
        ["Game Code (for ppl in other servers): ", '\n `' + str(payload.message_id) + "`"],
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