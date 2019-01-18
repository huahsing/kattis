G, S, C = map(int, input().split())
G_buyingPower = 3
S_buyingPower = 2
C_buyingPower = 1
totalBuyingPower = G*G_buyingPower + S*S_buyingPower + C*C_buyingPower
if totalBuyingPower >= 8:
    canBuy = 'Province or Gold'
elif totalBuyingPower >= 6:
    canBuy = 'Duchy or Gold'
elif totalBuyingPower >= 5:
    canBuy = 'Duchy or Silver'
elif totalBuyingPower >= 3:
    canBuy = 'Estate or Silver'
elif totalBuyingPower >= 2:
    canBuy = 'Estate or Copper'
else:
    canBuy = 'Copper'

print(canBuy)
