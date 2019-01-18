battles = int(input())
wonBattles = 0
for i in range(battles):
  record = input()
  if len(record) == 1:
    wonBattles += 1
  else:
    won = True
    # length is 2 or more characters
    for j in range(len(record)-1):
      if record[j] == 'C' and record[j+1] == 'D':
        won = False
        break
    if won:
      wonBattles += 1

print(wonBattles)