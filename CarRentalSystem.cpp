#include "CarRentalSystem.h"
#include <iostream>
#include <iomanip>

CarRentalSystem::CarRentalSystem() : idCounter(1), currentUser(nullptr){
    signUp("admin","admin",MANAGER);
}
void CarRentalSystem::signUp(string userName, string pass, Role role){
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
    if(currentUser!=nullptr){
        cout<<"How many times you want to login baby??"<<endl;
        return;
    }
    User* user=table.search(userName);
    if(user!=nullptr && user->passHash==hashString(pass)){
        currentUser=user;
        cout<<"Welcome "<<userName<<"!"<<endl;
        return;
    }
    cout<<"login failed!\n";
}
void CarRentalSystem::logOut(){
    if(currentUser!=nullptr){
        cout<<currentUser->userName<<" logged out"<<endl;
        currentUser=nullptr;
        return;
    }
    cout<<"Error: No user is logged in to log out!!!"<<endl;
    
}

void CarRentalSystem::addCar(string company , string model, double price){
    if(!currentUser || currentUser->userRole == GUEST || currentUser->userRole == CUSTOMER){
        cout<<"You dont have access!"<<endl;
        return;
    }
    Car* newCar=new Car(idCounter++,company,model,price);
    carList.append(newCar);
    carIndexes.insert(model,newCar);
    cout<<"car added successfully!"<<endl;
}
void CarRentalSystem::carFiltering(string filterCompany, double maxPrice){ //traversiing on carList
    if(currentUser==nullptr){
        cout<<"Login first!"<<endl;
        return;
    }
    Node<Car>* temp=carList.head;
    cout<<"\nFilter Result:\n";
    cout<<left<<setw(5)<<"ID"<<setw(15)<<"Make"<<setw(15)<<"Model"<<setw(10)<<"Price"<<"Status"<<endl;
    while(temp){
        Car* x=temp->data;
        bool flag=1;
        if((maxPrice!=-99) && (x->pricePerDay > maxPrice)) flag=0;
        if((filterCompany != "*")&&(x->company != filterCompany)) flag=0;

        if(flag){
            cout<<left<<setw(5)<<x->id <<setw(15)<<x->company<<setw(15)<<x->model<<setw(10)<<x->pricePerDay <<x->getStatusStr()<<endl;
        }
        temp=temp->next;
        cout<<"------------------------\n";
    }
}
void CarRentalSystem::carListPrinter(){
    carFiltering("*",-99); // each one is filter remover
}
void CarRentalSystem::searchCarByModel(string model){ // with AVl
    if(currentUser==nullptr){
        cout<<"Login first!"<<endl;
        return;
    }
    Car* temp=carIndexes.search(model);
    if(temp){
        cout<<"car found: "<<temp->company<<" "<<temp->model<<" "<<temp->getStatusStr()<<"\n";
    }
    else cout<<"car not found!\n";
} 
void CarRentalSystem::showAvailableCarsAndReserve(){
    if(!currentUser){ 
        cout<<"login first!\n"; 
        return; 
    }

    cout<<"\nAvailable cars:\n";
    Node<Car>* current=carList.head;
    cout<<left<<setw(15)<<"Company" << setw(15) << "Model" << setw(10) << "Price" << endl;
    while(current){
        if(current->data->status == AVAILABLE){
            cout<<left<<setw(15)<<current->data->company<<setw(15)<<current->data->model<<setw(10)<<current->data->pricePerDay<<endl;
        }
        current=current->next;
    }
    
    string userChoice;
    cout<<"\nEnter Model to Reserve (or type 'return'): "; 
    cin>>userChoice;
    if(userChoice=="return") return;

    Car* car = carIndexes.search(userChoice);
    if(!car || (car->status != AVAILABLE)){
        cout<<"Invalid or Unavailable.\n"; 
        return; 
    }

    int Startdate,dur;
    cout<<"Start Date (YYYYMMDD): "; 
    if(!(cin>>Startdate)){
        cout<<"Error: Invalid date format!\n";
        cin.clear(); 
        cin.ignore(10000,'\n');
        return;
    }
    cout<<"Duration(Days): "; 
    cin>>dur;

    Date d={Startdate/10000, (Startdate%10000)/100, Startdate%100};
    Reservation r={d, currentUser->userName, dur};
    
    car->Reservations->push(r);
    car->status=RESERVED;
    cout<<"Reserved successfully.\n";
}
void CarRentalSystem::processReservation(string model){
    if(!currentUser || currentUser->userRole == GUEST || currentUser->userRole == CUSTOMER ){
        cout<<"Access Denied!"<<endl;
        return;
    }
    
    Car* car = carIndexes.search(model);
    if(car && !car->Reservations->isEmpty()){
        Reservation r = car->Reservations->pop();

        car->status = RENTED;
        car->currentRenter = r.userName;
        // Date -> Days
        long startDays = r.startDate.dateToDays();
        long endDays = startDays + r.duration;
        
        int y = endDays/365;
        int rem = endDays%365;
        int m = rem/30;
        int d = rem % 30;
        if (d==0) d=30;
        car->dueReturnDate = {y, m, d};

        cout<<"Rented to "<<r.userName<<" By "<<r.duration<<" days.\n";
    } 
    else{
        cout<<"No reservation left.\n";
    }
}
void CarRentalSystem::returnCar(string model){
    if(!currentUser){
        cout << ">> Error: Please login first.\n";
        return;
    }
    Car* car = carIndexes.search(model);
    if(!car || car->status != RENTED){
        cout<< ">> Error: car has not been rented.\n";
        return;
    }

    if(car->currentRenter != currentUser->userName && currentUser->userRole != STAFF){
        cout << "Error: You have not rented this car!\n";
        return;
    }

    int returnDate;
    cout<<"Enter Actual Return Date (YYYYMMDD): "; 
    cin>>returnDate;
    Date RetDate = {returnDate/10000, (returnDate%10000)/100, returnDate%100};
    long dueDays = car->dueReturnDate.dateToDays();
    long RetDays = RetDate.dateToDays();
    long daysLate = RetDays-dueDays;

    cout << "\nbill:\n";
    cout << "Due Date: " << car->dueReturnDate.toStr() << endl;
    
    if (daysLate > 0) {
        double penalty = daysLate*(car->pricePerDay*2);
        cout<<"days late num: "<<daysLate<<"\n";
        cout<<"penalty: "<< penalty<<"\n";
        currentUser->balance-=penalty;
    } 
    else{
        cout<<"Return on time, No penalty.\n";
    }

    car->currentRenter = "";
    car->status = AVAILABLE;
    if (!car->Reservations->isEmpty()) {
        car->status = RESERVED;
        cout << ">> Status: RESERVED\n";
    }
    cout << "----------------\n";
}

void CarRentalSystem::promoteUserToStaff(string username){
    if(!currentUser || currentUser->userRole != MANAGER){
        cout<<"Access Denied!\n";
        return;
    }
    User* u=table.search(username);
    if(u==nullptr){
        cout<<"User not found!\n";
        return;
    }
    if(u->userRole==STAFF || u->userRole==MANAGER){
        cout<<"User is already Staff/Manager!\n";
        return;
    }
    u->userRole=STAFF;
    cout<<username<<" promoted to STAFF.\n";
}
void CarRentalSystem::Report(){
    if(!currentUser || currentUser->userRole != MANAGER){
        cout<<"Access Denied!\n";
        return;
    }
    int totalCars=0;
    int rentedCars=0;
    int reservedCars=0;
    int availableCars=0;
    Node<Car>* temp=carList.head;
    while(temp){
        totalCars++;
        switch(temp->data->status){
            case AVAILABLE : availableCars++; break;
            case RENTED : rentedCars++; break;
            case RESERVED : reservedCars++; break;
            default: break;
        }
        temp = temp->next;
    }
    cout<<"\n### MANAGER REPORT ###\n";
    cout<<"Total car numbers: "<<totalCars<<endl;
    cout<<"Available: "<<availableCars<<endl;
    cout<<"Rented: "<<rentedCars<<endl;
    cout<<"Reserved: "<<reservedCars<<endl;
}
