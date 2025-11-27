#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

struct Item {
    int value;
    int weight;
    
    Item(int v, int w) : value(v), weight(w) {}
};

bool compare(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

double fractionalKnapsack(int capacity, vector<Item>& items) {
    // Sort items by value/weight ratio in descending order
    sort(items.begin(), items.end(), compare);
    
    double totalValue = 0.0;
    
    for (int i = 0; i < items.size(); i++) {
        if (capacity >= items[i].weight) {
            // Take the whole item
            capacity -= items[i].weight;
            totalValue += items[i].value;
        } else {
            // Take fraction of the item
            double fraction = (double)capacity / items[i].weight;
            totalValue += items[i].value * fraction;
            break;
        }
    }
    
    return totalValue;
}

int main() {
    
    int capacity = 50;
    
    vector<Item> items;
    items.push_back(Item(60, 10));
    items.push_back(Item(100, 20));
    items.push_back(Item(120, 30));
    
    cout << "Items (value, weight):" << endl;
    for (int i = 0; i < items.size(); i++) {
        cout << "Item " << i + 1 << ": (" << items[i].value << ", " << items[i].weight << ")";
        cout << " - Ratio: " << (double)items[i].value / items[i].weight << endl;
    }
    
    cout << "\nKnapsack Capacity: " << capacity << endl;
    
    double maxValue = fractionalKnapsack(capacity, items);
    
    cout << "Maximum value: " << maxValue << endl;
    
    return 0;
}
