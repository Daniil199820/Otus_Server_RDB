#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <map>
#include <list>
#include <memory>
#include <cstdlib>


enum Type{TYPE_int,TYPE_string};

struct Column{
    Type type;
    std::string name;
};


int to_integer(const std::string& arg){
  int temp;
  try{
    temp = std::stoi(arg);
  }
  catch(const std::invalid_argument& inv_er){
    throw std::logic_error("Argument is not an integer.");
  }
  return temp;
}

class Data_storage{
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

class ICommand {
public:
    virtual void execute(std::list<std::string>& args) = 0;
    virtual ~ICommand() = default;
};

class Command : public ICommand {
public:
    virtual ~Command() = default;
protected:
    Command(Data_storage* d):data_store(d){}
    Data_storage* data_store;
};

class InsertCommand: public Command{
public:
    InsertCommand(Data_storage* d): Command(d){}

    void execute(std::list<std::string>& args) override {
        if(args.size()==3){
            data_store->insert(args);
            std::cout<<"OK.\n";
        }
        else{
            throw std::logic_error("Uncorrect number of arguments(Should be 3)");
        }
    }
};

class TruncateCommand: public Command{
public:
    TruncateCommand(Data_storage* d): Command(d){}

    void execute(std::list<std::string>& args) override{
        if(args.size()==1){
            data_store->truncate(args);
        }
        else{
            std::cout<<"Uncorrect number of arguments(Should be 1)\n";
        }
    }
};

class IntersectionCommand: public Command{
public:
    IntersectionCommand(Data_storage* d): Command(d){}

    void execute(std::list<std::string>& args) override{
        if(args.size()==0){
            data_store->intersection(args);
        }
        else{
            std::cout<<"Uncorrect number of arguments(Should be 0)\n";
        }
    }
};

class SymmetricCommand: public Command{
public:
    SymmetricCommand(Data_storage* d): Command(d){}

    void execute(std::list<std::string>& args) override{
        if(args.size()==0){
            data_store->symmetric_difference(args);
        }
        else{
            std::cout<<"Uncorrect number of arguments(Should be 0)\n";
        }
    }
};



class Request_manager{
public:
    Request_manager(Data_storage* dd):data_(dd){}

    void set_request(const std::string& str_command){
        std::vector<Command*> commands;
        auto list_words =  parce_function(str_command);
        commands.push_back(commands_dict.at(list_words.front()));
        list_words.pop_front();
        for(auto& it:commands){
            it->execute(list_words);
        }  
    }

private:
    
    Data_storage* data_;

    std::unordered_map<const std::string, Command*,std::hash<std::string>> commands_dict = {
        {"INSERT", new InsertCommand(data_)},
        {"TRUNCATE", new TruncateCommand(data_)},
        {"INTERSECTION", new IntersectionCommand(data_)},
        {"SYMMETRIC_DIFFERENCE", new SymmetricCommand(data_)}
    };
    

    std::list<std::string> parce_function(const std::string& str_){
        std::list<std::string> temp_splitted = split(str_,' ');
        
        if(!temp_splitted.empty()){
        }
        
        if( temp_splitted.empty()){
            //throw ("use tabulations for splitting"); 
        }

        return temp_splitted;
    }

    std::list<std::string> split(const std::string &str, char d)
    {
	    std::list<std::string> r;

	    std::string::size_type start = 0;
	    std::string::size_type stop = str.find_first_of(d);
	    while (stop != std::string::npos)
	    {
		    r.push_back(str.substr(start, stop - start));

		    start = stop + 1;
		    stop = str.find_first_of(d, start);
	    }

	    r.push_back(str.substr(start));

	    return r;
    }

};

