import random
n = 3

with open(f"grid{n}.txt", "w") as file:
    file.write(str(n) + "\n")
    for i in range(n):
        for j in range(n):
            v = random.randint(1, n*n)
            file.write(str(v) + " ")
        file.write("\n")
