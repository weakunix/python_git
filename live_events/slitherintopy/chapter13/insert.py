import math
import random

def sorts(arraytosort) -> bool:
    x = 0
    for i in range(len(arraytosort) - 1):
        if arraytosort[i] > arraytosort[i + 1]:
            x += 1
    return True if x == 0 else False

def sortthedamnthing(arraytosort):
    while not sorts(arraytosort):
        for i in range(len(arraytosort) - 1):
            if arraytosort[i] > arraytosort[i + 1]:
                a = arraytosort[i]
                arraytosort[i] = arraytosort[i + 1]
                arraytosort[i + 1] = a
    return arraytosort

def insert(lists, number):
    lenOfSearch = len(lists) // 2
    if number < lists[lenOfSearch]:
        newlist = [lists[i] for i in range(lenOfSearch)]
    elif number > lists[lenOfSearch]:
        newlist = [lists[i + lenOfSearch] for i in range(lenOfSearch)]
    else: 
        newlist = []
        newlist.append(lists[lenOfSearch])
    if len(newlist) != 1:
        insert(newlist, number)
    else:
        print("where to put the number")
        print(newlist)
        return lenOfSearch

arrayofints = [random.randint(0, 100) for x in range(100)]
print("first list")
print(arrayofints)
print("\n")
arrayofints = sortthedamnthing(arrayofints)
print("sorted list")
print(arrayofints)
insert(arrayofints, 42)