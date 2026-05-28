# GridEvader: C-Based Obstacle Avoiding Game

A lightweight, high-performance terminal arcade game written entirely in native C. The game features real-time rendering, non-blocking keyboard input processing, and modular collision mechanics operating within a dynamic 2D grid matrix.

## 🚀 Features
* **Real-Time 2D Grid Engine:** Uses multi-dimensional arrays to compute and render game environments smoothly directly into the system terminal.
* **Non-Blocking Control Architecture:** Utilises interactive event polling loops to capture keyboard controls instantly without interrupting game performance.
* **Algorithmic Hurdle Spawning:** Generates pseudo-random descending obstacle configurations requiring tactical evasion.
* **Session Score Tracker:** Implements real-time tick counts to dynamically calculate and display player scores during active execution cycles.

## 🛠️ Tech Stack & Concepts Applied
* **Language:** C (C99 Standard syntax structure)
* **Core Concepts:** * Multi-dimensional data arrays (Matrix manipulation for player/obstacle positioning)
  * Memory optimization and continuous game loop iterations
  * Dynamic conditional checking for hitboxes and barrier collisions
  * Native terminal management configurations

## 💻 Installation & Compilation Guide

To run this application locally, ensure you have a standard C compiler configured on your machine (such as `gcc` or `clang`).

### 1. Clone the Repository
```bash
git clone [https://github.com/Vishnu-2010/c-based-obstacle-avoiding-game.git](https://github.com/Vishnu-2010/c-based-obstacle-avoiding-game.git)
cd c-based-obstacle-avoiding-game
