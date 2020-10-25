import json
import yaml

fileFolder = "./data/"

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