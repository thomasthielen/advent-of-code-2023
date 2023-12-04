with open('input.txt') as f:
    input = f.readlines()

special_characters = '!@#$%^&*()-+?_=,<>/'

line_length = len(input[0].strip())

marked = set()
def mark_surr(pos):
    for x in range(-1,2):
        marked.add(pos-line_length+x)
        marked.add(pos+x)
        marked.add(pos+line_length+x)

numbers = list()

i = 0
for line in input:
    line = line.strip()
    num = ''
    reading_digits = False
    for c in line:
        if c in special_characters:
            mark_surr(i)

        if c.isdigit():
            num += c
            reading_digits = True
        elif reading_digits:
            numbers.append(tuple([i-len(num), num]))
            num = ''
            reading_digits = False
        i += 1
    if reading_digits:
        numbers.append(tuple([i-len(num), num]))

sum = 0
for n in numbers:
    for x in range(0,len(n[1])):
        if n[0]+x in marked:
            sum += int(n[1])
            break

print(sum)