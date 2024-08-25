#include<string>
#include<cmath>
#include<vector>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<ctime>
#include<unistd.h>
#include<limits> // For numeric_limits
#include<stdexcept> // For std::invalid_argument

using namespace std;

// primary parent class
class Appliance {
protected:
    int ID;
    string name;
    int quantityOrdered;
    int stock;
    int quantitySold;
    double manufacturerPrice;
    double sellingPrice;

public:
    // default constructor
    Appliance(int id, string n, int qtyOrdered, int st, int qtySold, double manPrice, double sellPrice)
        : ID(id), name(n), quantityOrdered(qtyOrdered), stock(qtyOrdered), quantitySold(qtySold), manufacturerPrice(manPrice), sellingPrice(sellPrice) {}

    // virtual destructor for derived class objects
    virtual ~Appliance() {}

    // Getter methods
    int getID() const { return ID; }
    string getName() const { return name; }
    int getQuantityOrdered() const { return quantityOrdered; }
    double getManufacturerPrice() const { return manufacturerPrice; }
    double getSellingPrice() const { return sellingPrice; }

    int getStock() const { return stock; }
    void setStock(int newStock) { stock = newStock; }

    int getQuantitySold() const { return quantitySold; }
    void setQuantitySold(int newQuantitySold) { quantitySold = newQuantitySold; }
    // Virtual method for displaying attributes to be overridden by derived classes
    virtual void displayAttributes() const {}

};

// Derived class for dishwasher
class Dishwasher : public Appliance {
private:
    string waterUsage;

public:
    // Constructor
    Dishwasher(int id, string n, int qtyOrdered, int st, int qtySold, double manPrice, double sellPrice, string water)
        : Appliance(id, n, qtyOrdered, st, qtySold, manPrice, sellPrice), waterUsage(water) {}

    // function to display specific attribute
    void displayAttributes() const override {
        cout << setw(15) <<"Water Usage: " << waterUsage << endl;
    }
};

class Microwave : public Appliance {
private:
    string wattage;

public:
    Microwave(int id, string n, int qtyOrdered, int st, int qtySold, double manPrice, double sellPrice, string watts)
        : Appliance(id, n, qtyOrdered, st, qtySold, manPrice, sellPrice), wattage(watts) {}

    void displayAttributes() const override {
        cout <<setw(15) << "Wattage: " << wattage << endl;
    }
};

class CookingRange : public Appliance {
private:
    string burnerCount;

public:
    CookingRange(int id, string n, int qtyOrdered, int st, int qtySold, double manPrice, double sellPrice, string burners)
        : Appliance(id, n, qtyOrdered, st, qtySold, manPrice, sellPrice), burnerCount(burners) {}

    void displayAttributes() const override {
        cout << setw(15) <<"Burner Count: " << burnerCount << endl;
    }
};

class CircularSaw : public Appliance {
private:
    string amp;

public:
    CircularSaw(int id, string n, int qtyOrdered, int st, int qtySold, double manPrice, double sellPrice, string amps)
        : Appliance(id, n, qtyOrdered, st, qtySold, manPrice, sellPrice), amp(amps) {}

    void displayAttributes() const override {
        cout <<setw(15) << "Amps: " << amp << endl;
    }
};

// Function to load inventory data from a text file into a vector of Appliance pointers
vector<Appliance*> loadData(const string& filename) {
    vector<Appliance*> inventory;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file " << filename << endl;
        return inventory;
    }

    int id, qtyOrdered, stock, qtySold;
    double manPrice, sellPrice;
    string name, type, attribute;

    while (file >> id) {
        file.ignore(); // skip newline character after id
        getline(file, name);
        file >> qtyOrdered >> manPrice >> sellPrice;
        // extract the first word
        // checks id of imported item against known id values
        if (id == 1111) {
            // attributes not in text file, so custom made
            string waterUsage = "300 gal/min";
            // creates instance of class in the vector
            inventory.push_back(new Dishwasher(id, name, qtyOrdered, 0, 0, manPrice, sellPrice, waterUsage));
        } else if (id == 2222) {
            
            string watt = "1000 watts";
            inventory.push_back(new Microwave(id, name, qtyOrdered, 0,0, manPrice, sellPrice, watt));
        } else if (id == 3333) {
            
            string burnerCt = "4 Burners";
            inventory.push_back(new CookingRange(id, name, qtyOrdered, 0,0, manPrice, sellPrice, burnerCt));
        } else if (id == 4444) {
            string amp = "12 Amps";
            inventory.push_back(new CircularSaw(id, name, qtyOrdered, 0,0, manPrice, sellPrice, amp));
        }
    }

    file.close();
    // returns vector of stock
    return inventory;
}

// Function to add an item to inventory
void addToInventory(vector<Appliance*>& inventory) {
    int id, qtyOrdered, stock, qtySold;
    double manPrice, sellPrice;
    string name, type, attribute;

    cout << "Enter Appliance Details:" << endl;
    cout << "ID: ";
    cin >> id;
    cin.ignore();
    cout << "Name: ";
    getline(cin, name);
    cout << "Quantity Ordered: ";
    cin >> qtyOrdered;
    cout << "Stock: ";
    cin >> stock;
    cout << "Quantity Sold: ";
    cin >> qtySold;
    cout << "Manufacturer Price: ";
    cin >> manPrice;
    cout << "Selling Price: ";
    cin >> sellPrice;
    cout << "Type (Dish Washer, Micro Wave, Cooking Range, Circular Saw): ";
    cin >> type;

    if (id == 1111) {
        cout << "Water Usage: ";
        cin.ignore();
        getline(cin, attribute);
        inventory.push_back(new Dishwasher(id, name, qtyOrdered, stock, qtySold, manPrice, sellPrice, attribute));
    } else if (id == 2222) {
        cout << "Wattage: ";
        string wattage;
        cin >> wattage;
        inventory.push_back(new Microwave(id, name, qtyOrdered, stock, qtySold, manPrice, sellPrice, wattage));
    } else if (id == 3333) {
        cout << "Burner Count: ";
        string burnerCount;
        cin >> burnerCount;
        inventory.push_back(new CookingRange(id, name, qtyOrdered, stock, qtySold, manPrice, sellPrice, burnerCount));
    } else if (id == 4444) {
        cout << "Amperage: ";
        string amp;
        cin >> amp;
        inventory.push_back(new CircularSaw(id, name, qtyOrdered, stock, qtySold, manPrice, sellPrice, amp));
    } else {
        cout << "Invalid appliance type." << endl;
    }
}

// function to make sales transactions
void makeSale(vector<Appliance*>& inventory, vector<Appliance*>& purchasedItems) {
    string searchName1,searchName2,searchName;
    int quantity;

    cout << "Enter the name of the item you want to buy: ";
    // to get around the space that is in all of the names for some reason.
    // getline wasnt working
    cin >> searchName1 >> searchName2;
    searchName = searchName1 + " " + searchName2;

    Appliance* item = nullptr;
    // linear search because its only 4 things
    for (auto& appliance : inventory) {
        if (appliance->getName() == searchName) {
            item = appliance;
            break;
        }
    }

    if (item == nullptr) {
        cout << "Item not found in inventory." << endl;
        return;
    }

    cout << "Enter the quantity you want to buy: ";
    cin >> quantity;
    // if the user inputs a non-int, it wont make a sale
    if (quantity > item->getStock()) {
        cout << "Insufficient stock." << endl;
        return;
    }

    // Update stock and quantity sold
    int newStock = item->getStock() - quantity;
    int newQuantitySold = item->getQuantitySold() + quantity;
    item->setStock(newStock);
    item->setQuantitySold(newQuantitySold);
    cout << "Purchase successful." << endl;

    // adds to vector to store purchased items
    purchasedItems.push_back(new Appliance(item->getID(), item->getName(), quantity, item->getStock(), quantity, 
                                           item->getManufacturerPrice(), item->getSellingPrice()));

}

// Function to display inventory
void displayInventory(const vector<Appliance*>& inventory) {
    // header
    cout << setw(6) << "ID" << setw(15) << "Name" << setw(10) << "Ordered" << setw(10) << "In Stock" << setw(10) << "Sold"
         << setw(20) << "Manuf. Price" << setw(17) << "Selling Price" << setw(17) << "Attribute" << endl;
    cout << setfill('-') << setw(85) << "-" << setfill(' ') << endl;
    double totalInventory = 0.0;
    int totalItems = 0;
    for (const auto& item : inventory) {
        cout << setw(6) << item->getID() << setw(15) << item->getName() << setw(10) << item->getQuantityOrdered() << setw(10)
             << item->getStock() << setw(10) << item->getQuantitySold() << setw(17) << fixed << setprecision(2)
             << item->getManufacturerPrice() << setw(17) << item->getSellingPrice();
        item->displayAttributes();
        totalInventory += item->getStock() * item->getSellingPrice();
        totalItems += item->getStock(); // Increment totalItems by the stock count of each item
    }
    cout << setfill('-') << setw(85) << "-" << setfill(' ') << endl;
    cout << "Total Inventory: $" << totalInventory << endl;
    cout << "Total number of items in the store: " << totalItems << endl; // Display the total number of items
}


// merging logic
void merge(vector<Appliance*>& inventory, int left, int mid, int right){
    int i,j,k;
    int n1 = mid-left+1;
    int n2 = right-mid;

    vector<Appliance*> L(n1), R(n2);
    for (i = 0; i < n1; i++)
        L[i] = inventory[left + i];
    for (j = 0; j < n2; j++)
        R[j] = inventory[mid + 1 + j];

    // Merge the two arrays back into the original vector
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i]->getName() <= R[j]->getName()) {
            inventory[k] = L[i];
            i++;
        } else {
            inventory[k] = R[j];
            j++;
        }
        k++;
    }
    // Copy any remaining elements of L and R back into the original vector
    while (i < n1) {
        inventory[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        inventory[k] = R[j];
        j++;
        k++;
    }
}
// function to sort inventory by name using merge sort algorithm
void mergeSort(vector<Appliance*>& inventory, int left, int right) {
    if(left <right){
        int mid = left +(right-left)/2;
        mergeSort(inventory,left,mid);
        mergeSort(inventory,mid+1,right);
        merge(inventory,left,mid,right);
    }
}

// function to search for an appliance by name using binary search algorithm
Appliance* binarySearch(const vector<Appliance*>& inventory, const string& name) {
    
    int left = 0;
    int right = inventory.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Check if the middle appliance's name matches the target name
        if (inventory[mid]->getName() == name) {
            return inventory[mid]; // Found the appliance
        }
        // If the target name is less than the middle name, search in the left half
        else if (inventory[mid]->getName() > name) {
            right = mid - 1;
        }
        // If the target name is greater than the middle name, search in the right half
        else {
            left = mid + 1;
        }
    }

    return nullptr; // placeholder
}
// function to get item sell price
double getItemPrice(const vector<Appliance*>& inventory, const string& name) {
    for (const auto& item : inventory) {
        if (item->getName() == name) {
            return item->getSellingPrice(); // Return the selling price of the found item
        }
    }
    // If item not found, return a default price
    return 0.0; // Default price 

}
// Function to print reciept to text file
void printReceipt(const vector<Appliance*>& purchasedItems) {
    // opens text file
    ofstream receiptFile("receipt.txt");
    if (!receiptFile.is_open()) {
        cerr << "Error opening receipt file." << endl;
        return;
    }

    // Write header to the receipt file
    receiptFile << "Friendly Hardware Store\n\n";
    receiptFile << "Receipt\n\n";
    receiptFile << setw(15) << "Item Name" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
    receiptFile << setfill('-') << setw(35) << "-" << setfill(' ') << endl;

    double totalAmount = 0.0;

    // Write purchased items to the receipt file
    for (const auto& item : purchasedItems) {
        double totalPrice = item->getSellingPrice() * item->getQuantitySold();
        receiptFile << setw(15) << item->getName() << setw(10) << item->getQuantitySold()
                    << setw(10) << fixed << setprecision(2) << totalPrice << endl;
        totalAmount += totalPrice;
    }

    // Write total amount due to the receipt file
    receiptFile << "\nTotal Amount Due: $" << fixed << setprecision(2) << totalAmount << endl;

    receiptFile.close();
    cout << "Receipt printed successfully to receipt.txt" << endl;
}

int main() {
    try {
        // Initialize purchased items vector
        vector<Appliance*> purchasedItems;

        // Load inventory data from file
        vector<Appliance*> inventory = loadData("data/inventory.txt");
        string searchName1, searchName2, searchName;
        int choice;
        Appliance* foundAppliance = nullptr;
        double price = 0.0;
        // sort the inventory alphabetically
        mergeSort(inventory, 0, inventory.size()-1);

        do {
            cout << endl;
            try {
                cout << "Welcome to the Friendly Hardware Store!\n"
                    << "Choose among the following options:\n"
                    << "1: To see if an item is in the store.\n"
                    << "2: To buy an item.\n"
                    << "3: To check the price of an item.\n"
                    << "4: To print the inventory.\n"
                    << "5: To print receipt to a text file.\n"
                    << "9: To end the program.\n";
                cout << "Enter your choice: ";
                cin >> choice;

                if (cin.fail()) {
                    throw std::invalid_argument("Invalid input. Please enter a number.");
                }

                // Clear input buffer and reset error state
                cin.clear(); // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard input buffer

                switch (choice) {
                    case 1:
                        cout << "Enter the item you are looking for: ";
                        cin >> searchName1 >> searchName2;
                        searchName = searchName1 + " " + searchName2;
                        foundAppliance = binarySearch(inventory, searchName);
                        if (foundAppliance != nullptr && foundAppliance->getStock() >0) {
                            cout << "Appliance found in stock: " << foundAppliance->getName() << endl;
                        } 
                        else if(foundAppliance != nullptr && foundAppliance->getStock() ==0){
                            cout << "Appliance out of stock" << endl;
                        }
                        else {
                            cout << "Appliance not found." << endl;
                        }
                        break;
                    case 2:
                        makeSale(inventory, purchasedItems); // Pass purchasedItems by reference
                        break;
                    case 3:
                        cout << "Enter the item you are looking for: ";
                        cin >> searchName1 >> searchName2;
                        searchName = searchName1 + " " + searchName2;
                        cout << searchName << endl;
                        price = getItemPrice(inventory, searchName);
                        if (price != 0.0) {
                            cout << "The price of " << searchName << " is $" << price << endl;
                        } else {
                            cout << "Item not found." << endl;
                        }
                        break;
                    case 4:
                        // Print the inventory
                        displayInventory(inventory);
                        break;
                    case 5:
                        // Print receipt to a text file
                        printReceipt(purchasedItems);
                        break;
                    case 9:
                        // End the program
                        break;
                    default:
                        cout << "Invalid choice. Please enter a valid option.\n";
                        break;
                }
                // catch unwanted inputs for choice
            } catch (const std::invalid_argument& e) {
                cout << e.what() << endl;
                // Clear input buffer and reset error state
                cin.clear(); // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard input buffer
            }

        } while (choice != 9);

        // Cleanup memory
        for (Appliance* app : inventory) {
            delete app;
        }
        // catch any weird errors
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    return 0;
}

