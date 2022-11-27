#pragma once 
#include <string>
#include<exception>
#include<cstdlib>
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

#include "Observer.h"

int to_integer(const std::string& arg){
  int temp;
  try{
    temp = std::stoi(arg);
  }
  catch(const std::invalid_argument& inv_er){
    throw std::invalid_argument("Argument is not an integer.");
  }
  return temp;
}

class Data_storage:public Observable{
public:
    void insert(std::list<std::string>& args){
        
        auto arguments = args;  
        auto it = tables.find(arguments.front());
        if(it == tables.end()){
            throw std::logic_error("This table doesn't exist.");
        }
        arguments.pop_front();

        Table& current_table = it->second;
        auto it_second = current_table.find(std::stoi(arguments.front()));
        if(it_second==current_table.end()){
            int temp = std::stoi(arguments.front());
            current_table[temp] = arguments.back();
        }
        else{
            throw std::logic_error("Duplicate key.");
        }
    }

    void truncate(std::list<std::string>& args){
        auto arguments = args;
        auto it =tables.find(arguments.front());
        
        if(it!=tables.end()){
            std::cout<< "Element is finded!\n";
        }
        else{
            std::cout<<"Element isn't finded!\n";
        }

        arguments.pop_front();

        Table& current_table = it->second;
        current_table.clear();
        for(auto gg:A){
            std::cout<<gg.second;
        }

    }

    void intersection(std::list<std::string>& args){
        
        decltype(tables) temp_tables = tables;

        std::unordered_map<const int, int,std::hash<int>>table_counter;

        for(const auto& cur_table : tables){
            for(const auto& cur_key: cur_table.second){
                table_counter[cur_key.first] = table_counter.count(cur_key.first) + 1;
            }
        }
        
        std::vector<std::vector<std::string>> two_2_array;        

        for(const auto& it:table_counter){
            if(it.second==tables.size()){
                std::vector<std::string> temp_vector;
                temp_vector.push_back(std::to_string(it.first));
                for(const auto& cur_table : tables){
                    temp_vector.push_back(cur_table.second.at(it.first));
                }
                two_2_array.push_back(temp_vector);
            }
        }

        for(const auto& arr_2:two_2_array){
            for(const auto& arr:arr_2){
                std::cout<<arr<<", ";
            }
            std::cout<<"\n";
        }
    }

    void symmetric_difference(std::list<std::string>& args){
        
        decltype(tables) temp_tables = tables;

        std::unordered_map<const int, int,std::hash<int>>table_counter;

        for(const auto& cur_table : tables){
            for(const auto& cur_key: cur_table.second){
                table_counter[cur_key.first] = table_counter.count(cur_key.first) + 1;
            }
        }

        std::vector<std::vector<std::string>>two_2_array;

        for(const auto& it:table_counter){
            if(it.second==1){
                std::vector<std::string> temp_vector;
                temp_vector.push_back(std::to_string(it.first));
                for(const auto& cur_table: tables){
                    if(cur_table.second.find(it.first)!=cur_table.second.end()){
                        temp_vector.push_back(cur_table.second.at(it.first));
                    }
                }
                two_2_array.push_back(temp_vector);
            }
        }

        for(const auto& arr_2:two_2_array){
            for(const auto& arr:arr_2){
                std::cout<<arr<<", ";
            }
            std::cout<<"\n";
        }
    }

private:
    using Table = std::unordered_map<const int,std::string,std::hash<int>>;
    Table A;
    Table B;
    std::unordered_map<const std::string, Table,std::hash<std::string>> tables = {{"A",A},{"B",B}};
};