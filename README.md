# Sprite Player Demo

A simple 2D platformer demo built with **SFML** featuring a sprite-based player with animation, physics, and collision detection. This is for Learning what game engine development is about.    

---

## 🕹 Project Overview

This project demonstrates:

* Loading and rendering **backgrounds** and **sprites**
* **Player movement**: walking, jumping
* **Animation system** for different player states (idle, walk, jump)
* **Physics system**: gravity and collision with platforms
* Simple **Entity Component System (ECS)** for managing entities

The goal is to create a foundation for a small 2D platformer or a learning prototype for game engine concepts.

<img width="1366" height="768" alt="pii" src="https://github.com/user-attachments/assets/4b5d98a6-54ed-4d68-8d93-b235a2dbe480" />


---

## 🎮 Features

* Player movement (left, right, jump)
* Animated player sprite
* Platforms with collision detection
* Scalable background
* ECS-based architecture for clean entity management

---

## 🛠 Tech Stack

* **Language:** C++
* **Graphics / Windowing:** SFML
* **Animation:** Sprite sheet handling
* **Physics:** Gravity + collision detection
* **Architecture:** Simple ECS (Entity Component System)

---

## 📂 Project Structure

```
SpritePlayerDemo/
├── assets/
│   ├── player.png      # Player sprite sheet
│   └── background.png  # Background image
├── src/
│   ├── Game.h
│   ├── Game.cpp
│   ├── Player.cpp
│   ├── Player.h
│   ├── Systems/
│   │   ├── AnimationSystem.cpp
│   │   ├── PhysicsSystem.cpp
│   │   └── PlayerSystem.cpp
│   └── ECS/
├── CMakeLists.txt or Makefile
└── README.md
```

---

## ▶️ How to Run

1. Install **SFML** on your system:
   [SFML Installation Guide](https://www.sfml-dev.org/tutorials/2.5/)

2. Clone the repo:

```bash
git clone https://github.com/NtokozoMkhwanazi/SpritePlayerDemo.git
cd SpritePlayerDemo
```

3. Compile the project:

```bash
g++ src/*.cpp -o SpritePlayerDemo -lsfml-graphics -lsfml-window -lsfml-system
```

4. Run the game:

```bash
./SpritePlayerDemo
```

5. Controls:

* **A** → Move left
* **D** → Move right
* **Space** → Jump

---

## 📖 How It Works

1. **Game Initialization**

   * Loads background and scales to window
   * Creates floor/platform
   * Initializes player on top of floor

2. **Game Loop**

   * Handles input (left/right/jump)
   * Updates player system (movement)
   * Updates physics system (gravity + collisions)
   * Updates animation system (state & direction)
   * Renders background, player, and platforms

3. **Player States**

   * `Idle` → standing still
   * `Walk` → moving left or right
   * `Jump` → in the air (up or falling down)

---

## 🎯 Learning Outcomes

* Understanding **basic ECS architecture**
* Learning  **sprite-based animations**
* Learning **2D physics and collisions**
* Working with **SFML graphics library**

---

