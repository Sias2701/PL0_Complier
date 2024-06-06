#include "vm/vm.h"

int main(int argc, char* argv[]) {
    //input_stream_test();
    //number_test();
    //identifier_test();
    //token_stream_test();
    //expression_test();
    //condition_test();
    //program_test();
    std::string inputfile;
    if(argc == 2) {
        inputfile = argv[1];
    }
    if (!inputfile.empty()) {
        try
        {
            auto vm = VirtualMachine();
            vm.load(inputfile);
            vm.run();
            return 0;
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