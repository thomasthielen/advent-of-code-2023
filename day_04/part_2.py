with open('test.txt') as f:
    input = f.readlines()
    
instances = list()
for x in range(0,len(input)):
    instances.append(1)

i = 0
for card in input:
    winners = list()
    s_win = card.split(':')[1].split('|')[0]
    s_owned = card.split(':')[1].split('|')[1]
    
    number = ''
    for c in s_win:
        if c.isdigit():
            number += c
        elif len(number) > 0:
            winners.append(int(number))
            number = ''
            
    matching = 0
    number = ''
    for c in s_owned:
        if c.isdigit():
            number += c   
        elif len(number) > 0:
            if int(number) in winners:
                matching += 1
            number = ''
            
    for x in range(1, matching+1):
        instances[i+x] += instances[i]
            
    i += 1

sum = 0
for i in instances:
    sum += i
print(sum)