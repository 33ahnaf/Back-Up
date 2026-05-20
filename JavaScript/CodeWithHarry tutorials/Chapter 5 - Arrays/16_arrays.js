let random_things = ["Ahnaf", "Saad", 3, true, null, "404 Not found"];

console.log(random_things);
console.log(random_things[0]);
console.log(random_things[1]);
console.log(random_things[2]);
console.log(random_things[3]);
console.log(random_things[4]);
console.log(random_things[5]);
console.log(random_things[6]); // will print undefined because index 6 does not exist.
console.log(random_things.length);
random_things[3] = false;  // valid.
console.log(random_things);
console.log(typeof random_things);