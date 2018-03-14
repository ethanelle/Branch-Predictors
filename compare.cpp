#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

int main(int argc, char const* argv[])
{
	std::fstream aFile, bFile;
	aFile.open(argv[1], std::ios::in);
	bFile.open(argv[2], std::ios::in);
	
	std::vector<std::string> aList;
	std::vector<std::string> bList;
	
	std::vector<std::string>::iterator itA;
	std::vector<std::string>::iterator itB;
	
	std::string line;
	while(std::getline(aFile, line))
	{
		aList.push_back(line);
	}
	while(std::getline(bFile, line))
	{
		bList.push_back(line);
	}
	
	aFile.close();
	bFile.close();
	
	itB = bList.begin();
	for(itA = aList.begin(); itA != aList.end(); itA++)
	{
		std::string a = *itA;
		std::string b = *itB;
		if(a.compare(b) != 0)
		{
			std::cout << "No match!" << std::endl;
			std::cout << a << std::endl;
			std::cout << b << std::endl;
			return 0;
		}
		itB++;
	}
	std::cout << "Match!" << std::endl;
	return 0;
}
