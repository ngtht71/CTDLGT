#include <iostream>
#include <vector>

using namespace std;

struct Item {
    int weight;
    int value;

    Item(int weight_, int value_) {
        weight = weight_;
        value = value_;
    }
};

int dynamicPlanningAlgo(vector<Item>& item, int W){
    int n = item.size();
    int dp[n+1][W + 1];   /// dp[i][j], i: i frist items, capacity: j

    for (int i = 0; i <= W; i++) dp[0][i] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= W; j++) {
            Item tmp = item[i-1];
            if (tmp.weight > j) dp[i][j] = dp[i-1][j];
            else
                dp[i][j] = max(dp[i-1][j], dp[i-1][j - tmp.weight] + tmp.value);
        }
    }
    return dp[n][W];
}

int main() {
    //int n; cin >> n;    // num of item
    //int W; cin >> W;    // capacity

    int n = 5, W = 10;

    vector <Item> item;
    int weight[n] = {6, 2, 4, 3, 11};
    int value[n] = {20, 8, 14, 13, 35};
    for (int i = 0; i < n; i++) {
        int x, y;
        x = weight[i];
        y = value[i];
        //cin >> x >> y;
        Item* it = new Item(x, y);
        item.push_back(*it);
    }

    cout << "Max total value we can take with Dynamic Planning Algorithm is: "
         << dynamicPlanningAlgo(item, W) << endl;
    return 0;
}
