import sys

with open('input.txt') as f:
    input = f.readlines()

# read the required seeds
seeds_before = list()
num = ''
for c in input[0]:
    if c.isdigit():
        num += c
    else:
        if len(num) > 0:
            seeds_before.append(int(num))
            num = ''

# read the different maps and convert instantly
seeds_after = [None] * len(seeds_before)
for line in input[2:]:
    # skip empty lines
    if not line.strip():
        continue
    # restart conversion process for each map
    if 'map' in line:
        for i in range(0,len(seeds_before)):#
            if seeds_after[i] is None:
                seeds_after[i] = seeds_before[i]
        seeds_before = seeds_after.copy()
        seeds_after = [None] * len(seeds_before)
    else:
        # read out the details of each range
        numbers = line.split(' ')
        dest_start = int(numbers[0])
        src_start = int(numbers[1])
        length = int(numbers[2].strip())
        i = 0
        # check whether the conversion applies & apply
        for x in seeds_before:
            if src_start <= x < src_start+length:
                seeds_after[i] = x + (dest_start - src_start)
            i += 1

# one last conversion
for i in range(0,len(seeds_before)):#
    if seeds_after[i] is None:
        seeds_after[i] = seeds_before[i]

min = sys.maxsize
for v in seeds_after:
    if v < min:
        min = v

print(min)
