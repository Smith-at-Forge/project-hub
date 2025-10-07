  function startGameHandler() {
    console.log("Hello World");
  }

  document.addEventListener("DOMContentLoaded", function () {
    document.addEventListener("keydown", startGameHandler);

    document.addEventListener("click", startGameHandler);
  });