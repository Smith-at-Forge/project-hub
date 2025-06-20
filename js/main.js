// Randomly select a background image from the array
const imagesArr = [
  "./assets/images/swe-photo-1.avif",
  "./assets/images/swe-photo-2.avif",
  "./assets/images/swe-photo-3.avif",
];
const randomIndex = Math.floor(Math.random() * imagesArr.length);
const selectedImage = imagesArr[randomIndex];
document.body.style.backgroundImage = `url('${selectedImage}')`;
document.body.style.backgroundSize = "cover";
document.body.style.backgroundPosition = "center";

// Handle navigation between pages using AJAX
document.addEventListener("DOMContentLoaded", () => {
  const content = document.querySelector(".maincontent");
  const links = document.querySelectorAll("a[data-page]");

  links.forEach((link) => {
    link.addEventListener("click", async (e) => {
      // Using href="#" as a placeholder prevents real navigation.
      // The default behavior is suppressed with event.preventDefault() in the event listener.
      // This is a common pattern for links handled dynamically via JavaScript.
      e.preventDefault();
      const page = link.getAttribute("data-page");

      try {
        const response = await fetch(page);
        const html = await response.text();
        content.innerHTML = html;
      } catch (err) {
        content.innerHTML =
          "<p>Content could not be loaded. Please check the console for errors.</p>";
        console.error(err);
      }
    });
  });
});
