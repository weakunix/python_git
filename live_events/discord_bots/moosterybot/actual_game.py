import asyncio
import main
import character_classes
import json
import discord
import random


async def startGame(payload, client, ppl):
    # name   desc    day    night
    roles = character_classes.Characters.roleList
    channel = client.get_channel(payload.channel_id)
    emb = await main.embedMake(title='Starting game',
                               thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                               desc='Game starting!! Check your DM\'s! \n If you need to leave, this is the gamecode: `' + str(
                                   payload.message_id) + '`',
                               footer='The game will be played through DM\'s')
    await channel.send(embed=emb)
    ppltoroles = [random.randint(2, len(roles) - 1) for x in range(len(ppl[str(payload.message_id)]))]
    ppltoroles[random.randint(0, len(ppltoroles) - 1)] = 0 #change this to test
    tempcheck = random.randint(0, len(ppltoroles) - 1)
    if ppltoroles[tempcheck] != 0:
        ppltoroles[tempcheck] = 7 #change this to test
    else:
        for i in range(len(ppltoroles)):  # assigns murder to first perosn availible
            if i != tempcheck:
                ppltoroles[i] = 7
                break
    main.jason_it(str(payload.message_id), 'roles.json', ppltoroles)
    classes = initClasses(str(payload.message_id))
    for i in range(len(ppl[str(payload.message_id)])):
        emb = await main.embedMake(['You Are The', '**' + str(roles[int(ppltoroles[i])][0]) + '**' + '\n `' + str(
            roles[int(ppltoroles[i])][1]) + '`'],
                                   title='Role Reveal!',
                                   thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                                   desc='If you need to leave, this is the gamecode: `' + str(payload.message_id) + '`',
                                   footer='This is your role. Goodluck and have fun!!!')
        await client.get_user(int(ppl[str(payload.message_id)][i])).send(embed=emb)
    await client.http.delete_message(payload.channel_id, payload.message_id)
    await intro(payload, client, ppl, ppltoroles)
    emb = await main.embedMake(title='a')
    arymsg = []
    done = False
    for i in range(len(ppl[str(payload.message_id)])):
        arymsg.append(await client.get_user(int(ppl[str(payload.message_id)][i])).send(embed=emb))
    for i in range(10):
        if i < 9:
            emb = await main.embedMake(title='Game starting in:',
                                       desc=str(10 - (i + 1)),
                                       img='https://images-ext-2.discordapp.net/external/Wls1jDtGcUz3SaDbBd5_KHKTJ82Nem77ECA4Tx2Rz5g/https/media.discordapp.net/attachments/696699604003061784/747566312104001647/Screen_Shot_2020-08-24_at_5.20.21_PM.png',
                                       thumbnail='https://media.discordapp.net/attachments/746731386718912532/747590639151087636/Screen_Shot_2020-08-24_at_6.56.31_PM.png',
                                       footer='Tip: tip here')
        else:
            emb = await main.embedMake(
                ['Day one',
                 'First day after the murder, it is on the local news\n Everyone saw the grusome scene on camera and '
                 'wonders...\n Who did this? \n \n **Claim your role right now by reacting**\n``` 🗡️: Murder (lmao '
                 'why would you claim this) \n 🔎: Detective\n 💻: Hacker \n 🏹: Hunter \n 📚: Workhorse Dad \n 🍳: '
                 'Overprotective Mom \n ❤️: The Simp \n 🧪: Scientist \n 🧹: Witch \n 💰: Millionaire (don\'t claim '
                 'this lmao blackmail guarentee)``` \n if you react with something else than the provided above, you '
                 'are reacting as the Murder (just so you know LOL)'],
                title='Welcome to Murder Moostery...',
                thumbnail='https://media.discordapp.net/attachments/747159474753503343/748641985241415721/costume8_2_1.png',
                desc='Hopefully 10 seconds was enough time',
                footer='Note: if the reaction doesn\'t work the first time try again'
            )
        for eye in range(len(ppl[str(payload.message_id)])):
            await arymsg[eye].edit(embed=emb)
            if i == 9:
                await arymsg[eye].add_reaction("🗡️")
                await arymsg[eye].add_reaction("🔎")
                await arymsg[eye].add_reaction("💻")
                await arymsg[eye].add_reaction("🏹")
                await arymsg[eye].add_reaction("📚")
                await arymsg[eye].add_reaction("🍳")
                await arymsg[eye].add_reaction("❤")
                await arymsg[eye].add_reaction("🧪")
                await arymsg[eye].add_reaction("🧹")
                await arymsg[eye].add_reaction("💰")
                await asyncio.sleep(1)
        if i == 9:
            voted = 0

            def check(reaction, user):
                return str(reaction.emoji), user

            for iii in range(len(ppl[str(payload.message_id)])):
                try:
                    reaction, user = await client.wait_for('reaction_add', timeout=30.0, check=check)
                except asyncio.TimeoutError:
                    emb = await main.embedMake(
                        title='Claim Timed Out',
                        desc='You were automatically claimed as Millionaire',
                        thumbnail='https://images-ext-1.discordapp.net/external/a73EwOYEEHydxTjLBJARbB4LBsi46-tKH_m0mbcOMtI/https/images-ext-1.discordapp.net/external/p3Ujz5sOddyXFf6T_F_59ae7c779w8ax47Epd9v2Wy0/https/images-ext-2.discordapp.net/external/BAeOdPzafgkr43ervKSOByd063AO0MeENKlda4_FHW0/https/media.discordapp.net/attachments/724362941792649287/747969861061312632/mat6.png?width=438&height=438')
                    role = "Millionaire"
                    for eye in range(len(ppl[str(payload.message_id)])):
                        await arymsg[eye].edit(embed=emb)
                else:
                    if str(reaction) == "🗡️":
                        role = "Murder"
                    elif str(reaction) == "🔎":
                        role = "Detective"
                    elif str(reaction) == "💻":
                        role = "Hacker"
                    elif str(reaction) == "🏹":
                        role = "Hunter"
                    elif str(reaction) == "📚":
                        role = "Workhorse Dad"
                    elif str(reaction) == "🍳":
                        role = "Overprotective Mom"
                    elif str(reaction) == "❤":
                        role = "MVP Simp"
                    elif str(reaction) == "🧪":
                        role = "Scientist"
                    elif str(reaction) == "🧹":
                        role = "Witch"
                    elif str(reaction) == "💰":
                        role = "Millionaire"
                    else:
                        role = "Millionaire"
                    emb = await main.embedMake(
                        ['`' + str(user) + '` Claims that they are the ',
                         '**' + str(role) + '**'],
                        title='Role Claim!',
                        thumbnail='https://images-ext-1.discordapp.net/external/p3Ujz5sOddyXFf6T_F_59ae7c779w8ax47Epd9v2Wy0/https/images-ext-2.discordapp.net/external/BAeOdPzafgkr43ervKSOByd063AO0MeENKlda4_FHW0/https/media.discordapp.net/attachments/724362941792649287/747969861061312632/mat6.png',
                        desc='Hopefully they are truthful...',
                        footer='interesting...')
                    voted += 1
                    for b in range(len(ppl[str(payload.message_id)])):
                        await client.get_user(int(ppl[str(payload.message_id)][b])).send(embed=emb)
        await asyncio.sleep(1)  # for ppl to get to their dms first
    await recursion(classes, client)


async def recursion(classes, client):
    lockb = False
    locka = await day(classes, client)
    if locka:
        lockb = await night(classes, client)
    if lockb:
        await recursion(classes, client)


async def day(classes, client):
    for i in range(len(classes)):
        await classes[i].Dayrole(client)
    return True


async def night(classes, client):
    for i in range(len(classes)):
        await classes[i].Nightrole(client)
    return True


def initClasses(key):  # TODO limit to only making roles for one game i gtg eat now
    with open("roles.json", 'r') as brr:
        rolestuff = json.load(brr)
    with open("games.json", 'r') as brr:
        charac = json.load(brr)
    charlist = {i: "".join('character_classes.' + str(character_classes.Characters.roleList[i][0])) + '({})' for i in
                range(9)}
    listOfClasses = []
    for x in range(len(rolestuff[key])):
        a = eval(str(charlist[rolestuff[key][x]]).format(charac[key][x]))
        listOfClasses.append(a)
    return listOfClasses


async def intro(payload, client, ppl, ppltoroles):
    for i in range(len(ppl[str(payload.message_id)])):
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
                    break  # is host
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
