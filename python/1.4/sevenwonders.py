# let index 0 in cardcntlist be for card T
# let index 1 in cardcntlist be for card C
# let index 2 in cardcntlist be for card G
cardcntlist = [0 for i in range(3)]
cardstring = input()
strIdx = 0

while strIdx < len(cardstring):
  if cardstring[strIdx] == 'T':
    cardcntlist[0] += 1
  elif cardstring[strIdx] == 'C':
    cardcntlist[1] += 1
  else:
    cardcntlist[2] += 1    
  strIdx += 1
  
baseScore = cardcntlist[0]*cardcntlist[0] + cardcntlist[1]*cardcntlist[1] + cardcntlist[2]*cardcntlist[2]

# since input string has no more than 50 characters, max cards for a card type is 50
setCnt = 50
for i in range(3):
  if cardcntlist[i] < setCnt:
    setCnt = cardcntlist[i]
    
totalScore = baseScore + setCnt*7

print(str(totalScore))