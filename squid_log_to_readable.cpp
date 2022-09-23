#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

string convert_unixtimestamp_to_readable(string text, string converted_file) {
	string delimiter = " ";
	vector<string> content{};
    	size_t pos = 0;
    	while ((pos = text.find(delimiter)) != string::npos) {
        	content.push_back(text.substr(0, pos));
        	text.erase(0, pos + delimiter.length());
    	}
	time_t unix_timestamp = stoi(content[0]);
	stringstream ss; 
	ss << put_time(std::gmtime(&unix_timestamp), "%Y-%m-%d %I:%M:%S %p");
	content[0] = ss.str();
	string result;
	for (auto item: content){
		 result += item + delimiter;
	}	
	return result;
}

int main(int argc, char *argv[])
{
	if (argc < 2){
		cout << "Error: 2 arguments are required, only " << argc << " provied" << endl;
		cout << "Usage: squid_log_to_readable <orginal_log_file> <converted_log_file>" << endl; 
	}
  ifstream infile(argv[1]);
  ofstream outfile(argv[2], ios::out);
	if(infile.is_open() && outfile.is_open()) {
    string line;
    while (getline(infile, line)) {
      outfile << convert_unixtimestamp_to_readable(line, argv[2]) << endl;
    }
  }
	outfile.close();
  infile.close();
  cout << "Info: Orginal log file: " << argv[1] << endl;
  cout << "Info: coverted log file: " << argv[2] << endl;
	return EXIT_SUCCESS;
}
