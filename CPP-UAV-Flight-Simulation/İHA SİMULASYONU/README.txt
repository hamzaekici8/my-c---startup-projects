# UAV Flight Control Simulation System (C++)

This project is a Command Line Interface (CLI) based dynamic Unmanned Aerial Vehicle (UAV) and UCAV (Combat UAV) simulation system developed in C++. 

It was designed to grasp advanced Object-Oriented Programming (OOP) concepts before starting the 2nd year of Computer Engineering at Sivas Science and Technology University (SBTÜ).

## 🚀 Features
*   **Dynamic Fleet Management:** Uses `std::vector` to manage an unrestricted number of aircraft.
*   **Interactive Control Panel:** User interface driven by a continuous loop and switch-case mechanics.
*   **Dynamic Memory Allocation:** Objects are instantiated in the Heap memory using the `new` keyword for efficient lifetime management.

## 🛠️ Advanced C++ Concepts Implemented
*   **Inheritance:** `Siha` (UCAV) class inherits common properties from the base `HavaAraci` (Aircraft) class.
*   **Polymorphism:** Implemented via `virtual` functions and `override` specifiers to report specific status updates for different aircraft types using a single loop.
*   **Downcasting:** Utilizes `dynamic_cast` to safely isolate and trigger combat mechanics (`atesEt()`) only on weapon-equipped tactical units.

## 💻 How to Execute
1. Open the project in **Visual Studio 2022** or any modern C++ IDE.
2. Compile and run the `main.cpp` file.
