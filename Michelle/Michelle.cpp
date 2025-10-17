#include <iostream>
#include <cstring>
#include <unordered_map>
#include <set>
struct Students {
    std::string name;
    bool gender;
    int _class, score[10], avg;

    bool operator<(const Students& other) const {
        if (avg != other.avg) {
            return avg > other.avg;
        }
        return name < other.name;
    }
};

std::unordered_map<std::string, int> m;
std::set<Students> data;
bool flag = 0;


void Add() {
    Students curr;
    std::cin >> curr.name >> curr.gender >> curr._class;
    for (int i = 0; i < 9; i++) {
        std::cin >> curr.score[i];
    }
    if (flag) {
        std::cout << "[Error]Cannot add student now." << '\n';
        return;
    }
    if (m.find(curr.name) != m.end()) {
        std::cout << "[Error]Add failed." << '\n';
        return;
    }
    m[curr.name] = 0;
    data.insert(curr);
}


int main() {
    std::string oper;
    while(1) {
        std::cin >> oper;
        if (oper == "ADD") Add();
        if (oper == "START") flag = 1, Flush();
        if (oper == "UPDATE") Update();
        if (oper == "FLUSH") Flush();
        if (oper == "PRINTLIST") Printlist();
        if (oper == "QUERY") Query();
        if (oper == "END") break;
    }
    return 0;
}

// 是否可能没有START