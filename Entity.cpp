#include "Entity.h"
#include "DataStructures.h"

int Date::toInt(){
    return year*10000 + month*100 + day; // YYYYMMDD
}
std::string Date::toStr(){
    return std::to_string(year) + "/" + std::to_string(month) + "/" + std::to_string(day);
}
bool Date::operator>(Date& other){
    return toInt() > other.toInt();
}


User::User(std::string u , std::string p , Role r) : userName(u),passHash(p),userRole(r),balance(0.0) {};

Car::Car(int i,std::string c,std::string m,double p) : id(i),company(c),model(m),pricePerDay(p),status(AVAILABLE){
    Reservations=new ReservationQueue();
}
Car::~Car(){
    delete Reservations;
}
std::string Car::getStatusStr(){
    switch(status){
        case AVAILABLE : return "Available";
        case RESERVED : return "Reserved";
        case RENTED : return "Rented";
        case MAINTENANCE : return "Maintenance";
        default: return "Error";
    }
}


bool Reservation::operator>(Reservation& other){
    return startDate.toInt() > other.startDate.toInt();
}


ul hashString(const std::string& str){ // djb2
    ul hash=5381;
    for(char c : str){
        hash=hash*33 + c;
    }
    return hash;
}