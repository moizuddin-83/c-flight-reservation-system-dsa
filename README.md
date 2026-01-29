# Flight Reservation & Route Management System

A comprehensive C++ command-line application designed to simulate a real-world aviation management system. This project was developed as part of the **CS221: Data Structures and Algorithms** course at the **Ghulam Ishaq Khan Institute (GIKI)**.

## 🚀 Key Features
* **Smart Routing:** Utilizes **Breadth-First Search (BFS)** to calculate the shortest path between cities based on the minimum number of hops.
* **Flight Scheduling:** Implements a custom **Linked List** (`FlightList`) to manage flights, automatically sorting them by departure time for chronological display.
* **Real-time Reservations:** Supports passenger booking and cancellation, with automatic seat availability updates.
* **Multi-Leg Journeys:** If a direct flight is unavailable, the system intelligently books a sequence of connecting flights across the calculated path.
* **City Logistics:** Tracks airport codes, daily flight frequencies, and international connections for cities like Lahore, Dubai, and Tokyo.

## 🛠️ Technical Stack & Data Structures
The project demonstrates the efficient use of the following structures:
* **Graphs (Adjacency List):** Represents the network of routes between cities.
* **Linked Lists:** Powers the `FlightList` class for dynamic flight management.
* **Vectors & Maps:** Used for storing passenger reservations and mapping city nodes for the graph.
* **Queues:** Essential for the implementation of the BFS pathfinding algorithm.

## 📚 Documentation
For a detailed analysis of the algorithms, time complexity $O(V+E)$, and logic used in this project, please read the [Technical Documentation](TECHNICAL_DOCS.md).


## 💻 Installation & Usage
1.  **Clone the repository:**
    ```bash
    git clone https://github.com/moizuddin-83/c-flight-reservation-system-dsa.git
    ```
2.  **Compile the source code:**
    ```bash
    g++ -o flight_system 2023315_2023317_2023716_final_submission_v1.cpp
    ```
3.  **Run the application:**
    ```bash
    ./flight_system
    ```

## 👥 Contributors
* **Mian Moiz Ud Din** (2023315)
* **Tayyab Shahjehan** (2023317)
* **Taha Shafique** (2023716)


**Submitted to:** Dr. Ahmer Rashid
