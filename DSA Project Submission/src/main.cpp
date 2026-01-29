//Project made by 2023315 Mian Moiz Ud Din, 2023317 Tayyab Shahjehan, 2023716 Taha Shafique
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <list>
#include <queue>
#include <algorithm>
#include <stack>
using namespace std;

struct City {
    string name;
    string airportCode;
    string country;
    int dailyFlights;
};

struct Flight {
    string flightNumber;
    string origin;          
    string destination;     
    string time;
    string gateOrTerminal;
    string flightStatusOrAircraft;
    int availableSeats;
    double duration;
};


// Struct for reservation details
struct Reservation {
    string passengerName;
    string flightNumber;
    string destinationOrOrigin;
    string time;
};

// Class for linked list implementation
class FlightList {
    public:
vector<Flight> getArrivalsForCity(const string& city) {
    vector<Flight> arrivals;
    Node* current = head;
    while (current) {
        if (current->flight.destination == city) {
            arrivals.push_back(current->flight);
        }
        current = current->next;
    }
    return arrivals;
}
vector<Flight> getDeparturesForCity(const string& city) {
    vector<Flight> departures;
    Node* current = head;
    while (current) {
        if (current->flight.origin == city) { 
            departures.push_back(current->flight);
        }
        current = current->next;
    }
    return departures;
}



private:
    struct Node {
        Flight flight;
        Node* next;
        Node(const Flight& flight) : flight(flight), next(nullptr) {}
    };
    Node* head;


    

public:
    FlightList() : head(nullptr) {}

    // Add a flight to the list
    void addFlight(const Flight& flight) {
        Node* newNode = new Node(flight);
        if (!head || head->flight.time > flight.time) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next && current->next->flight.time < flight.time) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // Display all flights
void displayFlights() {
    Node* current = head;
    cout << left << setw(15) << "Flight No" << setw(15) << "Origin" << setw(15) << "Destination"
         << setw(15) << "Time" << setw(10) << "Gate/Terminal" << setw(20) << "Status/Aircraft"
         << setw(10) << "Seats" << endl;

    while (current) {
        cout << left << setw(15) << current->flight.flightNumber
             << setw(15) << current->flight.origin
             << setw(15) << current->flight.destination
             << setw(15) << current->flight.time
             << setw(10) << current->flight.gateOrTerminal
             << setw(20) << current->flight.flightStatusOrAircraft
             << setw(10) << current->flight.availableSeats
             << endl;
        current = current->next;
    }
}


    // Reserve a seat on a flight
bool reserveSeat(const string& flightNumber, const string& passengerName, vector<Reservation>& reservations) {
    Node* current = head;
    while (current) {
        if (current->flight.flightNumber == flightNumber) {
            if (current->flight.availableSeats > 0) {
                // Reserve a seat
                current->flight.availableSeats--;
                reservations.push_back({passengerName, flightNumber, current->flight.destination, current->flight.time});
                cout << "Reservation successful! Passenger: " << passengerName
                     << " has been booked on Flight " << flightNumber << " to "
                     << current->flight.destination << " at "
                     << current->flight.time << ".\n";
                return true;
            } else {
                cout << "Sorry, no available seats on Flight " << flightNumber << ".\n";
                return false;
            }
        }
        current = current->next;
    }
    cout << "Flight not found.\n";
    return false;
}


    // Get flights for a particular city
    vector<Flight> getFlightsForCity(const string& city) {
        vector<Flight> flights;
        Node* current = head;
        while (current) {
            if (current->flight.destination == city || current->flight.origin == city) {
                flights.push_back(current->flight);
            }
            current = current->next;
        }
        return flights;
    }
};

// Class for Graph representation
class RouteGraph {
private:
    map<string, list<pair<string, double>>> adjList;

public:
    void addRoute(const string& from, const string& to, double distance) {
        adjList[from].push_back({to, distance});
        adjList[to].push_back({from, distance}); 
    }

    void displayRoutes() {
        for (const auto& city : adjList) {
            cout << "\nRoutes from " << city.first << ":\n";
            for (const auto& route : city.second) {
                cout << "  -> " << route.first << " (Distance: " << route.second << " km)\n";
            }
        }
    }

    // Find the shortest path (in terms of hops) between two cities using BFS
    vector<string> findShortestPath(const string& start, const string& end) {
        if (adjList.find(start) == adjList.end() || adjList.find(end) == adjList.end()) {
            cout << "Either the start or end city does not exist in the route graph.\n";
            return {};
        }

        map<string, string> previous;
        map<string, bool> visited;
        queue<string> q;
        q.push(start);
        visited[start] = true;
        previous[start] = "";

        while (!q.empty()) {
            string current = q.front();
            q.pop();

            if (current == end) {
                break;
            }

            for (const auto& neighbor : adjList[current]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    previous[neighbor.first] = current;
                    q.push(neighbor.first);
                }
            }
        }

        // Reconstruct the path
        vector<string> path;
        string current = end;
        while (current != start && !current.empty()) {
            path.push_back(current);
            current = previous[current];
        }
        if (current.empty()) {
            cout << "No path found from " << start << " to " << end << ".\n";
            return {};
        }

        path.push_back(start);
        reverse(path.begin(), path.end());
        return path;
    }
};

// data initialization
void initializeData(vector<City>& cities, FlightList& departures, RouteGraph& routes) {
    cities = {
        {"Lahore", "LHR", "PK", 200},
        {"Karachi", "KHI", "PK", 150},
        {"Kuwait", "KWT", "QTR", 180},
        {"Dubai", "DBI", "UAE", 120},
        {"Colombo", "CMB", "LKA", 100},
        {"Dacca", "DCA", "BGD", 110},
        {"Bangkok", "BGK", "THI", 80},
        {"Manila", "MLA", "PH", 210},
        {"Tokyo", "TKY", "JP", 190},
        {"Muscat", "MCT", "OMA", 220},
    };

    departures.addFlight({"201", "Karachi", "Lahore", "09:00", "Gate A1", "Boeing 737", 100, 1.5});
    departures.addFlight({"203", "Karachi", "Kuwait", "21:00", "Gate A2", "Airbus A320", 150, 1.5});
    departures.addFlight({"204", "Karachi", "Dubai", "11:30", "Gate B2", "Airbus A380", 180, 2.3});
    departures.addFlight({"206", "Karachi", "Colombo", "14:00", "Gate C1", "Boeing 737", 160, 1.5});
    departures.addFlight({"102", "Lahore", "Karachi", "14:00", "Gate C2", "Airbus A320", 150, 1.5});
    departures.addFlight({"302", "Kuwait", "Karachi", "16:00", "Gate D1", "Boeing 737", 120, 3.0});
    departures.addFlight({"304", "Kuwait", "Dubai", "15:00", "Gate D2", "Airbus A320", 130, 3.0});
    departures.addFlight({"403", "Dubai", "Kuwait", "16:00", "Gate E1", "Boeing 747", 100, 4.0});
    departures.addFlight({"405", "Dubai", "Muscat", "19:00", "Gate E2", "Airbus A380", 120, 4.0});
    departures.addFlight({"502", "Muscat", "Karachi", "07:00", "Gate F1", "Boeing 737", 150, 4.0});
    departures.addFlight({"602", "Colombo", "Karachi", "19:00", "Gate F2", "Airbus A320", 140, 4.0});
    departures.addFlight({"607", "Colombo", "Dacca", "11:00", "Gate F2", "Airbus A320", 140, 4.0});
    departures.addFlight({"706", "Dacca", "Colombo", "15:00", "Gate F2", "Airbus A320", 140, 4.0});
    departures.addFlight({"708", "Dacca", "Bangkok", "15:00", "Gate F2", "Airbus A320", 140, 4.0});
    departures.addFlight({"711", "Dacca", "Tokyo", "19:00", "Gate F2", "Airbus A320", 140, 4.0});
    departures.addFlight({"807", "Bangkok", "Dacca", "18:00", "Gate F2", "Airbus A320", 140, 4.0});
    departures.addFlight({"809", "Bangkok", "Manila", "21:00", "Gate F2", "Airbus A320", 140, 4.0});
    departures.addFlight({"908", "Manila", "Bangkok", "20:30", "Gate F2", "Airbus A320", 140, 4.0});
    departures.addFlight({"911", "Manila", "Tokyo", "02:00", "Gate F2", "Airbus A320", 140, 4.0});
    departures.addFlight({"119", "Tokyo", "Manila", "08:00", "Gate F2", "Airbus A320", 140, 4.0});
    departures.addFlight({"117", "Tokyo", "Dacca", "15:00", "Gate F2", "Airbus A320", 140, 4.0});

 

    routes.addRoute("Lahore", "Karachi", 300);   
    routes.addRoute("Karachi", "Lahore", 300);
    routes.addRoute("Karachi", "Kuwait", 1000);
    routes.addRoute("Kuwait", "Karachi", 1000);
    routes.addRoute("Karachi", "Colombo", 1500);
    routes.addRoute("Colombo", "Karachi", 1500);
    routes.addRoute("Karachi", "Dubai", 3000);
    routes.addRoute("Dubai", "Muscat", 5000);
    routes.addRoute("Muscat", "Karachi", 2400);
    routes.addRoute("Dubai", "Kuwait", 2200);
    routes.addRoute("Kuwait", "Dubai", 2200);
    routes.addRoute("Colombo", "Dacca", 3200);
    routes.addRoute("Dacca", "Colombo", 3200);
    routes.addRoute("Dacca", "Tokyo", 3100);
    routes.addRoute("Tokyo", "Dacca", 3100);
    routes.addRoute("Dacca", "Bangkok", 5500);
    routes.addRoute("Bangkok", "Dacca", 5500);
    routes.addRoute("Bangkok", "Manila", 1800);
    routes.addRoute("Manila", "Bangkok", 1800);
    routes.addRoute("Manila", "Tokyo", 1600);
    routes.addRoute("Tokyo", "Manila", 1600);
}


void displayCityTable(const vector<City>& cities) {
    cout << left << setw(15) << "City Name" << setw(10) << "Code" << setw(15) << "Country"
         << "Daily Flights" << endl;
    for (const auto& city : cities) {
        cout << left << setw(15) << city.name << setw(10) << city.airportCode
             << setw(15) << city.country << city.dailyFlights << endl;
    }
}

void displayReservations(const vector<Reservation>& reservations) {
    cout << left << setw(20) << "Passenger Name" << setw(15) << "Flight No"
         << setw(25) << "Destination" << "Time" << endl;
    for (const auto& res : reservations) {
        cout << left << setw(20) << res.passengerName << setw(15) << res.flightNumber
             << setw(25) << res.destinationOrOrigin << res.time << endl;
    }
}

bool deleteReservation(const string& flightNumber, const string& passengerName, vector<Reservation>& reservations, FlightList& departures) {
    auto it = reservations.begin();
    while (it != reservations.end()) {
        if (it->flightNumber == flightNumber && it->passengerName == passengerName) {
 
            reservations.erase(it);
            cout << "Reservation for Passenger: " << passengerName << " on Flight: " << flightNumber << " has been deleted.\n";
            return true;
        }
        ++it;
    }
    cout << "Reservation not found for Passenger: " << passengerName << " on Flight: " << flightNumber << ".\n";
    return false;
}

int main() {
    vector<City> cities;
    FlightList departures;
    RouteGraph routes;
    vector<Reservation> reservations;
    initializeData(cities, departures, routes);

    int option;
    do {
        cout << "\nMenu:\n";
        cout << "1. View Cities\n";
        cout << "2. Reserve a Flight\n";
        cout << "3. Display Routes\n";
        cout << "4. Show All Reservations\n";
        cout << "5. Show All Departures\n";
        cout << "6. Show All Arrivals\n";
        cout<<"7. Show all flights\n";
        cout << "8. Delete a Reservation\n";
        cout << "0. Exit\n";
        cout << "Select an option: ";
        cin >> option;
        cin.ignore(); 

        switch (option) {
            case 1:
                displayCityTable(cities);
                break;
            case 2: {
    string startCity, endCity, passengerName;
    cout << "Enter departure city: ";
    getline(cin, startCity);
    cout << "Enter arrival city: ";
    getline(cin, endCity);

    // Find the shortest path (in terms of hops)
    vector<string> path = routes.findShortestPath(startCity, endCity);
    if (!path.empty()) {
        cout << "Flight path from " << startCity << " to " << endCity << ": ";
        for (const auto& city : path) {
            cout << city << " ";
        }
        cout << endl;

        // Attempt to reserve flights
        cout << "Enter passenger name: ";
        getline(cin, passengerName);

        bool reservationSuccess = true;

        for (size_t i = 0; i < path.size() - 1; ++i) { 
            string origin = path[i];
            string destination = path[i + 1];

            // Find flights between origin and destination
            vector<Flight> availableFlights = departures.getFlightsForCity(origin);
            bool flightFound = false;

  
            for (const auto& flight : availableFlights) {
                if (flight.destination == destination) {
                    if (!departures.reserveSeat(flight.flightNumber, passengerName, reservations)) {
                        reservationSuccess = false;
                    }
                    flightFound = true;
                    break;
                }
            }

            if (!flightFound) {
                cout << "No available flight from " << origin << " to " << destination << ". Reservation failed.\n";
                reservationSuccess = false;
                break; 
            }
        }

        if (reservationSuccess) {
            cout << "All legs of the journey reserved successfully!\n";
        }
    }
    break;
}

            case 3:
                routes.displayRoutes();
                break;
            case 4:
                displayReservations(reservations);
                break;
            case 5: {
                string city;
                cout << "Enter the city for departures: ";
                getline(cin, city);

                vector<Flight> cityDepartures = departures.getDeparturesForCity(city);
                if (!cityDepartures.empty()) {
                    cout << "Departures from " << city << ":\n";
                    cout << left << setw(15) << "Flight No" << setw(25) << "Destination"
                        << setw(15) << "Departure Time" << setw(10) << "Gate"
                        << setw(20) << "Aircraft" << setw(10) << "Seats" << endl;

                    for (const auto& flight : cityDepartures) {
                        cout << left << setw(15) << flight.flightNumber
                            << setw(25) << flight.destination
                            << setw(15) << flight.time
                            << setw(10) << flight.gateOrTerminal
                            << setw(20) << flight.flightStatusOrAircraft
                            << setw(10) << flight.availableSeats
                            << endl;
                    }
                } else {
                    cout << "No departures found for " << city << ".\n";
                }
                break;
            }
            case 6: {
    string city;
    cout << "Enter the city for arrivals: ";
    getline(cin, city);

    vector<Flight> arrivals = departures.getArrivalsForCity(city);
    if (!arrivals.empty()) {
        cout << "Arrivals to " << city << ":\n";
        cout << left << setw(15) << "Flight No" << setw(25) << "Origin" 
        << setw(10) << "Arrival"
             << setw(15) << "Arrival Time" << setw(10) << "Terminal"
             << setw(20) << "Status" << endl;

        for (const auto& flight : arrivals) {
            cout << left << setw(15) << flight.flightNumber << setw(15)<< flight.origin
                 << setw(25) << flight.destination
                 << setw(15) << flight.time
                 << setw(10) << flight.gateOrTerminal
                 << setw(20) << flight.flightStatusOrAircraft
                 << endl;
        }
    } else {
        cout << "No arrivals found for " << city << ".\n";
    }
    break;
}
            case 7:
                departures.displayFlights();
                break;
            case 8: {
                string flightNumber, passengerName;
                cout << "Enter flight number: ";
                getline(cin, flightNumber);
                cout << "Enter passenger name: ";
                getline(cin, passengerName);

                deleteReservation(flightNumber, passengerName, reservations, departures);
                break;
            }
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid option! Try again.\n";
            }
    } while (option != 0);

    return 0;
}
