import discord
import random

client = discord.Client()
prefix = "/cow "
v = '0.4'

cmd = [
    "help",
    "simp",
    "prefix",
    "moo",
    "version"
]

cowpun =[
    "What is a happy cowboy?\n> A jolly rancher",
    "What's a pampered cow?\n> Spoiled Milk",
    "Who did the cow call to relocate?\n> the MOOVING company",
    "What do you call a scardycow?\n> a coward",
    "Who is MrMoooo?\n> a business cow",
    "What did the cow say to the spilled milk?\n> udder cowtastrophe",
    "What does cows drive into war?\n> milk TANKERS"
]

@client.event
async def on_ready():
    print('Logged as {0.user}'.format(client))

@client.event
async def on_message(message):
    global prefix
    if message.author == client.user:
        return
    if message.content.startswith(prefix + cmd[0]):
        await message.channel.send('> MOO? You need halp? Here is the list of commands: \n ```/cow prefix [] ('
                                   'change prefix [itll always be /cow prefix to change]) \n'+prefix+'moo (play cow moo sound) \n'+prefix+'simp [girlfriend (i sad no '
                                   'hav)] (cow spams her name and hearts)\n'+prefix+'moo```')
    elif message.content.startswith(prefix + cmd[1]):
        simp = []
        for i in range(len(prefix) + len(cmd[1]), len(message.content)):
            simp.append(message.content[i])
        simp = "".join(simp)
        if simp != " i sad no hav":
            simp = (":heart:" + simp) * 5
        else:
            simp = "me too its fine ;("
        for i in range(0, 5):
            await message.channel.send(simp)
    elif message.content.startswith("/cow " + cmd[2]):
        newPFX = []
        for i in range(5 + len(cmd[2]) + 1, len(message.content)):
            newPFX.append(message.content[i])
        newPFX = "".join(newPFX)
        if newPFX != "default":
            prefix = newPFX+" "
        else:
            prefix = "/cow "
        await message.channel.send("> Prefix Successfully Changed To:\n```"+prefix+"```")
    elif message.content.startswith(prefix + cmd[3]):
        await message.channel.send("> "+cowpun[random.randint(0, 6)]+"\n https://www.youtube.com/watch?v=J0HgEEY2jts")
    elif message.content.startswith("/bing"):
        prefix = "moo "
        await message.channel.send("> ```Dev Cheats Activated```")
    elif message.content.startswith(prefix + cmd[4]):
        await message.channel.send("> BingBingBot Version: ```Version: "+v+"```> github repo here:\n "
                                                                 "> ```https://github.com/weakunix/python_git```")
client.run('NzQ1NDQ4Nzg5NjU3MTI0OTM1.Xzx7SQ.9v4GFjs4G0YdK-0vBo-wHvjozbo')