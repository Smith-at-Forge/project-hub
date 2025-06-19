import qr from "qr-image";
import fs from "fs";
import readline from "readline";

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});
// Consent
rl.question("Awaiting input: ", (answer) => {
  const text = answer;
  console.log("Your input was: ", text);
  const qr_png = qr.image(text, { type: "png" });
  qr_png.pipe(fs.createWriteStream("qr.png"));
  rl.close();
});
