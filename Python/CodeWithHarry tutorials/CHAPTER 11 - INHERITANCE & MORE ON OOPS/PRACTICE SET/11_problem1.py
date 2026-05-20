class _2D_Vector:
    def __init__(self, i, j):
        self.i = i
        self.j = j
    
    def show(self):
        print(f"i = {self.i} and j = {self.j}")

class _3D_Vector(_2D_Vector):
    def __init__(self, i, j, k):
        super().__init__(i, j)
        self.k = k
    
    def show(self):
        print(f"i = {self.i} and j = {self.j} and k = {self.k}")

_2D = _2D_Vector(3, 4)
_3D = _3D_Vector(3, 4, 5)

_2D.show()
_3D.show()