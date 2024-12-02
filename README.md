# Fantasy Football Manager Simulation

This project is a simulation of a fantasy football management game. Players can create teams, buy and sell players, manage squads, and compete in a fantasy league. The game includes both user and administrator functionalities to control gameplay and league operations.

## Features

### User Functionalities
- **Signup/Login**: Users can create and log into their fantasy teams.
- **Team Management**: Buy and sell players, view squad statistics, and manage team performance.
- **League Participation**: Compete against other users based on player performances in real-life matches.

### Administrator Functionalities
- **Admin Control**: Manage the game, including opening/closing the transfer window and advancing weeks.
- **Player Transfers**: Enable or restrict player buying/selling during specific windows.

### Gameplay
- **Game Data Management**: Automatically read player and team data for real-life simulation.
- **Match Results**: Simulate weekly matches and update player statistics accordingly.
- **Team of the Week**: Highlight top-performing players based on weekly results.

## File Structure

### Core Files
- **`Admin.cpp`**: Implements administrator functionalities like registration, login, and game controls.
- **`Futball.cpp`**: Main game logic, including reading match data, managing users, and handling orders.
- **`Player.cpp`**: Player class, representing individual players with attributes like position, availability, and performance.
- **`Real_Team.cpp`**: Represents real football teams, handling players and match results.
- **`game.cpp`**: Manages individual matches and their outcomes.

### Input/Output
- **`Admin_test_in.txt`**: Test cases for administrator operations.
- **`Buy_sell_test_in.txt`**: Test cases for player transfers.
- **`futballFantasy.out`**: Example output of game simulations.

### Main Entry Point
- **`main.cpp`**: Initializes the game, loads data, and handles user/admin interactions.

## How to Run

1. **Compile the Code**:
   Use a C++ compiler, such as `g++`:
   ```bash
   g++ main.cpp Admin.cpp Futball.cpp game.cpp Player.cpp Real_Team.cpp -o FantasyFootball
