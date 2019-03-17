#pragma once

#include <vector>
#include <unordered_map>
#include <set>
#include <string>

struct Predicate
{
    std::string left;
    std::string right;
    char rel;

    void print();    
};


struct Query
{
    std::vector <std::string> selattrs;
    std::vector <std::string> from;
    std::vector <Predicate> where;

    std::unordered_map<std::string, std::string> alias_table;

    std::set<std::stirng> useful_tables;

    void print();
};
