// Array of button IDs
let btnArray = ["green", "red", "yellow", "blue"];
// Array to hold the generated sequence
let btnSelectedArray = [];
// Array to hold the user's input sequence
let btnClickedArray = [];

// Flag to track the game state; prevents starting a new game while one is active.
let gameFlag = false;

// Named function for the start game handler.
// To activate and deactivate the event listener.
function startGameHandler() {
  if (!gameFlag) {
    startRound();
  }
}

$(document).ready(function () {
  // Event listener for starting the game.
  // Starts on keydown or click.
  $(document).on("keydown click", startGameHandler);
});

// Starts a new round of the game.
// Resets the user's clicks, adds a new color to the sequence,
// and plays the animation.
function startRound() {
  gameFlag = true;
  btnClickedArray = [];

  let randomNum = Math.floor(Math.random() * 4);
  let btnSelected = btnArray[randomNum];
  btnSelectedArray.push(btnSelected);
  console.log("Sequence:", btnSelectedArray);

  $("#level-title").css("color", "#80aeac");
  $("#status").text("Memorize");
  $("#rules").css("color", "#80aeac");

  for (let i = 0; i < btnSelectedArray.length; i++) {
    setTimeout(function () {
      $("#" + btnSelectedArray[i])
        .fadeOut(250)
        .fadeIn(250);
    }, i * 700);
  }

  setTimeout(function () {
    console.log("Your turn to click!");
    $("#status").text("Your turn");
    $(".btn").off("click").on("click", handleClick);
  }, btnSelectedArray.length * 700);
}

// Handles the user's click on a Simon button.
// This is the core game logic during the user's turn.
function handleClick() {
  const btnId = $(this).attr("id");
  $("#" + btnId)
    .fadeOut(150)
    .fadeIn(150);
  btnClickedArray.push(btnId);
  console.log("Clicked so far:", btnClickedArray);

  const lastClickIndex = btnClickedArray.length - 1;

  if (btnClickedArray[lastClickIndex] !== btnSelectedArray[lastClickIndex]) {
    handleGameOver();
  } else if (btnClickedArray.length === btnSelectedArray.length) {
    console.log("Correct! Proceeding to the next round.");
    $(".btn").off("click");
    setTimeout(startRound, 1000);
  }
}

// Executes the game-over sequence.
// Disables input, shows an alert, and resets the game state.
function handleGameOver() {
  console.log("Wrong! Game over. Resetting the game.");
  $(".btn").off("click");

  // deactivates the start listener before the alert appears
  $(document).off("keydown click", startGameHandler);

  alert("That's wrong, give it another try!");

  btnSelectedArray = [];
  gameFlag = false;

  $("#level-title").css("color", "#FFF1CA");
  $("#status").text("Get ready!");
  $("#rules").css("color", "#000");

  // This allows the start listener to be reactivated after a short delay,
  // ignoring the click from closing the alert.
  setTimeout(function () {
    $(document).on("keydown click", startGameHandler);
  }, 100);
}
