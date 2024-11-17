# XO Game in C

A repository containing two Tic Tac Toe games written in C:
1. **Terminal-based XO Game**: A simple text-based command-line game.
2. **Graphical XO Game**: A visually appealing version built using the Raylib library.

---

## Features
### Terminal-based XO Game
- Two-player mode.
- Simple text-based interface.

### Graphical XO Game
- Two-player mode.
- User-friendly graphical interface powered by Raylib.

---

## Prerequisites
### For Linux
1. **GCC** (GNU Compiler Collection)
2. **Git** (to clone the repository)

### For Windows
1. **MinGW** (Minimalist GNU for Windows) or another GCC compiler.
2. **Git** (to clone the repository)

---

## How to Clone the Repository

1. Clone the Repository:
    ```bash
    git clone https://github.com/Saitej2456/xo_game.git
    ```
2. Navigate to the project directory:
    ```bash
    cd xo_game
    ```

---

## How to Run the Terminal-based XO Game

### On Linux/Windows
1. Navigate to the terminal game directory:
    ```bash
    cd xo/terminal_XO
    ```
2. Compile the game:
    ```bash
    gcc -o xogame terminalxo.c
    ```
3. Run the game:
    ```bash
    ./xogame
    ```


---

## How to Run the Graphical XO Game

### On Linux
1. Navigate to the graphical game directory:
    ```bash
    cd xo/Graphical_XO
    ```
2. Install wine to run the executable:
    ```bash
    sudo apt update
    sudo apt install wine

    ```
3. Run the game:
    ```bash
    wine xom.exe
    ```

### On Windows
1. Open the **Command Prompt** or **MinGW terminal**.
2. Navigate to the graphical game directory:
    ```cmd
    cd xo\graphical_XO
    ```
3. Run the executable file:
    ```cmd
    ./xom
    ```
