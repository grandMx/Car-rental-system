#include "CarRentalSystem.h"
#include <iostream>

CarRentalSystem::CarRentalSystem() : idCounter(1), currentUser(nullptr){
    signUp("admin","admin",STAFF);
}
void CarRentalSystem::signUp(string userName, string pass, Role role=CUSTOMER){
    if(table.search(userName) != nullptr){
        cout<<"userName exists, choose another."<<endl;
        return;
    }
    User* newUser=new User(userName, pass, role);
    userList.append(newUser);
    table.insert(userName,newUser);
    cout<<"Registeration was successful!"<<endl;
}
void CarRentalSystem::login(string userName, string pass){
    User* user=table.search(userName);
    if(user!=nullptr && user->passHash==hashString(pass)){
        currentUser=user;
        cout<<"Welcome "<<userName<<"!"<<endl;
        return;
    }
    cout<<"login failed!\n";
}
void CarRentalSystem::logOut(){
    cout<<currentUser->userName<<" logged out"<<endl;
    currentUser=nullptr;
}

void CarRentalSystem::addCar(string company , string model, double price){

}
void CarRentalSystem::carListPrinter(){

}
void CarRentalSystem::searchCarByModel(string model){

}
void CarRentalSystem::carFiltering(){

}
void CarRentalSystem::processReservation(string model){

}
void CarRentalSystem::returnCar(string model){

}
void CarRentalSystem::availableCars(){

}