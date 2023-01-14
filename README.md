# Flow-Bot
A bot to solve games in Flow.

Flow is a game where a board is given, of various sizes, and different colored nodes. To solve the puzzle, the player must draw lines that connect each pair of colored nodes, without intersecting other color's lines, and filling every space on the board.

Run program on Linux by using `./obj/main` in the root folder of the program, where it holds `input_files`, a folder with your inputted puzzles.

The input file format is as follows: First line is the number of rows, followed by a space, followed by the number of columns. Each next character space represents spots on the Flow board.

` `: Empty space

`R`: Red node

`G`: Green node

`B`: Blue node

`Y`: Yellow node

`O`: Orange node

`C`: Cyan node

`M`: Magenta node

`W`: Brown node

`P`: Purple node

`H`: White node

`A`: Gray node

`L`: Lime node

`E`: Beige node

`N`: Navy node

`T`: Teal node

`K`: Pink node

Examples of input files are shown in [input_files/Classic_Pack](input_files/Classic_Pack).

When the program is run, all input files are listed and shown as previews in a numbered list. To select a puzzle to be solved, enter the number associated with that file.

![image](https://user-images.githubusercontent.com/55492673/212477650-786f35c4-4bfe-4538-8d46-c652a6cab26c.png)

Upon entering a number associated with a file, that puzzle will be shown again, along with its solution.

![image](https://user-images.githubusercontent.com/55492673/212477722-f2103412-bb5a-44b4-88e4-30ebc92345a8.png)

