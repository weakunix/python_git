import json
import main
import actual_game
import random
import discord
import asyncio


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

    def __init__(self, playerid, number):
        self.isAlive = True
        self.isTrapped = False
        self.number = number
        self.name = self.roleList[number][0]
        self.id = int(playerid)
        self.images = []
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
            reaction, user = await client.wait_for('reaction_add', timeout=30.0, check=check)
        except asyncio.TimeoutError:
            return False
        else:
            return reaction, user


class murder(Characters):
    def __init__(self, playerid):
        super().__init__(playerid, 0)
        self.killrate = random.uniform(80, 85)  # gets a boost up to 5%
        self.isGun = False

    def Passive(self):
        pass

    async def Dayrole(self, client):
        weaponNames = [  # name, isGun, damageSetter
            ["knife", False, 0],  # 80-85 (starting weapon)
            ["sword", False, random.uniform(85, 87)],  # 85-87
            ["pistol", True, random.uniform(87, 92)],  # 87
            ["machine gun", True, random.uniform(92, 95)],  # 95%
            ["Pineapple", False, random.uniform(91, 95)],  # does atleast 91% - 95 damage because it is spikey
            ["Duster", False, random.uniform(0, 100)],  # does ???% damamge depending on if the person is ticklish
            ["Burrito", False, 99],  # does 99% damage
            ["Philly Cheesesteak", False, 100]

        ]
        weaponIndex = int(random.randint(1, len(weaponNames)))  # CAN NOT BE DEFAULT KNIFE
        emb = await main.embedMake(
            title='Offer From Market (expires in 30s)',
            desc='It may be a catfish... \n Weapon name\n`' + str(
                weaponNames[weaponIndex][0]) + '`\n Weapon DMG\n`' + str(weaponNames[weaponIndex][2]) + '`',
            thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png',
            footer='This will boost your kill chances!')
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
                elif str(stuff[0]) == "❎":
                    emb = await main.embedMake(
                        title='Deal Ignored!',
                        desc='Maybe it was a wise choice, or maybe not...',
                        thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png',
                        footer='It\'s your call!')
                    await emoji.edit(embed=emb)

    async def Nightrole(self, blackmail, targetid, author):
        await self.targetPlayer(targetid, True, author)
        await self.targetPlayer(targetid, False, author)
        # kills the target
        # find target in the role list and get thir role if .getRole()[]

    async def targetPlayer(self, playerid, kill, author):
        # number = self.getRole(uid=int(playerid))[0]  # is its number
        if kill:
            if random.uniform(0, 100) <= self.killrate:
                emb = await main.embedMake(
                    title='You have been targeted by the **Murder**.',
                    desc='If you do nothing, you **will die**',
                    thumbnail='https://images-ext-2.discordapp.net/external/Gomb7LxVtut-EumV3HMa4s2S6lUVHLkEs6oSSW3aNyI/https/media.discordapp.net/attachments/747159474753503343/748632260680613919/murder_wins_1_1.png',
                    footer='If you have a retaliation role, use it right now!')
                main.client.get_user(int(playerid)).send(embed=emb)
                emb = await main.embedMake(
                    title='Action Successful. Waiting For response',
                    thumbnail='https://media.discordapp.net/attachments/747159474753503343/749360612169089176/costume11.png',
                    footer='Your night turn is finished. Wait until day to see the results.')
                main.client.get_user(int(author)).send(embed=emb)
            else:
                emb = await main.embedMake(
                    title='Action Unsuccessful! But you weren\'t caught!',
                    desc='LMAO your weapon broke while you were using it. \n Luckily you fled before the victim woke up. '
                         '(buy an upgrade when prompted from the market to increase your kill chances. \n chances '
                         ':' + str(self.killrate) + '% to kill',
                    thumbnail='https://media.discordapp.net/attachments/747159474753503343/749366041175523328/costume14.png',
                    footer='Your night turn is finished. Wait until day to get a better weapon.')
                main.client.get_user(int(author)).send(embed=emb)
        else:
            emb = await main.embedMake(
                title='You have been *blackmained* by the **Murder**.',
                desc='If you do nothing, you **will be forced to do what he messages!**',
                thumbnail='https://media.discordapp.net/attachments/747159474753503343/749358743191421019/costume10.png',
                footer='If you have a retaliation role, use it right now!')
            main.client.get_user(int(playerid)).send(embed=emb)
            emb = await main.embedMake(
                title='Action Successful. Waiting For Response',
                desc='Hopefully it ain\'t the hacker :yikes:',
                thumbnail='https://media.discordapp.net/attachments/747159474753503343/749358743191421019/costume10.png',
                footer='Your night turn is finished. Wait until day to see the results.')
            main.client.get_user(int(author)).send(embed=emb)


class detective(Characters):
    def __init__(self, playerid):
        super().__init__(playerid, 1)
        # self.number = 1

    def Passive(self):
        pass

    async def Dayrole(self, client):
        pass

    async def Nightrole(self, client):
        # return person
        pass


class hacker(Characters):
    def __init__(self, playerid):
        super().__init__(playerid, 2)
        # self.number = 2

    def Passive(self):
        pass

    async def Dayrole(self, client):
        pass

    async def Nightrole(self, client):
        pass


class scientist(Characters):
    def __init__(self, playerid):
        super().__init__(playerid, 6)
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
            desc='Upgrade to tier:`'+str(self.tier+1)+'`',
            thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png',
            footer='This will boost your passive and night! More info at https://bit.ly/2ExNTIr')
        emoji = await client.get_user(int(self.id)).send(embed=emb)
        await emoji.add_reaction("🛒")
        await emoji.add_reaction("❎")
        await asyncio.sleep(1)

        def check(reaction, user):
            return str(reaction.emoji), user

        try:
            reaction, user = await client.wait_for('reaction_add', timeout=30.0, check=check)
        except asyncio.TimeoutError:
            emb = await main.embedMake(
                title='Offer Timed Out',
                desc='No extra info',
                thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png')
            await emoji.edit(embed=emb)
        else:
            if str(user) == str(client.get_user(int(self.id))):
                if str(reaction) == "🛒":
                    emb = await main.embedMake(
                        title='Successfully Bought!',
                        desc='You have bought upgrade!' + '\n Now your tier:`' + str(self.tier) + '`',
                        thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png',
                        footer='Nice!')
                    await emoji.edit(embed=emb)
                elif str(reaction) == "❎":
                    emb = await main.embedMake(
                        title='Deal Ignored!',
                        desc='Maybe it was a wise choice, or maybe not...',
                        thumbnail='https://media.discordapp.net/attachments/747159474753503343/749363552225329152/costume13.png',
                        footer='It\'s your call!')
                    await emoji.edit(embed=emb)

    async def Nightrole(self, client):
        # return person
        pass


class witch(Characters):
    def __init__(self, playerid):
        super().__init__(playerid, 7)
        # self.number = 7

    def Passive(self):
        pass

    async def Dayrole(self, client):
        pass

    async def Nightrole(self, client):
        # return person
        pass


class hunter(Characters):
    def __init__(self, playerid):
        super().__init__(playerid, 3)
        # self.number = 3

    def Passive(self):
        pass

    async def Dayrole(self, client):
        pass

    async def Nightrole(self, client):
        # return person
        pass


class workhorse_dad(Characters):
    def __init__(self, playerid):
        super().__init__(playerid, 8)
        self.distractsLeft = 5
        self.exposeRole = False

    def Passive(self):
        pass

    async def Dayrole(self, client):
        pass

    async def Nightrole(self, client):
        # return person
        pass


class overprotective_mom(Characters):
    def __init__(self, playerid):
        super().__init__(playerid, 5)
        # self.number = 5
        self.deflect = 3
        self.cooldownOP = 3

    def Passive(self):
        pass

    async def Dayrole(self, client):
        pass

    async def Nightrole(self, client):
        # return person
        pass


class millionaire(Characters):
    def __init__(self, playerid):
        super().__init__(playerid, 4)
        # self.number = 4

    def Passive(self):
        pass

    async def Dayrole(self, client):
        pass

    async def Nightrole(self, client):
        # return person
        pass
