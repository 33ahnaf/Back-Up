// Arithmatic operators.
let a1 = 5;
let b1 = 7;
console.log("a + b =", a1 + b1);
console.log("a - b =", a1 - b1);
console.log("a * b =", a1 * b1);
console.log("a / b =", a1 / b1);
console.log("a ** b =", a1 ** b1);
console.log("a % b =", a1 % b1);

console.log(a1++);
console.log(a1);

console.log(++a1);
console.log(a1);


console.log(b1--);
console.log(b1);

console.log(--b1);
console.log(b1);



// Assign operators.
let a2 = 5;
console.log("a =", a2);

a2 += 5; // same as a2 = a2 + 5
console.log("a =", a2);
a2 = 5;
a2 -= 5; // same as a2 = a2 - 5
console.log("a =", a2);
a2 = 5;
a2 *= 5; // same as a2 = a2 * 5
console.log("a =", a2);
a2 = 5;
a2 /= 5; // same as a2 = a2 / 5
console.log("a =", a2);
a2 = 5;
a2 %= 5; // same as a2 = a2 % 5
console.log("a =", a2);
a2 = 5;
a2 **= 5; // same as a2 = a2 ** 5
console.log("a =", a2);
a2 = 5;



// Comparison operator.
console.log("3 == 3", 3 == 3);
console.log("3 == 4", 3 == 4);

console.log("3 > 2", 3 > 2);
console.log("2 > 3", 2 > 3);

console.log("2 < 3", 2 < 3);
console.log("3 < 2", 3 < 2);

console.log("10 >= 10", 10 >= 10);
console.log("11 >= 10", 11 >= 10);
console.log("10 >= 11", 10 >= 11);

console.log("11 <= 11", 11 <= 11);
console.log("10 <= 11", 10 <= 11);
console.log("11 <= 10", 11 <= 10);

console.log("19 != 3", 19 != 3);
console.log("19 != 19", 19 != 19);

console.log("3 === \"3\"", 3 === "3");
console.log("3 !== \"3\"", 3 !== "3");
// Note: == and != operator checks if the values are the same or not. But === and !== operator checks if the values and the types are both same at the same time or not.



// Logical operator.
console.log("true && true", true && true);
console.log("true && false", true && false);
console.log("false && true", false && true);
console.log("false && false", false && false);

console.log("true || true", true || true);
console.log("true || false", true || false);
console.log("false || true", false || true);
console.log("false || false", false || false);

console.log("!true", !true);
console.log("!false", !false);



// Ternary operator.
let age = 14;
console.log(age >= 18 ? "Adult" : "Kid");
// Note: >>age >= 18 ? "Adult" : "Kid"<< returns the command statement. Here, it's "Adult" or "Kid".
// Syntax -> condition ? exp1 : exp2



/*
This is a tutorial
from
CodeWithHarry
*/