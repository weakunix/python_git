import random
import discord

key = []
with open('key.txt', 'r') as b:
    for line in b:
        key.append(line[:-1])  # need to add a extra char
key = str("".join(key))
client = discord.Client()
prefix = '-type '  # default prefix
typing = False
wordList = []
with open('words.txt', 'r') as b:
    for line in b:
        wordList.append(line[:-1])  # need to add a extra char
word = ''
success = 0
fail = 0
typist = 0

@client.event
async def on_ready():
    print("{} is now ready".format(client.user))

@client.event
async def on_message(message):
    global typing
    global word
    global success
    global fail
    global typist
    if message.author.id == client.user:
        return #not bot messages or other messages
    elif typing and message.author.id != typist:
        return
    if message.content.startswith(prefix + 'start'):
        await message.channel.send('Typing Starting')
        word = wordList[random.randint(0, len(wordList) - 1)]
        typing = True
        typist = message.author.id
        await message.channel.send('type this: \n `'+str(word)+'`')
    elif message.content.startswith(prefix + 'stop'):
        sof = str(success/fail) if fail != 0 else str(success)
        await message.channel.send('Stopped '+str(message.author.mention)+'\n Success:'+str(success)+'\n Fails:'+str(fail)+'\n S/F:'+str(sof))
        typing = False
        word = ''
        typist = 0
        success = 0
        fail = 0
    else:
        if typing:
            if str(message.content).lower() == str(word):
                success += 1
            else:
                fail += 1
            await message.channel.purge(limit=2)
            word = wordList[random.randint(0, len(wordList) - 1)]
            await message.channel.send('type this: \n `' + str(word) + '`')





client.run(key)