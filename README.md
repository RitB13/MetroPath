# MetroPath – Console-Based Delhi Metro Route and Fare Finder

MetroPath is a Java-based console application that simulates the Delhi Metro railway network. It enables users to determine the shortest route, travel time, and fare between any two metro stations. The application utilizes graph data structures and pathfinding algorithms such as Dijkstra’s algorithm, Breadth-First Search (BFS), and Depth-First Search (DFS) to provide efficient routing results. This system also accounts for interchanges between different metro corridors and supports user-friendly input modes including station names, codes, and serial numbers.

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
- [Author](#author)

---

## Project Overview

MetroPath simulates a metro transportation system using object-oriented design and graph algorithms. Stations are modeled as graph vertices and connections between them as weighted edges. The edge weights represent either the physical distance between stations or estimated travel times. A custom min-heap implementation is used in conjunction with Dijkstra’s algorithm for accurate shortest path computations.

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

- **Java** – Core programming language
- **Data Structures** – Graph, Heap, HashMap, ArrayList, Queue
- **Algorithms** – Dijkstra’s Algorithm, BFS, DFS
- **Java I/O** – BufferedReader for interactive console input
- **Custom Classes** – Graph, Vertex, Heap, DijkstraPair, Pair

---

## Installation and Setup

1. Clone the repository or download the source code.
2. Open the project in any Java IDE (Eclipse, IntelliJ IDEA, NetBeans).
3. Ensure `Graph_M.java` and `Heap.java` are in the same package or directory.
4. Compile and run `Graph_M.java`.

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

- `Graph_M.java`: Core file containing the main method, metro map creation, graph implementation, pathfinding logic, and user interface.
- `Heap.java`: Custom generic min-heap class used by Dijkstra’s algorithm to prioritize nodes based on cost.
- Each metro station is modeled as a `Vertex` containing adjacent stations and the respective distances.
- A HashMap-based graph is used to manage vertices and adjacency lists efficiently.

---

## Algorithms Implemented

- **Dijkstra’s Algorithm**: Computes the shortest path between two stations with weighted edges.
- **Breadth-First Search (BFS)**: Traverses the graph to validate connectivity.
- **Depth-First Search (DFS)**: Used internally for traversal and alternate route checking.
- **Custom Min-Heap**: Supports dynamic priority queue operations for Dijkstra’s algorithm.

---
