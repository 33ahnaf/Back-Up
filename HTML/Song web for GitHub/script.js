let list_of_songs = {
    "Stereo Love": "Stereo Love.mp4",
    "Ride It": "Ride It.mp4",
    "CODER": "CODER.mp4",
    "After Dark": "After Dark.mp4",
    "Dreaveler": "Dreaveler.mp4",
    "Drugs": "Drugs.mp4",
    "Dandelions": "Dandelions.mp4",
    "Play Date": "Play Date.mp4",
    "Runaway": "Runaway.mp4",
    "Love Story": "Love Story.mp4",
    "Alone Pt. II": "Alone Pt II.mp4",
    "Safe And Sound": "Safe And Sound.mp4",
    "Who Is She": "Who Is She.mp4",
    "number one girl": "number one girl.mp4",
    "The Perfect Girl": "The Perfect Girl.mp4",
    "Lost Soul": "Lost Soul.mp4",
    "The Lost Soul Down": "The Lost Soul Down.mp4",
    "Death Is No More": "Death Is No More.mp4",
    "FE!N": "FE!N.mp4",
    "Midnight City": "Midnight City.mp4",
    "Mysterious Game": "Mysterious Game.mp4",
    "Patience Is A Virtue": "Patience Is A Virtue.mp4",
    "Señorita": "Senorita.mp4",
    "Old Town Road": "Old Town Road.mp4",
    "The Last of Us Theme Song": "The Last of Us Theme Song.mp4",
    "Talking To The Moon": "Talking To The Moon.mp4",
    "Rap God": "Rap God.mp4",
    "APT": "APT.mp4",
    "Cheri Cheri Lady": "Cheri Cheri Lady.mp4",
    "Faded": "Faded.mp4",
    "Fluxxwave": "Fluxxwave.mp4",
    "GANGSTA'S PARADISE": "GANGSTAS PARADISE.mp4",
    "Shootout": "Shootout.mp4",
    "Shootout (slowed)": "Shootout (slowed).mp4",
    "Skyfall": "Skyfall.mp4",
    "Arcade": "Arcade.mp4",
    "Ava": "Ava.mp4",
    "Love Me Again": "Love Me Again.mp4",
    "Cotton Spheres": "Cotton Spheres.mp4",
    "Cradles": "Cradles.mp4",
    "Dancin": "Dancin.mp4",
    "GOTH": "GOTH.mp4",
    "House of Memories": "House of Memories.mp4",
    "Hung Up": "Hung Up.mp4",
    "Levitating": "Levitating.mp4",
    "Moral of the Story": "Moral of the Story.mp4",
    "On The Floor": "On The Floor.mp4",
    "Past Lives": "Past Lives.mp4",
    "Blinding Lights": "Blinding Lights.mp4",
    "Moonlight": "Moonlight.mp4",
    "Stay": "Stay.mp4",
    "Die With A Smile": "Die With A Smile.mp4"
};

let main_div = document.getElementById("main_div");
let footer_section = document.getElementById("footer-section");
let content = "";

for(let i = 0; i < Object.keys(list_of_songs).length; i++){
    content += `<div class="song"><h2>${Object.keys(list_of_songs)[i]}</h2><video width="300px" controls><source src="${list_of_songs[Object.keys(list_of_songs)[i]]}" type="video/mp4">Something went wrong!</video></div>`;
}

main_div.innerHTML = content;

let username = prompt("Username:");
if (username == "Meghna" || username == "meghna" || username == "Afrina" || username == "afrina" || username == "Ahnaf1024" || username == "ahnaf1024"){
	footer_section.innerHTML = `<h2>Special Shoutout 💖</h2><p>This entire site exists because of a convo about our favorite tracks.<br>Big thanks to <strong>Meghna</strong> — you brought the vibe ✨</p><p>Also special thanks to <a href="https://www.youtube.com/@7clouds" target="_blank">7clouds</a> and the amazing artists for the music inspiration.</p><p><em><b>&copy; Ahnaf Shariar 2025. All rights reserved.</b></em></p>`;
}else{
	footer_section.innerHTML = `<h2>Special Shoutout 💖</h2><p>Special thanks to <a href="https://www.youtube.com/@7clouds" target="_blank">7clouds</a> and the amazing artists for the music inspiration.</p><p><em><b>&copy; Ahnaf Shariar 2025. All rights reserved.</b></em></p>`;
}

console.log("12 hours of work");
console.log("Made with 🎵 and ❤️ — sparkled by Meghna");