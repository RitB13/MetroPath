# MetroPath – Console-Based Delhi Metro Route and Fare Finder

MetroPath is a C++-based console application that simulates the Delhi Metro railway network. It enables users to determine the shortest route, travel time, and fare between any two metro stations. The application utilizes graph data structures and pathfinding algorithms such as Dijkstra's algorithm, Breadth-First Search (BFS), and Depth-First Search (DFS) to provide efficient routing results. This system also accounts for interchanges between different metro corridors and supports user-friendly input modes including station names, codes, and serial numbers.

---

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Technologies Used](#technologies-used)
- [Installation and Setup](#installation-and-setup)
- [Usage Guide](#usage-guide)
- [Program Architecture](#program-architecture)
- [Algorithms Implemented](#algorithms-implemented)
- [Sample Output](#sample-output)

---

## Project Overview

MetroPath simulates a metro transportation system using object-oriented design and graph algorithms. Stations are modeled as graph vertices and connections between them as weighted edges. The edge weights represent either the physical distance between stations or estimated travel times. A custom min-heap implementation is used in conjunction with Dijkstra's algorithm for accurate shortest path computations.

The application provides a text-based menu allowing users to list stations, view the metro map, and compute optimal routes based on distance or time. It also includes logic for computing interchanges between lines and calculating total fare.

---

## Features

- Lists all available metro stations with indexing and codes.
- Displays the complete metro map (adjacency list).
- Calculates shortest path based on:
  - Distance (in kilometers)
  - Time (in minutes)
- Detects and reports required interchanges between lines.
- Estimates total fare based on the route distance.
- Accepts multiple input modes: station name, station code, or serial number.
- Implements data structures and algorithms without external libraries.
- Modular code design for scalability and clarity.

---

## Technologies Used

- **C++** – Core programming language (C++11 or later)
- **Data Structures** – Graph, Heap, unordered_map, vector, list, priority_queue
- **Algorithms** – Dijkstra's Algorithm, BFS, DFS
- **C++ I/O** – cin, getline() for interactive console input
- **Custom Classes** – Graph_M, Vertex, Heap (template-based)
- **STL Containers** – unordered_map, vector, list, stringstream

---

## Installation and Setup

1. Clone the repository or download the source code.
2. Ensure you have a C++ compiler installed (g++, clang++, or MSVC).
3. Ensure `Graph_M.cpp` and `Heap.cpp` are in the same package or directory.
4. Compile and run `Graph_M.cpp`.

No external libraries or dependencies are required.

---

## Usage Guide

When the program starts, a menu is displayed with the following options:

1. List all the stations in the map  
2. Show the metro map (graph representation)  
3. Get the shortest distance between two stations  
4. Get the estimated minimum time between two stations  
5. Get the optimal route (distance-wise) between two stations  
6. Get the optimal route (time-wise) between two stations  
7. Exit  

Users are prompted to input the source and destination stations using either their names, serial numbers, or generated codes. The program validates the input, computes the result, and displays:

- The total distance or time
- The complete travel path
- The number of interchanges (if applicable)
- The approximate fare

---

## Program Architecture

- `Graph_M.cpp`: Core file containing the main function, metro map creation, graph implementation, pathfinding logic, and user interface.
- `Heap.cpp`: Custom generic min-heap class used by Dijkstra’s algorithm to prioritize nodes based on cost.
- Each metro station is modeled as a `Vertex` containing adjacent stations and the respective distances.
- An unordered_map-based graph is used to manage vertices and adjacency lists efficiently.
- STL containers (vector, list, unordered_map) provide efficient data management.

---

## Algorithms Implemented

- **Dijkstra’s Algorithm**: Computes the shortest path between two stations with weighted edges.
- **Breadth-First Search (BFS)**: Traverses the graph to validate connectivity.
- **Depth-First Search (DFS)**: Used internally for traversal and alternate route checking.
- **Custom Min-Heap**: Supports dynamic priority queue operations for Dijkstra’s algorithm.

---

**SAMPLE OUTPUT**

                ****WELCOME TO THE METRO APP*****
                        ~~LIST OF ACTIONS~~

1. LIST ALL THE STATIONS IN THE MAP
2. SHOW THE METRO MAP
3. GET SHORTEST DISTANCE FROM A 'SOURCE' STATION TO 'DESTINATION' STATION
4. GET SHORTEST TIME TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION
5. GET SHORTEST PATH (DISTANCE WISE) TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION
6. GET SHORTEST PATH (TIME WISE) TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION
7. EXIT THE MENU

ENTER YOUR CHOICE FROM THE ABOVE LIST (1 to 7) : 3

***********************************************************

List of station along with their codes:

1. Noida Sector 62~B         NS62
2. Botanical Garden~B        BG
3. Yamuna Bank~B             YB
...

ENTER THE SOURCE AND DESTINATION STATIONS
Noida Sector 62~B
AIIMS~Y

SHORTEST DISTANCE FROM Noida Sector 62~B TO AIIMS~Y IS 31KM

---
