let my_name = "Ahnaf";  // Valid.
let friend_name = 'Muyaj';  // Valid.
// let unknown_person_name = "Afrina';  // Invalid.

let first_char_of_my_name = my_name[0];
let length_of_my_name = my_name.length;



// Template literals
let boy1 = "Saad";
let boy2 = "Hasin";
let sentence = `${boy1} is a friend of ${boy2}.`;
// Note: the upper thing is called "Template literal". And, inserting variable directly in template literal is called "String Interpolation".
console.log(sentence);
// Note: >`< (backtick) is used to make f-string like things. We can insert variables in it and we can also insert
//  "(double quote) or '(single quote) in it, no need to write \"  or  \'        
// if we insert \'  or  \"     , no problem it will work as expected.



// Escape Sequence Characters
let famous_quote = 'Rose \'By Any Other Name';
console.log(famous_quote);
//      \"  -> escape sequence for "
//      \'  -> escape sequence for '
//      \n  -> escape sequence for newline
//      \t  -> escape sequence for tab
//      \\  -> escape sequence for backslash



// Note: my_name[2] = "G";  << is Invalid as Strings are immutable.