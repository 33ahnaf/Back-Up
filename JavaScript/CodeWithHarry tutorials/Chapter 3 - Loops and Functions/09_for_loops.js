// for loop
for (let i = 0; i < 100; i++) {
    console.log("Count:", i+1);
}





// for-in loop
let rolls = {Afrina: 3, Ahnaf: 19, Saad: 2, Rupto: 39};
for (let roll in rolls) {
    console.log(roll);
}
// Note: for-in loop just returns the key(s) of an object  or  the index number(s) of an array.

for (let roll in rolls) {
    console.log("Roll of " + roll + " is : " + rolls[roll]);
} // we can also print the keys with the values.





// for-of loop
let friends = ["Ahnaf", "Saad", "Hasin", "Rupto", "Afrina"];
for (let friend of friends) {
    console.log(friend);
}
// Note: for-of loop just returns the element(s) of an array or string.