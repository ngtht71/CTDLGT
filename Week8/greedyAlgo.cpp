#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Item {
    int weight;
    int value;
    double real_value;

    Item(int weight_, int value_) {
        weight = weight_;
        value = value_;
        real_value = 1.0 * value_ / weight_;
    }
};

bool cmp (Item a, Item b) {
    return a.real_value > b.real_value;
}

void greedyAlgo (vector<Item> item, int n, int W) {
    int total_weight = 0;
    int total_value = 0;
    for (int i = 0; i < n; i++) {
        if (item[i].weight + total_weight > W) break;
        total_weight += item[i].weight;
        total_value += item[i].value;
    }
    cout << "With capacity " << W << " we can take:\n";
    cout << "Total weight: " << total_weight << endl;
    cout << "Total value: " << total_value << endl;
}

int main() {
    int n; cin >> n;    // num of item
    int W; cin >> W;    // capacity

    vector <Item> item;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        Item* it = new Item(x, y);
        item.push_back(*it);

    }

    sort (item.begin(), item.end(), cmp);
    greedyAlgo(item, n, W);
    return 0;
}
