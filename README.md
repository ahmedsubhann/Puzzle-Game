# 🧩 24-Puzzle Console Game

A command-line 24-puzzle game developed in C++. Test your logic and strategy as you arrange numbered tiles into the correct order, starting from a randomized (yet solvable) board layout.

---

## 💡 Game Highlights

- 🔄 **Random Puzzle Generation**: Starts with a new, solvable tile configuration each time.
- 💾 **Save & Resume**: Automatically saves your progress. Load previous sessions using your game ID.
- 🧭 **Move Guidance**: Displays possible directions you can move (Up, Down, Left, Right).
- 📜 **Move Tracking**: Keeps a log of your path to solution.
- 🎨 **Enhanced Console Display**: Uses Windows API to add color and improve visual feedback.

---

## 🔧 Tech Stack

| Component   | Details                             |
|-------------|--------------------------------------|
| Language    | C++                                  |
| Platform    | Windows OS                           |
| Libraries   | `windows.h`, `conio.h`, `ctime`, `fstream` |

---

## ▶️ Getting Started

1. **Run the executable.**
2. **Select an option:**
   - 🆕 **Start New Game** – Creates a fresh solvable puzzle.
   - 📂 **Load Existing Game** – Resume progress by entering your saved ID.
   - ❓ **Instructions** – Learn how the game works.
3. **Use the displayed valid keys** to move tiles.
4. **To save and exit**, press `1` during gameplay.

---

## 📁 Required Files

Ensure that `ids.txt` is located in the same directory as your `24PuzzleGameCode.cpp` file. It stores saved game identifiers.

---

## 👤 Created By

Developed by **Ahmed Subhan**  
Inspired collaboration with a friend to expand the project’s reach and usability.
