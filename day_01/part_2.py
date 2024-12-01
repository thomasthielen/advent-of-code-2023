# running the code on 'test_2.txt' yields the correct sum of 281.
with open('test_2.txt') as f:
    input = f.readlines()
    
# translate digits
digits = set()
digits.add(('one', '1'))
digits.add(('two', '2'))
digits.add(('three', '3'))
digits.add(('four', '4'))
digits.add(('five', '5'))
digits.add(('six', '6'))
digits.add(('seven', '7'))
digits.add(('eight', '8'))
digits.add(('nine', '9'))

modified_input = list()

for line in input:
    replacement = ''
    sub = ''
    for c in line:
        # check for digit
        if c.isdigit():
            replacement += c
            continue
        sub += c
        # check for spelled out digits
        for d in digits:
            if d[0] in sub:
                replacement += d[1]
                sub = sub[-1] # clean the substring, leaving only the last letter
    modified_input.append(replacement)
                
sum = 0
for line in modified_input:
    value = 0
    for c in line:
        if c.isdigit():
            value += int(c) * 10
            break
    for c in reversed(line):
        if c.isdigit():
            value += int(c)
            break
    sum += value

print(sum)
