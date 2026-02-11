#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H
#include "Entity.h"
#include <iostream>

using namespace std;

class ReservationQueue{
private:
    Reservation* arr;
    int size;
    int capacity;
    void resize();
    void upHeap(int index);
    void downHeap(int index);
public:
    ReservationQueue();
    ~ReservationQueue();
    void push(Reservation r);
    Reservation pop();
    bool isEmpty();
    Reservation prior();

};

#endif