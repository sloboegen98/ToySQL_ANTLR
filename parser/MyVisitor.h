#pragma once

#include "ToySQLBaseVisitor.h"
#include "../src/Query.h"

#include <vector>
#include <typeinfo>

class MyVisitor : public ToySQLBaseVisitor {

    Query query;

//----------------------START ACTION----------------------//

public:
    antlrcpp::Any visitSelparams(ToySQLParser::SelparamsContext *ctx) override {
        std::vector<ToySQLParser::Result_columnContext *> vec_attrs = ctx->result_column();

        if (ctx->ALL() != nullptr) {
            (query.selattrs).push_back(Column("ALL"));
        } 
        else if (vec_attrs.size() != 0) {
            for (auto& attrname : vec_attrs) {
                auto attr = attrname->ATTRNAME();
                auto alias = attrname->ALIAS();

                if (alias == nullptr) {
                    (query.selattrs).push_back(Column(attr->getText()));
                }
                else {
                    (query.attrs_alias)[alias->getText()] = attr->getText();
                    (query.selattrs).push_back(Column(attr->getText(), alias->getText()));
                }
            }
        }

        return visitChildren(ctx);
    }

    antlrcpp::Any visitFrparams(ToySQLParser::FrparamsContext *ctx) override {
        std::vector<ToySQLParser::From_tableContext *> vec_tables = ctx->from_table();
        for (auto &table : vec_tables) {
            auto tbl = table->TABLENAME();
            auto alias = table->ALIAS();
            (query.useful_tables).insert(tbl->getText());

            if (alias == nullptr) {
                (query.from).push_back(Table(tbl->getText()));
            } else {
                (query.tables_alias)[alias->getText()] = table->getText();
                (query.from).push_back(Table(tbl->getText(), alias->getText()));
            }            
        }

        return visitChildren(ctx);
    }

    antlrcpp::Any visitWhparam(ToySQLParser::WhparamContext *ctx) override {
        auto left = ctx->whparam_left();
        auto right = ctx->whparam_right();
        char rel = (ctx->relation()->getText())[0];
        std::string lhs, rhs;

        Predicate::LeftType lt;
        Predicate::RightType rt;

        if (left->ATTRNAME() != nullptr) {
            lhs = left->ATTRNAME()->getText();
            lt = Predicate::LeftType::COLUMN;
        } else if (left->ALIAS() != nullptr) {
            lhs = left->ALIAS()->getText();
            lt = Predicate::LeftType::ALIAS;
        }   

        if (right->ATTRNAME() != nullptr) {
            rhs = right->ATTRNAME()->getText();
            rt = Predicate::RightType::COLUMN;
        } else if (right->ALIAS() != nullptr) {
            rhs = right->ALIAS()->getText();
            rt = Predicate::RightType::ALIAS;
        } else if (right->WORD() != nullptr) {
            rhs = right->WORD()->getText();
            rt = Predicate::RightType::WORD;
        }  else if (right->NUMBER() != nullptr) {
            rhs = right->NUMBER()->getText();
            rt = Predicate::RightType::NUMBER;
        }
       
        Predicate pr = Predicate(lhs, rhs, rel, lt, rt);
        (query.where).push_back(pr);

        return visitChildren(ctx);
    }

//----------------------END ACTION----------------------//

    Query get() { return query; }

};
