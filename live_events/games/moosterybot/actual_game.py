import main
import json
import discord


async def startGame(payload, client, ppl):
    roles = [
        []
    ]
    play = True
    channel = client.get_channel(payload.channel_id)
    emb = await main.embedMake(title='Starting game',
                               thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                               desc='Game starting',
                               footer='You will get your role in the dm.')
    await channel.send(embed=emb)
    emb = await main.embedMake(title='Your Role:',
                               thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                               desc='',
                               footer='This is your role. Goodluck and have fun!!!')
    if str(payload.message_id) in ppl:
        for i in range(len(ppl[str(payload.message_id)])):
            if i != 0:  # not host
                try:
                    await client.get_user(int(ppl[str(payload.message_id)][i])).send(embed=emb)
                except:
                    break  # is host


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
