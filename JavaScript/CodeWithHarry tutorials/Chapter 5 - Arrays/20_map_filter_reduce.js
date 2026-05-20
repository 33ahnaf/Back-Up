let nums = [2, 3, 19, 35, 39];


// map
function square (x) {
    return x**2;
}
let squared_nums = nums.map(square);
console.log(squared_nums);

// same as the upper one.
let squared_nums2 = nums.map((x) => {
    return x**2;
})
console.log(squared_nums2);


// filter
function isOdd(x) {
    if (x%2 != 0) {
        return true;
    }
    return false;
}
let only_odd_nums = nums.filter(isOdd);
console.log(only_odd_nums);


// reduce
function sum(x, y) {
    return x + y;
}
let sum_of_nums = nums.reduce(sum);
console.log(sum_of_nums);