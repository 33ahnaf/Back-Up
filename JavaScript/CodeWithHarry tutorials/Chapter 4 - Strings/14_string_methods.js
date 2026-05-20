//  .length
let my_name = "Ahnaf";
console.log(my_name.length);
let random_text = "Bottle o\' enchanting";
console.log(random_text.length); // Will print 20, not 21 because, \' is a escape sequence character which is actually 1 character long.



//  .toUpperCase()  and  .toLowerCase()  and  .slice()
let friend_name = "Afrina";
console.log(friend_name); // Will print "Afrina"
console.log(friend_name.toUpperCase()); // Will print "AFRINA"
console.log(friend_name.toLowerCase()); // Will print "afrina"
friend_name = friend_name.toUpperCase();
console.log(friend_name); // Will print "AFRINA", because the upper one statement.
console.log(friend_name.slice(2, 5)); // Will print "RIN"
console.log(friend_name.slice(2, 6)); // Will print "RINA"
console.log(friend_name.slice(2)); // Will print "RINA"
console.log(friend_name.slice(0, 2)); // Will print "AF"
console.log(friend_name.slice(0, -2)); // Will print "AFRI"



//  .replace
let my_friend_text = "Afrina is my best friend. I like Afrina soo much.";
console.log(my_friend_text);
my_friend_text = my_friend_text.replace("Afrina", "Saad");
my_friend_text = my_friend_text.replace("Afrina", "Saad");
// Note: we have to replace every word one-by-one, if we want, as .replace() function only replaces one word.
console.log(my_friend_text);



// .concat()
friend_name = "Afrina";
let full_text = my_name.concat(" is a very good friend of ", friend_name, ". Or is she. . . ?");  // Note: ,(comma) will not add any spaces.
console.log(full_text);



//  .trim()
let friend2_name = "      Hasin   ";
friend2_name = friend2_name.trim();
console.log(friend2_name);



// quick quiz
let another_friend = "Rupto";
for (let i = 0; i < another_friend.length; i++) {
    process.stdout.write(another_friend[i]);  // process.stdout.write() is used to print things without printing "\n" at the end.
}