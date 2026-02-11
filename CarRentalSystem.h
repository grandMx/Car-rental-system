#ifndef CARRENTALSYSTEM_H
#define CARRENTALSYSTEM_H
#include "DataStructures.h"

class CarRentalSystem{
private:
    DoublyLinkedList<Car> carList;
    DoublyLinkedList<User> userList;
    User* currentUser;
    AVLTree carIndexes;
    hashTable table;//usernames map to userPtrs
    int idCounter;
public:
    CarRentalSystem();

    void signUp(string userName, string pass, Role role=CUSTOMER);
    void login(string userName, string pass);
    void logOut();

    void addCar(string company , string model, double price);
    void carListPrinter();
    void searchCarByModel(string model); // with AVL
    void carFiltering(string flterCompany, double maxPrice); 
    //staff works
    void processReservation(string model); //giving the car and set the car returns date
    void returnCar(string model); // return car and calculate penalty

    void showAvailableCarsAndReserve();


};



#endif