#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <cstring>
struct Activity {
    std::string str;
    int avg, level;

    bool operator<(const Activity& other) const {
        if (avg != other.avg) {
            return avg > other.avg;
        }
        if (level != other.level) {
            return level < other.level;
        }
        return str < other.str;
    }
};

std::map<std::string, std::vector<int>> m;
std::set<Activity> s;
std::string type, oper;

void mapInsert() {
    std::string name;
    int num, x;
    std::cin >> name >> num;
    if (m.find(name) != m.end()) {
        for(int i = 0; i < num; i++) {
            std::cin >> x;
        }
        std::cout << "Error" << std::endl;
    }
    else for(int i = 0; i < num; i++) {
        std::cin >> x;
        m[name].push_back(x);
    }
}

void mapTraverse() {
    for (auto it = m.begin(); it != m.end(); it++) {
        std::cout << it->first << " ";
        for (int i = 0; i < it->second.size(); i++) {
            std::cout << it->second[i] << " ";
        }
        std::cout << std::endl;
    }
}

void mapSize() {
    std::cout << m.size() << std::endl;
}

void mapErase() {
    // std::cout << "erase" << std::endl;
    std::string name;
    std::cin >> name;
    if (m.find(name) == m.end()) std::cout << "Error" << std::endl;
    else m.erase(name);
}

void mapCount() {
    std::string name;
    std::cin >> name;
    std::cout << m.count(name) << std::endl;
}

void mapVisitVec() {
    std::string name;
    int index;
    std::cin >> name >> index;
    if (m.find(name) == m.end()) {
        std::cout << "Error" << std::endl;
        return;
    }
    if (m[name].size() <= index || index < 0) {
        std::cout << "Error" << std::endl;
        return;
    }
    std::cout << m[name][index] << std::endl;
}

void mapVisit() {
    std::string name;
    std::cin >> name;
    if (m.find(name) == m.end()) {
        std::cout << "Error" << std::endl;
        return;
    }
    int len = m[name].size();
    std::cout << len << " ";
    for (int i = 0; i < len; i++) {
        std::cout << m[name][i] << " ";
    }
    std::cout << std::endl;
}

void mapAppend() {
    std::string name;
    int element;
    std::cin >> name >> element;
    if (m.find(name) == m.end()) {
        std::cout << "Error" << std::endl;
        return;
    }
    m[name].push_back(element);
}

void setSize() {
    std::cout << s.size() << std::endl;
}

void setInsert() {
    Activity x;
    std::cin >> x.avg >> x.level >> x.str;
    if (s.find(x) == s.end()) s.insert(x);
    else std::cout << "Error" << std::endl;
}

void setErase() {
    Activity x;
    std::cin >> x.avg >> x.level >> x.str;
    if(s.find(x) == s.end()) std::cout << "Error" << std::endl;
    else s.erase(x);
}

void setCount() {
    Activity x;
    std::cin >> x.avg >> x.level >> x.str;
    std::cout << s.count(x) << std::endl;
}

void setTraverse() {
    for (auto it = s.begin(); it != s.end(); it++) {
        std::cout << it->avg << " " << it->level << " " << it->str << std::endl;
    }
}

int main() {
    // std::freopen("P1383.out", "w", stdout);
    while(1) {
        std::cin >> type;
        if (type == "end") break;
        std::cin >> oper;
        if (type == "map") {
            if(oper == "insert") mapInsert();
            if(oper == "traverse") mapTraverse();
            if(oper == "size") mapSize();
            if(oper == "erase") mapErase();
            if(oper == "count") mapCount();
            if(oper == "append") mapAppend();
            if(oper == "visit") mapVisit();
            if(oper == "visitVec") mapVisitVec();
        }
        if (type == "set") {
            if(oper == "insert") setInsert();
            if(oper == "traverse") setTraverse();
            if(oper == "size") setSize();
            if(oper == "erase") setErase();
            if(oper == "count") setCount();
        }
    }
    return 0;
}