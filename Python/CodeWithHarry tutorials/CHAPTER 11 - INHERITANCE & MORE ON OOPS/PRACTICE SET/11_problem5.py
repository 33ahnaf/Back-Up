class Vector:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z
    
    def __add__(self1, self2):
        result = Vector(self1.x + self2.x, self1.y + self2.y, self1.z + self2.z)
        return result
    
    def __mul__(self1, self2):
        result = self1.x * self2.x + self1.y * self2.y + self1.z * self2.z
        return result
    
    def __str__(self):
        result = f"Vector({self.x}, {self.y}, {self.z})"
        return result

v1 = Vector(1, 2, 3)
v2 = Vector(4, 5, 6)

print(v1 + v2)
print(v1 * v2)