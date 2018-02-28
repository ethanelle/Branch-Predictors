#include <string>
#include <fstream>
#include <iostream>

/* TAKE ALL BRANCHES */

int main (int argc, char const* argv[])
{
	long correct, total;
	correct = total = 0;
	int history = 1;
	
	std::fstream inFile, outFile;
	inFile.open(argv[1], std::ios::in);
	outFile.open("output.txt", std::ios::out | std::ios::app);
	
	if(!inFile || !outFile){std::cerr << "Error opening either the input or output file!" << std::endl; return 1;}
	
	std::string line;
	while(std::getline(inFile, line))
	{
		total++;
		if(history == 1)
		{
			if(line[11] == 84) /* ASCII 'T' */
			{
				correct++;
			}else
			{
				history = 0;
			}
		}else
		{
			if(line[11] == 78) /* ASCII 'N' */
			{
				correct++;
			}else
			{
				history = 1;
			}
		}
	}
	
	std::cout << correct << ", " << total << std::endl;
	outFile << correct << ", " << total << std::endl;

	outFile.close(); inFile.close();
	
	return 0;
}
