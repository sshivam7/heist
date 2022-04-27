<h3 align="center">
     <img src="./demo/name.png" alt="Anolight Icon" width="350">
</h3>

<p align="center">
     <img src="https://img.shields.io/badge/Author-Shivam-BF9460?style=for-the-badge">
     <img src="https://img.shields.io/badge/Version-v1.0-BF9460?style=for-the-badge">
</p>

Heist is a 2D game created using OpenGL and C++. Inspired by the classic Pac-Man arcade game, you play as the purple Panda, who must navigate the bamboo forest to find and capture the coins located throughout the map. However, with the red enemies tracking you down, getting to the coins won't be so easy!



### Game Demo
<img src="demo/demo.gif">
&nbsp;

<div align="center">
     <img src="resources/player.png" width="100px">
     <img src="resources/coin.png" width="100px">
     <img src="resources/enemy.png" width="100px">
</div>
&nbsp;

### Features
* Implemented grid based **spatial partitioning** algorithm to limit amount of data being rendered at once
* Implemented **A\* path finding algorithm** to allow enemies to locate and move to player
* **Level selection & creation** (Add your own custom .hlvl file to the levels folder)
* AABB **collision detection** for circles and rectangles

### Screenshots
<div align="center">
     <img src="demo/main_menu.png">
     <img src="demo/game.png">
     <img src="demo/end.png">
</div>

### Libraries Used
Heist makes use of GLFW, GLAD, GLM and STBI libraries. 