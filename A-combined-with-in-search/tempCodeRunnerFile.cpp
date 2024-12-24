#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <cmath>
#include <algorithm>

using namespace std;

struct Node {
    pair<int, int> position; 
    int g; 
    int h; 
    int f; 
    Node* parent; 

    Node(pair<int, int> pos, Node* par = nullptr) : position(pos), parent(par), g(0), h(0), f(0) {}
};


int heuristic(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second); // Khoảng cách Manhattan
}

vector<pair<int, int>> a_star_dfs(pair<int, int> start, pair<int, int> goal, const vector<vector<int>>& grid) {
    stack<Node*> dfsStack; 
    unordered_set<string> closedSet; 

    Node* startNode = new Node(start); 
    startNode->h = heuristic(start, goal); 
    startNode->f = startNode->g + startNode->h; 
    dfsStack.push(startNode); 

    while (!dfsStack.empty()) {
        Node* currentNode = dfsStack.top(); 
        dfsStack.pop(); 

        if (currentNode->position == goal) {
            vector<pair<int, int>> path; 
            while (currentNode) {
                path.push_back(currentNode->position); 
                currentNode = currentNode->parent;
            }
            reverse(path.begin(), path.end()); 
            return path; 
        }

        string currentKey = to_string(currentNode->position.first) + "," + to_string(currentNode->position.second);
        closedSet.insert(currentKey); // Thêm nút vào tập hợp đã khám phá

        vector<pair<int, int>> neighbors = {
            {0, 1}, {1, 0}, {0, -1}, {-1, 0} // 4 hướng di chuyển
        };

        for (const auto& move : neighbors) {
            pair<int, int> newPos = {currentNode->position.first + move.first, currentNode->position.second + move.second};

            if (newPos.first < 0 || newPos.first >= grid.size() || newPos.second < 0 || newPos.second >= grid[0].size() || grid[newPos.first][newPos.second] == 1) {
                continue; 
            }

            Node* neighborNode = new Node(newPos, currentNode); // Tạo nút hàng xóm
            neighborNode->g = currentNode->g + 1; // Cập nhật g
            neighborNode->h = heuristic(newPos, goal); // Tính h cho hàng xóm
            neighborNode->f = neighborNode->g + neighborNode->h; // Tính f cho hàng xóm

            string neighborKey = to_string(neighborNode->position.first) + "," + to_string(neighborNode->position.second);
            if (closedSet.find(neighborKey) != closedSet.end()) {
                continue;
            }

            dfsStack.push(neighborNode); 
        }
    }
    return {};
}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0}
    };
int x,y,a,b;
cout<<"Nhap toa do cua diem bat dau: ";cin>>x>>y;
cout<<"Nhap toa do cua diem ket thuc: ";cin>>a>>b;

    pair<int, int> start = {x, y};
    pair<int, int> goal = {a, b}; 

    vector<pair<int, int>> path = a_star_dfs(start, goal, grid); 

    if (!path.empty()) {
        cout << "Duong di tu diem bat dau den diem ket thuc:" << endl;
        for (const auto& pos : path) {
            cout << "(" << pos.first << ", " << pos.second << ") "; 
        }
        cout << endl;
    } else {
        cout << "Khong tim thay duong di!" << endl;
    }

    return 0;
}