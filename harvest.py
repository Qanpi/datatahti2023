import random

#n = random.randint(1, 1000)
n = 100000 

with open(f"harvest{n}.txt", "w") as file:
    lst = [i for i in range(1, n+1)]
    lst_2 = [i for i in range(1, n+1)]
    file.write(str(n) + "\n")

    for i in range(n):
        file.write(str(random.randint(0, 1)) + " ")

    file.write("\n")

    for i in range(1, n):
        a = random.choice(lst)
        lst.remove(a)
        b = random.choice(lst_2)
        while (b == a): b = random.choice(lst_2)
        lst_2.remove(b)
        c = random.randint(1, 1000)
        file.write(f"{a} {b} {c}\n")
