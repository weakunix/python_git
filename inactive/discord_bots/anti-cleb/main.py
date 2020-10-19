import discord
import asyncio
from pynput.keyboard import Controller

#stole code from some repo

keyboardsim = Controller()
client = discord.Client()

@client.event
async def on_message(message):
    try:
        if message.embeds[0].title == "A trick-or-treater has stopped by!" and message.author.id == 755580145078632508:
            if "h!treat" in message.embeds[0].description:
                keyboardsim.type("h!treat\n")
            else:
                keyboardsim.type("h!trick\n")
            keyboardsim.type("a\na\na\n")
    except:
        return

print("stinky")
client.run()