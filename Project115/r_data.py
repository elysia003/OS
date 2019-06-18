import random
f = open('e:\\OS\\data.txt', 'r+', encoding='UTF-8')
print(f.read())
for i in range(0, 1999):
    f.write(str(random.randint(0, 50000))+'\n')
    if i % 5 == 0:
        f.write(str(random.randint(28888, 888888))+'\n')
print('*')
for i in range(0, 1999):
    f.write(str(random.randint(59999, 190555))+'\n')
    if i % 9 == 0:
        for j in range(0, 7):
            f.write(str(random.randint(8888, 290888))+'\n')
print('*')
for i in range(0, 1999):
    f.write(str(random.randint(11111, 66666))+'\n')
print('*')
    
