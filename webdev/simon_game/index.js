// Array of button IDs
let btnArray = ["green", "red", "yellow", "blue"];
// Array to hold selected buttons
let btnSelectedArray = [];
// Array to hold clicked buttons
let btnClickedArray = [];

let gameFlag = false; // Game-Flag

$(document).ready(function () {
  // Register a keydown event to start the game
  $(document).keydown(function () {
    if (gameFlag) return; // Prevent multiple initializations
    startRound();
  });
});

// Function to start a new round
function startRound() {
  gameFlag = true; // Prevent further initializations
  btnClickedArray = []; // Reset clicked array for each round

  let randomNum = Math.floor(Math.random() * 4); // Random number generation
  let btnSelected = btnArray[randomNum]; // Select the button based on the random number
  btnSelectedArray.push(btnSelected); // Add the selected button to the array
  console.log("Sequence:", btnSelectedArray); // Log the selected button

  $("#level-title").css("color", "#80aeac");
  $("#status").text("Memorize"); // Update status text
  $("#rules").css("color", "#80aeac");
  // for loop to flash the buttons within array, with setTimeout
  for (let i = 0; i < btnSelectedArray.length; i++) {
    setTimeout(function () {
      $("#" + btnSelectedArray[i])
        .fadeOut(250)
        .fadeIn(250);
    }, i * 500); // Delay each flash by 500ms (fadeOut + fadeIn)
  }

  // Set a timeout to enable clicks after the for loop completes
  setTimeout(function () {
    console.log("Click it now!");
    $("#status").text("Your turn");
    $(".btn").on("click", handleClick);
  }, btnSelectedArray.length * 500);
}

// Register a click handler for the buttons
$(".btn").on("click", handleClick);

function handleClick() {
  if (!gameFlag) return; // Prevent clicks before the round starts

  const btnId = $(this).attr("id");
  $("#" + btnId)
    .fadeOut(250)
    .fadeIn(250);
  btnClickedArray.push(btnId);
  console.log("Clicked so far:", btnClickedArray);

  // Compare arrays if their lengths match
  if (btnClickedArray.length === btnSelectedArray.length) {
    $(".btn").off("click", handleClick); // Disable buttons to prevent further clicks
    gameFlag = false; // Reset game flag for the next round

    if (arraysEqual(btnClickedArray, btnSelectedArray)) {
      console.log("Correct! Proceeding to the next round.");
      setTimeout(function () {
        $(document).trigger("keydown");
      }, 1000);
    } else {
      console.log("Wrong! Game over. Resetting the game.");
      alert("Wrong! Game over. Resetting the game.");
      // Reset selected array and the rest
      // Clicked array is reset automatically in the next round
      btnSelectedArray = [];
      $("#level-title").css("color", "#FFF1CA");
      $("#status").text("Get ready!");
      $("#rules").css("color", "#000");
    }
  }
}

// Helper function to compare two arrays
function arraysEqual(a, b) {
  if (a.length !== b.length) return false;
  return a.every((val, idx) => val === b[idx]);
}
