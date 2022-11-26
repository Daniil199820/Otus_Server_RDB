#include <iostream>
#include <vector>
#include "Ditchr_Clients.h"
#include "Ditchr_Requests.h"
#include <memory>
#include <sstream>
// realize class for data visualizer and send them using observer
int main(){
	Client_require cl;
	try{
		cl.make_request("INSERT A 0 Lean");
		cl.make_request("INSERT A 1 Sweater");
		cl.make_request("INSERT A 2 Frank");
		cl.make_request("INSERT A 3 Violation");
		cl.make_request("INSERT A 4 Quality");
		cl.make_request("INSERT A 5 Presicion");
		cl.make_request("INSERT B 3 Proposal");
		cl.make_request("INSERT B 4 Example");
		cl.make_request("INSERT B 5 Lake");
		cl.make_request("INSERT B 6 Flour");
		cl.make_request("INSERT B 7 Wonder");
		cl.make_request("INSERT B 8 Selection");
		cl.make_request("INTERSECTION");
		cl.make_request("SYMMETRIC_DIFFERENCE");

	}
	catch (const std::exception& ex)
  	{
    	std::cerr << "Exception: " << ex.what() << "\n";
  	}
	//cl.make_request("INSERT A 0 mms");
	//cl.make_request("TRUNCATE A");

	return 0;
}

/*int main() {

	const char* dbName = "test_database.sqlite";
	// const char* dbName = ":memory:";
	// const char * dbName = "";

	sqlite3* handle = nullptr;
	if (sqlite3_open(dbName, &handle)) {
		std::cout << "sqlite3_open failed! " << sqlite3_errmsg(handle) << std::endl;
		return -1;
	}
	std::cout << "Successfully opened!" << std::endl;

	char * errMsg = nullptr;

	const std::string createQuery = "CREATE TABLE test_table(name, age, cource);";
#pragma region EX
	// const std::string createQuery = "CREATE TABLE IF NOT EXISTS test_table(name, age, cource);";
#pragma endregion
	if (sqlite3_exec(handle, createQuery.c_str(), /*callback*//*nullptr, /*cb 1st argument*//*nullptr, &errMsg)) {
	/*	std::cout << "sqlite3_exec with createQuery failed! " << errMsg << std::endl;
		sqlite3_free(errMsg);
		return -1;
	}
	std::cout << "Successfully created!" << std::endl;


	

	auto readCallback = [](void* context, int columns, char **data, char **names) -> int {
		if (!columns) {
			std::cout << "Empty result!" << std::endl;
			return 0;
		}

		if (!names) {
			std::cout << "No columns!" << std::endl;
			return 0;
		}

	//	std::cout << "Columns:" << std::endl;
	//	for (int i=0; i<columns; ++i) {
	//		if (i != 0)
	//			std::cout << '\t';
	//		std::cout << names[i];
	//	}
	//	std::cout << std::endl;

		if (!data) {
			std::cout << "No data!" << std::endl;
			return 0;
		}

		std::cout << "Data:" << std::endl;
		for (int i=0; i<columns; ++i) {
			if (i != 0)
				std::cout << '\t';
			std::cout << data[i];
		}
		std::cout << std::endl;

		return 0;
	};

	const std::string selectAllQuery = "SELECT * FROM test_table;";
	if (sqlite3_exec(handle, selectAllQuery.c_str(), /*callbackreadCallback, /*cb 1st argumentnullptr, &errMsg)) {
	/*	std::cout << "sqlite3_exec with createQuery failed! " << errMsg << std::endl;
		sqlite3_free(errMsg);
		return -1;
	}
	std::cout << "Successfully selected!" << std::endl;





	const std::vector<const char *> insertQueries = {
		"INSERT INTO test_table VALUES('Ivan', 32, 1);",
		"INSERT INTO test_table VALUES('Andrew', 10, 2);",
		"INSERT INTO test_table VALUES('Alex', 48, 3);"
	};

	for (const auto& query : insertQueries)
		if (sqlite3_exec(handle, query, /*callbacknullptr, /*cb 1st argumentnullptr, &errMsg)) {
	/*		std::cout << "sqlite3_exec with createQuery failed! " << errMsg << std::endl;
			sqlite3_free(errMsg);
			return -1;
		}		
	std::cout << "Successfully inserted!" << std::endl;

	if (sqlite3_exec(handle, selectAllQuery.c_str(), /*callbackreadCallback, /*cb 1st argumentnullptr, &errMsg)) {
	/*	std::cout << "sqlite3_exec with createQuery failed! " << errMsg << std::endl;
		sqlite3_free(errMsg);
		return -1;
	}
	std::cout << "Successfully selected!" << std::endl;

	const std::string sorted_request = "SELECT * from test_table ORDER BY age;";
	if (sqlite3_exec(handle, sorted_request.c_str(), /*callbackreadCallback, /*cb 1st argumentnullptr, &errMsg)) {
	/*	std::cout << "sqlite3_exec with createQuery failed! " << errMsg << std::endl;
		sqlite3_free(errMsg);
		return -1;
	}
	std::cout << "Successfully selected!" << std::endl;

	return 0;
}*/