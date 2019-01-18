N = int(input())
cnt = 0
daysWithEvents = [False for i in range(365)]
totalDaysOfFreeFood = 0

while cnt < N:
  s, t = map(int, input().split())
  for i in range(s, t+1):
    daysWithEvents[i-1] = True
  cnt += 1

for i in range(365):
  if daysWithEvents[i]:
    totalDaysOfFreeFood += 1

print(totalDaysOfFreeFood)
    