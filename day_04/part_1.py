with open('input.txt') as f:
    input = f.readlines()
    
sum = 0
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
            
    value = 0
    number = ''
    for c in s_owned:
        if c.isdigit():
            number += c   
        elif len(number) > 0:
            if int(number) in winners:
                if value == 0:
                    value = 1
                else:
                    value *= 2
            number = ''
            
    sum += value
    
print(sum)
