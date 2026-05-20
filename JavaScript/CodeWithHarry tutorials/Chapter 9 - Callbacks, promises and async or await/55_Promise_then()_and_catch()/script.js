let promise1 = new Promise((resolve, reject) => {
    setTimeout(() => {
        // console.log("It's promise.");
        resolve(true);
    }, 3000);
});
console.log(promise1);
// To get the resolve value.
// promise1.then((value) => {
//     console.log(value);
// });

promise1.then((value) => {
    console.log(value)
}, (error) => {
    alert(error);
}); // same as the upper one but it can handle resolve and reject both.




let promise2 = new Promise((resolve, reject) => {
    setTimeout(() => {
        // console.log("It's promise.");
        reject(new Error("Roses are red, Violets are blue, unexpected error at line 32."));
    }, 3000);
});
console.log(promise1);
// To catch the error.
// promise2.catch((error) => {
//     console.log(error);
// });

promise2.then((value) => {
    console.log(value)
}, (error) => {
    alert(error);
}); // same as the upper one but it can handle resolve and reject both.