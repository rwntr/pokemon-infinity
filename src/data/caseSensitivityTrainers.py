import re
regex='(Name: .)(\w*)'

def repl(m):
    return str(m.group(1)) + str(m.group(2)).lower()

with open('trainers_lower.party', 'w') as lowercase, open('trainers.party') as original:
    pattern = re.compile("(Name: .)(.+)")

    for line in original:
        result = re.match(pattern, line)
        if result:
            toLower = re.sub(pattern, repl(result), line, 0, 0)
            print(toLower)
            lowercase.write(toLower)
        else:
            lowercase.write(line)


