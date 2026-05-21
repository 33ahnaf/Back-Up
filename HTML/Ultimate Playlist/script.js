import { lyricss } from "./lyrics.js"; // importing the JS file containing the lyrics

// creating a object which contains song name, author name and file paths
const songs = [
  { song_name: "En nuit", author_name: "VIDEOCLUB", file_path: "En nuit.mp4", tn_path: "En nuit tn.jpg" },
  { song_name: "BIRDS OF A FEATHER", author_name: "Billie Eilish", file_path: "BIRDS OF A FEATHER.mp4", tn_path: "BIRDS OF A FEATHER tn.jpg" },
  { song_name: "this is what heartbreak feels like", author_name: "JVKE", file_path: "this is what heartbreak feels like.mp4", tn_path: "this is what heartbreak feels like tn.jpg" },
  { song_name: "Fluxxwave", author_name: "Clovis Reyes", file_path: "Fluxxwave.mp4", tn_path: "Fluxxwave tn.jpg" },
  { song_name: "Romantic Homicide", author_name: "d4vd", file_path: "Romantic Homicide.mp4", tn_path: "Romantic Homicide tn.jpg" },
  { song_name: "Safe And Sound", author_name: "Capital Cities", file_path: "Safe And Sound.mp4", tn_path: "Safe And Sound tn.jpg" },
  { song_name: "Sweater Weather", author_name: "The Neighbourhood", file_path: "Sweater Weather.mp4", tn_path: "Sweater Weather tn.jpg" },
  { song_name: "Midnight City", author_name: "M83", file_path: "Midnight City.mp4", tn_path: "Midnight City tn.jpg" },
  { song_name: "Let It Happen", author_name: "Tame Impala", file_path: "Let It Happen(shorter).mp4", tn_path: "Let It Happen(shorter) tn.jpg" },
  { song_name: "assumptions", author_name: "Sam Gellaitry", file_path: "assumptions.mp4", tn_path: "assumptions4 tn.png" },
  { song_name: "Golden Brown", author_name: "The Stranglers", file_path: "Golden Brown.mp4", tn_path: "Golden Brown tn.jpg" },
  { song_name: "Chamber of Reflection", author_name: "Mac DeMarco", file_path: "Chamber Of Reflection.mp4", tn_path: "Chamber Of Reflection tn.jpg" },
  { song_name: "After Dark", author_name: "Mr.Kitty", file_path: "After Dark.mp4", tn_path: "After Dark tn.jpg" },
  { song_name: "Alone, Pt. II", author_name: "Alan Walker && Ava Max", file_path: "Alone Pt II.mp4", tn_path: "Alone Pt II tn.jpg" },
  { song_name: "APT.", author_name: "Bruno Mars && Rosé", file_path: "APT.mp4", tn_path: "APT3 tn.png" },
  { song_name: "Blue", author_name: "Yung Kai", file_path: "blue.mp4", tn_path: "blue tn.jpg" },
  { song_name: "CODER", author_name: "Astrofusion", file_path: "CODER.mp4", tn_path: "CODER tn.jpg" },
  { song_name: "Comfort Chain", author_name: "Instupendo", file_path: "Comfort Chain.mp4", tn_path: "Comfort Chain tn.jpg" },
  { song_name: "Cotton Spheres", author_name: "Lama House", file_path: "Cotton Spheres.mp4", tn_path: "Cotton Spheres tn.jpg" },
  { song_name: "Crystal Skies", author_name: "ENXK, VXLLAIN && iGRES", file_path: "Crystal Skies.mp4", tn_path: "Crystal Skies tn.jpg" },
  { song_name: "Dancefloor Dreamer", author_name: "NIVIRO", file_path: "Dancefloor Dreamer.mp4", tn_path: "Dancefloor Dreamer tn.jpg" },
  { song_name: "Dandelions", author_name: "Ruth B.", file_path: "Dandelions.mp4", tn_path: "Dandelions tn.jpg" },
  { song_name: "did i tell u that i miss u", author_name: "adore", file_path: "did i tell u that i miss u.mp4", tn_path: "did i tell u that i miss u tn.jpg" },
  { song_name: "Dreaveler", author_name: "Pensees", file_path: "Dreaveler.mp4", tn_path: "Dreaveler tn.jpg" },
  { song_name: "Drugs", author_name: "OBESØN", file_path: "Drugs.mp4", tn_path: "Drugs tn.jpg" },
  { song_name: "FE!N", author_name: "Travis Scott", file_path: "FE!N.mp4", tn_path: "FE!N tn.jpg" },
  { song_name: "Freaks", author_name: "Surf Curse", file_path: "Freaks.mp4", tn_path: "Freaks tn.jpg" },
  { song_name: "GANGSTA'S PARADISE", author_name: "Coolio", file_path: "GANGSTA'S PARADISE.mp4", tn_path: "GANGSTA'S PARADISE tn.jpg" },
  { song_name: "Glue Song", author_name: "beabadoobee", file_path: "Glue Song.mp4", tn_path: "Glue Song tn.png" },
  { song_name: "Heat Waves", author_name: "Glass Animals", file_path: "Heat Waves.mp4", tn_path: "Heat Waves tn.jpg" },
  { song_name: "Honeypie", author_name: "Jawny", file_path: "Honeypie.mp4", tn_path: "Honeypie tn.jpg" },
  { song_name: "Hurts So Good", author_name: "Astrid S", file_path: "Hurts So Good.mp4", tn_path: "Hurts So Good tn.jpg" },
  { song_name: "Let Go", author_name: "Ark Patrol", file_path: "Let Go.mp4", tn_path: "Let Go tn.jpg" },
  { song_name: "Let It Happen (long)", author_name: "Tame Impala", file_path: "Let It Happen.mp4", tn_path: "Let It Happen tn.jpg" },
  { song_name: "Lost Soul", author_name: "NBSPLV", file_path: "Lost Soul.mp4", tn_path: "Lost Soul tn.jpg" },
  { song_name: "Love Me Again", author_name: "John Newman", file_path: "Love Me Again.mp4", tn_path: "Love Me Again tn.jpg" },
  { song_name: "Lovers Rock", author_name: "TV Girl", file_path: "Lovers Rock.mp4", tn_path: "Lovers Rock tn.png" },
  { song_name: "Mockingbird", author_name: "Eminem", file_path: "Mockingbird.mp4", tn_path: "Mockingbird tn.jpg" },
  { song_name: "Moonlight", author_name: "Kali Uchis", file_path: "Moonlight.mp4", tn_path: "Moonlight tn.jpg" },
  { song_name: "Mysterious Game", author_name: "LXNGVX", file_path: "Mysterious Game.mp4", tn_path: "Mysterious Game tn.jpg" },
  { song_name: "New Person, Same Old Mistakes", author_name: "Tame Impala", file_path: "New Person, Same Old Mistakes.mp4", tn_path: "New Person, Same Old Mistakes tn.jpg" },
  { song_name: "next to you", author_name: "Øneheart", file_path: "next to you.mp4", tn_path: "next to you tn.jpg" },
  { song_name: "number one girl", author_name: "Rosé", file_path: "number one girl.mp4", tn_path: "number one girl tn.jpg" },
  { song_name: "Past Lives", author_name: "Slushii && sapientdream", file_path: "Past Lives.mp4", tn_path: "Past Lives tn.jpg" },
  { song_name: "Patience Is a Virtue", author_name: "Clem Leek", file_path: "Patience Is a Virtue.mp4", tn_path: "Patience Is A Virtue tn.jpg" },
  { song_name: "Play Date", author_name: "Melanie Martinez", file_path: "Play Date.mp4", tn_path: "Play Date tn.jpg" },
  { song_name: "Resonance", author_name: "HOME", file_path: "Resonance.mp4", tn_path: "Resonance tn.jpg" },
  { song_name: "ROI", author_name: "VIDEOCLUB", file_path: "ROI.mp4", tn_path: "ROI tn.jpg" },
  { song_name: "ROI (instrumental)", author_name: "VIDEOCLUB", file_path: "ROI INSTRUMENTAL.mp4", tn_path: "ROI INSTRUMENTAL tn.jpg" },
  { song_name: "roi x did i tell u that i miss u", author_name: "VIDEOCLUB, adore", file_path: "roi x did i tell u that i miss u.mp4", tn_path: "roi x did i tell u that i miss u tn.jpg" },
  { song_name: "Runaway", author_name: "AURORA", file_path: "Runaway.mp4", tn_path: "Runaway tn.jpg" },
  { song_name: "Señorita", author_name: "Camila Cabello && Shawn Mendes", file_path: "Senorita.mp4", tn_path: "Senorita tn.jpg" },
  { song_name: "Shootout", author_name: "Izzamuzzic && Julien Marchal", file_path: "Shootout.mp4", tn_path: "Shootout tn.jpg" },
  { song_name: "The Lost Soul Down", author_name: "NBSPLV", file_path: "The Lost Soul Down.mp4", tn_path: "The Lost Soul Down tn.jpg" },
  { song_name: "The Perfect Girl", author_name: "Mareux", file_path: "The Perfect Girl.mp4", tn_path: "The Perfect Girl tn.jpg" },
  { song_name: "this is what falling in love feels like", author_name: "JVKE", file_path: "this is what falling in love feels like.mp4", tn_path: "this is what falling in love feels like tn.jpg" },
  { song_name: "Two Different Worlds", author_name: "KORUSE && mzmff", file_path: "Two Different Worlds.mp4", tn_path: "Two Different Worlds tn.jpg" },
  { song_name: "Two Different Worlds (slowed + reverbed)", author_name: "KORUSE && mzmff", file_path: "Two Different Worlds(slowed).mp4", tn_path: "Two Different Worlds(slowed) tn.jpg" },
  { song_name: "Who Is She?", author_name: "I Monster", file_path: "Who Is She.mp4", tn_path: "Who Is She tn.jpg" }
];

const mainDiv = document.getElementById("main-div"); // div of main contents

// main renderer function
function mainRenderer() {
  mainDiv.innerHTML = ""; // making sure mainDiv is empthy
  songs.forEach(song => {
    const song_card = document.createElement("div");
    song_card.className = "video-card";
    song_card.innerHTML = `
      <div class="thumbnail">
        <img src="${song.tn_path}" alt="Video Thumbnail">
      </div>
      <div class="title">${song.author_name} - ${song.song_name}</div>
    `;
    song_card.onclick = () => playerRenderer(song);
    mainDiv.appendChild(song_card);
  });
}

function playerRenderer(song) {
  mainDiv.innerHTML = `
    <div id="only-one">
      <video id="video" controls autoplay width="100%">
          <source src="${song.file_path}" type="video/mp4">
          Your browser does not support the video tag.
      </video>
      <div class="title">${song.author_name} - ${song.song_name}</div>
    </div>
    <div class="btn-bar">
      <button id="back-btn" class="action-btn">Back</button>
      <button id="lyrics-btn" class="action-btn">Lyrics</button>
    </div>
  `;
  document.getElementById("back-btn").addEventListener("click", goBack);
  document.getElementById("lyrics-btn").addEventListener("click", () => lyricsRenderer(song));
}

function goBack() {
  mainDiv.innerHTML = "";
  mainRenderer();
}

function parseLRC(str) {
  return str.trim().split(/\r?\n/).map(line => {
    const m = line.match(/\[(\d{2}):(\d{2})(?:\.(\d{2,3}))?\](.*)/);
    if(!m) return null;
    const min = +m[1], sec = +m[2];
    const frac = m[3] ? (m[3].length === 3 ? +m[3] : +m[3] * 10) : 0;
    return { t: min * 60 + sec + frac / 1000, text: m[4].trim() };
  }).filter(Boolean).sort((a, b) => a.t - b.t);
}

function lyricsRenderer(song) {
  const modal = document.getElementById("lyrics-modal");
  const container = document.getElementById("lyrics");
  const video = document.getElementById("video");
  const song_lyrics = lyricss[song.song_name];
  const lyrics_title = document.getElementById("lyrics-title");
  lyrics_title.textContent = `${song.author_name} - ${song.song_name}`;

  modal.style.display = "flex";
  container.innerHTML = "";

  const lines = parseLRC(song_lyrics);

  lines.forEach(line => {
    const p = document.createElement("p");
    p.textContent = line.text || " ";
    container.appendChild(p);
  });

  function currentIndex(t) {
    let i = 0;
    while(i < lines.length && t >= lines[i].t) i++;
    return i - 1;
  }

  let active = -1;
  function tick() {
    const t = video.currentTime;
    const i = currentIndex(t);

    if(i !== active){
      if(active >= 0) container.children[active].classList.remove("active");
      if(i >= 0){
        const el = container.children[i];
        el.classList.add("active");
        el.scrollIntoView({ block: "center", behavior: "smooth" });
      }
      active = i;
    }
    requestAnimationFrame(tick);
  }
  requestAnimationFrame(tick);

  document.getElementById("close-lyrics").onclick = () => {
    modal.style.display = "none";
  };
}

mainRenderer();

console.log("Life isn't the party we imagined, but since we are here, lets dance");