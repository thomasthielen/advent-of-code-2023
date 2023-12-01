# running the code on 'test_1.txt' yields the correct sum of 142.
with open('input.txt') as f:
    input = f.readlines()
    
sum = 0
for line in input:
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
