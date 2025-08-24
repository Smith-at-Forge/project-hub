import express from "express";
import qr from "qr-image";
import fs from "fs";
import { dirname } from "path"; // 'dirname' gets the directory name from a file path.
import { fileURLToPath } from "url"; // 'fileURLToPath' converts a file URL (from ES modules) to a standard path string.

const __dirname = dirname(fileURLToPath(import.meta.url));
const app = express();
const port = 3000;

app.use(express.static(__dirname)); // Serve static files from the current directory
app.use(express.urlencoded({ extended: true })); // Middleware to parse URL-encoded bodies

// Input sanitization function
function sanitizeInput(input) {
  const trimmed = input.trim();
  // Limit input length (e.g., 200 characters)
  if (trimmed.length > 200) return null;
  // Allow only letters, numbers, spaces and a few punctuation characters
  // Allowed characters: a-z, A-Z, 0-9, space, dash, underscore, colon, slash, question mark, ampersand, dot, equals, plus, comma, percent
  if (/[^a-zA-Z0-9 \-_:\/\?&\.=+,%]/.test(trimmed)) return null;
  return trimmed;
}

app.get("/", (userInput, serverOutput) => {
  serverOutput.sendFile(__dirname + "/index.html");
});

app.post("/check", (userInput, serverOutput) => {
  // Get the raw user input.
  const rawInput = userInput.body.key_ident || "";
  const sanitizedInput = sanitizeInput(rawInput);

  // If input is invalid, send an error response.
  if (!sanitizedInput) {
    return serverOutput.status(400).send("Invalid input provided.");
  }

  // Generate the QR code from the sanitized input.
  const qr_png = qr.image(sanitizedInput, { type: "png" });
  const filePath = __dirname + "/qr.png";

  // Remove any existing QR code file to prevent conflicts.
  if (fs.existsSync(filePath)) {
    fs.unlinkSync(filePath);
  }

  const writeStream = fs.createWriteStream(filePath);
  qr_png.pipe(writeStream).on("finish", () => {
    // Wait shortly to ensure the file is fully written.
    setTimeout(() => {
      serverOutput.sendFile(filePath);
    }, 1000);
  });
});

app.listen(port, () => {
  console.log(`Server started on port ${port}`);
});
