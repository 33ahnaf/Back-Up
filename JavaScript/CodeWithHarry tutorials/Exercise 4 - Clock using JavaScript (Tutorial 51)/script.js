let days_of_the_week = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"];
let months_of_the_year = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December'];

const updateTime = () => {
    let current_time = new Date();
    let div_of_DayMonthDateYear = document.getElementById("day-month-date-year");
    let div_of_hour_minute_second = document.getElementById("hour-minute-second");

    let day = days_of_the_week[current_time.getDay()];
    let month = months_of_the_year[current_time.getMonth()];
    let date = current_time.getDate();
    let year = current_time.getFullYear();
    let hour = '' + current_time.getHours();
    hour.length < 2 ? hour = '0' + hour : void(0);
    let minute = '' + current_time.getMinutes();
    minute.length < 2 ? minute = '0' + minute : void(0);
    let second = '' + current_time.getSeconds();
    second.length < 2 ? second = '0' + second : void(0);
    
    div_of_DayMonthDateYear.innerHTML = `<h1>${day} - ${month} ${date}, ${year}</h1>`;
    div_of_hour_minute_second.innerHTML = `<h1>${hour}:${minute}:${second}</h1>`;
}

setTimeout(function () {
    setInterval(updateTime, 250);
}, 3000); // easter egg :D