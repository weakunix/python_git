import json
import main
import actual_game
import random
import discord
import asyncio


class Game:
    def __init__(self, id, containerFilledWithKids):
        self.id = str(id)
        self.date = 1
        with open("games.json", 'r') as brr:
            ppl = json.load(brr)
        self.players = ppl[str(self.id)]
        self.badGuys = 1 if len(self.players) < 7 else 2
        self.kids = containerFilledWithKids  # all the character classes of the game (sorry FBI)
        self.log = []
        '''
        [<character_classes.detective object at 0x7f95667b7b80>, <character_classes.murder object at 0x7f956675db50>]
        ['369652997308809226', '713106996055769110']
        1
        1
        749759828250984508
        '''

    async def startLoop(self, client, classtobind):
        for i in range(len(self.kids)):
            self.kids[i].binding(classtobind)
        while True:
            if self.date == 1:
                await self.claiming(client)
            # await self.events(client)
            await self.voting(client)
            await self.day(client)
            await self.night(client)
            if self.checkIfStop():
                with open("games.json", 'r') as brr:
                    ppl = json.load(brr)
                await client.get_user(int(ppl[self.id][0])).send("You Win!!")
                ppl.pop(str(self.id))
                return
            self.date += 1

    def checkIfStop(self):
        with open("games.json", 'r') as brr:
            ppl = json.load(brr)
        return True if len(ppl[self.id]) == 1 else False

    async def claiming(self, client):
        with open("games.json", 'r') as brr:
            ppl = json.load(brr)
        arymsg = []
        a = 'Hopefully 10 seconds was enough time' if self.date == 1 else 'goodluck!'
        emb = await main.embedMake(
            ['Day ' + str(self.date) + ':',
             '**Claim your role right now by reacting**\n``` 🗡️: Murder (lmao '
             'why would you claim this) \n 🔎: Detective\n 💻: Hacker \n 🏹: Hunter \n 📚: Workhorse Dad \n 🍳: '
             'Overprotective Mom \n ❤️: The Simp \n 🧪: Scientist \n 🧹: Witch \n 💰: Millionaire (don\'t claim '
             'this lmao blackmail guarentee)``` \n if you react with something else than the provided above, you '
             'are reacting as the Murder (just so you know LOL)'],
            title='Welcome to Murder Moostery...',
            thumbnail='https://media.discordapp.net/attachments/747159474753503343/748641985241415721/costume8_2_1.png',
            desc=a,
            footer='Note: wait until the second message to start reacting!'
        )
        for i in range(len(ppl[str(self.id)])):
            arymsg.append(await client.get_user(int(ppl[str(self.id)][i])).send(embed=emb))
        for eye in range(len(ppl[str(self.id)])):
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
        claimed = []

        emb = await main.embedMake(
            title='Ready to claim!',
            thumbnail='',
            desc='Claim by reacting to one of the emojis above ^',
            footer='Yes this is the second message, react now!'
        )
        for i in range(len(ppl[str(self.id)])):
            await client.get_user(int(ppl[str(self.id)][i])).send(embed=emb)

        def check(reaction, user):
            nonlocal claimed
            if str(user) not in claimed:
                claimed.append(str(user))
                return str(reaction.emoji), user

        while len(ppl[str(self.id)]) != len(claimed):  # make sure everyone has claimed
            try:
                reaction, user = await client.wait_for('reaction_add', timeout=30.0, check=check)
            except asyncio.TimeoutError:
                emb = await main.embedMake(
                    title='Claim Timed Out',
                    desc='You were automatically claimed as Millionaire',
                    thumbnail='https://images-ext-1.discordapp.net/external/a73EwOYEEHydxTjLBJARbB4LBsi46-tKH_m0mbcOMtI/https/images-ext-1.discordapp.net/external/p3Ujz5sOddyXFf6T_F_59ae7c779w8ax47Epd9v2Wy0/https/images-ext-2.discordapp.net/external/BAeOdPzafgkr43ervKSOByd063AO0MeENKlda4_FHW0/https/media.discordapp.net/attachments/724362941792649287/747969861061312632/mat6.png?width=438&height=438')
                for eye in range(len(ppl[str(self.id)])):
                    await client.get_user(int(ppl[str(self.id)][eye])).send(embed=emb)
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
                    footer='interesting...',
                    color=0xFFFF00
                )
                for b in range(len(ppl[str(self.id)])):
                    await client.get_user(int(ppl[str(self.id)][b])).send(embed=emb)

    async def voting(self, client):
        if self.date != 1:
            with open("games.json", 'r') as brr:
                ppl = json.load(brr)
            for b in range(len(ppl[str(self.id)])):
                await client.get_user(int(ppl[str(self.id)][b])).send("Voting right now owo wow")
        return

    async def day(self, client):
        with open("roles.json", 'r') as brr:
            role = json.load(brr)
        with open("games.json", 'r') as brr:
            ppl = json.load(brr)
        for i in range(len(ppl[str(self.id)])):
            emb = await main.embedMake(
                title='Turns:',
                desc='The ' + str(Characters.roleList[int(role[str(self.id)][i])][0]) + ' is taking their **day** turn!',
                footer='it won\'t take that long... right?',
                color=0x9900FF
            )
            for ier in range(len(ppl[str(self.id)])):
                if ier != i:
                    await client.get_user(int(ppl[str(self.id)][ier])).send(embed=emb)
            await self.kids[i].Dayrole(client)

    async def night(self, client):
        with open("games.json", 'r') as brr:
            ppl = json.load(brr)
        with open("roles.json", 'r') as brr:
            role = json.load(brr)
        try:
            for i in range(len(ppl[str(self.id)])):
                emb = await main.embedMake(
                    title='Turns:',
                    desc='The ' + str(Characters.roleList[int(role[str(self.id)][i])][0]) + ' is taking their **night** turn!',
                    footer='hurry up!!!!!',
                    color=0x0000FF
                )
                for ier in range(len(ppl[str(self.id)])):
                    if ier != i:
                        await client.get_user(int(ppl[str(self.id)][ier])).send(embed=emb)
                await self.kids[i].Nightrole(client, ppl[str(self.id)])
        except IndexError:
            return  # someone died and now the list is shorter. boo hoo, too bad so sad


class Characters:
    roleList = [
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
    excuses = [
        "food",
        "milk",
        "idoine",
        "cheesesteak",
        "bing",
        "lab",
        "witchcraft",
        "ancient chinese medicine"
    ]
    def __init__(self, playerid, gameid, number):
        self.isAlive = True
        self.isTrapped = False
        self.number = number
        self.name = self.roleList[number][0]
        self.id = int(playerid)
        self.images = []
        self.gameId = gameid
        self.father = None
        self.hasVoted = False
        self.hasClaimed = False
        for i in range(2):
            nameOfImg = "".join(str(self.name) + str(i))
            self.images.append(nameOfImg)
            if self.number == 0:
                break

    def goTo(self, target):
        pass

    def getPlayers(self, key):
        with open('games.json', 'r') as brr:
            target = json.load(brr)
        for i in range(len(target)):
            if target[key] == str(self.id):
                return True
        return False

    def getRole(self, **kwargs):  # hacky way without needing key to get player info and role
        tempid = kwargs.get('uid', None)
        uid = self.id if tempid is None else tempid
        with open('roles.json', 'r') as brr:
            role = json.load(brr)
        with open('games.json', 'r') as brr:
            target = json.load(brr)
        for i in range(len(list(target.values()))):
            if str(uid) in list(target.values())[i]:
                place = list(target.values())[i].index(str(uid))
                a = list(role.values())[i][place]
                if int(a) == self.number:
                    nmb = True
                else:
                    nmb = False
                return a, place, nmb
        return False

    @staticmethod
    async def buyFromShop(client):
        def check(reaction, user):
            return str(reaction.emoji), user

        try:
            reaction, user = await client.wait_for('reaction_add', timeout=15.0, check=check)
        except asyncio.TimeoutError:
            return False
        else:
            return reaction, user

    def binding(self, a):
        self.father = a

    async def die(self, client, target):
        with open("games.json", 'r') as brr:
            games = json.load(brr)
        with open("roles.json", 'r') as brr:
            role = json.load(brr)
        for i in range(len(games[str(self.gameId)])):
            if str(target) == games[str(self.gameId)][i]:
                emb = await main.embedMake(
                    title=str(client.get_user(int(target)))+' has been killed!',
                    desc='They are now out of the game and will stop recieving notifications!',
                    thumbnail='https://media.discordapp.net/attachments/663150753946402820/750106585451200542/business_man.png',
                    footer='gg',
                    color=0xFF0000
                )
                for b in range(len(games[str(self.gameId)])):
                    await client.get_user(int(games[str(self.gameId)][b])).send(embed=emb)
                games[str(self.gameId)].pop(i)
                role[str(self.gameId)].pop(i)
                self.father.kids.pop(i)
                self.father.players.pop(i)
                out_file = open("games.json", "w")
                json.dump(games, out_file, indent=4)
                out_file.close()
                break

    async def hackerPassive(self, client, text, personid):
        with open("roles.json", 'r') as brr:
            roles = json.load(brr)
        for i in range(len(roles[str(self.gameId)])):
            if 2 == roles[str(self.gameId)][i]:
                if random.randint(0, 20) < 20:
                    emb = await main.embedMake(
                        title='Activity at the market! (Your passive)',
                        desc='`' + str(client.get_user(personid)) + ' Has bought ' + str(text) + '`',
                        thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png',
                        footer='Nice code! You\'ve hacked them!')
                    await client.get_user(int(self.father.players[i])).send(embed=emb)


class murder(Characters):
    def __init__(self, playerid, gameid):
        super().__init__(playerid, gameid, 0)
        self.killrate = random.randint(80, 85)  # gets a boost up to 5%
        self.isGun = False
        self.target = None

    def Passive(self):
        pass

    async def Dayrole(self, client):
        weaponNames = [  # name, isGun, damageSetter
            ["knife", False, 0],  # 80-85 (starting weapon)
            ["sword", False, random.randint(85, 87)],  # 85-87
            ["pistol", True, random.randint(87, 92)],  # 87
            ["machine gun", True, random.randint(92, 95)],  # 95%
            ["Pineapple", False, random.randint(91, 95)],  # does atleast 91% - 95 damage because it is spikey
            ["Duster", False, random.randint(0, 100)],  # does ???% damamge depending on if the person is ticklish
            ["Burrito", False, 99],  # does 99% damage
            ["Philly Cheesesteak", False, 100]

        ]
        weaponIndex = int(random.randint(1, len(weaponNames) - 1))  # CAN NOT BE DEFAULT KNIFE
        emb = await main.embedMake(
            title='Offer From Market (expires in 30s)',
            desc='It may be a catfish... \n Weapon name\n`' + str(
                weaponNames[weaponIndex][0]) + '`\n Weapon Successrate\n`' + str(weaponNames[weaponIndex][2]) + '%`',
            thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png',
            footer='This will boost your kill chances! If you react anything other than shop or x, itll be defaulted to x')
        emoji = await client.get_user(int(self.id)).send(embed=emb)
        await emoji.add_reaction("🛒")
        await emoji.add_reaction("❎")
        await asyncio.sleep(1)
        stuff = await self.buyFromShop(client)
        if type(stuff) != tuple:
            emb = await main.embedMake(
                title='Offer Timed Out',
                desc='No extra info',
                thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png')
            await emoji.edit(embed=emb)
            return
        else:
            if str(stuff[1]) == str(client.get_user(int(self.id))):
                if str(stuff[0]) == "🛒":
                    self.killrate = weaponNames[weaponIndex][2]
                    self.isGun = weaponNames[weaponIndex][1]
                    emb = await main.embedMake(
                        title='Successfully Bought!',
                        desc='You have bought:' + str(
                            weaponNames[weaponIndex][0]) + '\n Now your assassin rate: `' + str(self.killrate) + '%`',
                        thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png',
                        footer='Nice!')
                    await emoji.edit(embed=emb)
                    await self.hackerPassive(client, str(weaponNames[weaponIndex][0]), self.id)
                else:
                    emb = await main.embedMake(
                        title='Deal Ignored!',
                        desc='Maybe it was a wise choice, or maybe not...',
                        thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png',
                        footer='It\'s your call!')
                    await emoji.edit(embed=emb)
                    return

    async def Nightrole(self, client, ppl):
        emb = await main.embedMake(
            title='Nighty night, who u gon kill tonight? (Blackmail/kill 15s)',
            desc='You can kill or blackmail someone. \n Choose the ✉️ to *blackmail* or 🗡️ to **KILL** or ⏩ to skip\n Your kill '
                 'chances `' + str(self.killrate) + '%`',
            thumbnail='https://images-ext-2.discordapp.net/external/Gomb7LxVtut-EumV3HMa4s2S6lUVHLkEs6oSSW3aNyI/https/media.discordapp.net/attachments/747159474753503343/748632260680613919/murder_wins_1_1.png',
            footer='If you react anything besides knife it is default to skip (just so you know)',
            color=0x0000FF
        )
        a = await client.get_user(self.id).send(embed=emb)
        await a.add_reaction('✉️')
        await a.add_reaction('🗡️')
        await a.add_reaction('⏩')
        await asyncio.sleep(1)
        stuff = await self.buyFromShop(client)
        if type(stuff) != tuple:
            emb = await main.embedMake(
                title='Offer Timed Out',
                desc='No extra info',
                # thumbnail='https://media.discordapp.net/attachments/747159474753503343/750048572707176509/costume15.png'
            )
            await a.edit(embed=emb)
            return
        else:
            if str(stuff[0]) == '✉️':
                kill = False
            elif str(stuff[0]) == '🗡️':
                kill = True
            else:
                emb = await main.embedMake(
                    title='No Naughty Things Tonight!',
                    desc='"I\'m innocent... right?"',
                    thumbnail='https://media.discordapp.net/attachments/747159474753503343/750048572707176509/costume15.png',
                    color=0x0000FF
                )
                await a.edit(embed=emb)
                return
        reactions = ['0️⃣', '1️⃣', '2️⃣', '3️⃣', '4️⃣', '5️⃣', '6️⃣', '7️⃣', '8️⃣', '9️⃣', '🔟', '🅰️', '🅱️', '🇨']
        emb = await main.embedMake(
            title='Choose your target!',
            desc='React numbers 1-10 (and A-Z if applicable) that correspond to the user and their id.',
            thumbnail='https://media.discordapp.net/attachments/663150753946402820/749998056048558123/costume11_1.png',
            footer='Hmm i think that number -static- looks very like the detective... (note: 💠 is your place in the alpha-numeric code, and you can click on it to cancel your action (but will cost a turn))',
            color=0x0000FF
        )
        for i in range(len(ppl)):
            emb.add_field(name=reactions[i], value=client.get_user(int(ppl[i])), inline=False)
        a = await client.get_user(int(self.id)).send(embed=emb)
        for i in range(len(ppl)):
            if str(ppl[i]) != str(self.id):
                await a.add_reaction(reactions[i])
            else:
                await a.add_reaction('💠')
        await asyncio.sleep(1)
        stufff = await self.buyFromShop(client)
        if type(stufff) != tuple:
            emb = await main.embedMake(
                title='Offer Timed Out',
                desc='No extra info',
                thumbnail='',
                color=0xFFFFFF
            )
            await a.edit(embed=emb)
            return
        else:
            for i in range(len(ppl)):
                if str(stufff[0]) == str(reactions[i]):
                    playerid = str(ppl[i])
                    if kill:
                        if random.randint(0, 100) <= int(self.killrate):
                            with open("roles.json", 'r') as brr:
                                roles = json.load(brr)
                            if roles[str(self.gameId)][i] == 3 or \
                                    roles[str(self.gameId)][i] == 4 or roles[str(self.gameId)][i] == 5:
                                emb = await main.embedMake(
                                    title='You have been targeted by the **Murder**.',
                                    desc='If you do nothing, you **will die**',
                                    thumbnail='https://images-ext-2.discordapp.net/external/Gomb7LxVtut-EumV3HMa4s2S6lUVHLkEs6oSSW3aNyI/https/media.discordapp.net/attachments/747159474753503343/748632260680613919/murder_wins_1_1.png',
                                    footer='Use your realiation role right now and react below! ```\n ⚔️: Fight Back \n 💀️:Accept death ```(if you are helpless then o well sorry ;( )',
                                    color=0xFF0000
                                )
                                retaliation = await client.get_user(int(playerid)).send(embed=emb)
                                await retaliation.add_reaction("⚔️")
                                await retaliation.add_reaction("💀")
                                await asyncio.sleep(1)
                                reactionstuff = await self.buyFromShop(client)
                                if type(reactionstuff) != tuple:
                                    emb = await main.embedMake(
                                        title='Offer Timed Out',
                                        desc='This was your last chance ;(',
                                        color=0xFF0000
                                    )
                                    await retaliation.edit(embed=emb)
                                    return
                                else:
                                    if str(reactionstuff[0]) == "⚔️":
                                        if roles[str(self.gameId)][i] == 4:
                                            self.father.log.append("Attempted Murder! At " + str(client.get_user(int(
                                                playerid))) + "'s house!\n **HE IS A MILLIONAIRE AND WAS ABLE TO "
                                                              "BRIBE HIS WAY OUT!**")
                                        elif roles[str(self.gameId)][i] == 5 and self.isGun:
                                            self.father.log.append("Attempted Murder! At " + str(
                                                client.get_user(int(playerid))) + "'s house!\n She was overprotective "
                                                                                  "and used her pan!")
                                        elif roles[str(self.gameId)][i] == 3:
                                            self.father.log.append("Attempted Murder! At " + str(
                                                client.get_user(int(playerid))) + "'s house!\n The hunter must strike "
                                                                                  "back!")
                                        for ii in range(len(ppl)):
                                            emb = await main.embedMake(
                                                title='Attention!',
                                                desc=str(self.father.log[len(self.father.log) - 1]),
                                                color=0x990000,
                                                # thumbnail='https://media.discordapp.net/attachments/747159474753503343/750048572707176509/costume15.png'
                                            )
                                            if ppl[ii] != str(self.id): await client.get_user(int(ppl[ii])).send(embed=emb)  # dont send to murder
                                        emb = await main.embedMake(
                                            title='Mission Failed! We\'ll get \'em next time...',
                                            thumbnail='https://media.discordapp.net/attachments/747159474753503343/749366041175523328/costume14.png',
                                            footer='Your night turn is finished. Wait until day',
                                            color=0xFF0000
                                        )
                                        await client.get_user(int(self.id)).send(embed=emb)  # sends to murder
                                        return
                            emb = await main.embedMake(
                                title='Action Successful. Waiting For response',
                                thumbnail='https://media.discordapp.net/attachments/747159474753503343/749360612169089176/costume11.png',
                                footer='Your night turn is finished. Wait until day to see the results.',
                                color=0xCBFB3A
                            )
                            await client.get_user(int(self.id)).send(embed=emb)
                            await self.die(client, playerid)
                        else:
                            emb = await main.embedMake(
                                title='Action Unsuccessful! But you weren\'t caught!',
                                desc='LMAO your weapon broke while you were using it. \n Luckily you fled before the victim woke up. '
                                     '(buy an upgrade when prompted from the market to increase your kill chances. \n chances '
                                     ':' + str(self.killrate) + '% to kill',
                                thumbnail='https://media.discordapp.net/attachments/747159474753503343/749366041175523328/costume14.png',
                                footer='Your night turn is finished. Wait until day to get a better weapon.',
                                color=0xFF0000
                            )
                            await client.get_user(int(self.id)).send(embed=emb)
                    else:
                        emb = await main.embedMake(
                            title='You have been *blackmained* by the **Murder**.',
                            desc='If you do nothing, you **will be forced to do what he messages!**',
                            thumbnail='https://media.discordapp.net/attachments/747159474753503343/749358743191421019/costume10.png',
                            footer='If you have a retaliation role, use it right now!',
                            color=0xFF0000
                        )
                        await client.get_user(int(playerid)).send(embed=emb)
                        emb = await main.embedMake(
                            title='Action Successful. Waiting For Response',
                            desc='Hopefully it ain\'t the hacker :yikes:',
                            thumbnail='https://media.discordapp.net/attachments/747159474753503343/749358743191421019/costume10.png',
                            footer='Your night turn is finished. Wait until day to see the results.',
                            color=0xCBFB3A
                        )
                        await client.get_user(int(self.id)).send(embed=emb)
                    break
        # kills the target
        # find target in the role list and get their role if .getRole()[]


class detective(Characters):
    def __init__(self, playerid, gameid):
        super().__init__(playerid, gameid, 1)
        # self.number = 1

    def Passive(self):
        pass

    async def Dayrole(self, client):
        pass

    async def Nightrole(self, client, ppl):
        # return person
        pass


class hacker(Characters):
    def __init__(self, playerid, gameid):
        super().__init__(playerid, gameid, 2)
        # self.number = 2

    def Passive(self):
        pass #already defined

    async def Dayrole(self, client):
        pass

    async def Nightrole(self, client, ppl):
        pass


class scientist(Characters):
    def __init__(self, playerid, gameid):
        super().__init__(playerid, gameid, 6)
        self.tier = 1

    def Passive(self):
        pass

    async def Dayrole(self, client):
        emb = await main.embedMake(
            ["Tier/Actions", "Passive: \n 1: get 2 people that are neighbors of a **suspect** \n 2: gets 3 suspects "
                             "in which one is the murder \n 3: spots the MURDER (this will alert them) \n Night Role: "
                             "\n Tier 1: see *activity* in the trapped house \n Tier 2: see the **role** of the "
                             "person who was there \n Tier 3: see their name and role"],
            title='Offer From Market (expires in 30s)',
            desc='Upgrade to tier:`' + str(self.tier + 1) + '`',
            thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png',
            footer='This will boost your passive and night! More info at https://bit.ly/2ExNTIr If you react anything other than shop or x, itll be defaulted to x')
        emoji = await client.get_user(int(self.id)).send(embed=emb)
        await emoji.add_reaction("🛒")
        await emoji.add_reaction("❎")
        await asyncio.sleep(1)

        stuff = await self.buyFromShop(client)
        if type(stuff) != tuple:
            emb = await main.embedMake(
                title='Offer Timed Out',
                desc='No extra info',
                thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png')
            await emoji.edit(embed=emb)
            return
        else:
            if str(stuff[1]) == str(client.get_user(int(self.id))):
                if str(stuff[0]) == "🛒":
                    emb = await main.embedMake(
                        title='Successfully Bought!',
                        desc='You have bought upgrade!' + '\n Now your tier:`' + str(self.tier) + '`',
                        thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png',
                        footer='Nice!')
                    await self.hackerPassive(client, Characters.excuses[random.randint(0, len(Characters.excuses) - 1)], self.id)
                    await emoji.edit(embed=emb)
                else:
                    emb = await main.embedMake(
                        title='Deal Ignored!',
                        desc='Maybe it was a wise choice, or maybe not...',
                        thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png',
                        footer='It\'s your call!')
                    await emoji.edit(embed=emb)
                    return

    async def Nightrole(self, client, ppl):
        # return person
        pass


class witch(Characters):
    def __init__(self, playerid, gameid):
        super().__init__(playerid, gameid, 7)
        self.materials = 2

    def Passive(self):
        pass

    async def Dayrole(self, client):
        emb = await main.embedMake(
            title='Offer From Market (expires in 30s)',
            desc='Buy Materials?`\n You will be at' + str(self.materials + 1) + '/2`',
            thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png',
            footer='This will make you able to save more people! More info at https://bit.ly/2ExNTIr')
        emoji = await client.get_user(int(self.id)).send(embed=emb)
        await emoji.add_reaction("🛒")
        await emoji.add_reaction("❎")
        await asyncio.sleep(1)

        stuff = await self.buyFromShop(client)
        if type(stuff) != tuple:
            emb = await main.embedMake(
                title='Offer Timed Out',
                desc='No extra info',
                thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png')
            await emoji.edit(embed=emb)
            return
        else:
            if str(stuff[1]) == str(client.get_user(int(self.id))):
                if str(stuff[0]) == "🛒":
                    self.materials += 1
                    emb = await main.embedMake(
                        title='Successfully Bought!',
                        desc='You have bought upgrade!' + '\n Now your witch has:`' + str(
                            self.materials) + '/2 materials for a save`',
                        thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png',
                        footer='Nice!',
                        color=0xCBFB3A
                    )
                    await self.hackerPassive(client, Characters.excuses[random.randint(0, len(Characters.excuses) - 1)],
                                             self.id)
                    await emoji.edit(embed=emb)
                else:
                    emb = await main.embedMake(
                        title='Deal Ignored!',
                        desc='Maybe it was a wise choice, or maybe not...',
                        thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png',
                        footer='It\'s your call!')
                    await emoji.edit(embed=emb)
                    return

    async def Nightrole(self, client, ppl):
        # return person
        pass


class hunter(Characters):
    def __init__(self, playerid, gameid):
        super().__init__(playerid, gameid, 3)
        # self.number = 3

    def Passive(self):
        pass

    async def Dayrole(self, client):
        emb = await main.embedMake(
            title='Offer From Market',
            desc='You have bought hunting materials (this is automatic)',
            thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png',
            footer='You can go hunt tonight!'
        )
        await self.hackerPassive(client, Characters.excuses[random.randint(0, len(Characters.excuses) - 1)], self.id)
        await client.get_user(int(self.id)).send(embed=emb)

    async def Nightrole(self, client, ppl):
        # return person
        pass


class workhorse_dad(Characters):
    def __init__(self, playerid, gameid):
        super().__init__(playerid, gameid, 8)
        self.distractsLeft = 5
        self.exposeRole = False

    def Passive(self):
        pass

    async def Dayrole(self, client):
        '''emb = await main.embedMake(
            title='Offer From Market',
            desc='You have bought hunting materials (this is automatic)',
            thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png',
            footer='You can go hunt tonight!')
        await client.get_user(int(self.id)).send(embed=emb)'''
        pass

    async def Nightrole(self, client, ppl):
        # return person
        pass


class overprotective_mom(Characters):
    def __init__(self, playerid, gameid):
        super().__init__(playerid, gameid, 5)
        # self.number = 5
        self.deflect = 3
        self.cooldownOP = 3

    def Passive(self):
        pass

    async def Dayrole(self, client):
        emb = await main.embedMake(
            title='Offer From Market',
            desc='You have bought groceries (and sleeping medicine)',
            thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png',
            footer='Time to get someone to sleep early!!!!!',
            color=0x0000FF
        )
        await self.hackerPassive(client, Characters.excuses[random.randint(0, len(Characters.excuses) - 1)], self.id)
        await client.get_user(int(self.id)).send(embed=emb)

    async def Nightrole(self, client, ppl):
        # return person
        pass


class millionaire(Characters):
    def __init__(self, playerid, gameid):
        super().__init__(playerid, gameid, 4)
        self.extra = 0

    def Passive(self):
        pass

    async def Dayrole(self, client):
        self.extra = random.randint(1, 3)
        emb = await main.embedMake(
            title='Investment',
            desc='Your smart daily automatic investments have gave you a lot of power in Politics aswell! as a result, you get `' + str(
                self.extra) + '` votes today!',
            thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png',
            footer='You can go business tonight!')
        await client.get_user(int(self.id)).send(embed=emb)

    async def Nightrole(self, client, ppl):
        # return person
        pass


class simp(Characters):
    def __init__(self, playerid, gameid):
        super().__init__(playerid, gameid, 9)

    def Passive(self):
        pass

    async def Dayrole(self, client):
        pass

    async def Nightrole(self, client, ppl):
        pass
