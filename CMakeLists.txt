cmake_minimum_required(VERSION 3.10)

project(PL0)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(PL0 
    pl0.cpp 
    stream/input_stream.cpp 
    stream/token_stream.cpp 
    token/dfa.cpp 
    token/number.cpp 
    token/identifier.cpp 
    token/symbol.cpp 
    token/token.cpp 
    token/keyword.cpp 
    token/charstr.cpp
    parser/term.cpp
    parser/argument.cpp
    parser/expression.cpp
    parser/factor.cpp
    parser/condition.cpp
    parser/condition_term.cpp
    parser/condition_factor.cpp
    runtime/statement.cpp
    vm/instruction.cpp
)

add_executable(PL0VM
    pl0vm.cpp 
    vm/vm.cpp
)