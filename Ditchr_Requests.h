#pragma once

#include "Ditchr_Data.h"
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

