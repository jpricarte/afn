cmake_minimum_required(VERSION 3.17)
project(automaton)

set(CMAKE_CXX_STANDARD 14)

add_executable(automaton test_file_pt.cpp automaton/Automaton.cpp automaton/Automaton.h automaton/Reader.cpp automaton/Reader.h)