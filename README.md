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

![image](https://user-images.githubusercontent.com/55492673/215620733-8d7df38b-b22f-497a-beee-6dfb99832134.png)

Upon entering a number associated with a file, that puzzle will be shown again, along with its solution.

![image](https://user-images.githubusercontent.com/55492673/215620883-ebe948e3-59d9-4186-b936-d7096f1274bd.png)

