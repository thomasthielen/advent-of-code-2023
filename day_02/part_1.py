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

# change the values below:
limit_rgb = (12,13,14)
with open('test.txt') as f:
    input = f.readlines()
    
games = list()

for line in input:
    reveals = line.split(';')
    id = int(reveals[0].split(':')[0].split()[1])

    reveals[0] = reveals[0].split(':')[1]
    max_rgb = [0,0,0]
    for r in reveals:
        rgb = extractRGB(r)
        for x in range (0,3):
            if rgb[x] > max_rgb[x]:
                max_rgb[x] = rgb[x]
    
    games.append([id, max_rgb])
    
sum_id = 0
for g in games:
    valid = True
    for x in range (0,3):
        if g[1][x] > limit_rgb[x]:
            valid = False
            break
    if valid:
        sum_id += g[0]

print(sum_id)