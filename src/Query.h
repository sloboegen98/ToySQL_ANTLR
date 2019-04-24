#pragma once 

#include <vector>
#include <unordered_map>
#include <set>
#include <string>
#include <iostream>

struct Predicate {
    std::string left;
    std::string right;
    char rel;

    enum class LeftType { ALIAS, COLUMN };
    enum class RightType { ALIAS, COLUMN, NUMBER, WORD };

    LeftType left_type;
    RightType right_type;

    Predicate(std::string const& l, std::string const& r, char rel,
              LeftType lt, RightType rt) :
        left(l), right(r), rel(rel), left_type(lt), right_type(rt) {}

    friend std::ostream& operator<< (std::ostream& out, const Predicate& pr) {
        out << '\t' << pr.left << ' ' << pr.rel << ' ' << pr.right;
                return out;
    }   
};

struct Column {
    std::string name;
    std::string alias;

    Column(std::string const& name, std::string const& alias = "") : 
        name(name), alias(alias) {}

    friend std::ostream& operator<< (std::ostream& out, Column const& col) {
        out << col.name;
        if (col.alias != "")
            out << " AS: " << col.alias;
        return out;
    }   
};

struct Table {
    std::string name;
    std::string alias;

    Table(std::string const& name, std::string const& alias = "") : 
        name(name), alias(alias) {}

    friend std::ostream& operator<< (std::ostream& out, Table const& tbl) {
        out << tbl.name;
        if (tbl.alias != "")
            out << " AS: " << tbl.alias;
        return out;
    }
};

struct Query {
    std::vector<Column> selattrs;
    std::vector<Table> from;
    std::vector<Predicate> where;

    std::unordered_map<std::string, std::string> attrs_alias;
    std::unordered_map<std::string, std::string> tables_alias;    

    std::set<std::string> useful_tables;

    void print();
    void remove_alias();
    bool check_correct();
    std::string table_from_attr(std::string const &attr);
};