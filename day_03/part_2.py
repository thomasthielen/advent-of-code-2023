with open('test.txt') as f:
    input = f.readlines()

line_length = len(input[0].strip())

engine = list()
for line in input:
    line = line.strip()
    for c in line:
        engine.append(c)

def no_overflow(pos):
    return pos % line_length != 0

def read_number(pos):
    number = ''
    # go to the leftmost digit:
    while (engine[pos-1].isdigit() and no_overflow(pos)):
        pos -= 1
    # read the number up to the rightmost digit:
    number += engine[pos]
    while (engine[pos+1].isdigit() and no_overflow(pos+1)):
        pos += 1
        number += engine[pos]
    return int(number)

def check_gear(pos):
    adj_count = 0
    gear_ratio = 1
    # left
    if no_overflow(pos):
        check_pos = pos-1
        if engine[check_pos].isdigit():
            adj_count += 1
            gear_ratio *= read_number(check_pos)
    # right
    if no_overflow(pos+1):
        check_pos = pos+1
        if engine[check_pos].isdigit():
            adj_count += 1
            gear_ratio *= read_number(check_pos)
    # above / below
    for vertical in range(-1,2,2):
        check_pos = pos+vertical*line_length
        if engine[check_pos].isdigit():
            adj_count += 1
            gear_ratio *= read_number(check_pos)
        else:
            for horizontal in range(-1,2,2):
                check_pos = pos+vertical*line_length + horizontal
                if engine[check_pos].isdigit():
                    adj_count += 1
                    gear_ratio *= read_number(check_pos)
    if adj_count == 2:
        return gear_ratio
    return 0
        
sum = 0
i = 0

for c in engine:
    if c == '*':
        sum += check_gear(i)
    i += 1   

print(sum)