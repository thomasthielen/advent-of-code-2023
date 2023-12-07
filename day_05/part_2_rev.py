import sys

with open('input.txt') as f:
    input = f.readlines()

search_from = 100000
search_to = 1000000

arrived = False
for location in range(search_from, search_to):
    if arrived:
        break
    traveller = location
    skip = False
    for line in reversed(input[1:]):
        # restart conversion process at 'map'
        if 'map' in line:
            skip = False
            continue
        # skip if line is empty or at skip flag raised
        if not line.strip() or skip:
            continue
        else:
            # read out the details of each range
            numbers = line.split(' ')
            dest_start = int(numbers[0])
            src_start = int(numbers[1])
            length = int(numbers[2].strip())
            # check whether the conversion applies & apply
            if dest_start <= traveller < dest_start+length:
                traveller = traveller + (src_start - dest_start)
                skip = True

    # check whether the traveller exists in any given seed range
    num = ''
    start = -1
    for c in input[0]:
        if c.isdigit():
            num += c
        else:
            if len(num) > 0:
                n = int(num)
                if start == -1:
                    start = n
                else:
                    end_excl = start + n
                    # check is handled here 
                    if start <= traveller < end_excl:
                        print('Reverse Traveller arrived!')
                        print('From origin location ' + str(location) + ' to seed ' + str(traveller))
                        arrived = True
                        break
                    start = -1
                num = ''



# min = sys.maxsize
# for v in seeds_after:
#     if v < min:
#         min = v

# print(min)
