let text = "Ahnaf is a very good boy.";
let word = "very";

// .includes()
console.log(text.includes(word));
console.log(`The word \"${word}\" ${text.includes(word) ? "is" : "is not"} present in the sentence.`);
// Note: Srting1.includes(String2) function checks whether the "String2" is present in the "Srting1" or not.

// .startsWith()
console.log(text.startsWith("A"));
console.log(text.startsWith("Ahn"));
console.log(text.startsWith("Ahnaf"));

// .endsWith()
console.log(text.endsWith("."));
console.log(text.endsWith("oy."));
console.log(text.endsWith("boy."));