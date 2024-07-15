#include<unordered_map>
#include<fstream>
#include<string>
using namespace std;
class Item;
class Cart;
class Product{
    int id;
    string name;
    int price;
    int stock;

    public:
    Product(){}
    Product( int id, string name, int price,int stock) {
        this->id = id;
        this->name = name;
        this->price = price;
        this->stock = stock;
    }

    string displayname() {
        string s = to_string(id) + " -- " + name + "  Rs." + to_string(price) + "   Stock - " + to_string(stock) + "\n";
        return s;
    }
    int getstock() {
        return stock;
    }
    friend class Item;
    friend class Cart;
};

class Item {
    Product product;
    int qauntity;

    public:
    Item() {}
    Item( Product product, int qauntity) {
        this->product = product;
        this->qauntity = qauntity;
    }

    int getitemprice() {
        return qauntity*product.price;
    }
    string getiteminfo() {
        return " " + product.name + " x" + to_string(qauntity) + "     " + "Rs. " + to_string(qauntity*product.price) + "\n";
    }
    friend class Cart;
};

class Cart{
    unordered_map<int,Item> items;

    public:
    
    void addproduct(Product product) {
        if (items.count(product.id) == 0) {
            Item newItem(product,1);
            items[product.id] = newItem;

        }
        else {
            items[product.id].qauntity++;
        }
    }
    int getTotal(){
        int total=0;
        for(auto item:items){
            total=total+item.second.getitemprice();
        }
        return total;
    }

    string viewcart() {
        if (items.empty()){
            return "Cart is empty!";
        }
        string s;
        for (auto i: items) {
            s += i.second.getiteminfo();
        }
        return s + " Total Price = Rs. " + to_string(getTotal())+"\n";
    }

    bool isEmpty(){
        return items.empty();
    }
    unordered_map<int,int> getcart() {
        unordered_map<int,int> c;
        for (auto i : items) {
            c[i.first] = i.second.qauntity;
        }
        return c;
    }

};