#include<iostream>
#include<string>
// #include "model.h"
// #include "buyer.h"
#include "owner.h"
using namespace std;

int main() {
    cout<<"Choose : \n(1) Buyer \n(2) Owner\n";
    getproducts();
    int choice;
    cin>>choice;
    if (choice == 1) {
        buyer();
    }
    if (choice == 2) {
        owner();
    }
    return 0;
}