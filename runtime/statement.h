#ifndef __PL0_STATEMENT_PARSER__
#define __PL0_STATEMENT_PARSER__

#include <any>
#include <memory>
#include "stream/token_stream.h"
#include "parser/expression.h"
#include "parser/condition_factor.h"
#include "vm/instruction.h"

enum class PLStatementType : unsigned char {
    CONSTDECL,
    VARDECL,
    FUNCDECL,
    TYPEDEF,
    BLOCK,
    IFSTMT,
    WHILESTMT,
    DOWHILESTMT,
    FORSTMT,
    FUNCSTMT,
    ASSIGMENTSTMT,
    EXPR,
    RETSTMT
};


struct PLFunctionContext {
    std::string funcname;
    WORD start_address;
    std::string ret_type;
};

struct PLObjectContext {
    std::string name;
    WORD address;
    bool is_mutable = false;
    size_t ctx_size = 1;
    std::string type;
};

struct PLObjectTable {
    std::vector<PLObjectContext> objects;
    std::shared_ptr<PLObjectTable> father_ptr;
    size_t size() {
        size_t ret = 0;
        for(auto &i : objects) {
            ret += i.ctx_size;
        }
        if(father_ptr != nullptr) {
            ret += father_ptr->size();
        }
        return ret;
    }
    size_t current_domain_size() {
        size_t ret = 0;
        for(auto &i : objects) {
            ret += i.ctx_size;
        }
        return ret;
    }
};

class PLStatementParser {
private:
    std::shared_ptr<TokenStream> stream;
    std::vector<PLFunctionContext> func_table;
    void func_def_handler(std::shared_ptr<std::vector<WORD>> instruction, std::shared_ptr<PLObjectTable> father_objt);
    bool block_handler(std::shared_ptr<std::vector<WORD>> instruction, std::shared_ptr<PLObjectTable> father_objt, std::shared_ptr<std::map<std::string, std::string>> type_aliases);
    bool statement_handler(std::shared_ptr<std::vector<WORD>> instruction, std::shared_ptr<PLObjectTable> obj_tab,  std::shared_ptr<std::map<std::string, std::string>> type_aliases, bool& has_ret);
    void expression_handler(std::shared_ptr<std::vector<WORD>> instruction, std::shared_ptr<PLObjectTable> obj_tab, std::string type);
    size_t condition_handler(std::shared_ptr<std::vector<WORD>> instruction, std::shared_ptr<PLObjectTable> obj_tab);
    void factor_handler(SemanticToken tok, std::shared_ptr<std::vector<WORD>> instruction, std::shared_ptr<PLObjectTable> obj_tab, std::string type);
    void term_handler(SemanticToken tok, std::shared_ptr<std::vector<WORD>> instruction, std::shared_ptr<PLObjectTable> obj_tab, std::string type);
    void subexpression_handler(SemanticToken tok, std::shared_ptr<std::vector<WORD>> instruction, std::shared_ptr<PLObjectTable> obj_tab, std::string type);
    void if_handler(std::shared_ptr<std::vector<WORD>> instruction);
    void for_handler(std::shared_ptr<std::vector<WORD>> instruction);
    void while_handler(std::shared_ptr<std::vector<WORD>> instruction);
    //void expression_handler(std::shared_ptr<std::vector<WORD>> instruction, std::shared_ptr<PLObjectTable> obj_tab, std::string type);

public:
    PLStatementParser(std::shared_ptr<TokenStream> stream);
    void parse(std::shared_ptr<std::vector<WORD>> instruction);
};

#endif