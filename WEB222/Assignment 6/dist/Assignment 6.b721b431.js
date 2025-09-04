// js/forms.js
(function () {
  // Utilities
  function isValidEmail(value) {
    return /\S+@\S+\.\S+/.test(value);
  }
  function splitMultiUrls(value) {
    return value
      .split(/[\s,]+/)
      .map((s) => s.trim())
      .filter(Boolean);
  }
  function validateUrl(value) {
    try {
      const u = new URL(value);
      return !!u.protocol && !!u.host;
    } catch {
      return false;
    }
  }
  function setStatus(el, msg, isError = false) {
    if (!el) return;
    el.textContent = msg;
    el.classList.toggle("error", isError);
  }
  async function postForm(form, statusEl) {
    const data = new FormData(form);
    setStatus(statusEl, "Submitting\u2026");
    try {
      const res = await fetch(form.action, {
        method: "POST",
        body: data,
      });
      if (!res.ok) throw new Error(`HTTP ${res.status}`);
      setStatus(statusEl, "Thanks! Submission received.");
      form.reset();
    } catch (err) {
      setStatus(statusEl, "Submission failed. Please try again.", true);
    }
  }
  // Newsletter form
  const newsletterForm = document.getElementById("newsletter-form");
  if (newsletterForm) {
    const emailInput = document.getElementById("newsletter-email");
    const statusEl = document.getElementById("newsletter-status");
    newsletterForm.addEventListener("submit", (e) => {
      e.preventDefault();
      if (!emailInput.value || !isValidEmail(emailInput.value)) {
        setStatus(statusEl, "Please enter a valid email address.", true);
        emailInput.focus();
        return;
      }
      postForm(newsletterForm, statusEl);
    });
  }
  // Request Artist page
  const artistForm = document.getElementById("artist-form");
  if (artistForm) {
    const statusEl = document.getElementById("artist-status");
    const nameEl = document.getElementById("artist-name");
    const genreEl = document.getElementById("genre");
    const socialEl = document.getElementById("social-urls");
    const mediaList = document.getElementById("media-list");
    const addMediaBtn = document.getElementById("add-media");
    addMediaBtn.addEventListener("click", () => {
      const count = mediaList.querySelectorAll(".media-item").length;
      const wrap = document.createElement("div");
      wrap.className = "inline media-item";
      const input = document.createElement("input");
      input.type = "url";
      input.name = "mediaUrls[]";
      input.id = `media-${count}`;
      input.placeholder = "https://example.com/song-or-video";
      input.setAttribute("inputmode", "url");
      const removeBtn = document.createElement("button");
      removeBtn.type = "button";
      removeBtn.className = "remove-media";
      removeBtn.textContent = "Remove";
      removeBtn.addEventListener("click", () => wrap.remove());
      wrap.appendChild(input);
      wrap.appendChild(removeBtn);
      mediaList.appendChild(wrap);
      toggleRemoveButtons();
    });
    function toggleRemoveButtons() {
      const items = mediaList.querySelectorAll(".media-item");
      const showRemove = items.length > 1;
      items.forEach((item) => {
        const btn = item.querySelector(".remove-media");
        if (btn) btn.hidden = !showRemove;
      });
    }
    toggleRemoveButtons();
    artistForm.addEventListener("submit", (e) => {
      e.preventDefault();
      if (!nameEl.value.trim()) {
        setStatus(statusEl, "Please enter the artist\u2019s name.", true);
        nameEl.focus();
        return;
      }
      if (!genreEl.value.trim()) {
        setStatus(statusEl, "Please choose or type a genre.", true);
        genreEl.focus();
        return;
      }
      const socialRaw = socialEl.value.trim();
      if (socialRaw) {
        const socials = splitMultiUrls(socialRaw);
        const invalid = socials.filter((u) => !validateUrl(u));
        if (invalid.length) {
          setStatus(statusEl, "One or more social URLs are invalid.", true);
          socialEl.focus();
          return;
        }
        artistForm.append("socialUrlsParsed", JSON.stringify(socials));
      }
      const mediaInputs = [
        ...mediaList.querySelectorAll('input[name="mediaUrls[]"]'),
      ];
      const mediaUrls = mediaInputs.map((i) => i.value.trim()).filter(Boolean);
      const bad = mediaUrls.filter((u) => !validateUrl(u));
      if (bad.length) {
        setStatus(statusEl, "One or more song/video URLs are invalid.", true);
        const firstBad = mediaInputs.find(
          (i) => i.value && !validateUrl(i.value),
        );
        if (firstBad) firstBad.focus();
        return;
      }
      postForm(artistForm, statusEl);
    });
  }
})();

//# sourceMappingURL=Assignment 6.b721b431.js.map
