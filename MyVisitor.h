#include "ToySQLBaseVisitor.h"
#include "Query.h"


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
        std::vector<antlr4::tree::TerminalNode *> vec_attrs = ctx->ATTRNAME();
        auto all = ctx->ALL();

        if (all != nullptr) {
            (q_.selattrs).push_back("ALL");
        } 
        else if (vec_attrs.size() != 0) {
            for (auto &attr : vec_attrs) {
                (q_.selattrs).push_back(attr->getText());
            }
        } 

        return visitChildren(ctx);
    }

    antlrcpp::Any visitFrparams(ToySQLParser::FrparamsContext *ctx) override {
        std::vector<antlr4::tree::TerminalNode*> vec_tables = ctx->TABLENAME();
        
        for (auto &table : vec_tables) {
            (q_.from).push_back(table->getText());
        }

        return visitChildren(ctx);
    }

    antlrcpp::Any visitWhparams(ToySQLParser::WhparamsContext *ctx) override {
        return visitChildren(ctx);
    }

    antlrcpp::Any visitWhparam(ToySQLParser::WhparamContext *ctx) override {
        auto left = ctx->ATTRNAME(0);
        auto rel = ctx->relation();
        auto right_word = ctx->WORD();   
        auto right_attr = ctx->ATTRNAME(1);
        auto right_num  = ctx->NUMBER();

        Predicate cur_pr;
        cur_pr.left = std::move(left->getText());
        cur_pr.rel  = (rel->getText())[0];

        if (right_word != nullptr) 
            cur_pr.right = std::move(right_word->getText());
        else if (right_num != nullptr)
            cur_pr.right = std::move(right_num->getText());
        else if (right_attr != nullptr)
            cur_pr.right = std::move(right_attr->getText());

        (q_.where).push_back(cur_pr);

        return visitChildren(ctx);
    }

    antlrcpp::Any visitRelation(ToySQLParser::RelationContext *ctx) override {
        return visitChildren(ctx);
    }

//----------------------END ACTION----------------------//

    Query get() { return q_; }

};
