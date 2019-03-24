#include "Query.h"

#include <iostream>

void Query::print() {
    std::cout << "ATTRIBUTES:\n";

    for (size_t i = 0; i < selattrs.size(); ++i)
        std::cout << '\t' << selattrs[i] << '\n';
    
    std::cout << "TABLES:\n";

    for (size_t i = 0; i < from.size(); ++i)
        std::cout << '\t' << from[i] << '\n';

    if (where.size() != 0){
        std::cout << "PREDICATE:\n";

        for (size_t i = 0; i < where.size(); ++i)
            std::cout << where[i] << '\n';
    }
}

void Query::remove_alias() {
    for (size_t i = 0; i < where.size(); ++i) {
        Predicate p = where[i];
        auto it_l = attrs_alias.find(p.left);
        
        if (it_l != attrs_alias.end()) {
            where[i].left = it_l->second;
            where[i].left_type = Predicate::LeftType::COLUMN;
        }

        auto it_r = attrs_alias.find(p.right);
        if (it_r != attrs_alias.end()) {
            where[i].right = it_r->second;
            where[i].right_type = Predicate::RightType::COLUMN;
        }
    }
}

// get tablename from attrname
std::string Query::table_from_attr(std::string const &attr) {
    std::string table = "";
    for (auto c : attr) {
        if (c == '.')
            break;
        table += c;
    }

    return table;
}

// check correct table for each attribute and undeclarated alias
bool Query::check_correct() {
    for (auto &attr : selattrs) {
        if (attr.name == "ALL")
            break;
            
        std::string table = table_from_attr(attr.name);
        if (useful_tables.find(table) == useful_tables.end()) {
            std::cout << "Please add table " << table << std::endl;
            return false;
        }
    }

    for (auto &pr : where) {
        if (pr.left_type == Predicate::LeftType::ALIAS) {
            if (attrs_alias.find(pr.left) == attrs_alias.end()) {
                std::cout << "Incorrect alias " << pr.left << std::endl;
                return false; // unnamed alias
            }
        } else if (pr.left_type == Predicate::LeftType::COLUMN) {
            std::string table = table_from_attr(pr.left);
            if (useful_tables.find(table) == useful_tables.end()) {
                std::cout << "Please add table " << table << std::endl;
                return false;
            }
        }

        if (pr.right_type == Predicate::RightType::ALIAS) {
            if (attrs_alias.find(pr.right) == attrs_alias.end()) {
                std::cout << "Incorrect alias " << pr.right << std::endl;
                return false; // unnamed alias
            }
        } else if (pr.right_type == Predicate::RightType::COLUMN) {
            std::string table = table_from_attr(pr.right);
            if (useful_tables.find(table) == useful_tables.end()) {
                std::cout << "Please add table " << table << std::endl;
                return false;
            }
        }
    }

    return true;
}