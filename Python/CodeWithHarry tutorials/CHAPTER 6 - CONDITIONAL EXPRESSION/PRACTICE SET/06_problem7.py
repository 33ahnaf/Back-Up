post = "I'm Saad, I have a friend who's name is Ahnaf. He is a good boy. Ahnaf is very polite."
my_name = "ahnaf"

if(my_name.lower() in post.lower()): # lower() function returns a new string which is in lower case.
    print("Someone is talking about you.")
else:
    print("Nothing to see here.")