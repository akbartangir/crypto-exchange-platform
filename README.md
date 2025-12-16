# Cryptocurrency Trading Platform (Educational Project)

## Overview

This project is an educational example of a cryptocurrency trading platform. The platform is designed to demonstrate key concepts in software development, including user interaction, data processing, and algorithmic problem-solving. While the topic of cryptocurrency trading is chosen for its widespread appeal and technical depth, **this project is purely for educational purposes** and does not involve real trading or financial transactions. This project is part of my studying the **Object-Oriented Programming Specialization by the University of London on Coursera**. The concepts and techniques explored in this project reflect the knowledge and skills I am developing through the specialization.

## Disclaimer

Cryptocurrency trading involves substantial risks and may result in significant financial loss. The system implemented in this project does **not** support real-world trading, and I do not recommend or endorse actual cryptocurrency trading. 

Furthermore, developing a real cryptocurrency trading platform for public use carries even greater risks, requiring expertise in computer security and a thorough understanding of legal and regulatory frameworks within the financial industry. These aspects are **not covered in this project**. 

This project is meant solely for educational purposes and should not be used as a foundation for creating real trading platforms. I am not liable for any financial or legal consequences arising from its misuse.

## Project Goals

This project serves as an educational tool to:

- Demonstrate fundamental software development concepts.
- Explore user interaction, data processing, and algorithmic requirements through a real-world-inspired example.
- Provide an engaging and motivating example of system design and implementation.

## Features

- **User Interface**: Simulates basic user interaction for trading actions like placing orders.
- **Data Processing**: Illustrates methods for handling and analyzing market data.
- **Algorithmic Concepts**: Includes simplified examples of algorithms used in trading platforms.

## Future Work
I am using this project as an opportunity to deepen my understanding of object-oriented programming concepts and software design principles. As I progress further in the specialization, I plan to enhance the project by incorporating more advanced programming patterns and techniques.
Although this project is limited in scope to educational purposes, potential future extensions for learning might include:

- Simulating more advanced trading strategies.
- Exploring data visualization techniques for market trends.
- Studying foundational principles of financial technologies (FinTech).

## License

This project is open-source and available for educational use. Any implementation or modification of this project for real-world trading purposes is strongly discouraged and done at your own risk.


## Technologies Used

- **Programming Language:** C++
- **Development Environment:** Command Line Interface (CLI), Visual Studio Code, CMake
- **Others:** Standard Template Library (STL), File I/O for data storage, OOP


## Building and Running the Project
*clone this repository and navigate to the project directory*

1. Create a new directory for the project and navigate to it.
   ```bash
   mkdir build && cd build
   ```
2. Run CMake to configure the project.
   ```bash
    cmake ..
    ```
3. Build the project.
    ```bash
    cmake --build .
    ```
4. Run the executable.
    ```bash
    ./CryptoExchange
    ```

## Testing
This project uses **GoogleTest** for unit testing. Tests are automatically downloaded and built with the project.

**Run tests:**
```bash
cd build
./run_tests
```

**Or using CTest:**
```bash
cd build
ctest --output-on-failure
```

**Current test coverage includes:**
- OrderBookEntry type conversion and construction
- Price comparison functions
- Statistical calculations (mean, high, low prices)
