#ifndef Entity_H
#define Entity_H
#include<string>
#include<iostream>
#define ul unsigned long

enum Role{STAFF,GUEST,CUSTOMER,MANAGER};
enum CarStatus{AVAILABLE,RESERVED,RENTED,MAINTENANCE};

class ReservationQueue;

ul hashString(const std::string& str);

struct Date{
    int year,month,day;
    int toInt();
    std::string toStr();
    ul dateToDays();

    bool operator>(Date& other);
};

struct User{
    std::string userName;
    ul passHash;
    Role userRole;
    double balance;

    User(std::string u , std::string p , Role r);
};

struct Car{
    int id;
    std::string company;
    std::string model;
    double pricePerDay;
    CarStatus status;
    ReservationQueue* Reservations; // صف رزرو های مربوط به هر ماشین
    std::string currentRenter;
    Date dueReturnDate; // تاریخی که یارو باید ماشین رو تحویل بده

    std::string getStatusStr();
    Car(int i,std::string c,std::string m,double p);
    ~Car();
};

struct Reservation{
    Date startDate;
    std::string userName;
    int duration;

    bool operator>(Reservation& other);
};


#endif