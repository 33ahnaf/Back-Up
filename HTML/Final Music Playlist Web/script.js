let songs = [
    { song_name: "Safe and Sound", author_name: "Capital Cities", file_path: "../My Favourite Songs Website/my_playlist/Safe and Sound.mp4" },
    { song_name: "After Dark", author_name: "Mr. Kitty", file_path: "../My Favourite Songs Website/my_playlist/After Dark.mp4" },
    { song_name: "Alone, Pt. II", author_name: "Alan Walker & Ava Max", file_path: "../My Favourite Songs Website/my_playlist/Alone, Pt. II.mp4" },
    { song_name: "Moonlight", author_name: "Kali Uchis", file_path: "../My Favourite Songs Website/my_playlist/Moonlight.mp4" },
    { song_name: "Talking to the Moon", author_name: "Bruno Mars", file_path: "../My Favourite Songs Website/my_playlist/Talking To The Moon.mp4" },
    { song_name: "Dandelions", author_name: "Ruth B.", file_path: "../My Favourite Songs Website/my_playlist/Dandelions.mp4" },
    { song_name: "Lovers Rock", author_name: "TV Girl", file_path: "../My Favourite Songs Website/my_playlist/Lovers Rock.mp4" },
    { song_name: "Love Me Again", author_name: "John Newman", file_path: "../My Favourite Songs Website/my_playlist/Love Me Again.mp4" },
    { song_name: "Ava", author_name: "Famy", file_path: "../My Favourite Songs Website/my_playlist/Ava.mp4" },
    { song_name: "Dreaveler", author_name: "Pensees", file_path: "../My Favourite Songs Website/my_playlist/Dreaveler.mp4" },
    { song_name: "Skyfall", author_name: "Adele", file_path: "../My Favourite Songs Website/my_playlist/Skyfall.mp4" },
    { song_name: "CODER", author_name: "Astrofusion", file_path: "../My Favourite Songs Website/my_playlist/CODER.mp4" },
    { song_name: "Death Is No More", author_name: "BLESSED MANE", file_path: "../My Favourite Songs Website/my_playlist/Death Is No More.mp4" },
    { song_name: "Drugs", author_name: "OBESØN", file_path: "../My Favourite Songs Website/my_playlist/Drugs.mp4" },
    { song_name: "Lost Soul", author_name: "NBSPLV", file_path: "../My Favourite Songs Website/my_playlist/Lost Soul.mp4" },
    { song_name: "FE!N", author_name: "Travis Scott", file_path: "../My Favourite Songs Website/my_playlist/FE!N.mp4" },
    { song_name: "Fluxxwave", author_name: "Clovis Reyes", file_path: "../My Favourite Songs Website/my_playlist/Fluxxwave.mp4" },
    { song_name: "Hung Up", author_name: "Madonna", file_path: "../My Favourite Songs Website/my_playlist/Hung Up.mp4" },
    { song_name: "La Câlin", author_name: "Serhat Durmus", file_path: "../My Favourite Songs Website/my_playlist/La Calin.mp4" },
    { song_name: "Midnight City", author_name: "M83", file_path: "../My Favourite Songs Website/my_playlist/Midnight City.mp4" },
    { song_name: "Moral of the Story", author_name: "Ashe", file_path: "../My Favourite Songs Website/my_playlist/Moral of the Story.mp4" },
    { song_name: "Who is She", author_name: "I Monster", file_path: "../My Favourite Songs Website/my_playlist/Who Is She.mp4" },
    { song_name: "The Perfect Girl", author_name: "Mareux", file_path: "../My Favourite Songs Website/my_playlist/The Perfect Girl.mp4" },
    { song_name: "Next To You", author_name: "Øneheart", file_path: "../My Favourite Songs Website/my_playlist/Next to You.mp4" },
    { song_name: "Old Town Road", author_name: "Lil Nas X", file_path: "../My Favourite Songs Website/my_playlist/Old Town Road.mp4" },
    { song_name: "Past Lives", author_name: "Slushii and sapientdream", file_path: "../My Favourite Songs Website/my_playlist/Past Lives.mp4" },
    { song_name: "Play Date", author_name: "Melanie Martinez", file_path: "../My Favourite Songs Website/my_playlist/Play Date.mp4" },
    { song_name: "Runaway", author_name: "AURORA", file_path: "../My Favourite Songs Website/my_playlist/Runaway.mp4" },
    { song_name: "Señorita", author_name: "Shawn Mendes & Camila Cabello", file_path: "../My Favourite Songs Website/my_playlist/Senorita.mp4" },
    { song_name: "Shape of You", author_name: "Ed Sheeran", file_path: "../My Favourite Songs Website/my_playlist/Shape of You.mp4" },
    { song_name: "Shootout", author_name: "Izzamuzzic & Julien Marchal", file_path: "../My Favourite Songs Website/my_playlist/Shootout.mp4" },
    { song_name: "The Last of Us", author_name: "Gustavo Santaolalla", file_path: "../My Favourite Songs Website/my_playlist/The Last of Us.mp4" },
    { song_name: "The Lost Soul Down", author_name: "NBSPLV", file_path: "../My Favourite Songs Website/my_playlist/The Lost Soul Down.mp4" },
    { song_name: "GANGSTA'S PARADISE", author_name: "Coolio", file_path: "https://www.youtube.com/watch?v=NMNsvyDbdMQ" },
];

let mainDiv = document.getElementById("main-div");
let content = "";

function mainRenderer() {
    songs.forEach(song => {
        const song_card = document.createElement("div");
        song_card.className = "track";
        song_card.innerHTML = `
            <p class="music-name"><strong>${song.song_name}</strong></p>
            <p class="author-name">by <strong>${song.author_name}</strong></p>
        `;
        song_card.onclick = () => playerRenderer(song);
        mainDiv.appendChild(song_card);
    });
}

function playerRenderer(song) {
    if(song.song_name == "GANGSTA'S PARADISE"){
        window.location.href = `${song.file_path}`;
    }else{
        mainDiv.innerHTML = `
            <div class="song">
                <h2>${song.song_name}</h2>
                <video width="300px" controls><source src="${song.file_path}" type="video/mp4">
                    Something went wrong!
                </video>
            </div>
            <div style="text-align: center;"><button id="back-btn">Back to songs</button></div>
            `;
        const back_button = document.getElementById("back-btn");
        back_button.addEventListener("click", goBack);
    }
}

function goBack() {
    mainDiv.innerHTML = "";
    mainRenderer();
}

mainRenderer();