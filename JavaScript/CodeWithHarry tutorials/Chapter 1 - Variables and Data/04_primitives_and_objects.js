// nn bb ss u

let null_type = null;
let number_type = 69;

let boolean_type = true;
let BigInt_type = BigInt("567") + BigInt("2");

let string_type = "Ahnaf";
let symbol_type = Symbol("I'm a nice symbol.");

// same as let undefined_type;   because, if we don't define the value, then it will be automatically set to undefined.
let undefined_type = undefined;

console.log(null_type);
console.log(number_type);
console.log(boolean_type);
console.log(BigInt_type);
console.log(string_type);
console.log(symbol_type);
console.log(undefined_type);

console.log(typeof null_type);
console.log(typeof number_type);
console.log(typeof boolean_type);
console.log(typeof BigInt_type);
console.log(typeof string_type);
console.log(typeof symbol_type);
console.log(typeof undefined_type);


// Non-primitive data type - Object
const rolls_by_names = {
    "Saad": 2,
    "Afrina": 3,
    "Ahnaf": 19,
    "Bashirul": 23
};
console.log(rolls_by_names["Afrina"]);
console.log(rolls_by_names["Hasin"]); // will print 'undefined' because it's not in the Object.
console.log(typeof rolls_by_names);