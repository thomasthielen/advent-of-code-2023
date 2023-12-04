with open('test.txt') as f:
    input = f.readlines()

line_length = len(input[0].strip())

def check_gear(pos):
    adj_count = 0
    gear_ratio = 1
    # above:

i = 0
for line in input:
    for c in line:
        if c == '*':
            if check_gear(i):

    i += 1
