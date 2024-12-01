import sys

def extractRGB(r):
    rgb = [0,0,0]
    cubes = r.split(',')
    for c in cubes:
        value = int(c.split()[0])
        color = c.split()[1]
        match color:
            case 'red':
                rgb[0] = value
            case 'green':
                rgb[1] = value
            case 'blue':
                rgb[2] = value
            case _:
                print('Error: Unknown color!')
    return rgb

# change the filename below:
with open('test.txt') as f:
    input = f.readlines()
    
games = list()

for line in input:
    reveals = line.split(';')
    id = int(reveals[0].split(':')[0].split()[1])

    reveals[0] = reveals[0].split(':')[1]
    min_rgb = [0,0,0]
    for r in reveals:
        rgb = extractRGB(r)
        for x in range (0,3):
            if rgb[x] > 0 and rgb[x] > min_rgb[x]:
                min_rgb[x] = rgb[x]
    games.append([id, min_rgb])
    
sum_power = 0
for g in games:
    power = g[1][0]* g[1][1] * g[1][2]
    sum_power += power

print(sum_power)