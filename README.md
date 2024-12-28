# Welcome
Welcome to NJORDX, the new trading platform for the many citizens between Viborg and Skagen.
# Build guide
## Prerequisites
- make
- C++20 compiler
- Git

## Installation
1. Clone the repository:
    ```sh
    git clone https://github.com/CKCordes/NJORDX.git
    cd NJORDX
    ```
    No further actions are needed
## Building and running the Application
1. Configure, build and run the application with make
    ```sh
    make run ARGS="<person/company> <name> <CPR/CVR> <initial-balance>"
    ```
    Enjoy your NJORDX experience!
## Running Tests
1. Compile and run unit tests:
    ```sh
    make unit_tests
    ```
## Recommended use of the NJORDX application
To make testing of the application as simple and enjoyable as possible, we have made a list of short guides that display the possibilites offered by the NJORDX application. \
The guides comprises of a list of commands, with a short explaination.

### General runthrough 
1. Start the application as a company:
    ```sh
    make run ARGS="company <name> 123456 1000"
    ```
2. Get the list of commands:
    ```sh
    > help
    ```
    You will now see the plethora of options made available through NJORDX
3. Display info about yourself:
    ```sh
    > info
    ```
4. Imagine you have just turned into an ApS. You would now like to create some stock that can be bought/sold:
    ```sh
    > create <stock-name> 10
    ```
5. See the stock has been added to your portfolio:
    ```sh
    > info
    ```
6. Put your stock on the market to be sold
    ```sh
    > sell <stock-name> 5 100
    ```
7. Now wait for someone to buy it! (Nobody will ever come...)

### Using the sell "bots"
1. Start the application as a company (more interesting as you can create stock):
    ```sh
    make run ARGS="company <name> 123456 1000"
    ```
2. Execute the sell bot. It will create a random sell order that you can use:
    ```sh
    > sell_bot
    ```
3. Check the random generated order. This command shows all orders in the exchange:
    ```sh
    > show_orders
    ```
4. Buy the generated order:
    ```sh
    > buy <stock-name> 1 <number equal or over the price>
    ```
5. See that you are now the proud owner of a new stock:
    ```sh
    > info
    ```

### Using the buy "bots"
Using the buy bots 

## Notes
 - The difference between available stocks and active sell orders is that once a stock is put on the market, one will always be able to place a buy order on it, even when there is no sell order. If a stock has never been listed on NJORDX, a buy order cannot be placed on it.

  - A company can create any stock. This is of course an inteded feature and not a bug. The purpose of this is to display the functionality of the application.




- Njordx kan have en liste af traders, her kan vi få variadics med.

- Trader skal lave noget exception handling, hvis en trader forsøger at lave en en ordre uden exhange. 
- Tjek om man har nok stocks til at place order i trader
