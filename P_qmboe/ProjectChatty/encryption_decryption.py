#imports
import random
import datetime

#vars
inpt = ''
p = ''
#lists
allchar = ' abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789`~!@#$%^&*()-_=+[{]}\\|;:\'",<.>/?'

#dictonaries
convert = {
  ' ': 0,
                        'a': 1,
            'b': 2,
            'c': 3,
            'd': 4,
            'e': 5,
            'f': 6,
            'g': 7,
            'h': 8,
            'i': 9,
            'j': 10,
            'k': 11,
            'l': 12,
            'm': 13,
            'n': 14,
            'o': 15,
            'p': 16,
            'q': 17,
            'r': 18,
            's': 19,
            't': 20,
            'u': 21,
            'v': 22,
            'w': 23,
            'x': 24,
            'y': 25,
            'z': 26,
            'A': 27,
            'B': 28,
            'C': 29,
            'D': 30,
            'E': 31,
            'F': 32,
            'G': 33,
            'H': 34,
            'I': 35,
            'J': 36,
            'K': 37,
            'L': 38,
            'M': 39,
            'N': 40,
            'O': 41,
            'P': 42,
            'Q': 43,
            'R': 44,
            'S': 45,
            'T': 46,
            'U': 47,
            'V': 48,
            'W': 49,
            'X': 50,
            'Y': 51,
            'Z': 52,
            '0': 53,
            '1': 54,
            '2': 55,
            '3': 56,
            '4': 57,
            '5': 58,
            '6': 59,
            '7': 60,
            '8': 61,
            '9': 62,
            '`': 63,
            '~': 64,
            '!': 65,
            '@': 66,
            '#': 67,
            '$': 68,
            '%': 69,
            '^': 70,
            '&': 71,
            '*': 72,
            '(': 73,
            ')': 74,
            '-': 75,
            '_': 76,
            '=': 77,
            '+': 78,
            '[': 79,
            '{': 80,
            ']': 81,
            '}': 82,
            '\\': 83,
            '|': 84,
            ';': 85,
            ':': 86,
            '\'': 87,
            '"': 88,
            ',': 89,
            '<': 90,
            '.': 91,
            '>': 92,
            '/': 93,
            '?': 94 }
def encrypt():
  global convert
  global allchar
  code = ''
  key = ''
  m = input('Feed Bingcrypto: \n')
  for c in m:
    num = random.randint(0, 94)
    try:
      c = convert[c]
    except:
      print('Error: Unrecognized character input\n')
      return None
    c += num
    c %= 95
    c = allchar[c]
    num = allchar[num]
    code += c
    key += num
  wf = open("cowFood.txt","w");
  wf.write(str(datetime.datetime.now()));
  wf.write(":\n");
  wf.write(code);
  wf.write(key);
  wf.close();
  m = input('Cow Milk: {}{}\n\nEnter to continue\n'.format(code, key))

#decrypt
def decrypt():
  global convert
  global allchar
  count = -1
  m = ''
  code = input('Feed the cow!:\n')
  if(len(code) <= 1 or len(code)%2!=0):
    print("Error: Expected even amount of letters, got '",code,"'");
    print(len(code)/2);
    print(type(len(code)/2)==int);
  else:
    l = int(len(code) / 2);
    lo= int((len(code) / 2)*-1);
    key = code[lo:]
    code = code[:l]
    for c in code:
      count += 1
      c = convert[c] + 95
      k = convert[key[count]]
      c -= k
      c %= 95
      c = allchar[c]
      m += c
    wf = open("cowDump.txt","w");
    wf.write(str(datetime.datetime.now()));
    wf.write(":\n");
    wf.write(m);
    wf.close();
    code = input("Cow's dump: {}\n\nEnter to continue\n".format(m))
