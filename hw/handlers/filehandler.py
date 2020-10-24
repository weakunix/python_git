import json
import yaml

fileFolder = "./data/"

def getFileContents(filename):
    try:
        with open(fileFolder+filename) as file:
            data = json.load(file)
        return data
    except Exception as e:
        print(e)
        return False

def jason_it(filename, key, value):
    with open(fileFolder+filename, 'r') as brr:
        prefixes = json.load(brr)
    prefixes[str(key)] = value
    with open(fileFolder+filename, 'w') as brrr:
        json.dump(prefixes, brrr, indent=4)

def yaml_it(filename, key, value):
    with open(fileFolder+filename, 'r') as brr:
        prefixes = yaml.safe_load(brr)
    prefixes[str(key)] = value
    with open(fileFolder+filename, 'w') as brrr:
        yaml.dump(prefixes, brrr)

def yamlload(file):
    with open(file) as f:
        try:
            return yaml.load(f)
        except Exception:
            print(Exception)