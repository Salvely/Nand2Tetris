//
// Created by legion on 2024/4/19.
//

#ifndef JACK_ANALYZER_SYMBOLTABLE_H
#define JACK_ANALYZER_SYMBOLTABLE_H

#include <string>

using std::string;

class SymbolTable {
private:
    /**
     * 2 hashtable used to store the symbol table
     * one for the class scope, kind: STATIC FIELD
     * one for the subroutine scope, kind: ARG VAR
     */

public:
    /**
     * Creates a new empty symbol table.
     */
    SymbolTable();

    /**
     * Starts a new subroutine scope (i.e., resets the subroutine’s symbol table)
     */
    void start_subroutine();

    /**
     * Defines a new identifier of a given name, type, and kind and assigns it a running index.
     * STATIC and FIELD identifiers have a class scope, while ARG and VAR identifiers have a
     * subroutine scope. Add the new identifier to the symbol table.
     * @param name name of the identifier
     * @param type type of the identifier, such as int/boolean/String
     * @param kind kind of the identifier, such as FIELD/STATIC(class scope) or VAR/ARG(subroutine scope)
     */
    void define(string name, string type, string kind);

    /**
     * Returns the number of variables of the given kind
     * already defined in the current scope.
     * @param kind kind of the identifier, such as FIELD/STATIC(class scope) or VAR/ARG(subroutine scope)
     * @return the number of variables of the given kind
     */
    int var_count(string kind);

    /**
     * Returns the kind of the named identifier in the current scope.
     * If the identifier is unknown in the current scope, returns NONE
     * @param kind kind of the identifier, such as FIELD/STATIC(class scope) or VAR/ARG(subroutine scope)
     * @return the kind of the named identifier in the current scope
     */
    string kind_of(string name);

    /**
     * Returns the type of the named identifier in the current scope.
     * @param name name of the identifier
     * @return the type of the named identifier in the current scope, such as int/String/boolean
     */
    string type_of(string name);

    /**
     * Returns the index assigned to the named identifier.
     * @param name name of the identifier
     * @return the index assigned to the named identifier
     */
    string index_of(string name);
};

#endif //JACK_ANALYZER_SYMBOLTABLE_H
