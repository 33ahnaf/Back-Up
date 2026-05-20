/*
    Note: Check out "Promise API" in CodeWithHarry's JavaScript notes for more clear info.
*/



const printValue = (value) => {
    console.log(value);
}

let promise1 = new Promise((resolve, reject) => {
    setTimeout(() => {
        resolve(3);
    }, 1000);
});

let promise2 = new Promise((resolve, reject) => {
    setTimeout(() => {
        resolve(19);
    }, 2000);
});

let promise3 = new Promise((resolve, reject) => {
    setTimeout(() => {
        resolve(3+19);
    }, 3000);
});

promise1.then(printValue);
promise2.then(printValue);
promise3.then(printValue);

let all_promise1 = Promise.all([promise1, promise2, promise3]);
all_promise1.then((value) => {
    console.log(value);
}); // returns an array of value when all the promises become resolved.

let all_promise2 = Promise.allSettled([promise1, promise2, promise3]);
all_promise2.then((value) => {
    console.log(value);
}); // returns an object of status and values when all the promises are setteled.

let all_promise3 = Promise.race([promise1, promise2, promise3]);
all_promise3.then((value) => {
    console.log(value);
}); // returns the fastest promise as soon as it is setteled. (can be resolved or rejected)

let all_promise4 = Promise.any([promise1, promise2, promise3]);
all_promise4.then((value) => {
    console.log(value);
}); // returns the fastest promise as soon as it is resolved. (can only be resolved)

let promise4 = Promise.resolve(33); // returns a promise with a resolved value.
// let promise5 = Promise.reject(333); // returns a promise with a rejected error.