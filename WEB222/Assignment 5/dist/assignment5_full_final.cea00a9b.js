// app.js
function formatDuration(seconds) {
  const mins = Math.floor(seconds / 60);
  const secs = seconds % 60;
  return `${mins}:${secs.toString().padStart(2, "0")}`;
}
function shuffleSongs(songs) {
  return songs.sort(() => Math.random() - 0.5);
}
function createSongCard(song) {
  const card = document.createElement("div");
  card.classList.add("card");
  const img = document.createElement("img");
  img.src = song.imageUrl;
  img.alt = song.title;
  img.classList.add("card-image");
  img.addEventListener("click", () => {
    window.open(song.url, "_blank");
  });
  const title = document.createElement("h3");
  title.textContent = song.title;
  const year = document.createElement("time");
  year.textContent = song.year;
  const duration = document.createElement("span");
  duration.textContent = formatDuration(song.durationSec);
  card.appendChild(img);
  card.appendChild(title);
  card.appendChild(year);
  card.appendChild(duration);
  return card;
}
function displaySongs(songs) {
  const container = document.getElementById("songs-container");
  container.innerHTML = "";
  songs.forEach((song) => {
    const card = createSongCard(song);
    container.appendChild(card);
  });
}
function scrollSongs(direction) {
  const container = document.getElementById("songs-container");
  const scrollAmount = 300;
  container.scrollBy({
    left: direction * scrollAmount,
    behavior: "smooth",
  });
}
function enableDragScroll() {
  const scroller = document.getElementById("songs-container");
  let isDown = false;
  let startX, scrollLeft;
  scroller.addEventListener("mousedown", (e) => {
    isDown = true;
    scroller.classList.add("dragging");
    startX = e.pageX - scroller.offsetLeft;
    scrollLeft = scroller.scrollLeft;
  });
  scroller.addEventListener("mouseleave", () => {
    isDown = false;
    scroller.classList.remove("dragging");
  });
  scroller.addEventListener("mouseup", () => {
    isDown = false;
    scroller.classList.remove("dragging");
  });
  scroller.addEventListener("mousemove", (e) => {
    if (!isDown) return;
    e.preventDefault();
    const x = e.pageX - scroller.offsetLeft;
    const walk = (x - startX) * 2;
    scroller.scrollLeft = scrollLeft - walk;
  });
}
window.addEventListener("DOMContentLoaded", () => {
  const shuffled = shuffleSongs(window.songs);
  displaySongs(shuffled);
  enableDragScroll();
});

//# sourceMappingURL=assignment5_full_final.cea00a9b.js.map
