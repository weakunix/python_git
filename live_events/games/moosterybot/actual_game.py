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
                               desc='Game starting!! Check your DM\'s!',
                               footer='The game will be played through DM\'s')
    await channel.send(embed=emb)
    ppltoroles = [random.randint(2, len(roles) - 1) for x in range(len(ppl[str(payload.message_id)]))]
    ppltoroles[random.randint(0, len(ppltoroles) - 1)] = 0
    tempcheck = random.randint(0, len(ppltoroles) - 1)
    if ppltoroles[tempcheck] != 0:
        ppltoroles[tempcheck] = 1
    else:
        ppltoroles[0] = 1
    a = 0
    for i in range(len(ppl[str(payload.message_id)])):
        emb = await main.embedMake(['You Are The', '**' + str(roles[int(ppltoroles[i])][0]) + '**' + '\n `' + str(roles[int(ppltoroles[i])][1]) + '`'],
                                   title='Role Reveal!',
                                   thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                                   desc='',
                                   footer='This is your role. Goodluck and have fun!!!')
        await client.get_user(int(ppl[str(payload.message_id)][i])).send(embed=emb)
    await asyncio.sleep(1) #for ppl to get to their dms first
    #main.jason_it(str(payload.message_id), 'roles.json', str)
    await intro(payload, client, ppl)
    '''while play:
        await day()
        await night()'''


async def intro(payload, client, ppl):
    emb = await main.embedMake(['Splat!', 'There\'s a killer in this town...'],
                               title='It was a ordinary night in the city...',
                               thumbnail='https://media.discordapp.net/attachments/696699604003061784/748557547501256775/pfp2.png',
                               desc='until...',
                               img='https://media.discordapp.net/attachments/696699604003061784/748568734578376814/business_man_colored2.png'
                               )
    for i in range(len(ppl[str(payload.message_id)])):
        await client.get_user(int(ppl[str(payload.message_id)][i])).send(embed=emb)
    emb = await main.embedMake(['Remember...', 'He may be behind you'],
                               title='It is up to you to save the town!',
                               desc='and execute the murder...',
                               img='https://media.discordapp.net/attachments/747186165378973796/748573847934075070/unknown.png'
                               )
    for i in range(len(ppl[str(payload.message_id)])):
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

'''
    with open("games.json", 'r') as brr:
        gameppl = json.load(brr)
    pplingme = gameppl[str(payload.message_id)]
    arraynewgame = []
    if type(pplingme) != str:
        for i in range(len(pplingme)):
            arraynewgame.append(int(pplingme[i]))
    else:
        arraynewgame.append(pplingme)
    channel = client.get_channel(payload.channel_id)
    msg = await channel.fetch_message(payload.message_id)
    emb = await main.embedMake(["Game Code (for ppl in other servers):", '\n `' + "`"], ["Users queued:", "==============="],
                         arraytoembdt=arraynewgame,
                         title='New Room Made!',
                         desc='Game type: 🔓, Public',
                         footer="If you are the host, press the '☑️' to start game or '❌' to cancel!, Press '🚪' to join/leave the game")
    await msg.edit(embed=emb)
    '''
