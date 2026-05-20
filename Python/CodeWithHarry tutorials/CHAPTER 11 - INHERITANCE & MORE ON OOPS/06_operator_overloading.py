class Number:
    def __init__(self, n):
        self.n = n
    
    def __add__(self1, self2):
        return self1.n + self2.n
    
    def __sub__(self1, self2):
        return self1.n - self2.n

n = Number(1)
m = Number(2)

print(n - m)