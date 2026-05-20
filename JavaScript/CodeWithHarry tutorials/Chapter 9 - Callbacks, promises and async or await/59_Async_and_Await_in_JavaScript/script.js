// async function Ahnaf() {
//     return 3;
// }

// Ahnaf().then((x) => {
//     alert(x);
// });

async function getWheatherInfo(){
    let RangpurWeather = new Promise((resolve, reject) => {
        setTimeout(() => {
            resolve("35 Degree Celsius");
        }, 1000);
    });

    let DhakaWeather = new Promise((resolve, reject) => {
        setTimeout(() => {
            resolve("40 Degree Celsius");
        }, 2000);
    });
    // RangpurWeather.then(console.log);
    // DhakaWeather.then(console.log);
    let RangpurTemp = await RangpurWeather;
    let DhakaTemp = await DhakaWeather;
    return [RangpurTemp, DhakaTemp];
}

let a = getWheatherInfo();
a.then(console.log);