T = int(input())
for i in range(T):
  w = int(input())
  cities = {}
  for j in range(w):
    city = input()
    cities[city] = True
  print(str(len(cities)))