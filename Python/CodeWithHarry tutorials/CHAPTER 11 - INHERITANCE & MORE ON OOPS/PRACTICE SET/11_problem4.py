class Complex:
    def __init__(self, r, i):
        self.r = r
        self.i = i
    
    def __add__(self1, self2):
        return Complex(self1.r + self2.r, self1.i + self2.i)
    
    def __mul__(self1, self2):
        real_part = self1.r * self2.r - self1.i * self2.i
        imag_part = self1.r * self2.i + self1.i * self2.r
        return Complex(real_part, imag_part)
    
    def __str__(self):
        return f"{self.r} + {self.i}i"

c1 = Complex(1, 2)
c2 = Complex(3, 4)

print(c1 + c2)
print(c1 * c2)