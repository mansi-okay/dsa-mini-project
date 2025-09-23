# Mini Version Control System (C++) 
                                          - By Mansi Agrawat and Mayank Bajaj

A simplified **Version Control System (VCS)** implemented in **C++** using fundamental **Data Structures and Algorithms (DSA)** concepts.  
This project allows you to simulate commits, undo/redo operations, browse commit history, and access specific commits, similar to a lightweight Git system.

---

## Features

- **Commit System** – Save different versions of code with messages.  
- **Undo/Redo** – Navigate between commits silently without losing history.  
- **Commit History** – View all commits with IDs, messages, and timestamps.  
- **Checkout by ID** – Access any commit by its ID.  
- Lightweight simulation of **Git behavior** using C++.

---

## Data Structures Used

- **Doubly Linked List** → Stores commits for easy navigation (prev/next pointers).  
- **Hash Map (`unordered_map`)** → For fast lookup of commits by ID.  
- **Strings** → Stores commit content.

---

## Project Structure
Mini-VCS/
  - │── main.cpp # Full source code
  - │── README.md # Documentation
