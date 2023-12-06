cmake_minimum_required(VERSION 3.26)
project(OOP_LAB2)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")

add_executable(OOP_LAB2 Test.cpp
        Interpreter.cpp
        Factory.h
        Command.h
        Sum.cpp
        Sub.cpp
        Sub.h
        Mul.cpp
        Mul.h
        Div.cpp
        Div.h
        Mod.cpp
        Mod.h
        Dup.cpp
        Dup.h
        FactoryInitializer.h
        Drop.cpp
        Drop.h
        Dot.cpp
        Dot.h
        swap.cpp
        swap.h
        Rot.cpp
        Rot.h
        Over.cpp
        Over.h
        Emit.cpp
        Emit.h
        Cr.cpp
        Cr.h
        Bigger.cpp
        Bigger.h
        Less.cpp
        Less.h
        Equal.cpp
        Equal.h
        StringOutput.cpp
        If.cpp
        If.h
        Reader.cpp
        Reader.h
        Tokens.cpp
        Tokens.h
        FactoryComplexFuncInitializer.h
        Utility.cpp
        Utility.h
        Loop.cpp
        Loop.h
        StringOutput.h
        Operands.cpp
        Operands.h
        Command.cpp
)

target_link_libraries(OOP_LAB2 gtest gmock)