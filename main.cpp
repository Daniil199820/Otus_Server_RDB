#include <iostream>
#include <vector>
#include "Ditchr_Clients.h"
#include <memory>
#include <sstream>
#include "Server.h"

int to_integer(const char* arg){
  int temp;
  try{
     temp = std::stoi(arg);
  }
  catch(const std::invalid_argument& inv_er){
    throw std::invalid_argument("Argument is not an integer.");
  }
  return temp;
}

// realize class for data visualizer and send them using observer
int main(int argc, char* argv[]){

	try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: async_tcp_echo_server <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;

    server server(io_context,to_integer(argv[1]));

    io_context.run();
  }

  catch (const std::exception& ex)
  {
    std::cerr << "Exception: " << ex.what() << "\n";
  }

	
	/*Client_require cl;
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
	*/
	return 0;
}

