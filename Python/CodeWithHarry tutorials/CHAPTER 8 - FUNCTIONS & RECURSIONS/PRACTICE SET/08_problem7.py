def remove_and_strip(items, word):
    new_list = []
    items.remove(word)
    for item in items:
        new_list.append(item.strip(word))
    return new_list

items = ["Ahnaf", "Afrina", "Saad", "na"]

print(remove_and_strip(items, "na"))