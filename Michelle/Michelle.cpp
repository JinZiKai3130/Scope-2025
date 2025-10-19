#include <iostream>
#include <cstring>
#include <unordered_map>
#include <set>

const int N = 1e4+5;
struct Students {
    char gender;
    int _class, score[10], avg, ranking;
};
std::unordered_map<std::string, Students> m;

bool flag = 0;
int total_students;
struct cmp {
    bool operator ()(const std::string& stu1, const std::string& stu2) const {
        if (m[stu1].avg != m[stu2].avg) {
            return m[stu1].avg > m[stu2].avg;
        }
        for (int i = 0; i < 9; i++) {
            if (m[stu1].score[i] != m[stu2].score[i]) {
                return m[stu1].score[i] > m[stu2].score[i];
            }
        }
        return stu1 < stu2;
    }
};

std::set<std::string, cmp> data;
std::string unchanged_rank[N];

void Add() {
    std::string add_name;
    Students curr;
    int sum = 0;
    std::cin >> add_name >> curr.gender >> curr._class;
    for (int i = 0; i < 9; i++) {
        std::cin >> curr.score[i];
        sum += curr.score[i];
    }
    curr.avg = sum / 9;
    if (flag) {
        std::cout << "[Error]Cannot add student now.\n";
        return;
    }
    if (m.find(add_name) != m.end()) {
        std::cout << "[Error]Add failed.\n";
        return;
    }
    total_students++;
    m[add_name] = curr;
    data.insert(add_name);
}

void Flush() {
    int cnt = 0;
    for (auto it = data.begin(); it != data.end(); it++) {
        cnt++;
        m[*it].ranking = cnt;
        unchanged_rank[cnt] = *it;
    }
}

void Update() {
    std::string update_name;
    int update_score, update_code;
    std::cin >> update_name >> update_code >> update_score;
    if (m.find(update_name) == m.end()) {
        std::cout << "[Error]Update failed.\n";
        return;
    }
    Students curr = m[update_name];
    int sum = 0;
    for (int i = 0; i < 9; i++) sum += curr.score[i];
    curr.avg = (sum - curr.score[update_code] + update_score) / 9;
    curr.score[update_code] = update_score;
    data.erase(update_name);
    m[update_name] = curr;
    data.insert(update_name);
    // the number in the set can be updated and flushed
}

std::string OutPutGender(char gen) {
    if (gen == 'M') return "male";
    else return "female";
}


void Printlist() {
    for (int i = 1; i <= total_students; i++) {
        std::cout << i << " " << unchanged_rank[i] << " "
                  << OutPutGender(m[unchanged_rank[i]].gender) << " "
                  << m[unchanged_rank[i]]._class << " "
                  << m[unchanged_rank[i]].avg << "\n";
        for (int i = 1; i <= total_students; i++) {
            
        }
    }
}

void Query() {
    std::string query_name;
    std::cin >> query_name;
    if (m.find(query_name) == m.end()) {
        std::cout << "[Error]Query failed.\n";
        return;
    }
    else {
        std::cout << "STUDENT " << query_name << " NOW AT RANKING " 
                  << m[query_name].ranking << "\n";
    }
}

int main() {
    //freopen("1.in", "r", stdin);
    // freopen("1.ans", "w", stdout);
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