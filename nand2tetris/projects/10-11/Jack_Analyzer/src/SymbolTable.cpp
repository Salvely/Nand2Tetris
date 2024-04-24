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
    subroutine_st.scope_list.clear();
    // add a new std::list reference as the first element of the new subroutine scope symbol table
    scope_table table;
    subroutine_st.scope_list.push_front(table);
}

void SymbolTable::start_class() {
    // add a new std::list reference as the first element of the new class scope symbol table
    scope_table table;
    class_st.scope_list.push_front(table);
}

void SymbolTable::define(string name, string type, string kind) {
    scope_table *first_scope;
    // judge if there's the same kind of node
    if (kind == "argument" || kind == "local") {
        // search the subroutine symbol table with this kind
        first_scope = &subroutine_st.scope_list.front();
    } else if (kind == "static" || kind == "this") {
        // search the class symbol table with this kind
        first_scope = &class_st.scope_list.front();
    } else {
        cerr << "Invalid kind detected: " << kind << endl;
        exit(1);
    }

    for (same_kind_list &l: first_scope->table_kind_list) {
        if (l.kind == kind) {
            same_kind_node n{.name = name, .type = type, .index = (int) l.list.size()};
            l.list.push_back(n);
            return;
        }
    }

    // define a new kind list for the node
    same_kind_node n{.name = name, .type = type, .index = 0};
    same_kind_list l;
    l.kind = kind;
    l.list.push_back(n);
    first_scope->table_kind_list.push_back(l);
}

//bool SymbolTable::find_var(const string &name) {
//    for (scope_table &st: subroutine_st.scope_list) {
//        for (same_kind_list &l: st.table_kind_list) {
//            for (same_kind_node &n: l.list) {
//                if (n.name == name) {
//                    return true;
//                }
//            }
//        }
//    }
//
//    for (scope_table &st: class_st.scope_list) {
//        for (same_kind_list &l: st.table_kind_list) {
//            for (same_kind_node &n: l.list) {
//                if (n.name == name) {
//                    return true;
//                }
//            }
//        }
//    }
//
//    return false;
//}

int SymbolTable::var_count(const string &kind) {
    scope_table first_scope;
    // judge if there's the same kind of node
    if (kind == "argument" || kind == "local") {
        // search the subroutine symbol table with this kind
        first_scope = subroutine_st.scope_list.front();
    } else if (kind == "static" || kind == "this") {
        // search the class symbol table with this kind
        first_scope = class_st.scope_list.front();
    } else {
        cerr << "Invalid kind detected: " << kind << endl;
        exit(1);
    }

    for (same_kind_list &l: first_scope.table_kind_list) {
        if (l.kind == kind) {
            return (int) l.list.size();
        }
    }

    cerr << "Kind not yet existed" << endl;
    return 0;
}

string SymbolTable::kind_of(const string &name) {
    for (scope_table &st: subroutine_st.scope_list) {
        for (same_kind_list &l: st.table_kind_list) {
            for (same_kind_node &n: l.list) {
                if (n.name == name) {
                    return l.kind;
                }
            }
        }
    }

    for (scope_table &st: class_st.scope_list) {
        for (same_kind_list &l: st.table_kind_list) {
            for (same_kind_node &n: l.list) {
                if (n.name == name) {
                    return l.kind;
                }
            }
        }
    }

    cerr << "name doesn't exists" << endl;
    exit(1);
}

string SymbolTable::type_of(const string &name) {
    for (scope_table &st: subroutine_st.scope_list) {
        for (same_kind_list &l: st.table_kind_list) {
            for (same_kind_node &n: l.list) {
                if (n.name == name) {
                    return n.type;
                }
            }
        }
    }

    for (scope_table &st: class_st.scope_list) {
        for (same_kind_list &l: st.table_kind_list) {
            for (same_kind_node &n: l.list) {
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
    for (scope_table &st: subroutine_st.scope_list) {
        for (same_kind_list &l: st.table_kind_list) {
            for (same_kind_node &n: l.list) {
                if (n.name == name) {
                    return n.index;
                }
            }
        }
    }

    for (scope_table &st: class_st.scope_list) {
        for (same_kind_list &l: st.table_kind_list) {
            for (same_kind_node &n: l.list) {
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
    scope_table table;
    subroutine_st.scope_list.push_front(table);
}

void SymbolTable::close_current_scope() {
    subroutine_st.scope_list.pop_front();
}

