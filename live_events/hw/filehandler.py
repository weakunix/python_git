import json

class OpenFile():
    @staticmethod 
    def get(filename):
        try:
            with open(filename) as file:
                data = file.read()
            return data
        except:
            return False

    @staticmethod
    def checkForUserInDatabase(filename, username, password):
        data = OpenFile.get(filename)
        try:
            if username in data:
                if password in data[str(username)]:
                    return True
        except:
            return False