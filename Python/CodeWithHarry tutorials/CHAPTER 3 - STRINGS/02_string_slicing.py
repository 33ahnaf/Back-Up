name = "Ahnaf"
short_name1 = name[0:3] # start from index 0 all the way till 3 (excluding 3)
print(short_name1) # output: Ahn

short_name2 = name[1:3] # start from index 1 all the way till 3 (excluding 3)
print(short_name2) # output: hn

short_name3 = name[0:4] # start from index 0 all the way till 4 (excluding 4)
print(short_name3) # output: Ahna

short_name4 = name[0:5] # start from index 0 all the way till end (index 4).
print(short_name4) # output: Ahnaf

short_name5 = name[ :3] # same as name[0:3]
print(short_name5) # output: Ahn

short_name6 = name[1: ] # index 1 to end. (same as name[0:5] )
print(short_name6) # output: hnaf

charecter0 = name[0]
charecter1 = name[1]
print(charecter0) # output: A
print(charecter1) # output: h