let compare_in_accending_order = (a, b) => {
    return a - b;
}



// delete operator
let nums = [1, 2, 3, 4, 5, 6];
console.log(nums, nums.length);
delete nums[2];
console.log(nums, nums.length);
console.log(typeof nums[2]);



// concat()
let nums1 = [1, 2];
let nums2 = [3, 4];
let nums3 = [5, 6];
let all_nums = nums1.concat(nums2, nums3);
console.log(all_nums);



// sort()
let unsorted_array = [32, 12, 0, 45, 3];
console.log(unsorted_array);
unsorted_array.sort();
// Note: .sort() function modifies the array by sorting it alphabetically.
console.log(unsorted_array);

let unsorted_array_of_friends = ["Ahnaf", "Saad", "Hasin", "Afrina", "Rupto", "Bashirul"];
console.log(unsorted_array_of_friends);
unsorted_array_of_friends.sort();
// Note: .sort() function modifies the array by sorting it alphabetically.
console.log(unsorted_array_of_friends);

unsorted_array.sort(compare_in_accending_order);
console.log(unsorted_array);
// Note: by giving the optional compare function, now it will sort it in accending order.


// reverse()
unsorted_array.reverse();
console.log(unsorted_array);



// splice()
let nums4 = [1, 2, 3, 4, 5, 6, 7, 8, 9];
let deleted_values = nums4.splice(2, 3, 1025, 1026, 1023, 1024); // syntax -> string.splice(from_index_no, delete_count, items. . .);
console.log(nums4, deleted_values);
// deletes elements from index X and replaces them with the items and returns the deleted elements.



// slice()
let array_of_my_name = ["A", "h", "n", "a", "f"];
console.log(array_of_my_name.slice(1, 4));