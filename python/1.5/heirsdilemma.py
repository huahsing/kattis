L, H = map(int, input().split())
c = 0
for trying in range(L, H+1):
  digits = [False for i in range(10+1)]
  nonZeroAndUniqueAndDivisible = True
  # check each digit is unique
  temp = trying
  while temp > 0:
    # first condition true --> digit is zero
    # second condition true --> not unique
    # third condition true --> not divisible
    if temp % 10 == 0 or digits[temp % 10] or trying % (temp % 10) != 0:
      nonZeroAndUniqueAndDivisible = False
      break
    digits[temp % 10] = True
    temp = int(temp/10)

  if not nonZeroAndUniqueAndDivisible:
    continue
    
  c += 1  
  
print(c)
  