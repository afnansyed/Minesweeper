# Mineweeper
Version of the Minesweeper game for COP3503 

### Rules Overview

The rules of the game are as follows:

- There exists a board, which contains a grid of spaces. A space could be a mine, or not. The player clicks
on a space, and it gets revealed. The goal of the game is to reveal all the spaces that are not mines, while
avoiding the spaces that are.

- When a space is revealed:
      - If it’s a mine, the game ends
      - If it’s not a mine, it shows the number of mines adjacent to that space (anywhere from 0 to 8, with 0 just
      showing as an empty space)
      
- If a space has no adjacent mines, all non-mine spaces adjacent to it are also revealed The
player uses the numbers as clues to figure out where other mines may be located.
When all of the non-mine spaces have been revealed, the player wins!

        Documentation below provided by course professor Dr. Fox at University of Florida
        
![Project_Minesweeper-03](https://user-images.githubusercontent.com/44105687/236574332-d28cb7a4-fe03-46e8-8e5a-17449393e2ea.png)
![Project_Minesweeper-15](https://user-images.githubusercontent.com/44105687/236574474-597dba28-3b35-48a7-9736-6254af3ec2a1.png)
![Project_Minesweeper-16](https://user-images.githubusercontent.com/44105687/236574287-e7c6367b-5f11-4d13-8108-d13889f09367.png)
