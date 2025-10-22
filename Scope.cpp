#include <iostream>
#include <utility>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

const int N = 1e6+5;
struct Variables {
    std::string s, type;
    int num;
};

struct cmp {
    bool operator()(const std::pair<std::string, int> &data_1,
                    const std::pair<std::string, int> &data_2) const {
        if (data_1.second != data_2.second) {
            return data_1.second > data_2.second;
        }
        return data_1.first < data_2.first;
    }
};

struct PairHash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

std::unordered_map<std::pair<std::string, int>, Variables, PairHash> data;
std::vector<std::string> level_name[N];
std::unordered_map<std::string, std::vector<int>> name_level;

void dedent(int &level) {
    // check whether it's level 0
    if (level == 0) {
        std::cout << "Invalid operation\n";
        return;
    }
    // clearing all variables in this level
    std::pair<std::string, int> curr;
    for (int i = 0; i < level_name[level].size(); i++) {
        curr = std::make_pair(level_name[level][i], level);
        name_level[level_name[level][i]].pop_back();
        if (name_level[level_name[level][i]].size() == 0) {
            name_level.erase(level_name[level][i]);
        }
        data.erase(curr);
    }
    level_name[level].clear();
    level--;
}

bool variableCheck(const std::string &declare_name) {
    if (declare_name.empty()) {
        return 0;
    }
    if (!(declare_name[0] == '_' || 
          (declare_name[0] >= 'a' && declare_name[0] <= 'z') || 
          (declare_name[0] >= 'A' && declare_name[0] <= 'Z'))) {
        return 0;
    }
    for (char c : declare_name) {
        if (!(c == '_' || 
              (c >= 'a' && c <= 'z') || 
              (c >= 'A' && c <= 'Z') || 
              (c >= '0' && c <= '9'))) {
            return 0;
        }
    }
    const std::unordered_set<std::string> keywords = {
        "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", 
        "bitor", "bool", "break", "case", "catch", "char", "char8_t", 
        "char16_t", "char32_t", "class", "compl", "concept", "const", 
        "consteval", "constexpr", "const_cast", "continue", "co_await", 
        "co_return", "co_yield", "decltype", "default", "delete", "do", 
        "double", "dynamic_cast", "else", "enum", "explicit", "export", 
        "extern", "false", "float", "for", "friend", "goto", "if", 
        "inline", "int", "long", "mutable", "namespace", "new", 
        "noexcept", "not", "not_eq", "nullptr", "operator", "or", 
        "or_eq", "private", "protected", "public", "register", 
        "reinterpret_cast", "requires", "return", "short", "signed", 
        "sizeof", "static", "static_assert", "static_cast", "struct", 
        "switch", "template", "this", "thread_local", "throw", "true", 
        "try", "typedef", "typeid", "typename", "union", "unsigned", 
        "using", "virtual", "void", "volatile", "wchar_t", "while", 
        "xor", "xor_eq"
    };
    if (keywords.find(declare_name) != keywords.end()) {
        return 0;
    }
    if (declare_name.length() >= 2) {
        if (declare_name[0] == '_' && declare_name[1] == '_') {
            return 0;
        }
        if (declare_name[0] == '_' && std::isupper(declare_name[1])) {
            return 0;
        }
    }
    return 1;
}

bool inputAndTypeCheck(bool std_type, std::string input, int &input_num) {
    // std::cerr << input << std::endl;
    if (!std_type) {
        int sum = 0;
        bool sgn = 1;
        for (int i = 0; i < input.length(); i++) {
            if (i == 0 && input[i] == '-') sgn = 0;
            else if (input[i] < '0' || input[i] > '9') {
                std::cout << "Invalid operation\n";
                return 0;
            }
            else sum = sum * 10 + static_cast<int>(input[i] - '0');
        }
        if (sgn) {
            input_num = sum;
        }
        else {
            input_num = -sum;
        }
        return 1;
    }
    else {
        // std::cerr << input[0] << " " << input[input.length() - 1]  << std::endl;
        if(input[0] != '"' || input[input.length() - 1] != '"') {
            std::cout << "Invalid operation\n";
            return 0;
        }
        return 1;
    }
}

bool findVariable(std::pair<std::string, int> &tmp, const std::string var_name) {
    if (name_level.find(var_name) != name_level.end()) {
        tmp = make_pair(var_name, name_level[var_name].back());
        return 1;
    }
    std::cout << "Invalid operation\n";
    return 0;
}

void declare(const int &level) {
    std::string declare_type, declare_name, declare_string;
    int declare_int;
    std::cin >> declare_type >> declare_name;
    getline(std::cin, declare_string);
    declare_string.erase(0, 1);
    std::pair<std::string, int> curr_key;
    curr_key = std::make_pair(declare_name, level);
    // std::cerr << curr_key.first << curr_key.second << std::endl;
    if (!variableCheck(declare_name)) { // check the error of invalid variable name
        std::cout << "Invalid operation\n";
        return;
    }
    if (data.find(curr_key) != data.end()) { // check the error of same name
        std::cout << "Invalid operation\n";
        return;
    }
    Variables curr_var;
    curr_var.type = declare_type;
    if (declare_type == "int") {
        if (!inputAndTypeCheck(0, declare_string, declare_int)) {
            return;
        }
        curr_var.num = declare_int;
        level_name[level].push_back(declare_name);
        name_level[declare_name].push_back(level);
    }
    else {
        if (!inputAndTypeCheck(1, declare_string, declare_int)) {
            return;
        }
        curr_var.s = declare_string.substr(1, declare_string.length() - 2);
        level_name[level].push_back(declare_name);
        name_level[declare_name].push_back(level);
    }
    data[curr_key] = curr_var;
}

void add(const int &level) {
    std::string variable_add[4];
    std::pair<std::string, int> p[4];
    int variable_add_level[4];
    for (int i = 1; i <= 3; i++) std::cin >> variable_add[i];
    // find the level of variables
    // error of no existing variable
    std::pair<std::string, int> tmp;
    for (int i = 1; i <= 3; i++) {
        if (!findVariable(tmp, variable_add[i])) { // error of no existing variable
            return;
        }
        p[i] = tmp;
    }
    // error of different types
    for (int i = 1; i < 3; i++) {
        if (data[p[i]].type != data[p[i + 1]].type) {
            std::cout << "Invalid operation\n";
            return;
        }
    }
    // caution: different level can be added together
    if (data[p[1]].type == "int") {
        data[p[1]].num = data[p[2]].num + data[p[3]].num;
    }
    else {
        data[p[1]].s = data[p[2]].s + data[p[3]].s;
    }
}

void selfAdd(const int &level) {
    std::string selfAdd_name, selfAdd_s;
    int selfAdd_num;
    std::cin >> selfAdd_name;
    getline(std::cin, selfAdd_s);
    selfAdd_s.erase(0, 1);
    // error of no existing variable
    std::pair<std::string, int> tmp;
    if (!findVariable(tmp, selfAdd_name)) {
        return;
    }
    // error of different types
    if (data[tmp].type == "int") {
        if (!inputAndTypeCheck(0, selfAdd_s, selfAdd_num)) {
            return;
        }
        data[tmp].num += selfAdd_num;
    }
    else {
        if (!inputAndTypeCheck(1, selfAdd_s, selfAdd_num)) {
            return;
        }
        data[tmp].s += selfAdd_s.substr(1, selfAdd_s.length() - 2);
    }
}

void print(const int &level) {
    std::string print_name;
    std::cin >> print_name;
    // error of no existing variable
    std::pair<std::string, int> tmp;
    bool flag = 0;
    if (!findVariable(tmp, print_name)) { // error of no existing variable
        return;
    }
    if (data[tmp].type == "int") {
        std::cout << print_name << ":" << data[tmp].num << "\n";
    }
    else {
        std::cout << print_name << ":" << data[tmp].s << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, level = 0;
    std::cin >> n;
    std::string oper;
    while(n--) {
        std::cin >> oper;
        if (oper == "Indent") level++;
        if (oper == "Dedent") dedent(level);
        if (oper == "Declare") declare(level);
        if (oper == "Add") add(level);
        if (oper == "SelfAdd") selfAdd(level);
        if (oper == "Print") print(level);
    }
    return 0;
}