#vars
logins = set() #50 login attempts
digit = 0 #which digit of the login you are on
works = False #if all the logins are successful
relations = set() #relationships between numbers
password = '' #password
last_digit = '' #last digit of password (needs to be stored as all relations with it will be removed)
used = [] #used relationships

#user def functions
def place_value(relations, highest = True):
    possible = {i for i in range(10)}
    not_in = {i for i in range(10)}
    high_or_low = { True: [1, 0],
                    False: [0, 1]   }
    for i in relations:
        try:
            possible.remove(i[high_or_low[highest][0]])
        except:
            pass
        try:
            not_in.remove(i[high_or_low[highest][1]])
        except:
            pass
    for i in not_in:
        try:
            possible.remove(i)
        except:
            pass
    try:
        return str(list(possible)[0])
    except:
        pass
        #TODO MAKE A BETTER VERSION OF THIS PROGRAM SO THAT IF THERE WERE TO BE REPEATING DIGITS IT WOULD STILL WORK
        #THE STRATEGY FOR THIS WOULD BE TO DETECT IF THERE ARE TUPLES THAT CONTRADICT EACH OTHER
        #I.E. IF THIS HAPPENS: (1, 2) (2, 3) (3, 1) WE CAN SEE THAT THERE NEEDS TO BE TWO OF ONE NUMBER

#reading logins file
with open('p079_keylog.txt', 'r') as login_file:
    for attempt in login_file:
        logins.add(attempt.strip('\n'))

#getting raltionships of numbers
for i in logins:
    relations.add((int(i[0]), int(i[1])))
    relations.add((int(i[1]), int(i[2])))

#get last digit
last_digit = place_value(relations, False)

#finding order based on relationships between numbers
while relations != set():
    used = []
    password += place_value(relations)
    for i in relations:
        if str(i[0]) == place_value(relations):
            used.append(i)
    for i in used:
        relations.remove(i)
print(password + last_digit)
