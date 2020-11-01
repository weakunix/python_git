import json
import yaml

def yaml_it(filename, key, value):
    with open(filename, 'r') as brr:
        prefixes = yaml.safe_load(brr)
    prefixes[str(key)] = value
    with open(filename, 'w') as brrr:
        yaml.dump(prefixes, brrr)

def yamlload(file):
    with open(file) as f:
        try:
            return yaml.load(f)
        except Exception:
            print(Exception)