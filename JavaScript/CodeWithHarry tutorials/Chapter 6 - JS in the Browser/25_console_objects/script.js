console.time("process_1"); // starts a timer with a given lebel.

let students = {
    Saad: 2,
    Meghna: 3,
    Ahnaf: 19,
    Rupto: 39
};
console.clear(); // clears the console.
console.log("This is a log."); // outputs a message to the console.
console.info("This is an info."); // used for special information.
console.warn("This is a warning."); // used for warnings.
console.error("This is an error."); // used for errors.
console.assert(2 > 3); // used to assert a statement.
console.assert(3 > 2); // used to assert a statement.
console.table(students); // displays a table of data. (Usually an array or an object).

console.timeEnd("process_1"); // ends a timer with a given lebel and displays the elapsed time in milliseconds.



console.time("process_2");
for (let i = 0; i < 20000; i++) {
    console.log(3);
}
console.timeEnd("process_2");