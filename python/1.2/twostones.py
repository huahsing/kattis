numOfStones = int(input())
while numOfStones > 1:
    numOfStones -= 2
if numOfStones % 2 == 0:
    print('Bob')
else:
    print('Alice')
