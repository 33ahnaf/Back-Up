let promise1 = new Promise((resolve, reject) => {
    setTimeout(() => {
        console.log("Hey I'm gonna resolve now.");
        resolve(3);
    }, 2000);
});

promise1.then(() => {
    console.log("Congratulations this promise is now resolved!");
});

promise1.then(() => {
    console.log("I repeat, this promise is now resolved!");
});