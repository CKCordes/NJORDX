# Welcome
Welcome to NJORDX, the new trading platform for the many citizens between Viborg and Skagen.
# Build guide
## Prerequisites
- CMake
- C++17 compiler
- Git

## Installation
1. Clone the repository:
    ```sh
    git clone https://github.com/CKCordes/NJORDX.git
    cd NJORDX
    ```

## Building and running the Application
1. Navigate to build directory
    ```sh
    cd build
    ```
2. Configure the project with CMake
    ```sh
    cmake ..
    ```
3. Build the project
    ```sh
    cmake --build .
    ```
4. Run the executable
    ```sh
    ./NjordxApp
    ```

## Running Tests
1. Compile and run unit tests:
    ```sh
    make unit_tests
    ```
## Notes and TODOs
- Njordx kan have en liste af traders, her kan vi få variadics med.
