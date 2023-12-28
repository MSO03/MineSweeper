# Minesweeper in C

  

This project is an exercise in C programming to implement a text-based version of the classic Microsoft Minesweeper game. The game features a command-line interface (CLI) and provides a prompt-response loop for user interaction. The goal is to recreate the Minesweeper experience without using graphics libraries, relying on textual commands from the keyboard.

## Features

  

- **CLI:** The project implements a command-line interface for user interaction.

- **Commands:** Supports commands such as "new" (create a new board), "show" (display the board), "quit" (exit the app), "uncover" (reveal a cell), "flag" (place a flag on a cell), and "unflag" (remove a flag from a cell).


## How to Play

  

1. Clone the repository.

2. Compile the C code.

3. Run the executable to start the Minesweeper game.

4. Use commands to create a new board, display the board, and perform in-game actions.

  

## Commands

  

- **new:** `new <rows> <columns> <mines>` - Create a new board with specified dimensions and mines.

- **show:** `show` - Display the current board.

- **quit:** `quit` - Exit the application.

- **uncover:** `uncover <row> <column>` - Uncover a cell at the specified row and column.

- **flag:** `flag <row> <column>` - Put a flag on the cell at the specified row and column.

- **unflag:** `unflag <row> <column>` - Remove a flag from the cell at the specified row and column.


### Getting Started

```bash

git clone [https://github.com/your-username/minesweeper-c.git](https://github.com/your-username/minesweeper-c.git)

cd minesweeper-c
