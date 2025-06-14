// This is a simple JavaScript code that adds an event listener to a button.
// Two parameters are passed to the `addEventListener` method:
// 1. The event type (in this case, "click")
// 2. The function to be executed when the event occurs (in this case, `handleClick`)
// The button is selected using `document.querySelector("button")`
// ("click", handleClick()) in Event Listener would call the function asap
document.querySelector("button").addEventListener("click", handleClick);

function handleClick() {
  /* alert("I got clicked!"); */
}

for (let i = 0; i < document.querySelectorAll(".drum").length; i++) {
  // Concept with anonymous function
  // You can use this block solo without the for loop
  document.querySelectorAll(".drum")[i].addEventListener("click", function () {
    buttonAnimation(this.innerHTML);
    // "this" refers to the element that was clicked (the Identity)
    // console.log(this); >>>> <button class="w drum">w</button>
    switch (this.innerHTML) {
      case "w":
        let tom1 = new Audio("./sounds/tom-1.mp3");
        tom1.play();
        break;
      case "a":
        let tom2 = new Audio("./sounds/tom-2.mp3");
        tom2.play();
        break;
      case "s":
        let tom3 = new Audio("./sounds/tom-3.mp3");
        tom3.play();
        break;
      case "d":
        let tom4 = new Audio("./sounds/tom-4.mp3");
        tom4.play();
        break;
      case "j":
        let snare = new Audio("./sounds/snare.mp3");
        snare.play();
        break;
      case "k":
        let crash = new Audio("./sounds/crash.mp3");
        crash.play();
        break;
      case "l":
        let kick = new Audio("./sounds/kick-bass.mp3");
        kick.play();
        break;
      default:
        console.log(this.innerHTML);
        break;
    }

    // new Audio() is a constructor function that creates a new audio object
    // and has a method called play() that plays the audio file
    /* let audioVar = new Audio("./sounds/tom-1.mp3");
    audioVar.play(); */
    /* alert("I got clicked!"); */
  });
}
// This is an event listener that listens for a keydown event on the ENTIRE document
document.addEventListener("keydown", function (eventVar) {
  // "keydown" is an event that occurs when a key is pressed down
  // "eventVar" is a parameter that represents the event object
  // The event object contains information about the event that occurred
  // In this case, we extract the key that was pressed using eventVar.key
  // "eventVar" is passed as a parameter to the function
  // And the function is executed when a key is pressed down
  // console.log(eventVar.key); >>>> "w"
  // This type of function is called an Callback Function
  // It is a function that is passed as an argument to another function
  // And the Higher-Order Function (in this case, `addEventListener`) calls the Callback Function when the event occurs
  switch (eventVar.key) {
    case "w":
      let tom1 = new Audio("./sounds/tom-1.mp3");
      tom1.play();
      break;
    case "a":
      let tom2 = new Audio("./sounds/tom-2.mp3");
      tom2.play();
      break;
    case "s":
      let tom3 = new Audio("./sounds/tom-3.mp3");
      tom3.play();
      break;
    case "d":
      let tom4 = new Audio("./sounds/tom-4.mp3");
      tom4.play();
      break;
    case "j":
      let snare = new Audio("./sounds/snare.mp3");
      snare.play();
      break;
    case "k":
      let crash = new Audio("./sounds/crash.mp3");
      crash.play();
      break;
    case "l":
      let kick = new Audio("./sounds/kick-bass.mp3");
      kick.play();
      break;
    default:
      console.log(eventVar.key);
  }
});

function buttonAnimation(currentKey) {
  // This function adds a CSS class to the button that was clicked
  // The class is added for a short period of time and then removed
  let activeButton = document.querySelector("." + currentKey);
  // The class "pressed" is added to the button that was clicked
  activeButton.classList.add("pressed");
  // setTimeout is a function that executes a function after a specified amount of time
  setTimeout(function () {
    // The class "pressed" is removed from the button after 100 milliseconds
    activeButton.classList.remove("pressed");
  }, 100);
}
