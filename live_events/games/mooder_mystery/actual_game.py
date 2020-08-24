import home
import json


async def startGame(payload, client):
    await client.http.delete_message(payload.channel_id, payload.message_id)
    channel = client.get_channel(payload.channel_id)
    emb = await home.embedMake(title='Starting game',
                         desc='Game starting',
                         footer='L')
    await channel.send(embed=emb)


async def noGame(payload, client, prefix):
    await client.http.delete_message(payload.channel_id, payload.message_id)
    channel = client.get_channel(payload.channel_id)
    emb = await home.embedMake(title='Game Cancelled By Host',
                         desc='use `' + str(prefix) + 'create` to host a game',
                         footer='BOOOOOOOO why cancel!')
    await channel.send(embed=emb)


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
    emb = await home.embedMake(["Game Code (for ppl in other servers):", '\n `' + "`"],
                               ["Users queued:", "==============="],
                               arraytoembdtt=arraynewgame,
                               valuett=arraypeople,
                               title='New Room Made!',
                               desc='Game type: 🔓, Public',
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
    emb = await home.embedMake(["Game Code (for ppl in other servers):", '\n `' + "`"], ["Users queued:", "==============="],
                         arraytoembdt=arraynewgame,
                         title='New Room Made!',
                         desc='Game type: 🔓, Public',
                         footer="If you are the host, press the '☑️' to start game or '❌' to cancel!, Press '🚪' to join/leave the game")
    await msg.edit(embed=emb)
    '''