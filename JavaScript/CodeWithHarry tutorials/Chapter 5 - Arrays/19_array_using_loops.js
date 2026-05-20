let nums = [2, 3, 19, 35, 39];



// using standard for loop
for (let i = 0; i < nums.length; i++) {
    console.log(nums[i]);
}



// using forEach() loop
nums.forEach((num) => {
    console.log(num);
})



// Array.from()
let my_name = "Ahnaf";
let array_of_my_name = Array.from(my_name);
console.log(my_name);
console.log(array_of_my_name);
// Note Array.from() function makes array out of an object.



// for of loop
for (let num of nums) {
    console.log(num); // prints elements
}



// for in loop
for (let i in nums) {
    console.log(i); // prints indices
}