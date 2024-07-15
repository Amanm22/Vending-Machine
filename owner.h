#include<unordered_map>
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include "buyer.h"
using namespace std;

void Additems(){
    getproducts();
    string s = showallproductsowner();
    cout<<s;
    cout<<"(1) Add new product\n(2) Update Stock\n";
    int choice;
    cin>>choice;
    if (choice == 1){
        ofstream outfile("input.txt",ios :: app);
        int id = products.size() + 1;
        cout<< " Enter name of product\n";
        string name;
        cin>>name;
        cout<< " Enter price\n";
        int price;
        cin>>price;
        cout<< " Enter stock\n";
        int stock;
        cin>>stock;
        string s = to_string(id) + " " + name + " " + to_string(price) + " " + to_string(stock) + "\n";
        outfile << s;
        
    }
    if (choice == 2){
        cout<< " Enter id\n";
        int id;
        cin>>id;
        ifstream file("input.txt");
        ofstream ofile("temp.txt");
        string line;
        while(getline(file,line)){
            stringstream ss(line);
            string x;
            getline(ss , x , ' ');
            int cid = stoi(x);
            if(cid == id){
                cout<<" Enter stock\n";
                int stock;
                cin >> stock;
                string newline = x;
                getline(ss , x , ' ');
                newline += " " + x;
                getline(ss , x , ' ');
                newline += " " + x;
                getline(ss , x , ' ');
                newline += " " + to_string(stoi(x) + stock) +"\n";
                ofile << newline;
            }
            else{
                ofile << line << "\n";
            }
        }
        file.close();
        ofile.close();
        remove("input.txt");
        rename("temp.txt" , "input.txt");
    } 
}

void seeprofit(){
    ifstream ifile("profit.txt");
    string x;
    if(getline(ifile, x)){
        cout<< "Total profit is Rs. "<< x<<endl;
    }else{
        cout<< "Total profit is Rs. 0"<<endl;
    }
    
}
void owner() {
    string password = "vending123";
    cout <<" Enter password : \n";
    string ipass;
    cin>>ipass;
    while (true) {
        if (ipass == password){
            cout<< "(1) Add Items\n(2) See Profit\n(3) Done\n";
            int action;
            cin>>action;
            if (action == 1) {
                Additems();
            }
            if (action == 2) {
                seeprofit();
            }
            if (action == 3) break; 

        }
        else{
            cout<<"Wrong Password!";
        }
    }

}