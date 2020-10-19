import discord
import asyncio
from pynput.keyboard import Controller

#stole code from some repo

keyboardsim = Controller()
client = discord.Client()

@client.event
async def on_message(message):
    if message.embeds.title == "A trick-or-treater has stopped by!":
        if "h!treat" in message.description:
            keyboardsim.type("h!treat\n")
        else:
            keyboardsim.type("h!trick\n")
        await asyncio.sleep(2)
        keyboardsim.type("a\na\na\n")

client.login()