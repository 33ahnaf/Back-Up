name = "Ahnaf"

length_of_name = len(name)
print(length_of_name)

ends_with1 = name.endswith("naf")
ends_with2 = name.endswith("af")
ends_with3 = name.endswith("f")
ends_with4 = name.endswith("hn")
print(ends_with1)
print(ends_with2)
print(ends_with3)
print(ends_with4)
# Note: endswith() and startswith() functions are case-sensitive, means "Ah" and "ah" are not the same.
starts_with1 = name.startswith("Ah")
starts_with2 = name.startswith("hn")
print(starts_with1)
print(starts_with2)

count_func = name.count("a")
print(count_func)
# Note: this is also case-sensitive, means "A" and "a" are not the same.

name2 = "hello, world!"
capitalized_name2 = name2.capitalize()
print(capitalized_name2) # output: Hello, world!

first_occurrence_of_world_string = name2.find("world") # find() function finds a word and returns the index of first occurrence of
#                                                        the word in the string.
# Note: if find() function can't find a word then it returns -1
print(first_occurrence_of_world_string) # output: 7

new_name2 = name2.replace("hello", "Bye") # this function replaces old word with new word. (Remember, it needs to be store in a variable.)
print(new_name2) # output: Bye, world!



# Note: Strings are immutable, means functions can't modify strings insteed they make a new string.
# HOWEVER! They can, like this:
my_name = "Ahanaf Shariar"
print(my_name)
my_name = my_name.replace("Ahanaf", "Ahnaf")
print(my_name)