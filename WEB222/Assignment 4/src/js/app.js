document.addEventListener("DOMContentLoaded", () => {
  const menuEl = document.getElementById("menu");
  const selectedArtistEl = document.getElementById("selected-artist");
  const songsTbody = document.getElementById("songs");

  window.artists.forEach((artist, index) => {
    const btn = document.createElement("button");
    btn.textContent = artist.name;
    btn.addEventListener("click", () => showArtist(artist));
    menuEl.appendChild(btn);
    if (index === 0) showArtist(artist);
  });

  function showArtist(artist) {
    selectedArtistEl.innerHTML = "";
    selectedArtistEl.appendChild(document.createTextNode(artist.name + " "));
    Object.keys(artist.links).forEach((key, i, arr) => {
      const a = document.createElement("a");
      a.href = artist.links[key];
      a.target = "_blank";
      a.textContent = key.charAt(0).toUpperCase() + key.slice(1);
      selectedArtistEl.appendChild(a);
      if (i < arr.length - 1) selectedArtistEl.appendChild(document.createTextNode(", "));
    });

    songsTbody.innerHTML = "";
    const filtered = window.songs
      .filter((song) => song.artistId === artist.id)
      .filter((song) => !song.flagged);

    filtered.forEach((song) => {
      const tr = document.createElement("tr");
      tr.addEventListener("click", () => console.log({ song }));

      const tdTitle = document.createElement("td");
      const link = document.createElement("a");
      link.href = song.url;
      link.target = "_blank";
      link.textContent = song.title;
      tdTitle.appendChild(link);
      tr.appendChild(tdTitle);

      const tdYear = document.createElement("td");
      tdYear.textContent = song.year;
      tr.appendChild(tdYear);

      const tdDur = document.createElement("td");
      const minutes = Math.floor(song.durationSec / 60);
      const seconds = String(song.durationSec % 60).padStart(2, "0");
      tdDur.textContent = `${minutes}:${seconds}`;
      tr.appendChild(tdDur);

      songsTbody.appendChild(tr);
    });
  }
});
