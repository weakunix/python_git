import json

class File():
    @staticmethod 
    def getFileContents(filename):
        try:
            with open(filename) as file:
                data = json.load(file)
            return data
        except Exception as e:
            print(e)
            return False

    @staticmethod
    def checkForUserInDatabase(filename, username, password):
        data = File.getFileContents(filename)
        try:
            if username in data:
                if password == data[str(username)][0]:
                    return "True"
                return "BADPASSWORD"
            return "False"
        except Exception as e:
            print(e)
            return "False"

    @staticmethod
    def jason_it(filename, key, value):
        with open(filename, 'r') as brr:
            prefixes = json.load(brr)
        prefixes[str(key)] = value
        with open(filename, 'w') as brrr:
            json.dump(prefixes, brrr, indent=4)