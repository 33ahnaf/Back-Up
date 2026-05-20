const Afrina = {
    name: "Afrina",
    roll: 2,
    isFemale: true
};

console.log(Afrina);
Afrina['roll'] = 3;
Afrina['isBeautiful'] = true;
console.log(Afrina);

// Note: Although "Afrina" is const object, but it can change values and even can add more key-value-pairs.
//       It just can't change to another data type nor can completely change to another object.
//       "Afrina" is loyal to his object and no matter the object changes it will not forget it.