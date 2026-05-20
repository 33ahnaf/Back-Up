class Vector:
    def __init__(self, lst):
        self.lst = lst
    
    def __len__(self):
        return len(self.lst)

v1 = Vector([1, 2, 3])
v2 = Vector([4, 5, 6])
print(len(v1), len(v2))