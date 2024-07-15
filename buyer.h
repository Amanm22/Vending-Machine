#include "model.h"
#include<unordered_map>
#include<fstream>
#include<iostream>
#include<vector>
#include<string.h>
#include<sstream>

using namespace std;

vector<Product> products;

void getproducts() {
    products.clear();
    ifstream infile;
    infile.open("input.txt");
    if(!infile){
        cout<<"file can't be opened";
    }
    string line;
    while(getline(infile,line)){
        stringstream ss(line);
        string x;
        getline(ss,x,' ');
        int id=stoi(x);
        string name;
        getline(ss,name,' ');
        // x="";
        getline(ss,x,' ');
        int price = stoi(x);
        // x="";
        getline(ss,x,' ');
        int stock = stoi(x);
        Product newproduct(id,name,price,stock);
        products.push_back(newproduct);    
    }
    infile.close();
}
string showallproductsowner() {
    string s;
    for (auto i : products) {
        s += i.displayname();
    }
    return s;
}
string showallproducts() {
    string s;
    for (auto i: products) {
        if (i.getstock() > 0) {
            s += i.displayname();
        }
    }
    return s;
}
Product* chooseproduct() {
    cout<< " Available Products : \n"<<showallproducts();
    cout<<" Select the number of the Product : ";
    int choice;
    cin>>choice;
    if(choice>products.size()){
        cout<<" Product not found!";
        return NULL;
    }
    return &products[choice-1];
}

bool Checkout(Cart &cart){
    if(cart.isEmpty()){
        return false;
    }
    unordered_map<int,int> bought = cart.getcart();
    int total=cart.getTotal();
    cout<<" Please pay a total of Rs. "<<total<<endl;
    int cash;
    cin>>cash;
    if(cash>=total){
        ifstream file("input.txt");
        ofstream ofile("temp.txt");
        string line;
        while(getline(file,line)) {
            stringstream ss(line);
            string newline;
            string x;
            getline(ss , x , ' ');
            newline += x + " ";
            int id = stoi(x);
            getline(ss , x , ' ');
            newline += x + " ";
            getline(ss , x , ' ');
            newline += x + " ";
            getline(ss , x , ' ');
            newline += to_string(stoi(x)-bought[id]) + "\n";
            ofile << newline;
        }
        file.close();
        ofile.close();
        remove("input.txt");
        rename("temp.txt" , "input.txt");
        ofstream outfile("profit.txt",ios::app);
        string x = cart.viewcart() + "\n";
        
        outfile << x;
        outfile.close();
        cout<<" Change -- Rs. "<<cash-total<<"\n";
        cout<<" Thankyou for shopping :) \n";
        return true;
    }
    else{
        cout<<" Insuficient Cash\n";
        return false;
    }
}
void buyer(){
    
    int action;
    Cart cart;
    while(true){
        cout<<"(1) Add Item\n"<<"(2) View Cart\n"<<"(3) Checkout\n";
        cin>>action;

        if(action==1){
            Product* p = chooseproduct();
            if (p != NULL) {
                cart.addproduct(*p);
            }
        }
        
        if(action==2){
            string s=cart.viewcart();
            cout<<s;
        }

        if(action==3){
            if(Checkout(cart)){
                break;
            }
        }
    }
}
