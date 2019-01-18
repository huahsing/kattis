first, second = map(int, input().split())
largestValue = first + second
# 1 additional slot to start array with index 1 (makes it easier to debug)
outcomeFrequency = [0 for i in range(largestValue+1)]
largestOutcomeFrequency = 0

for i in range(first):
  for j in range(second):
    outcome = (i+1)+(j+1)
    outcomeFrequency[outcome] += 1
    if outcomeFrequency[outcome] > largestOutcomeFrequency:
      largestOutcomeFrequency = outcomeFrequency[outcome]
      
for i in range(1, largestValue+1):
  if outcomeFrequency[i] == largestOutcomeFrequency:
    print(str(i))
