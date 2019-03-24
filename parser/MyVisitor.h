#include "ToySQLBaseVisitor.h"
#include "../src/Query.h"

#include <vector>
#include <typeinfo>

class MyVisitor : public ToySQLBaseVisitor {

    Query q_;

//----------------------START ACTION----------------------//

public:
    antlrcpp::Any visitQuery(ToySQLParser::QueryContext *ctx) override {  
        return visitChildren(ctx);
    }

    antlrcpp::Any visitWhole_query(ToySQLParser::Whole_queryContext *ctx) override {
        return visitChildren(ctx);
    }

    antlrcpp::Any visitBasic_query(ToySQLParser::Basic_queryContext *ctx) override {
        return visitChildren(ctx);
    }

    antlrcpp::Any visitSelparams(ToySQLParser::SelparamsContext *ctx) override {
        std::vector<ToySQLParser::Result_columnContext *> vec_attrs = ctx->result_column();

        if (ctx->ALL() != nullptr) {
            (q_.selattrs).push_back(Column("ALL"));
        } 
        else if (vec_attrs.size() != 0) {
            for (auto& attrname : vec_attrs) {
                auto attr = attrname->ATTRNAME();
                auto alias = attrname->ALIAS();

                if (alias == nullptr) {
                    (q_.selattrs).push_back(Column(attr->getText()));
                }
                else {
                    (q_.attrs_alias)[alias->getText()] = attr->getText();
                    (q_.selattrs).push_back(Column(attr->getText(), alias->getText()));
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
            (q_.useful_tables).insert(tbl->getText());

            if (alias == nullptr) {
                (q_.from).push_back(Table(tbl->getText()));
            } else {
                (q_.tables_alias)[alias->getText()] = table->getText();
                (q_.from).push_back(Table(tbl->getText(), alias->getText()));
            }            
        }

        return visitChildren(ctx);
    }

    antlrcpp::Any visitWhparams(ToySQLParser::WhparamsContext *ctx) override {
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
        (q_.where).push_back(pr);

        return visitChildren(ctx);
    }

    antlrcpp::Any visitRelation(ToySQLParser::RelationContext *ctx) override {
        return visitChildren(ctx);
    }

    antlrcpp::Any visitResult_column(ToySQLParser::Result_columnContext *ctx) override {
        return visitChildren(ctx);
     }

    antlrcpp::Any visitFrom_table(ToySQLParser::From_tableContext *ctx) override {
        return visitChildren(ctx);
    }

//----------------------END ACTION----------------------//

    Query get() { return q_; }

};
