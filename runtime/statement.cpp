#include "runtime/statement.h"

PLStatementParser::PLStatementParser(std::shared_ptr<TokenStream> stream) {
    this->stream = stream;
}
void PLStatementParser::func_def_handler(std::shared_ptr<std::vector<WORD>> instruction, std::shared_ptr<PLObjectTable> father_objt) {
    Token current_token = this->stream->get();
    PLFunctionContext ctx;
    if(current_token.type != TokenType::IDENTIFIER){
        throw "Funcdef ERROR";
    }
    this->stream->next();
    auto type_aliases = std::make_shared<std::map<std::string, std::string>>();
    ctx.funcname = std::any_cast<std::string>(current_token.object);
    ctx.start_address = instruction->size();
    if(ctx.funcname == "main") {
        (*instruction)[1] = ctx.start_address ;
    }
    instruction->push_back(prepare_inst(PUSH, REG, EMP));
    instruction->push_back(BP);
    instruction->push_back(prepare_inst(MOV, REG, REG));
    instruction->push_back(SP);
    instruction->push_back(BP);
    bool ret = this->block_handler(instruction, father_objt, type_aliases);
    this->func_table.push_back(ctx);
    instruction->push_back(prepare_inst(MOV, REG, REG));
    instruction->push_back(BP);
    instruction->push_back(SP);
    instruction->push_back(prepare_inst(POP, REG, EMP));
    instruction->push_back(BP);
    instruction->push_back(prepare_inst(RET, EMP, EMP));
}

bool PLStatementParser::block_handler(std::shared_ptr<std::vector<WORD>> instruction, std::shared_ptr<PLObjectTable> father_objt, std::shared_ptr<std::map<std::string, std::string>> type_aliases) {
    Token current_token = this->stream->get();
    auto object_table = std::make_shared<PLObjectTable>();
    object_table->father_ptr = father_objt;
    if(current_token.type != TokenType::KEYWORD && std::any_cast<std::string>(current_token.object) == "begin"){
        throw "BLOCK ERROR";
    }
    bool has_ret = false;
    this->stream->next();
    auto tab = std::make_shared<std::vector<PLObjectContext>>();
    while (this->statement_handler(instruction, object_table, type_aliases, has_ret));
    current_token = this->stream->get();
    if(current_token.type != TokenType::KEYWORD && std::any_cast<std::string>(current_token.object) == "end"){
        throw "BLOCK ERROR";
    }
    this->stream->next();
    return has_ret;
}

bool PLStatementParser::statement_handler(std::shared_ptr<std::vector<WORD>> instruction, std::shared_ptr<PLObjectTable> obj_tab, std::shared_ptr<std::map<std::string, std::string>> type_aliases, bool& has_ret) {
    Token current_token = this->stream->get();
    if(current_token.type == TokenType::KEYWORD) {
        std::string kw = std::any_cast<std::string>(current_token.object);

        if(kw == "var") {
            this->stream->next();
            current_token = this->stream->get();
            if(current_token.type != TokenType::IDENTIFIER){
                throw "DEF ERROR";
            }
            std::string type = std::any_cast<std::string>(current_token.object);
            if(type != "integer" && type != "float") {
                auto it = type_aliases->find(type);
                if (it != type_aliases->end()) {
                    type = it->second;
                }
                else {
                    throw "INVALID TYPE";
                }
            }
            if(type == "integer") {
                PLObjectContext ctx;
                this->stream->next();
                current_token = this->stream->get();
                if(current_token.type != TokenType::IDENTIFIER){
                    throw "BLOCK ERROR";
                }

                bool hit = false;
                for(auto i : obj_tab->objects) {
                    if(i.name == std::any_cast<std::string>(current_token.object)) {
                        ctx = i;
                        hit = true;
                        break;
                    }
                }
            

                if (hit) {
                    throw "VAR AREADY DEFINED";
                }
                
                int init = 0;
                WORD mem_ctx = *reinterpret_cast<int*>(&init);
                instruction->push_back(prepare_inst(PUSH, IMM, EMP));
                instruction->push_back(mem_ctx);
                ctx.name = std::any_cast<std::string>(current_token.object);
                ctx.type = "integer";
                ctx.ctx_size = 1;
                ctx.address = obj_tab->size() + 1;
                ctx.is_mutable = true;
                obj_tab->objects.push_back(ctx);
            } else if(type == "float") {
                PLObjectContext ctx;
                this->stream->next();
                current_token = this->stream->get();
                if(current_token.type != TokenType::IDENTIFIER){
                    throw "BLOCK ERROR";
                }

                bool hit = false;
                for(auto i : obj_tab->objects) {
                    if(i.name == std::any_cast<std::string>(current_token.object)) {
                        ctx = i;
                        hit = true;
                        break;
                    }
                }
            

                if (hit) {
                    throw "VAR AREADY DEFINED";
                }
            

                if (hit) {
                    throw "VAR AREADY DEFINED";
                }

                float init = 0;
                WORD mem_ctx = *reinterpret_cast<float*>(&init);
                instruction->push_back(prepare_inst(PUSH, IMM, EMP));
                instruction->push_back(mem_ctx);
                ctx.name = std::any_cast<std::string>(current_token.object);
                ctx.type = "float";
                ctx.ctx_size = 1;
                ctx.address = obj_tab->size()+1;
                ctx.is_mutable = true;
                obj_tab->objects.push_back(ctx);
            }

            this->stream->next();
            current_token = this->stream->get();
            if(current_token.type != TokenType::SYMBOL || std::any_cast<SymbolType>(current_token.object) != SymbolType::SEMICOLON){
                throw "EXPR ERROR";
            }
            this->stream->next();
            return true;

        } else if (kw == "const") {
            this->stream->next();
            PLObjectContext ctx;
            current_token = this->stream->get();
            if(current_token.type != TokenType::IDENTIFIER){
                throw "DEF ERROR";
            }   
            std::string type = std::any_cast<std::string>(current_token.object);
            if(type == "integer") {
                this->stream->next();
                current_token = this->stream->get();
                if(current_token.type != TokenType::IDENTIFIER){
                    throw "BLOCK ERROR";
                }

                bool hit = false;
                for(auto i : obj_tab->objects) {
                    if(i.name == std::any_cast<std::string>(current_token.object)) {
                        ctx = i;
                        hit = true;
                        break;
                    }
                }
            

                if (hit) {
                    throw "VAR AREADY DEFINED";
                }
            

                if (hit) {
                    throw "AREADY DEFINED";
                }

                int init = 0;
                WORD mem_ctx = *reinterpret_cast<int*>(&init);
                instruction->push_back(prepare_inst(PUSH, IMM, EMP));
                instruction->push_back(mem_ctx);
                ctx.name = std::any_cast<std::string>(current_token.object);
                ctx.type = "integer";
                ctx.ctx_size = 1;
                ctx.address = obj_tab->size() + 1;
                ctx.is_mutable = false;
                obj_tab->objects.push_back(ctx);
            } else if(type == "float") {
                this->stream->next();
                current_token = this->stream->get();
                if(current_token.type != TokenType::IDENTIFIER){
                    throw "STYNAX ERROR";
                }

                bool hit = false;
                for(auto i : obj_tab->objects) {
                    if(i.name == std::any_cast<std::string>(current_token.object)) {
                        ctx = i;
                        hit = true;
                        break;
                    }
                }
            

                if (hit) {
                    throw "VAR AREADY DEFINED";
                }
            

                if (hit) {
                    throw "AREADY DEFINED";
                }

                float init = 0;
                WORD mem_ctx = *reinterpret_cast<float*>(&init);
                instruction->push_back(prepare_inst(PUSH, IMM, EMP));
                instruction->push_back(mem_ctx);
                ctx.name = std::any_cast<std::string>(current_token.object);
                ctx.type = "integer";
                ctx.ctx_size = 1;
                ctx.address = obj_tab->size() + 1;
                ctx.is_mutable = false;
                obj_tab->objects.push_back(ctx);
            } else {
                throw "INVALID TYPE";
            }
            this->stream->next();
            current_token = this->stream->get();
            if(current_token.type != TokenType::SYMBOL || std::any_cast<SymbolType>(current_token.object) != SymbolType::ASSIGN){
                throw "EXPR ERROR";
            }
            this->stream->next();
            this->expression_handler(instruction, obj_tab, ctx.type);
            instruction->push_back(prepare_inst(POP, REG, IMM));
            instruction->push_back(RA);
            instruction->push_back(prepare_inst(MOV, REG, SEG));
            instruction->push_back(RA);
            instruction->push_back(ctx.address);
            current_token = this->stream->get();
            if(current_token.type != TokenType::SYMBOL || std::any_cast<SymbolType>(current_token.object) != SymbolType::SEMICOLON){
                throw "EXPR ERROR";
            }
            this->stream->next();
            return true;
        } else if (kw == "if") {
            this->stream->next();
            size_t if_addr = this->condition_handler(instruction, obj_tab);
            
            auto instruction_block1 = std::make_shared<std::vector<WORD>>();
            current_token = this->stream->get();
            if(current_token.type != TokenType::KEYWORD || std::any_cast<std::string>(current_token.object) != "then"){
                throw "STYNAX ERROR";
            }
            this->stream->next();
            this->block_handler(instruction_block1, obj_tab, type_aliases);
            current_token = this->stream->get();
            if(current_token.type == TokenType::KEYWORD && std::any_cast<std::string>(current_token.object) == "else"){
                this->stream->next();
                auto instruction_block2 = std::make_shared<std::vector<WORD>>();
                this->block_handler(instruction_block2, obj_tab, type_aliases);
                instruction->insert(instruction->end(), instruction_block2->begin(), instruction_block2->end());
                instruction->push_back(prepare_inst(JMP, IMM, EMP));
                size_t else_addr = instruction->size();
                instruction->push_back(0xffffffff);
                (*instruction)[if_addr] = instruction->size();
                instruction->insert(instruction->end(), instruction_block1->begin(), instruction_block1->end());
                (*instruction)[else_addr] = instruction->size();
            } else {
                instruction->push_back(prepare_inst(JMP, IMM, EMP));
                size_t else_addr = instruction->size();
                instruction->push_back(0xffffffff);
                (*instruction)[if_addr] = instruction->size();
                instruction->insert(instruction->end(), instruction_block1->begin(), instruction_block1->end());
                (*instruction)[else_addr] = instruction->size();
            }
            return true;
        } else if (kw == "call") {
            this->stream->next();
            current_token = this->stream->get();
            if(current_token.type != TokenType::IDENTIFIER){
                throw "EXPR ERROR";
            }
            bool hit = false;
            PLFunctionContext ctx;
            auto current = obj_tab;
            while (current != nullptr)
            {
                for(auto i : this->func_table) {
                    if(i.funcname == std::any_cast<std::string>(current_token.object)) {
                        ctx = i;
                        hit = true;
                        break;
                    }
                }

                if(hit) break;
                current = obj_tab->father_ptr;
            }

            if (!hit) {
                throw "FUNCTION NOT DEFINED";
            }

            instruction->push_back(prepare_inst(CALL, IMM, EMP));
            instruction->push_back(ctx.start_address);
            this->stream->next();
            current_token = this->stream->get();
            if(current_token.type != TokenType::SYMBOL && std::any_cast<SymbolType>(current_token.object) == SymbolType::SEMICOLON){
                throw "STYNAX ERROR";
            }
            this->stream->next();
            return true;
        } else if (kw == "end") {
            return false;
        } else if (kw == "typedef") {
            this->stream->next();
            current_token = this->stream->get();
            if(current_token.type != TokenType::IDENTIFIER){
                throw "STYNAX ERROR";
            }
            std::string alias = std::any_cast<std::string>(current_token.object);
            this->stream->next();
            current_token = this->stream->get();
            if(current_token.type != TokenType::IDENTIFIER){
                throw "STYNAX ERROR";
            }
            std::string type = std::any_cast<std::string>(current_token.object);
            if(type != "integer" && type != "float") {
                throw "INVALID TYPE";
            }
            type_aliases->insert(std::make_pair(alias, type));
            this->stream->next();
            current_token = this->stream->get();
            if(current_token.type != TokenType::SYMBOL || std::any_cast<SymbolType>(current_token.object) != SymbolType::SEMICOLON){
                throw "EXPR ERROR";
            }
            this->stream->next();
            return true;
        } else if (kw == "for") {
            this->stream->next();
            bool has_ret = false;
            this->statement_handler(instruction, obj_tab, type_aliases, has_ret);
            WORD cond_addr = instruction->size();
            current_token = this->stream->get();
            if(current_token.type != TokenType::KEYWORD && std::any_cast<std::string>(current_token.object) == "until"){
                throw "STYNAX ERROR";
            }
            this->stream->next();
            size_t branch_addr = this->condition_handler(instruction, obj_tab);
            current_token = this->stream->get();
            if(current_token.type != TokenType::KEYWORD && std::any_cast<std::string>(current_token.object) == "step"){
                throw "STYNAX ERROR";
            }
            this->stream->next();
            auto step_block1 = std::make_shared<std::vector<WORD>>();

            this->statement_handler(step_block1, obj_tab, type_aliases, has_ret);
            current_token = this->stream->get();
            if(current_token.type != TokenType::KEYWORD && std::any_cast<std::string>(current_token.object) == "repeat"){
                throw "STYNAX ERROR";
            }
            this->stream->next();
            this->block_handler(instruction, obj_tab, type_aliases);
            instruction->insert(instruction->end(), step_block1->begin(), step_block1->end());
            instruction->push_back(prepare_inst(JMP, IMM, EMP));
            instruction->push_back(cond_addr);
            (*instruction)[branch_addr] = instruction->size();
            return true;
        } else if (kw == "return") {
            instruction->push_back(prepare_inst(MOV, REG, REG));
            instruction->push_back(BP);
            instruction->push_back(SP);
            instruction->push_back(prepare_inst(POP, REG, EMP));
            instruction->push_back(BP);
            instruction->push_back(prepare_inst(RET, EMP, EMP));
            this->stream->next();
            current_token = this->stream->get();
            if(current_token.type != TokenType::SYMBOL || std::any_cast<SymbolType>(current_token.object) != SymbolType::SEMICOLON){
                throw "EXPR ERROR";
            }
            return true;
        } else if (kw == "while") {
            this->stream->next();
            WORD jmp_addr = instruction->size();
            size_t cond_addr = this->condition_handler(instruction, obj_tab);
            instruction->push_back(prepare_inst(JMP, IMM, EMP));
            size_t out_addr = instruction->size();
            instruction->push_back(0xffffffff);
            auto instruction_block1 = std::make_shared<std::vector<WORD>>();
            current_token = this->stream->get();
            if(current_token.type != TokenType::KEYWORD || std::any_cast<std::string>(current_token.object) != "do"){
                throw "STYNAX ERROR";
            }
            this->stream->next();
            (*instruction)[cond_addr] = instruction->size();
            this->block_handler(instruction_block1, obj_tab, type_aliases);
            instruction->insert(instruction->end(), instruction_block1->begin(), instruction_block1->end());
            instruction->push_back(prepare_inst(JMP, IMM, EMP));
            instruction->push_back(jmp_addr);
            (*instruction)[out_addr] = instruction->size();
            return true;
        } else if (kw == "read") {
            this->stream->next();
            current_token = this->stream->get();
            if(current_token.type != TokenType::SYMBOL && std::any_cast<SymbolType>(current_token.object) == SymbolType::LPAR){
                throw "STYNAX ERROR";
            }

            this->stream->next();
            current_token = this->stream->get();
            if(current_token.type != TokenType::IDENTIFIER){
                throw "STYNAX ERROR";
            }
            bool hit = false;
            PLObjectContext ctx;
            auto current = obj_tab;
            while (current != nullptr)
            {
                for(auto i : current->objects) {
                    if(i.name == std::any_cast<std::string>(current_token.object)) {
                        ctx = i;
                        hit = true;
                        break;
                    }
                }

                if(hit) break;
                current = obj_tab->father_ptr;
            }
            

            if (!hit) {
                throw "VAR NOT DEFINED";
            }

            if (ctx.is_mutable == false) {
                throw "CONST IS NOT MUTABLE";
            }
            if (ctx.type == "integer") {
                instruction->push_back(prepare_inst(READW, SEG, IMM));
                instruction->push_back(ctx.address);
            } else if (ctx.type == "float") {
                instruction->push_back(prepare_inst(READF, SEG, IMM));
                instruction->push_back(ctx.address);
            }

            this->stream->next();
            current_token = this->stream->get();
            if(current_token.type != TokenType::SYMBOL && std::any_cast<SymbolType>(current_token.object) == SymbolType::RPAR){
                throw "STYNAX ERROR";
            }
            this->stream->next();
            current_token = this->stream->get();
            if(current_token.type != TokenType::SYMBOL && std::any_cast<SymbolType>(current_token.object) == SymbolType::SEMICOLON){
                throw "STYNAX ERROR";
            }
            this->stream->next();
            return true;

        } else if (kw == "write") {
            this->stream->next();
            current_token = this->stream->get();
            if(current_token.type != TokenType::SYMBOL && std::any_cast<SymbolType>(current_token.object) == SymbolType::LPAR){
                throw "STYNAX ERROR";
            }
            this->stream->next();
            current_token = this->stream->get();
            if(current_token.type != TokenType::IDENTIFIER){
                throw "STYNAX ERROR";
            }
            bool hit = false;
            PLObjectContext ctx;
            auto current = obj_tab;
            while (current != nullptr)
            {
                for(auto i : current->objects) {
                    if(i.name == std::any_cast<std::string>(current_token.object)) {
                        ctx = i;
                        hit = true;
                        break;
                    }
                }

                if(hit) break;
                current = obj_tab->father_ptr;
            }

            if (!hit) {
                throw "VAR NOT DEFINED";
            }

            if (ctx.type == "integer") {
                instruction->push_back(prepare_inst(WRITEW, SEG, IMM));
                instruction->push_back(ctx.address);
            } else if (ctx.type == "float") {
                instruction->push_back(prepare_inst(WRITEF, SEG, IMM));
                instruction->push_back(ctx.address);
            }

            this->stream->next();
            current_token = this->stream->get();
            if(current_token.type != TokenType::SYMBOL && std::any_cast<SymbolType>(current_token.object) == SymbolType::RPAR){
                throw "STYNAX ERROR";
            }
            this->stream->next();
            current_token = this->stream->get();
            if(current_token.type != TokenType::SYMBOL && std::any_cast<SymbolType>(current_token.object) == SymbolType::SEMICOLON){
                throw "STYNAX ERROR";
            }
            this->stream->next();
            return true;
        } else {
            throw "INVALID KEYWORD";
        }
    } else if (current_token.type == TokenType::IDENTIFIER) {
        bool hit = false;
        PLObjectContext ctx;
        auto current = obj_tab;
        while (current != nullptr)
        {
            for(auto i : current->objects) {
                if(i.name == std::any_cast<std::string>(current_token.object)) {
                    ctx = i;
                    hit = true;
                    break;
                }
            }
            if(hit) break;
            current = obj_tab->father_ptr;
        }
        if (!hit) {
            throw "VAR NOT DEFINED";
        }
        if (ctx.is_mutable == false) {
            throw "CONST IS NOT MUTABLE";
        }

        this->stream->next();
        current_token = this->stream->get();
        this->stream->next();
        if(current_token.type == TokenType::SYMBOL) {
            switch (std::any_cast<SymbolType>(current_token.object))
            {
                case SymbolType::ASSIGN:{
                    this->expression_handler(instruction, obj_tab, ctx.type);
                    instruction->push_back(prepare_inst(POP, REG, IMM));
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(MOV, REG, SEG));
                    instruction->push_back(RA);
                    instruction->push_back(ctx.address);
                    break;
                }

                case SymbolType::MULBY:{
                    this->expression_handler(instruction, obj_tab, ctx.type);
                    if (ctx.type == "integer") {
                        instruction->push_back(prepare_inst(POP, REG, IMM));
                        instruction->push_back(RA);
                        instruction->push_back(prepare_inst(MOV, SEG, REG));
                        instruction->push_back(ctx.address);
                        instruction->push_back(RB);
                        instruction->push_back(prepare_inst(MULW, REG, REG));
                        instruction->push_back(RA);
                        instruction->push_back(RB);
                        instruction->push_back(prepare_inst(MOV, REG, SEG));
                        instruction->push_back(RR);
                        instruction->push_back(ctx.address);
                    } else if (ctx.type == "float") {
                        instruction->push_back(prepare_inst(POP, REG, IMM));
                        instruction->push_back(FA);
                        instruction->push_back(prepare_inst(MOV, SEG, REG));
                        instruction->push_back(ctx.address);
                        instruction->push_back(FB);
                        instruction->push_back(prepare_inst(MULF, REG, REG));
                        instruction->push_back(FA);
                        instruction->push_back(FB);
                        instruction->push_back(prepare_inst(MOV, REG, SEG));
                        instruction->push_back(FR);
                        instruction->push_back(ctx.address);
                    }

                    break;
                }

                case SymbolType::ADDBY:{
                    this->expression_handler(instruction, obj_tab, ctx.type);
                    if (ctx.type == "integer") {
                        instruction->push_back(prepare_inst(POP, REG, IMM));
                        instruction->push_back(RA);
                        instruction->push_back(prepare_inst(MOV, SEG, REG));
                        instruction->push_back(ctx.address);
                        instruction->push_back(RB);
                        instruction->push_back(prepare_inst(ADDW, REG, REG));
                        instruction->push_back(RB);
                        instruction->push_back(RA);
                        instruction->push_back(prepare_inst(MOV, REG, SEG));
                        instruction->push_back(RR);
                        instruction->push_back(ctx.address);
                    } else if (ctx.type == "float") {
                        instruction->push_back(prepare_inst(POP, REG, IMM));
                        instruction->push_back(FA);
                        instruction->push_back(prepare_inst(MOV, SEG, REG));
                        instruction->push_back(ctx.address);
                        instruction->push_back(FB);
                        instruction->push_back(prepare_inst(ADDF, REG, REG));
                        instruction->push_back(FB);
                        instruction->push_back(FA);
                        instruction->push_back(prepare_inst(MOV, REG, SEG));
                        instruction->push_back(FR);
                        instruction->push_back(ctx.address);
                    }
                    break;
                }

                case SymbolType::SUBBY:{
                    this->expression_handler(instruction, obj_tab, ctx.type);
                    if (ctx.type == "integer") {
                        instruction->push_back(prepare_inst(POP, REG, IMM));
                        instruction->push_back(RA);
                        instruction->push_back(prepare_inst(MOV, SEG, REG));
                        instruction->push_back(ctx.address);
                        instruction->push_back(RB);
                        instruction->push_back(prepare_inst(SUBW, REG, REG));
                        instruction->push_back(RB);
                        instruction->push_back(RA);
                        instruction->push_back(prepare_inst(MOV, REG, SEG));
                        instruction->push_back(RR);
                        instruction->push_back(ctx.address);
                    } else if (ctx.type == "float") {
                        instruction->push_back(prepare_inst(POP, REG, IMM));
                        instruction->push_back(FA);
                        instruction->push_back(prepare_inst(MOV, SEG, REG));
                        instruction->push_back(ctx.address);
                        instruction->push_back(FB);
                        instruction->push_back(prepare_inst(SUBF, REG, REG));
                        instruction->push_back(FB);
                        instruction->push_back(FA);
                        instruction->push_back(prepare_inst(MOV, REG, SEG));
                        instruction->push_back(FR);
                        instruction->push_back(ctx.address);
                    }
                    break;
                }

                case SymbolType::DIVBY:{
                    this->expression_handler(instruction, obj_tab, ctx.type);
                    if (ctx.type == "integer") {
                        instruction->push_back(prepare_inst(POP, REG, IMM));
                        instruction->push_back(RA);
                        instruction->push_back(prepare_inst(MOV, SEG, REG));
                        instruction->push_back(ctx.address);
                        instruction->push_back(RB);
                        instruction->push_back(prepare_inst(DIVW, REG, REG));
                        instruction->push_back(RB);
                        instruction->push_back(RA);
                        instruction->push_back(prepare_inst(MOV, REG, SEG));
                        instruction->push_back(RR);
                        instruction->push_back(ctx.address);
                    } else if (ctx.type == "float") {
                        instruction->push_back(prepare_inst(POP, REG, IMM));
                        instruction->push_back(FA);
                        instruction->push_back(prepare_inst(MOV, SEG, REG));
                        instruction->push_back(ctx.address);
                        instruction->push_back(FB);
                        instruction->push_back(prepare_inst(DIVF, REG, REG));
                        instruction->push_back(FB);
                        instruction->push_back(FA);
                        instruction->push_back(prepare_inst(MOV, REG, SEG));
                        instruction->push_back(FR);
                        instruction->push_back(ctx.address);
                    }
                    break;
                }

                default:
                    throw "INVALID OPERATION";
            }

            current_token = this->stream->get();
            if(current_token.type != TokenType::SYMBOL || std::any_cast<SymbolType>(current_token.object) != SymbolType::SEMICOLON){
                throw "EXPR ERROR";
            }
            this->stream->next();
            return true;
        } else {
            throw "EXPECTED ASSIGMENT OR SELF OPERATION HERE";
        }
    } else {
        return false;
    }
}

void PLStatementParser::parse(std::shared_ptr<std::vector<WORD>> instruction) {
    
    instruction->push_back(prepare_inst(CALL, IMM, EMP));
    instruction->push_back(0xffffffff);
    instruction->push_back(prepare_inst(HALT, EMP, EMP));
    auto object_table = nullptr;
    Token current_token = this->stream->get();
    while (current_token.type != TokenType::EOT)
    {
        if(current_token.type == TokenType::KEYWORD && std::any_cast<std::string>(current_token.object) == "procedure") {
            this->stream->next();
            this->func_def_handler(instruction, object_table);
        }
        else {
            SymbolType a = std::any_cast<SymbolType>(current_token.object);
            throw "Invalid Action";
        }
        current_token = this->stream->get();
    }
}

void PLStatementParser::expression_handler(std::shared_ptr<std::vector<WORD>> instruction, std::shared_ptr<PLObjectTable> obj_tab, std::string type) {
    PLExpressionParser expr_parser(this->stream);
    SemanticToken expr = expr_parser.parse();
    if(expr.type != SemanticTokenType::EXPRESSION) {
        throw "REQUIRE EXPRESSION HERE";
    }

    std::vector<SemanticToken> suffix = std::any_cast<std::vector<SemanticToken>>(expr.object);
    if(suffix.size() == 0) {
        throw "REQUIRE EXPRESSION HERE";
    }

    if(type == "integer") {
        for(auto &i : suffix) {
            switch (i.type) {
                case SemanticTokenType::ADD:
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(RB);
                    instruction->push_back(prepare_inst(ADDW, REG, REG));
                    instruction->push_back(RA);
                    instruction->push_back(RB);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(RR);
                    break;

                case SemanticTokenType::SUB:
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(RB);
                    instruction->push_back(prepare_inst(SUBW, REG, REG));
                    instruction->push_back(RA);
                    instruction->push_back(RB);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(RR);
                    break;
                case SemanticTokenType::TERM:
                    this->term_handler(i, instruction, obj_tab, type);
                default:
                    break;
            }
    }
    } else if (type == "float") {
        for(auto &i : suffix) {
            switch (i.type) {
                case SemanticTokenType::ADD:
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(FB);
                    instruction->push_back(prepare_inst(ADDF, REG, REG));
                    instruction->push_back(FA);
                    instruction->push_back(FB);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(FR);
                    break;

                case SemanticTokenType::SUB:
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(FB);
                    instruction->push_back(prepare_inst(SUBF, REG, REG));
                    instruction->push_back(FA);
                    instruction->push_back(FB);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(FR);
                    break;
                case SemanticTokenType::TERM:
                    this->term_handler(i, instruction, obj_tab, type);
                default:
                    break;
            }
        }
    } else {
        throw "INVALID TYPE";
    }
}

void PLStatementParser::subexpression_handler(SemanticToken tok, std::shared_ptr<std::vector<WORD>> instruction, std::shared_ptr<PLObjectTable> obj_tab, std::string type) {
    if(tok.type != SemanticTokenType::EXPRESSION) {
        throw "REQUIRE EXPRESSION HERE";
    }

    std::vector<SemanticToken> suffix = std::any_cast<std::vector<SemanticToken>>(tok.object);
    if(suffix.size() == 0) {
        throw "REQUIRE EXPRESSION HERE";
    }

    if(type == "integer") {
        for(auto &i : suffix) {
            switch (i.type) {
                case SemanticTokenType::ADD:
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(RB);
                    instruction->push_back(prepare_inst(ADDW, REG, REG));
                    instruction->push_back(RA);
                    instruction->push_back(RB);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(RR);
                    break;

                case SemanticTokenType::SUB:
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(RB);
                    instruction->push_back(prepare_inst(SUBW, REG, REG));
                    instruction->push_back(RA);
                    instruction->push_back(RB);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(RR);
                    break;
                case SemanticTokenType::TERM:
                    this->term_handler(i, instruction, obj_tab, type);
                default:
                    break;
            }
    }
    } else if (type == "float") {
        for(auto &i : suffix) {
            switch (i.type) {
                case SemanticTokenType::ADD:
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(FB);
                    instruction->push_back(prepare_inst(ADDF, REG, REG));
                    instruction->push_back(FA);
                    instruction->push_back(FB);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(FR);
                    break;

                case SemanticTokenType::SUB:
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(FB);
                    instruction->push_back(prepare_inst(SUBF, REG, REG));
                    instruction->push_back(FA);
                    instruction->push_back(FB);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(FR);
                    break;
                case SemanticTokenType::TERM:
                    this->term_handler(i, instruction, obj_tab, type);
                default:
                    break;
            }
        }
    } else {
        throw "INVALID TYPE";
    }
}

void PLStatementParser::term_handler(SemanticToken tok, std::shared_ptr<std::vector<WORD>> instruction, std::shared_ptr<PLObjectTable> obj_tab, std::string type) {
    if(tok.type != SemanticTokenType::TERM) {
        throw "REQUIRE TERM HERE";
    }

    std::vector<SemanticToken> suffix = std::any_cast<std::vector<SemanticToken>>(tok.object);
    if(suffix.size() == 0) {
        throw "REQUIRE FACTOR HERE";
    }

    if(type == "integer") {
        for(auto &i : suffix) {
            switch (i.type) {
                case SemanticTokenType::MUL:
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(RB);
                    instruction->push_back(prepare_inst(MULW, REG, REG));
                    instruction->push_back(RA);
                    instruction->push_back(RB);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(RR);
                    break;

                case SemanticTokenType::DIV:
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(RB);
                    instruction->push_back(prepare_inst(DIVW, REG, REG));
                    instruction->push_back(RA);
                    instruction->push_back(RB);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(RR);
                    break;
                case SemanticTokenType::FACTOR:
                    this->factor_handler(i, instruction, obj_tab, type);
                default:
                    break;
            }
        }
    } else if (type == "float") {
        for(auto &i : suffix) {
            switch (i.type) {
                case SemanticTokenType::MUL:
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(FB);
                    instruction->push_back(prepare_inst(MULF, REG, REG));
                    instruction->push_back(FA);
                    instruction->push_back(FB);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(FR);
                    break;

                case SemanticTokenType::SUB:
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(POP, REG, EMP));
                    instruction->push_back(FB);
                    instruction->push_back(prepare_inst(DIVF, REG, REG));
                    instruction->push_back(FA);
                    instruction->push_back(FB);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(FR);
                    break;
                case SemanticTokenType::FACTOR:
                    this->factor_handler(i, instruction, obj_tab, type);
                default:
                    break;
            }
        }
    } else {
        throw "INVALID TYPE";
    }
}

void PLStatementParser::factor_handler(SemanticToken tok, std::shared_ptr<std::vector<WORD>> instruction, std::shared_ptr<PLObjectTable> obj_tab, std::string type) {
    if(tok.type != SemanticTokenType::FACTOR) {
        throw "REQUIRE FACTOR HERE";
    }

    SemanticToken factor = std::any_cast<SemanticToken>(tok.object);

    if(type == "integer") {
        switch (factor.type)
        {
            case SemanticTokenType::IMMEDIATE_INTEGER: {
                int val = std::any_cast<int>(factor.object);
                WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                instruction->push_back(prepare_inst(PUSH, IMM, EMP));
                instruction->push_back(mem_ctx);
                break;
            }

            case SemanticTokenType::IMMEDIATE_FLOAT: {
                float valf = std::any_cast<float>(factor.object);
                int val = static_cast<int>(std::floor(valf));
                WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                instruction->push_back(prepare_inst(PUSH, IMM, EMP));
                instruction->push_back(mem_ctx);
                break;
            }
            case SemanticTokenType::IDENTIFIER: {
                std::string id = std::any_cast<std::string>(factor.object);
                bool hit = false;
                PLObjectContext ctx;
                auto current = obj_tab;
                while (current != nullptr)
                {
                    for(auto i : current->objects) {
                        if(i.name == id) {
                            ctx = i;
                            hit = true;
                            break;
                        }
                    }

                    if(hit) break;
                    current = obj_tab->father_ptr;
                }
                if (!hit) {
                    throw "VAR NOT DEFINED";
                }
                instruction->push_back(prepare_inst(MOV, SEG, REG));
                instruction->push_back(ctx.address);
                if(ctx.type == "float") {
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(CVTW, SEG, EMP));
                } else {
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(RA);
                }
                break;
            }
            case SemanticTokenType::NEG: {
                int val = -1;
                WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                this->subexpression_handler(factor, instruction, obj_tab, type);
                instruction->push_back(prepare_inst(POP, REG, EMP));
                instruction->push_back(RA);
                instruction->push_back(prepare_inst(MULW, IMM, REG));
                instruction->push_back(mem_ctx);
                instruction->push_back(RB);
                instruction->push_back(prepare_inst(PUSH, REG, EMP));
                instruction->push_back(RR);
                break;
            }
            case SemanticTokenType::INCBEFORE: {
                SemanticToken id_tok = std::any_cast<SemanticToken>(factor.object);
                std::string id = std::any_cast<std::string>(id_tok.object);
                bool hit = false;
                PLObjectContext ctx;
                auto current = obj_tab;
                while (current != nullptr)
                {
                    for(auto i : current->objects) {
                        if(i.name == std::any_cast<std::string>(id)) {
                            ctx = i;
                            hit = true;
                            break;
                        }
                    }
                    if(hit) break;
                    current = obj_tab->father_ptr;
                }
                if (!hit) {
                    throw "VAR NOT DEFINED";
                }
                if (ctx.is_mutable == false) {
                    throw "CONST IS NOT MUTABLE";
                }
                
                if (ctx.type == "integer") {
                    int val = 1;
                    WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                    instruction->push_back(prepare_inst(MOV, SEG, REG));
                    instruction->push_back(ctx.address);
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(ADDW, REG, IMM));
                    instruction->push_back(RA);
                    instruction->push_back(mem_ctx);
                    instruction->push_back(prepare_inst(MOV, REG, SEG));
                    instruction->push_back(RR);
                    instruction->push_back(ctx.address);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(RR);
                } else if (ctx.type == "float") {
                    float val = 1;
                    WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                    instruction->push_back(prepare_inst(MOV, SEG, REG));
                    instruction->push_back(ctx.address);
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(ADDF, REG, IMM));
                    instruction->push_back(FA);
                    instruction->push_back(mem_ctx);
                    instruction->push_back(prepare_inst(MOV, REG, SEG));
                    instruction->push_back(FR);
                    instruction->push_back(ctx.address);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(FR);
                    instruction->push_back(prepare_inst(CVTW, SEG, EMP));
                }
                break;
            }
            case SemanticTokenType::INCAFTER: {
                SemanticToken id_tok = std::any_cast<SemanticToken>(factor.object);
                std::string id = std::any_cast<std::string>(id_tok.object);
                bool hit = false;
                PLObjectContext ctx;
                auto current = obj_tab;
                while (current != nullptr)
                {
                    for(auto i : current->objects) {
                        if(i.name == std::any_cast<std::string>(id)) {
                            ctx = i;
                            hit = true;
                            break;
                        }
                    }
                    if(hit) break;
                    current = obj_tab->father_ptr;
                }
                if (!hit) {
                    throw "VAR NOT DEFINED";
                }
                if (ctx.is_mutable == false) {
                    throw "CONST IS NOT MUTABLE";
                }
                
                if (ctx.type == "integer") {
                    int val = 1;
                    WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                    instruction->push_back(prepare_inst(MOV, SEG, REG));
                    instruction->push_back(ctx.address);
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(ADDW, REG, IMM));
                    instruction->push_back(RA);
                    instruction->push_back(mem_ctx);
                    instruction->push_back(prepare_inst(MOV, REG, SEG));
                    instruction->push_back(RR);
                    instruction->push_back(ctx.address);
                } else if (ctx.type == "float") {
                    float val = 1;
                    WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                    instruction->push_back(prepare_inst(MOV, SEG, REG));
                    instruction->push_back(ctx.address);
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(CVTW, SEG, EMP));
                    instruction->push_back(prepare_inst(ADDF, REG, IMM));
                    instruction->push_back(FA);
                    instruction->push_back(mem_ctx);
                    instruction->push_back(prepare_inst(MOV, REG, SEG));
                    instruction->push_back(FR);
                    instruction->push_back(ctx.address);
                }
                break;
            }
            case SemanticTokenType::DECAFTER: {
                SemanticToken id_tok = std::any_cast<SemanticToken>(factor.object);
                std::string id = std::any_cast<std::string>(id_tok.object);
                bool hit = false;
                PLObjectContext ctx;
                auto current = obj_tab;
                while (current != nullptr)
                {
                    for(auto i : current->objects) {
                        if(i.name == std::any_cast<std::string>(id)) {
                            ctx = i;
                            hit = true;
                            break;
                        }
                    }
                    if(hit) break;
                    current = obj_tab->father_ptr;
                }
                if (!hit) {
                    throw "VAR NOT DEFINED";
                }
                if (ctx.is_mutable == false) {
                    throw "CONST IS NOT MUTABLE";
                }
                
                if (ctx.type == "integer") {
                    int val = -1;
                    WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                    instruction->push_back(prepare_inst(MOV, SEG, REG));
                    instruction->push_back(ctx.address);
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(ADDW, REG, IMM));
                    instruction->push_back(RA);
                    instruction->push_back(mem_ctx);
                    instruction->push_back(prepare_inst(MOV, REG, SEG));
                    instruction->push_back(RR);
                    instruction->push_back(ctx.address);
                } else if (ctx.type == "float") {
                    float val = -1;
                    WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                    instruction->push_back(prepare_inst(MOV, SEG, REG));
                    instruction->push_back(ctx.address);
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(CVTW, SEG, EMP));
                    instruction->push_back(prepare_inst(ADDF, REG, IMM));
                    instruction->push_back(FA);
                    instruction->push_back(mem_ctx);
                    instruction->push_back(prepare_inst(MOV, REG, SEG));
                    instruction->push_back(FR);
                    instruction->push_back(ctx.address);
                }
                break;
            }
            case SemanticTokenType::DECBEFORE: {
                SemanticToken id_tok = std::any_cast<SemanticToken>(factor.object);
                std::string id = std::any_cast<std::string>(id_tok.object);
                bool hit = false;
                PLObjectContext ctx;
                auto current = obj_tab;
                while (current != nullptr)
                {
                    for(auto i : current->objects) {
                        if(i.name == std::any_cast<std::string>(id)) {
                            ctx = i;
                            hit = true;
                            break;
                        }
                    }
                    if(hit) break;
                    current = obj_tab->father_ptr;
                }
                if (!hit) {
                    throw "VAR NOT DEFINED";
                }
                if (ctx.is_mutable == false) {
                    throw "CONST IS NOT MUTABLE";
                }
                
                if (ctx.type == "integer") {
                    int val = -1;
                    WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                    instruction->push_back(prepare_inst(MOV, SEG, REG));
                    instruction->push_back(ctx.address);
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(ADDW, REG, IMM));
                    instruction->push_back(RA);
                    instruction->push_back(mem_ctx);
                    instruction->push_back(prepare_inst(MOV, REG, SEG));
                    instruction->push_back(RR);
                    instruction->push_back(ctx.address);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(RR);
                } else if (ctx.type == "float") {
                    float val = -1;
                    WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                    instruction->push_back(prepare_inst(MOV, SEG, REG));
                    instruction->push_back(ctx.address);
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(ADDF, REG, IMM));
                    instruction->push_back(FA);
                    instruction->push_back(mem_ctx);
                    instruction->push_back(prepare_inst(MOV, REG, SEG));
                    instruction->push_back(FR);
                    instruction->push_back(ctx.address);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(FR);
                    instruction->push_back(prepare_inst(CVTW, SEG, EMP));
                }
                break;
            }
            default:
                throw "INVALID TOKEN";
        }
    } else if( type == "float") {
        switch (factor.type)
        {
            case SemanticTokenType::IMMEDIATE_FLOAT: {
                float val = std::any_cast<float>(factor.object);
                WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                instruction->push_back(prepare_inst(PUSH, IMM, EMP));
                instruction->push_back(mem_ctx);
                break;
            }

            case SemanticTokenType::IMMEDIATE_INTEGER: {
                int valf = std::any_cast<int>(factor.object);
                float val = static_cast<float>(std::floor(valf));
                WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                instruction->push_back(prepare_inst(PUSH, IMM, EMP));
                instruction->push_back(mem_ctx);
                break;
            }
            case SemanticTokenType::IDENTIFIER: {
                std::string id = std::any_cast<std::string>(factor.object);
                bool hit = false;
                PLObjectContext ctx;
                auto current = obj_tab;
                while (current != nullptr)
                {
                    for(auto i : current->objects) {
                        if(i.name == id) {
                            ctx = i;
                            hit = true;
                            break;
                        }
                    }

                    if(hit) break;
                    current = obj_tab->father_ptr;
                }
                if (!hit) {
                    throw "VAR NOT DEFINED";
                }
                instruction->push_back(prepare_inst(MOV, SEG, REG));
                instruction->push_back(ctx.address);
                if(ctx.type == "integer") {
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(CVTF, SEG, EMP));
                } else {
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(FA);
                }
                break;
            }
            case SemanticTokenType::NEG: {
                float val = -1;
                WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                this->subexpression_handler(factor, instruction, obj_tab, type);
                instruction->push_back(prepare_inst(POP, REG, EMP));
                instruction->push_back(FA);
                instruction->push_back(prepare_inst(MULF, IMM, REG));
                instruction->push_back(mem_ctx);
                instruction->push_back(FB);
                instruction->push_back(prepare_inst(PUSH, REG, EMP));
                instruction->push_back(FR);
                break;
            }
            case SemanticTokenType::EXPRESSION: {
                this->subexpression_handler(factor, instruction, obj_tab, type);
                break;
            }
            case SemanticTokenType::INCBEFORE: {
                SemanticToken id_tok = std::any_cast<SemanticToken>(factor.object);
                std::string id = std::any_cast<std::string>(id_tok.object);
                bool hit = false;
                PLObjectContext ctx;
                auto current = obj_tab;
                while (current != nullptr)
                {
                    for(auto i : current->objects) {
                        if(i.name == std::any_cast<std::string>(id)) {
                            ctx = i;
                            hit = true;
                            break;
                        }
                    }
                    if(hit) break;
                    current = obj_tab->father_ptr;
                }
                if (!hit) {
                    throw "VAR NOT DEFINED";
                }
                if (ctx.is_mutable == false) {
                    throw "CONST IS NOT MUTABLE";
                }
                
                if (ctx.type == "integer") {
                    int val = 1;
                    WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                    instruction->push_back(prepare_inst(MOV, SEG, REG));
                    instruction->push_back(ctx.address);
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(ADDW, REG, IMM));
                    instruction->push_back(RA);
                    instruction->push_back(mem_ctx);
                    instruction->push_back(prepare_inst(MOV, REG, SEG));
                    instruction->push_back(RR);
                    instruction->push_back(ctx.address);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(RR);
                    instruction->push_back(prepare_inst(CVTF, SEG, EMP));

                } else if (ctx.type == "float") {
                    float val = 1;
                    WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                    instruction->push_back(prepare_inst(MOV, SEG, REG));
                    instruction->push_back(ctx.address);
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(ADDF, REG, IMM));
                    instruction->push_back(FA);
                    instruction->push_back(mem_ctx);
                    instruction->push_back(prepare_inst(MOV, REG, SEG));
                    instruction->push_back(FR);
                    instruction->push_back(ctx.address);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(FR);
                }
                break;
            }
            case SemanticTokenType::INCAFTER: {
                SemanticToken id_tok = std::any_cast<SemanticToken>(factor.object);
                std::string id = std::any_cast<std::string>(id_tok.object);
                bool hit = false;
                PLObjectContext ctx;
                auto current = obj_tab;
                while (current != nullptr)
                {
                    for(auto i : current->objects) {
                        if(i.name == std::any_cast<std::string>(id)) {
                            ctx = i;
                            hit = true;
                            break;
                        }
                    }
                    if(hit) break;
                    current = obj_tab->father_ptr;
                }
                if (!hit) {
                    throw "VAR NOT DEFINED";
                }
                if (ctx.is_mutable == false) {
                    throw "CONST IS NOT MUTABLE";
                }
                
                if (ctx.type == "integer") {
                    int val = 1;
                    WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                    instruction->push_back(prepare_inst(MOV, SEG, REG));
                    instruction->push_back(ctx.address);
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(CVTF, SEG, EMP));
                    instruction->push_back(prepare_inst(ADDW, REG, IMM));
                    instruction->push_back(RA);
                    instruction->push_back(mem_ctx);
                    instruction->push_back(prepare_inst(MOV, REG, SEG));
                    instruction->push_back(RR);
                    instruction->push_back(ctx.address);
                } else if (ctx.type == "float") {
                    float val = 1;
                    WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                    instruction->push_back(prepare_inst(MOV, SEG, REG));
                    instruction->push_back(ctx.address);
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(ADDF, REG, IMM));
                    instruction->push_back(FA);
                    instruction->push_back(mem_ctx);
                    instruction->push_back(prepare_inst(MOV, REG, SEG));
                    instruction->push_back(FR);
                    instruction->push_back(ctx.address);
                }
                break;
            }
            case SemanticTokenType::DECAFTER: {
                SemanticToken id_tok = std::any_cast<SemanticToken>(factor.object);
                std::string id = std::any_cast<std::string>(id_tok.object);
                bool hit = false;
                PLObjectContext ctx;
                auto current = obj_tab;
                while (current != nullptr)
                {
                    for(auto i : current->objects) {
                        if(i.name == std::any_cast<std::string>(id)) {
                            ctx = i;
                            hit = true;
                            break;
                        }
                    }
                    if(hit) break;
                    current = obj_tab->father_ptr;
                }
                if (!hit) {
                    throw "VAR NOT DEFINED";
                }
                if (ctx.is_mutable == false) {
                    throw "CONST IS NOT MUTABLE";
                }
                
                if (ctx.type == "integer") {
                    int val = -1;
                    WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                    instruction->push_back(prepare_inst(MOV, SEG, REG));
                    instruction->push_back(ctx.address);
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(CVTF, SEG, EMP));
                    instruction->push_back(prepare_inst(ADDW, REG, IMM));
                    instruction->push_back(RA);
                    instruction->push_back(mem_ctx);
                    instruction->push_back(prepare_inst(MOV, REG, SEG));
                    instruction->push_back(RR);
                    instruction->push_back(ctx.address);
                } else if (ctx.type == "float") {
                    float val = -1;
                    WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                    instruction->push_back(prepare_inst(MOV, SEG, REG));
                    instruction->push_back(ctx.address);
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(ADDF, REG, IMM));
                    instruction->push_back(FA);
                    instruction->push_back(mem_ctx);
                    instruction->push_back(prepare_inst(MOV, REG, SEG));
                    instruction->push_back(FR);
                    instruction->push_back(ctx.address);
                }
                break;
            }
            case SemanticTokenType::DECBEFORE: {
                SemanticToken id_tok = std::any_cast<SemanticToken>(factor.object);
                std::string id = std::any_cast<std::string>(id_tok.object);
                bool hit = false;
                PLObjectContext ctx;
                auto current = obj_tab;
                while (current != nullptr)
                {
                    for(auto i : current->objects) {
                        if(i.name == std::any_cast<std::string>(id)) {
                            ctx = i;
                            hit = true;
                            break;
                        }
                    }
                    if(hit) break;
                    current = obj_tab->father_ptr;
                }
                if (!hit) {
                    throw "VAR NOT DEFINED";
                }
                if (ctx.is_mutable == false) {
                    throw "CONST IS NOT MUTABLE";
                }
                
                if (ctx.type == "integer") {
                    int val = -1;
                    WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                    instruction->push_back(prepare_inst(MOV, SEG, REG));
                    instruction->push_back(ctx.address);
                    instruction->push_back(RA);
                    instruction->push_back(prepare_inst(ADDW, REG, IMM));
                    instruction->push_back(RA);
                    instruction->push_back(mem_ctx);
                    instruction->push_back(prepare_inst(MOV, REG, SEG));
                    instruction->push_back(RR);
                    instruction->push_back(ctx.address);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(RR);
                    instruction->push_back(prepare_inst(CVTF, SEG, EMP));
                } else if (ctx.type == "float") {
                    float val = -1;
                    WORD mem_ctx = *reinterpret_cast<WORD *>(&val);
                    instruction->push_back(prepare_inst(MOV, SEG, REG));
                    instruction->push_back(ctx.address);
                    instruction->push_back(FA);
                    instruction->push_back(prepare_inst(ADDF, REG, IMM));
                    instruction->push_back(FA);
                    instruction->push_back(mem_ctx);
                    instruction->push_back(prepare_inst(MOV, REG, SEG));
                    instruction->push_back(FR);
                    instruction->push_back(ctx.address);
                    instruction->push_back(prepare_inst(PUSH, REG, EMP));
                    instruction->push_back(FR);
                }
                break;
            }
            default:
                throw "INVALID TOKEN";
        }
    } else {
        throw "INVALID TYPE";
    }
}


size_t PLStatementParser::condition_handler(std::shared_ptr<std::vector<WORD>> instruction, std::shared_ptr<PLObjectTable> obj_tab) {
    PLConditionFactorParser condition_parser(this->stream);
    SemanticToken tok = condition_parser.parse();
    if(tok.type != SemanticTokenType::CONDITION_FACTOR) {
        throw "STYNAX ERROR";
    }
    size_t next_addr = 0xffffffff;
    auto cond_expr = std::any_cast<std::vector<SemanticToken>>(tok.object);
    bool quit = false;
    for(auto &i : cond_expr) {
        switch (i.type) {
            case SemanticTokenType::ODD:{
                auto expr = std::any_cast<SemanticToken>(i.object);
                if(expr.type != SemanticTokenType::EXPRESSION) throw "STYNAX ERROR";
                this->subexpression_handler(expr, instruction, obj_tab, "integer");
                instruction->push_back(prepare_inst(POP, REG, EMP));
                instruction->push_back(RA);
                instruction->push_back(prepare_inst(CMPW, REG, EMP));
                instruction->push_back(RA);
                quit = true;
                instruction->push_back(prepare_inst(JODD, IMM, EMP));
                next_addr = instruction->size();
                instruction->push_back(0xffffffff);
                break;
            }
            case SemanticTokenType::GT: {
                instruction->push_back(prepare_inst(POP, REG, EMP));
                instruction->push_back(FB);
                instruction->push_back(prepare_inst(POP, REG, EMP));
                instruction->push_back(FA);
                instruction->push_back(prepare_inst(CMPF, REG, REG));
                instruction->push_back(FA);
                instruction->push_back(FB);
                quit = true;
                instruction->push_back(prepare_inst(JG, IMM, EMP));
                next_addr = instruction->size();
                instruction->push_back(0xffffffff);
                break;
            }
            case SemanticTokenType::LT: {
                instruction->push_back(prepare_inst(POP, REG, EMP));
                instruction->push_back(FB);
                instruction->push_back(prepare_inst(POP, REG, EMP));
                instruction->push_back(FA);
                instruction->push_back(prepare_inst(CMPF, REG, REG));
                instruction->push_back(FA);
                instruction->push_back(FB);
                quit = true;
                instruction->push_back(prepare_inst(JL, IMM, EMP));
                next_addr = instruction->size();
                instruction->push_back(0xffffffff);
                break;
            }
            case SemanticTokenType::GEQ: {
                instruction->push_back(prepare_inst(POP, REG, EMP));
                instruction->push_back(FB);
                instruction->push_back(prepare_inst(POP, REG, EMP));
                instruction->push_back(FA);
                instruction->push_back(prepare_inst(CMPF, REG, REG));
                instruction->push_back(FA);
                instruction->push_back(FB);
                quit = true;
                instruction->push_back(prepare_inst(JEG, IMM, EMP));
                next_addr = instruction->size();
                instruction->push_back(0xffffffff);
                break;
            }
            case SemanticTokenType::LEQ: {
                instruction->push_back(prepare_inst(POP, REG, EMP));
                instruction->push_back(FB);
                instruction->push_back(prepare_inst(POP, REG, EMP));
                instruction->push_back(FA);
                instruction->push_back(prepare_inst(CMPF, REG, REG));
                instruction->push_back(FA);
                instruction->push_back(FB);
                quit = true;
                instruction->push_back(prepare_inst(JEL, IMM, EMP));
                next_addr = instruction->size();
                instruction->push_back(0xffffffff);
                break;
            }
            case SemanticTokenType::EQ: {
                instruction->push_back(prepare_inst(POP, REG, EMP));
                instruction->push_back(FB);
                instruction->push_back(prepare_inst(POP, REG, EMP));
                instruction->push_back(FA);
                instruction->push_back(prepare_inst(CMPF, REG, REG));
                instruction->push_back(FA);
                instruction->push_back(FB);
                quit = true;
                instruction->push_back(prepare_inst(JE, IMM, EMP));
                next_addr = instruction->size();
                instruction->push_back(0xffffffff);
            }
            case SemanticTokenType::NEQ: {
                instruction->push_back(prepare_inst(POP, REG, EMP));
                instruction->push_back(FB);
                instruction->push_back(prepare_inst(POP, REG, EMP));
                instruction->push_back(FA);
                instruction->push_back(prepare_inst(CMPF, REG, REG));
                instruction->push_back(FA);
                instruction->push_back(FB);
                quit = true;
                instruction->push_back(prepare_inst(JNE, IMM, EMP));
                next_addr = instruction->size();
                instruction->push_back(0xffffffff);
                break;
            }
            case SemanticTokenType::EXPRESSION: {
                this->subexpression_handler(i, instruction, obj_tab, "float");
                break;
            }
            default:
                break;
        }

        if(quit) break;
    }
    return next_addr;
}
