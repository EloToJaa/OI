from pyperclip import copy
#n = int(input("Podaj rozmiar danych wejściowych: "))

def ntree(n):
	x = 1
	while x < n:
		x *= 2
	return x

inp = input("Podaj ilosc danych: ")
n = 1
if "e" in inp:
	inp = inp.split("e")
	n = int(inp[0]) * (10 ** int(inp[1]))
else:
	n = int(inp)

r = str(ntree(n))
print("Rozmiar drzewa powinien wynosić")
print(r)

copy(r)
print("Skopiowano do schowka")

#pos = int(input("Podaj pos: "))

#pos += ntree - 1
#print("Pozycja w drzewie: ", pos)