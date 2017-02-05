import json
with open("maps.json") as f:
    data = json.load(f)

for k in data:
    print (data[k])
