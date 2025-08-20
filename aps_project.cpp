#include<iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <string>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
using namespace std;

struct Flight {
    string flightNumber;
    string sourceAirport;
    string destinationAirport;
    double distance;
    string departureTime;
    string arrivalTime;
    int availableSeats;
    double price;
};

struct Passenger {
    string name;
    string passportNumber;
    string contactInfo;
    string seatNumber;
};

struct Feedback {
    string reviewText;
    string sentiment;
};

pair<string, string> getUserInputForAirports() {
    string sourceAirport, destinationAirport;
    cout << "Enter source airport code: ";
    cin >> sourceAirport;
    cout << "Enter destination airport code: ";
    cin >> destinationAirport;
    return {sourceAirport, destinationAirport};
}

vector<Flight> filterFlights(const vector<Flight>& flights, const string& sourceAirport, const string& destinationAirport) {
    vector<Flight> filteredFlights;
    for (const auto& flight : flights) {
        if (flight.sourceAirport == sourceAirport && flight.destinationAirport == destinationAirport) {
            filteredFlights.push_back(flight);
        }
    }
    return filteredFlights;
}

bool sortByArrivalTime(const Flight& a, const Flight& b) {
    return a.arrivalTime < b.arrivalTime;
}

void scheduleFlightsOnArrivalTime(const vector<Flight>& flights) {
    vector<Flight> sortedFlights = flights;
    sort(sortedFlights.begin(), sortedFlights.end(), sortByArrivalTime);
    cout << "Available Flights (sorted by arrival time):" << endl;
    for (const auto& flight : sortedFlights) {
        cout << "Flight Number: " << flight.flightNumber << ", Source: " << flight.sourceAirport << ", Destination: " << flight.destinationAirport << ", Departure: " << flight.departureTime << ", Arrival: " << flight.arrivalTime << ", Price: $" << flight.price << ", Seats Available: " << flight.availableSeats << endl;
    }
}

map<string, double> shortestPath(const vector<Flight>& flights, const string& sourceAirport, const string& destinationAirport) {
    map<string, double> distances;
    map<string, string> previous;
    for (const auto& flight : flights) {
        distances[flight.sourceAirport] = flight.sourceAirport == sourceAirport ? 0 : numeric_limits<double>::infinity();
    }

    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
    pq.push({0, sourceAirport});
     // Dijkstra's algorithm
    while (!pq.empty()) {
        string airport = pq.top().second;
        double dist = pq.top().first;
        pq.pop();
        for (const auto& flight : flights) {
            if (flight.sourceAirport == airport) {
                double newDist = dist + flight.price;
                if (newDist < distances[flight.destinationAirport]) {
                    distances[flight.destinationAirport] = newDist;
                    previous[flight.destinationAirport] = airport;
                    pq.push({newDist, flight.destinationAirport});
                }
            }
        }
    }
    string currentAirport = destinationAirport;
    vector<string> path;
    while (currentAirport != sourceAirport) {
        path.push_back(currentAirport);
        currentAirport = previous[currentAirport];
    }
    path.push_back(sourceAirport);
    reverse(path.begin(), path.end());
    string pathString;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        pathString += path[i] + "->";
    }
    pathString += path.back();
    cout << "Optimal path from " << sourceAirport << " to " << destinationAirport << ": " << pathString << endl;
    return distances;
}

// Data retrieval
vector<Flight> retrieveFlightData() {
    return {
    {"AI101", "DEL", "BOM", 1148, "08:00", "10:00", 150, 500},
    {"AI102", "BOM", "DEL", 1148, "11:00", "13:00", 200, 550},
    {"6E501", "DEL", "MAA", 1753, "09:00", "12:00", 180, 4000},
    {"6E502", "MAA", "DEL", 1753, "13:00", "16:00", 190, 4200},
    {"SG703", "DEL", "CCU", 1304, "10:00", "13:00", 160, 3500},
    {"SG704", "CCU", "DEL", 1304, "14:00", "17:00", 170, 3700},
    {"AI103", "DEL", "BOM", 1148, "06:30", "08:30", 180, 520},
    {"AI104", "BOM", "DEL", 1148, "14:30", "16:30", 190, 580},
    {"6E503", "DEL", "MAA", 1753, "08:30", "11:30", 200, 4300},
    {"6E504", "MAA", "DEL", 1753, "12:30", "15:30", 210, 4500},
    {"SG705", "DEL", "CCU", 1304, "11:00", "14:00", 180, 3800},
    {"SG706", "CCU", "DEL", 1304, "15:00", "18:00", 190, 4000},
    {"AI105", "DEL", "BOM", 1148, "05:00", "07:00", 160, 480},
    {"AI106", "BOM", "DEL", 1148, "09:00", "11:00", 170, 520},
    {"6E505", "DEL", "MAA", 1753, "07:30", "10:30", 180, 4200},
    {"6E506", "MAA", "DEL", 1753, "11:30", "14:30", 190, 4400},
    {"SG707", "DEL", "CCU", 1304, "12:30", "15:30", 200, 3900},
    {"SG708", "CCU", "DEL", 1304, "16:30", "19:30", 210, 4100},
    {"AI107", "DEL", "BOM", 1148, "04:30", "06:30", 170, 460},
    {"AI108", "BOM", "DEL", 1148, "08:30", "10:30", 180, 500},
    {"6E507", "DEL", "MAA", 1753, "06:00", "09:00", 190, 4100},
    {"6E508", "MAA", "DEL", 1753, "10:00", "13:00", 200, 4300},
    {"SG709", "DEL", "CCU", 1304, "13:00", "16:00", 210, 4000},
    {"SG710", "CCU", "DEL", 1304, "17:00", "20:00", 220, 4200},
    {"AI107", "BOM", "CCU", 1740, "09:00", "12:00", 180, 5500},
    {"6E507", "CCU", "BOM", 1740, "13:00", "16:00", 170, 5600},
    {"SG708", "DEL", "LHR", 6674, "09:30", "15:30", 200, 10000},
    {"AI108", "LHR", "DEL", 6674, "16:30", "22:30", 190, 10500},
    {"6E508", "DEL", "PUN", 1173, "08:00", "10:00", 160, 4800},
    {"SG709", "PUN", "DEL", 1173, "11:00", "13:00", 150, 4900},
    {"AI109", "DEL", "DUB", 2209, "10:00", "14:00", 170, 8000},
    {"6E509", "DUB", "DEL", 2209, "15:00", "19:00", 180, 8200},
    {"SG710", "BOM", "BEN", 842, "12:00", "14:00", 190, 4400},
    {"AI110", "BEN", "BOM", 842, "15:00", "17:00", 200, 4300}
};
}

// Linear regression for price determination
double predictPrice(const vector<Flight>& historicalData, const Flight& newFlight, const string& sourceAirport, const string& destinationAirport) {
    double totalDistance = 0;
    double totalPrice = 0;
    int numFlights = 0; // Variable to count the number of flights considered

    // Iterate over all historical flights
    for (const auto& flight : historicalData) {
        // Check if the flight matches the specified source and destination airports
        if (flight.sourceAirport == sourceAirport && flight.destinationAirport == destinationAirport) {
            // If the flight matches, add its distance and price to the totals
            totalDistance += flight.distance;
            totalPrice += flight.price;
            numFlights++; // Increment the count of flights considered
        }
    }

    // Calculate the average distance and average price only if there are flights considered
    double averageDistance = (numFlights > 0) ? totalDistance / numFlights : 0;
    double averagePrice = (numFlights > 0) ? totalPrice / numFlights : 0;

    // Use the average distance and average price to predict the price of the new flight
    double predictedPrice = newFlight.distance * (averagePrice / averageDistance);

    return predictedPrice;
}

// FCFS seat allocation
void allocateSeats(queue<Passenger>& passengerQueue, vector<Flight>& flights) {
    while (!passengerQueue.empty()) {
        Passenger passenger = passengerQueue.front();
        passengerQueue.pop();
        for (auto& flight : flights) {
            if (flight.availableSeats > 0) {
                passenger.seatNumber = "Seat" + to_string(flight.availableSeats);
                flight.availableSeats--;
                break;
            }
        }
        cout << "Passenger " << passenger.name << " allocated seat " << passenger.seatNumber << endl;
    }
}

void displayFlights(const vector<Flight>& flights) {
    cout << "Flight Details:" << endl;
    int i = 0;
    for (const auto& flight : flights) {
        cout << i << endl;
        cout << "Flight Number: " << flight.flightNumber << endl;
        cout << "Source Airport: " << flight.sourceAirport << endl;
        cout << "Destination Airport: " << flight.destinationAirport << endl;
        cout << "Distance: " << flight.distance << " km" << endl;
        cout << "Departure Time: " << flight.departureTime << endl;
        cout << "Arrival Time: " << flight.arrivalTime << endl;
        cout << "Available Seats: " << flight.availableSeats << endl;
        cout << "Price: $" << flight.price << endl;
        cout << "----------------------------" << endl;
        i++;
    }
}



// Function to display menu and get user's choice
int getUserChoice() {
    cout << "Select Functionality:" << endl;
    cout << "1. Route Optimization" << endl;
    cout << "2. Flight Scheduling" << endl;
    cout << "3. Price Prediction" << endl;
    cout << "4. Passenger Seat Allocation" << endl;
    cout << "5. Feedback Analysis" << endl;
    cout << "6. Display The Data of flights" << endl;
    cout << "7.Exit \n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    
    // Platform-specific sleep implementation
    #ifdef _WIN32
        Sleep(2000); // Windows sleep (milliseconds)
    #else
        sleep(2);    // Unix sleep (seconds)
    #endif
    
    return choice;
}

int main() {
    // Retrieve flight data
    vector<Flight> flights = retrieveFlightData();
    while (true) {
        int choice = getUserChoice();

        switch (choice) {
            case 1:
                // Route Optimization
                cout << "Route Optimization" << endl;
                {
                    auto airports = getUserInputForAirports();
                    string sourceAirport = airports.first;
                    string destinationAirport = airports.second;
                    map<string, double> shortestPaths = shortestPath(flights, sourceAirport, destinationAirport);
                    if (shortestPaths.find(destinationAirport) != shortestPaths.end()) {
                        cout << "Optimal cost from " << sourceAirport << " to " << destinationAirport << ": $" << shortestPaths[destinationAirport] << endl;
                    } else {
                        cout << "No path found from " << sourceAirport << " to " << destinationAirport << endl;
                    }
                }
                break;
            case 2:
                // Flight Scheduling
                cout << "Flight Scheduling" << endl;
                {
                    auto airports = getUserInputForAirports();
                    string sourceAirport = airports.first;
                    string destinationAirport = airports.second;
                    vector<Flight> filteredFlights = filterFlights(flights, sourceAirport, destinationAirport);
                    scheduleFlightsOnArrivalTime(filteredFlights);
                }
                break;
            case 3:
                // Price Prediction
                cout << "Price Prediction" << endl;
                {
                    Flight newFlight;
                    cout << "Enter new flight details:" << endl;
                    cout << "Flight Number: ";
                    cin >> newFlight.flightNumber;
                    cout << "Distance (in km): ";
                    cin >> newFlight.distance;
                    cout << "Departure Time: ";
                    cin >> newFlight.departureTime;
                    cout << "Arrival Time: ";
                    cin >> newFlight.arrivalTime;
                    string sourceAirport,destinationAirport;
                    cout << "Source Airport: ";
                    cin >> sourceAirport;
                    cout << "Destination Airport: ";
                    cin >> destinationAirport;
                    double predictedPrice = predictPrice(flights, newFlight,sourceAirport,destinationAirport);
                    cout << "Predicted price for the new flight " << newFlight.flightNumber << ": $" << predictedPrice << endl;
                    newFlight.price = predictedPrice; // Optionally, you can also set the price to the predicted price
                    flights.push_back(newFlight);
                    cout << "NEW FLIGHT SUCESSFULLY ADDED !! \n";
                }
                break;
            case 4:
                // Passenger Seat Allocation
                cout << "Passenger Seat Allocation" << endl;
                {
                    queue<Passenger> passengerQueue;

                    int numPassengers;
                    cout << "Enter number of passengers: ";
                    cin >> numPassengers;
                    for (int i = 0; i < numPassengers; ++i) {
                        Passenger passenger;
                        cout << "Passenger " << i + 1 << " details:" << endl;
                        cout << "Name: ";
                        cin >> passenger.name;
                        cout << "Passport Number: ";
                        cin >> passenger.passportNumber;
                        cout << "Contact Info: ";
                        cin >> passenger.contactInfo;
                        passengerQueue.push(passenger);
                    }
                    allocateSeats(passengerQueue, flights);
                }
                break;
            case 5:
                
                break;
             case 6:
                // Display Flight Details
                cout << "Displaying Flight Details..." << endl;
                displayFlights(flights);
                break;
            case 7:
                // Exit
                cout << "Exiting program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
    return 0;
}
