#include <iostream>
#include "stream/input_stream.h"
#include "stream/token_stream.h"
#include "token/number.h"
#include "token/identifier.h"
#include "parser/expression.h"
#include "parser/condition.h"
#include "runtime/statement.h"


/* void input_stream_test() {
    InputStream stream("C:/Users/sias/Desktop/PL0/test.txt");
    try
    {
        char c;
        do
        {
            stream.forward();
            c = stream.get();
            
            std::cout << c;
            stream.next();
        }while (c != 0);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void number_test() {
    auto stream = std::make_shared<InputStream>("C:/Users/sias/Desktop/PL0/number.txt");
    Token ret;
    NumberParser parser;
    try
    {
        while (true)
        {
            ret = parser.parse(stream);
            if(ret.type == TokenType::INVALID) {
                stream->next();
                continue;
            } else if (ret.type == TokenType::EOT) {
                std::cout << "EOT" << std::endl;
                break;
            } else {
                PL0Number obj = std::any_cast<PL0Number>(ret.object);
                
                if(std::holds_alternative<int>(obj)) {

                    std::cout << "INT" << " : " << std::get<int>(obj) << std::endl;
                } else if (std::holds_alternative<float>(obj))
                {
                    std::cout << "FLOAT" << " : " << std::get<float>(obj) << std::endl;
                }
                
            }
            
        }
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void identifier_test() {
    auto stream = std::make_shared<InputStream>("C:/Users/sias/Desktop/PL0/identifier.txt");
    Token ret;
    IdentifierParser parser;
    try
    {
        while (true)
        {
            ret = parser.parse(stream);
            if(ret.type == TokenType::INVALID) {
                stream->next();
                continue;
            } else if (ret.type == TokenType::EOT) {
                std::cout << "EOT" << std::endl;
                break;
            } else {
                std::string id = std::any_cast<std::string>(ret.object);
                std::cout << "IDENTIFIER" << " : " << id << std::endl;
            }
            
        }
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void token_stream_test() {
    auto stream = std::make_shared<InputStream>("C:/Users/sias/Desktop/PL0/prog2.pl0");
    Token ret;
    auto token_stream = std::make_shared<TokenStream>(stream);
    try
    {
        while (true)
        {
            ret = token_stream->get();
            std::cout << ret.type << " : ";

            if(ret.type == TokenType::EOT) {
                break;
            }

            PL0Number obj;

            switch (ret.type)
            {
                case TokenType::INVALID:
                    throw "InvalidToken";

                case TokenType::NUMBER:
                    obj = std::any_cast<PL0Number>(ret.object);
                    if(std::holds_alternative<int>(obj)) {     
                        std::cout << std::get<int>(obj) << std::endl;
                    } else if (std::holds_alternative<float>(obj)) {
                        std::cout << std::get<float>(obj) << std::endl;
                    }
                    break;
                case TokenType::SYMBOL:
                    std::cout << std::any_cast<SymbolType>(ret.object) << std::endl;
                    break;
                case TokenType::KEYWORD:
                case TokenType::IDENTIFIER:
                case TokenType::CHAR:
                case TokenType::STRING:
                    std::cout << std::any_cast<std::string>(ret.object) << std::endl;
                    break;
            }
            token_stream->next();
        }
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void expression_test() {
    auto stream = std::make_shared<InputStream>("C:/Users/sias/Desktop/PL0/expression.txt");
    auto token_stream = std::make_shared<TokenStream>(stream);
    PLExpressionParser expr_parser(token_stream);
    SemanticToken ret;
    try
    {
        while (true)
        {
            ret = expr_parser.parse();

            if(ret.type == SemanticTokenType::EOT) {
                break;
            }
            token_stream->next();
        }
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void condition_test() {
    auto stream = std::make_shared<InputStream>("C:/Users/sias/Desktop/PL0/condition.txt");
    auto token_stream = std::make_shared<TokenStream>(stream);
    PLConditionParser cond_parser(token_stream);
    SemanticToken ret;
    try
    {
        while (true)
        {
            ret = cond_parser.parse();

            if(ret.type == SemanticTokenType::EOT) {
                break;
            }
            token_stream->next();
        }
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void program_test() {
    auto stream = std::make_shared<InputStream>("C:/Users/sias/Desktop/PL0/prog2.pl0");
    auto token_stream = std::make_shared<TokenStream>(stream);
    auto stmt = PLStatementParser(token_stream);

    auto code = std::make_shared<std::vector<WORD>>();
    stmt.parse(code);
    std::ofstream outFile("C:/Users/sias/Desktop/PL0/a.out", std::ios::binary);
    size_t vecSize = code->size();
    outFile.write(reinterpret_cast<const char*>(&vecSize), sizeof(vecSize));
    
    outFile.write(reinterpret_cast<const char*>(code->data()), vecSize * sizeof(WORD));
    
    outFile.close();
} */

int main(int argc, char* argv[]) {
    //input_stream_test();
    //number_test();
    //identifier_test();
    //token_stream_test();
    //expression_test();
    //condition_test();
    //program_test();
    std::string outputfile = "a.out";
    std::string inputfile;
    if(argc == 2) {
        inputfile = argv[1];
    } else if (argc == 4) {
        for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-o" && (i + 2) < argc) {
            outputfile = argv[i + 1];
            inputfile = argv[i + 2];
            break;
        }
    }
    }
    if (!outputfile.empty() && !inputfile.empty()) {
        try
        {
            auto stream = std::make_shared<InputStream>(inputfile);
            auto token_stream = std::make_shared<TokenStream>(stream);
            auto stmt = PLStatementParser(token_stream);
            auto code = std::make_shared<std::vector<WORD>>();
            stmt.parse(code);
            std::ofstream outFile(outputfile, std::ios::binary);
            size_t vecSize = code->size();
            outFile.write(reinterpret_cast<const char*>(&vecSize), sizeof(vecSize));

            outFile.write(reinterpret_cast<const char*>(code->data()), vecSize * sizeof(WORD));

            outFile.close();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        catch(const std::string& s) {
            std::cerr << s << '\n';
        }
        
    } else {
        std::cerr << "No -o parameter provided or one of the paths is missing." << std::endl;
    }
}