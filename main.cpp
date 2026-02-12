#include <iostream>
#include "CarRentalSystem.h"

using namespace std;

int main() {
    CarRentalSystem sys;

    sys.login("admin", "admin");
    sys.addCar("Toyota", "Camry", 50.0);
    sys.addCar("Toyota", "Corolla", 40.0);
    sys.addCar("Benz", "C200", 120.0);
    sys.addCar("Benz", "S500", 300.0);
    sys.logOut();

    int choice;
    while (true) {
        cout << "\n### CAR RENTAL System ###\n";
        cout << "1.Register\n2.Login\n3.List All Cars\n4.Filter Cars (company/price)\n";
        cout << "5.Search Model\n6.Reserve Car\n7.Process Rent(STAFF only!)\n";
        cout << "8.Return & calculate penalty(STAFF only!)\n9.Add New Car(STAFF only!)\n10.Promote User(MANAGER)\n11.System Report(MANAGER)\n12.Log Out\n0.Exit\n";
        cin >> choice;

        string s1, s2;
        double d1;

        switch (choice) {
            case 1:
                cout << "UserName: "; 
                cin >> s1; 
                cout << "Password: "; 
                cin >> s2;
                sys.signUp(s1, s2);
                break;
            case 2:
                cout << "UserNama: "; 
                cin >> s1; 
                cout << "Password: "; 
                cin >> s2;
                sys.login(s1, s2);
                break;
            case 3:
                sys.carListPrinter();
                break;
            case 4:
                cout << "Company('*' for Any): "; 
                cin >> s1;
                cout << "Max Price(-99 for Any): "; 
                cin >> d1;
                sys.carFiltering(s1, d1);
                break;
            case 5:
                cout << "Model: "; 
                cin >> s1;
                sys.searchCarByModel(s1);
                break;
            case 6:
                sys.showAvailableCarsAndReserve();
                break;
            case 7:
                cout << "Model: "; 
                cin >> s1;
                sys.processReservation(s1);
                break;
            case 8:
                cout << "Model: "; 
                cin >> s1;
                sys.returnCar(s1);
                break;
            case 9:
                cout << "Add New Car:\n";
                cout << "Company: "; cin >> s1;
                cout << "Model: "; cin >> s2;
                cout << "Price Per Day: "; cin >> d1;
                sys.addCar(s1, s2, d1); 
                break;
            case 10:
                cout<<"Enter username to promote to STAFF: ";
                cin>>s1;
                sys.promoteUserToStaff(s1);
                break;
            case 11:
                sys.Report();
                break;
            case 12:
                sys.logOut();
                break;
            case 0:
                return 0;
            default:
                cout << "Invalid Option.\n";
        }
    }
}