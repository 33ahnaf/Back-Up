const isDivisableByTen = (x) => {
    if (x%10 == 0) {
        return true;
    }
    return false;
}

let nums = [23, 34, 20, 60, 73, 90, 203, 510];
let divisable_By_Ten_Nums = nums.filter(isDivisableByTen);
console.log(nums);
console.log(divisable_By_Ten_Nums);