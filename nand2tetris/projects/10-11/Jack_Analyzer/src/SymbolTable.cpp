//
// Created by legion on 2024/4/19.
//

#include "SymbolTable.h"
#include <iostream>

using std::cerr;
using std::endl;

SymbolTable::SymbolTable() = default;

void SymbolTable::start_subroutine() {
    // clean the old subroutine table
    subroutine_st.clear();
    // add a new std::list reference as the first element of the new subroutine scope symbol table
    list<node_t> new_list;
    subroutine_st.push_front(new_list);
}

void SymbolTable::start_class() {
    // add a new std::list reference as the first element of the new class scope symbol table
    list<node_t> new_list;
    class_st.push_front(new_list);
}

void SymbolTable::define(string name, string type, string kind) {
    list<node_t> first_scope;
    // judge if there's the same kind of node
    if (kind == "arg" || kind == "var") {
        // search the subroutine symbol table with this kind
        first_scope = subroutine_st.front();
    } else if (kind == "static" || kind == "this") {
        // search the class symbol table with this kind
        first_scope = class_st.front();
    } else {
        cerr << "Invalid kind detected: " << kind << endl;
        exit(1);
    }
    // check if kind already exists in the node list(which categorized the nodes according to their kind)
    bool find = false;
    for (node_t &n: first_scope) {
        if (n.kind == kind) {
            find = true;
            int index = (int) n.lst.size();
            same_kind_node_t new_node = {name, type, index};
            n.lst.push_back(new_node);
            break;
        }
    }
    if (!find) {
        // if the kind is not found
        // create a new kind list
        list<same_kind_node_t> new_lst;
        // initialize a new node
        same_kind_node_t new_node = {name, type, 0};
        // add the node to the end of the kind list
        new_lst.push_back(new_node);
        node_t new_kind_list = {kind, new_lst};
        // add the kind list to the end of this scope node list
        first_scope.push_back(new_kind_list);
    }
}

int SymbolTable::var_count(const string &kind) {
    list<node_t> first_scope;
    if (kind == "var" || kind == "arg") {
        first_scope = subroutine_st.front();
    } else if (kind == "this" || kind == "static") {
        first_scope = class_st.front();
    } else {
        cerr << "Invalid kind detected: " << kind << endl;
        exit(1);
    }
    for (node_t &n: first_scope) {
        if (n.kind == kind) {
            return (int) n.lst.size();
        }
    }
    cerr << "Kind not yet existed" << endl;
    return 0;
}

string SymbolTable::kind_of(const string &name) {
    for (list<node_t> &scope: subroutine_st) {
        for (node_t &kind_lst: scope) {
            list<same_kind_node_t> lst = kind_lst.lst;
            for (same_kind_node &n: lst) {
                if (n.name == name) {
                    return kind_lst.kind;
                }
            }
        }
    }
    for (list<node_t> &scope: class_st) {
        for (node_t &kind_lst: scope) {
            list<same_kind_node_t> lst = kind_lst.lst;
            for (same_kind_node &n: lst) {
                if (n.name == name) {
                    return kind_lst.kind;
                }
            }
        }
    }
    cerr << "name doesn't exists" << endl;
    exit(1);
}

string SymbolTable::type_of(const string &name) {
    for (list<node_t> &scope: subroutine_st) {
        for (node_t &kind_lst: scope) {
            list<same_kind_node_t> lst = kind_lst.lst;
            for (same_kind_node &n: lst) {
                if (n.name == name) {
                    return n.type;
                }
            }
        }
    }
    for (list<node_t> &scope: class_st) {
        for (node_t &kind_lst: scope) {
            list<same_kind_node_t> lst = kind_lst.lst;
            for (same_kind_node &n: lst) {
                if (n.name == name) {
                    return n.type;
                }
            }
        }
    }
    cerr << "name doesn't exists" << endl;
    exit(1);
}

int SymbolTable::index_of(const string &name) {
    for (list<node_t> &scope: subroutine_st) {
        for (node_t &kind_lst: scope) {
            list<same_kind_node_t> lst = kind_lst.lst;
            for (same_kind_node &n: lst) {
                if (n.name == name) {
                    return n.index;
                }
            }
        }
    }
    for (list<node_t> &scope: class_st) {
        for (node_t &kind_lst: scope) {
            list<same_kind_node_t> lst = kind_lst.lst;
            for (same_kind_node &n: lst) {
                if (n.name == name) {
                    return n.index;
                }
            }
        }
    }
    cerr << "name doesn't exists" << endl;
    exit(1);
}

void SymbolTable::subroutine_new_scope() {
    // not clearing the subroutine symbol table
    // add a new std::list reference as the first element of the new subroutine scope symbol table
    list<node_t> new_list;
    subroutine_st.push_front(new_list);
}

void SymbolTable::close_current_scope() {
    subroutine_st.pop_front();
}

