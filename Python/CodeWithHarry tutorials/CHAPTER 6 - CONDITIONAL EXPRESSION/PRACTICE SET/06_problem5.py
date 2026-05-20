list_of_names = ["Ahnaf", "Afrina", "Saad", "Hasin", "Fahad", "Muyaz"]
name = input("Enter a name: ")

if(name in list_of_names):
    print(f"{name} is present in the list")
else:
    print(f"{name} is not present in the list")