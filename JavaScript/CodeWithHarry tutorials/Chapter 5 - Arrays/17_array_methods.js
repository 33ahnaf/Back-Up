let random_things = ["Ahnaf", "Saad", 3, true, null, "404 Not found"];

let str1 = random_things.toString(); // Ahnaf,Saad,3,true,,404 Not found
console.log(str1);

let str2 = random_things.join(" and "); // Fun fact: I just casually typed " and " after some tries, and. . . after returning to CodeWithHarry's tutorial I saw he also typed " and " after me, what a coencident.
console.log(str2);


let nums = [];

nums = [1, 2, 3, 4, 5];
console.log(nums);
let popped_item = nums.pop()
console.log(nums, popped_item);
// .pop() function pops and returns the popped element. Deletes last element.

nums = [1, 2, 3, 4, 5];
console.log(nums);
let shifted_item = nums.shift();
console.log(nums, shifted_item);
// .shift() function shifts and returns the shifted element. Deletes first element.


nums = [1, 2, 3, 4, 5];
console.log(nums);
nums.unshift(0);
console.log(nums);
// .unshift() function unshifts and returns the new array's length. Appends a element to the beginning of the array.

nums = [1, 2, 3, 4, 5];
console.log(nums);
nums.push(6);
console.log(nums);
// .push() function pushs and returns the new array's length. Appends a element at the end of the array.