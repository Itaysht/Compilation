#ifndef HW3_NODE_H
#define HW3_NODE_H
#include "hw3_output.hpp"
#include <iostream>

class Node{
public:
    int line_number;
    string name;
    Types type;
    bool is_id;
    Node(int line_number, string lexema) : line_number(line_number), name(lexema), is_id(false) {}
};

class Num : public Node{
public:
    Num(int line_number, string lexema) : Node(line_number, lexema) {}
};

class TypeNode : public Node{
public:
    TypeNode(int line_number, string lexema) : Node(line_number, lexema) {}
};

class Identifier : public Node{
public:
    Identifier(int line_number, string lexema) : Node(line_number, lexema) {}
};

class OperatorRelop : public Node{
public:
    OperatorRelop(int line_number, string lexema) : Node(line_number, lexema) {}
};
class BoolNode : public Node{
public:
    BoolNode(int line_number, string lexema) : Node(line_number, lexema) {}
};
class StringNode : public Node{
public:
    StringNode(int line_number, string lexema) : Node(line_number, lexema) {}
};

class Table{
    vector<string> m_names;
    vector<Types> m_types;
    vector<int> m_offsets;
    int m_size;
    Table* m_father;
    bool m_is_while;
public:
    Table(Table* father) {
        m_father = father;
        m_names = vector<string>();
        m_types = vector<Types>();
        m_offsets = vector<int>();
        m_size = 0;
        m_is_while = false;
    }
    void addToTable(string name, Types t, int offset) {
        m_names.push_back(name);
        m_types.push_back(t);
        m_offsets.push_back(offset);
        m_size+=1;
    }
    void setIsWhile(bool isit) {m_is_while = isit;}
    bool getIsWhile() {return m_is_while;}
    bool isExistId(string name){
        for (string s : m_names){
            if ((s == name) && (s != "readi") && (s != "printi") && (s != "print")){
                return true;
            }
        }
        return false;
    }
    Types getMeType(string name){
        for (int i = 0; i < m_size; i++){
            if (m_names[i] == name){
                return m_types[i];
            }
        }
        return T_NONE;
    }
    Table* myFather(){
        return m_father;
    }
    void printThisTable(){
        for (int i = 0; i < m_size; i++) {
            output::printID(m_names[i], m_offsets[i], output::bringMeType(m_types[i]));
        }
    }
};
#endif //HW3_NODE_H
