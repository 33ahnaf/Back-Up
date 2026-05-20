const marks = {
    Ahnaf: 97,
    Afrina: 97,
    Saad: 100,
    Bashirul: 73
};


// Same as the lower one.
for (let i = 0; i < Object.keys(marks).length; i++) {
    console.log("Mark of " + Object.keys(marks)[i] + ": " + marks[Object.keys(marks)[i]]);
}



// Same as the upper one.
for (let key_of_mark in marks) {
    console.log("Mark of " + key_of_mark + ": " + marks[key_of_mark]);
}