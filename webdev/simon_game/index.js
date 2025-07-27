// Array of button IDs
let btnArray = ["green", "red", "yellow", "blue"];
// Array to hold the generated sequence
let btnSelectedArray = [];
// Array to hold the user's input sequence
let btnClickedArray = [];

// Flag to track the game state; prevents starting a new game while one is active.
let gameFlag = false;

// NEU: Die Start-Logik wird in eine benannte Funktion ausgelagert,
// damit wir sie gezielt de- und reaktivieren können.
function startGameHandler() {
  if (!gameFlag) {
    startRound();
  }
}

$(document).ready(function () {
  // GEÄNDERT: Der Event-Listener ruft jetzt die benannte Funktion auf.
  $(document).on("keydown click", startGameHandler);
});

/**
 * @brief Starts a new round of the game.
 * Resets the user's clicks, adds a new color to the sequence, and plays the animation.
 */
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

/**
 * @brief Handles the user's click on a Simon button.
 * This is the core game logic during the user's turn.
 */
function handleClick() {
  const btnId = $(this).attr("id");
  $("#" + btnId)
    .fadeOut(100)
    .fadeIn(100);
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

/**
 * @brief Executes the game-over sequence.
 * Disables input, shows an alert, and resets the game state.
 */
function handleGameOver() {
  console.log("Wrong! Game over. Resetting the game.");
  $(".btn").off("click");

  // GEÄNDERT: Deaktiviert den Start-Listener, BEVOR der Alert erscheint.
  $(document).off("keydown click", startGameHandler);

  alert("Falsch! Spiel vorbei. Das Spiel wird zurückgesetzt.");

  btnSelectedArray = [];
  gameFlag = false;

  $("#level-title").css("color", "#FFF1CA");
  $("#status").text("Get ready!");
  $("#rules").css("color", "#000");

  // GEÄNDERT: Reaktiviert den Start-Listener mit einer kurzen Verzögerung.
  // Dadurch wird der Klick vom Schließen des Alerts ignoriert.
  setTimeout(function () {
    $(document).on("keydown click", startGameHandler);
  }, 100);
}
