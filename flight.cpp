#include "flight.h"

void createAirport(string newAirportID, adrAirport &a) {
    a = new airport;
    if (a != NULL) {
        airportID(a) = newAirportID;
        nextAirport(a) = NULL;
        firstRoute(a) = NULL;
    }
}

void initNetwork(flightNetwork &N) {
    firstAirport(N) = NULL;
}

void addAirport(flightNetwork &N, string newAirportID) {
    adrAirport newAirport, temp;
    createAirport(newAirportID, newAirport);

    if (firstAirport(N) == NULL) {
        firstAirport(N) = newAirport;
    } else {
        temp = firstAirport(N);
        while (nextAirport(temp) != NULL) {
            temp = nextAirport(temp);
        }
        nextAirport(temp) = newAirport;
    }
}

void addRoute(flightNetwork &N, string fromAirportID, string toAirportID, int flightTime, int price) {
    adrAirport fromAirport = firstAirport(N);
    adrAirport toAirport = NULL;

    while (fromAirport != NULL && airportID(fromAirport) != fromAirportID) {
        fromAirport = nextAirport(fromAirport);
    }

    toAirport = firstAirport(N);
    while (toAirport != NULL && airportID(toAirport) != toAirportID) {
        toAirport = nextAirport(toAirport);
    }

    if (fromAirport != NULL && toAirport != NULL) {
        adrRoute newRoute = new route;
        destAirportID(newRoute) = toAirportID;
        flightTime(newRoute) = flightTime;
        routePrice(newRoute) = price;
        nextRoute(newRoute) = firstRoute(fromAirport);
        firstRoute(fromAirport) = newRoute;
    } else {
        cout << "Bandara " << fromAirportID << " atau " << toAirportID << " tidak ditemukan." << endl;
    }
}

void printNetwork(flightNetwork &N) {
    adrAirport a = firstAirport(N);
    adrRoute r;

    while (a != NULL) {
        cout << airportID(a) << " ->";
        r = firstRoute(a);
        while (r != NULL) {
            cout << " (" << destAirportID(r) << ", " << flightTime(r) << " mins, Rp" << routePrice(r) << ")";
            r = nextRoute(r);
        }
        cout << endl;
        a = nextAirport(a);
    }
}

void printRoutesByPrice(flightNetwork &N) {
    struct Route {
        string path;
        int price;
        Route *next;
    } *head = NULL, *tail = NULL;

    adrAirport a = firstAirport(N);
    while (a != NULL) {
        adrRoute r = firstRoute(a);
        while (r != NULL) {
            Route *newRoute = new Route;
            newRoute->path = airportID(a) + " -> " + destAirportID(r);
            newRoute->price = routePrice(r);
            newRoute->next = NULL;

            if (head == NULL || newRoute->price < head->price) {
                newRoute->next = head;
                head = newRoute;
            } else {
                Route *current = head;
                while (current->next != NULL && current->next->price < newRoute->price) {
                    current = current->next;
                }
                newRoute->next = current->next;
                current->next = newRoute;
            }

            r = nextRoute(r);
        }
        a = nextAirport(a);
    }

    Route *current = head;
    while (current != NULL) {
        cout << current->path << " | Harga: Rp" << current->price << endl;
        Route *temp = current;
        current = current->next;
        delete temp;
    }
}

void printRoutesByTime(flightNetwork &N) {
    struct Route {
        string path;
        int time;
        Route *next;
    } *head = NULL, *tail = NULL;

    adrAirport a = firstAirport(N);
    while (a != NULL) {
        adrRoute r = firstRoute(a);
        while (r != NULL) {
            Route *newRoute = new Route;
            newRoute->path = airportID(a) + " -> " + destAirportID(r);
            newRoute->time = flightTime(r);
            newRoute->next = NULL;

            if (head == NULL || newRoute->time < head->time) {
                newRoute->next = head;
                head = newRoute;
            } else {
                Route *current = head;
                while (current->next != NULL && current->next->time < newRoute->time) {
                    current = current->next;
                }
                newRoute->next = current->next;
                current->next = newRoute;
            }

            r = nextRoute(r);
        }
        a = nextAirport(a);
    }

    Route *current = head;
    while (current != NULL) {
        cout << current->path << " | Waktu: " << current->time << " menit" << endl;
        Route *temp = current;
        current = current->next;
        delete temp;
    }
}
