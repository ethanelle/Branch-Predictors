#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

enum HistorySingle{notTaken = 0, taken};
enum HistorySaturating{stronglyTaken = 0, weaklyTaken, weaklyNotTaken, stronglyNotTaken};
enum Selector{stronglyGShare = 0, weaklyGShare, weaklyBimodal, stronglyBimodal};
struct S{
	unsigned int b : 11;
};

void takeAll(std::vector<std::string> &list, std::fstream &outFile);
void notTakeAll(std::vector<std::string> &list, std::fstream &outFile);
void bimodalSingleHelper(std::string line, int table_size, HistorySingle *table, long &correct);
void bimodalSingle(std::vector<std::string> &list, std::fstream &outFile);
void bimodalSaturatingHelper(std::string line, int table_size, HistorySaturating *table, long &correct);
void bimodalSaturating(std::vector<std::string> &list, std::fstream &outFile);
void gShareHelper(std::string line, unsigned short bitMask, S &globalHistory, 
	HistorySaturating *table, long &correct);
void gShare(std::vector<std::string> &list, std::fstream &outFile);
void tournament(std::vector<std::string> &list, std::fstream &outFile);

void takeAll(std::vector<std::string> &list, std::fstream &outFile)
{
	long total, correct;
	total = correct = 0;
	
	std::vector<std::string>::iterator it;
	
	std::string tmp;
	for(it = list.begin(); it != list.end(); it++)
	{
		total++;
		tmp = *it;
		if(tmp[11] == 84)
			correct++;
	}
	std::cout << correct << "," << total << ";" << std::endl;
	outFile << correct << "," << total << ';' << std::endl;
}

void notTakeAll(std::vector<std::string> &list, std::fstream &outFile)
{
	long total, correct;
	total = correct = 0;
	
	std::vector<std::string>::iterator it;
	
	std::string tmp;
	for(it = list.begin(); it != list.end(); it++)
	{
		total++;
		tmp = *it;
		if(tmp[11] == 78)
			correct++;
	}
	std::cout << correct << "," << total << ";" << std::endl;
	outFile << correct << "," << total << ';' << std::endl;
}

void bimodalSingleHelper(std::string line, int table_size, HistorySingle *table, long &correct)
{
	long addr;
	std::string line_long = line.substr(0,10);
	addr = std::stoul(line_long, nullptr, 16);
	addr = addr % table_size;
	HistorySingle *h = &(table[addr]);
	
	if(*h == taken)
	{
		if(line[11] == 84) /* ASCII 'T' */
		{
			correct++;
		}else
		{
			*h = notTaken;
		}
	}else
	{
		if(line[11] == 78) /* ASCII 'N' */
		{
			correct++;
		}else
		{
			*h = taken;
		}
	}
}

void bimodalSingle(std::vector<std::string> &list, std::fstream &outFile)
{
	long correct, total;
	HistorySingle *h;
	int i = 16;
	bool result = false;
	
	while(i <= 2048)
	{
		HistorySingle table[i];
		for(int j = 0; j < i; j++)
			table[j] = taken;
		std::vector<std::string>::iterator it;
		
		correct = total = 0;
		for(it = list.begin(); it != list.end(); it++)
		{
			bimodalSingleHelper(*it, i, table, correct);
			total++;
		}
		if(i != 2048)
		{
			std::cout << correct << "," << total << "; ";
			outFile << correct << "," << total << "; ";
		}else
		{
			std::cout << correct << "," << total << ";";
			outFile << correct << "," << total << ";";
		}
		i = i*2;
		if(i == 64)
			i = i*2;
	}
	std::cout << std::endl;
	outFile << std::endl;
}

void bimodalSaturatingHelper(std::string line, int table_size, HistorySaturating *table, long &correct)
{
	long addr;
	std::string line_long = line.substr(0,10);
	addr = std::stoul(line_long, nullptr, 16);
	addr = addr % table_size;
	HistorySaturating *h = &(table[addr]);
	
	if(*h == stronglyTaken)
	{
		if(line[11] == 84)
			correct++;
		else
		{
			*h = weaklyTaken;
		}
	}else if(*h == weaklyTaken)
	{
		if(line[11] == 84)
		{	
			correct++;
			*h = stronglyTaken;
		}else
			*h = weaklyNotTaken;
	}else if(*h == weaklyNotTaken)
	{
		if(line[11] == 78)
		{
			correct++;
			*h = stronglyNotTaken;
		}else
			*h = weaklyTaken;
	}else
	{
		if(line[11] == 78)
			correct++;
		else
			*h = weaklyNotTaken;
	}
}

void bimodalSaturating(std::vector<std::string> &list, std::fstream &outFile)
{
	long correct, total;
//	HistorySaturating *h;
	int i = 16;
	std::vector<std::string>::iterator it;
	
	while(i <= 2048)
	{
		HistorySaturating table[i];
		for(int j = 0; j<i; j++)
			table[j] = stronglyTaken;
		
		total = correct = 0;
		for(it = list.begin(); it != list.end(); it++)
		{
			bimodalSaturatingHelper(*it, i, table, correct);
			total++;
		}
		if(i != 2048)
		{
			std::cout << correct << "," << total << "; ";
			outFile << correct << "," << total << "; ";
		}else
		{
			std::cout << correct << "," << total << ";";
			outFile << correct << "," << total << ";";
		}
		i = i*2;
		if(i == 64)
			i = i*2;
	}
	std::cout << std::endl;
	outFile << std::endl;
}

void gShareHelper(std::string line, unsigned short bitMask, S &globalHistory, 
	HistorySaturating *table, long &correct)
{
	std::string line_long = line.substr(0,10);
	long addr, index;
	unsigned short ghr;
	HistorySaturating *h;
	
	addr = std::stoul(line_long, nullptr, 16);
	ghr = globalHistory.b & bitMask;
	index = addr ^ ghr;
	index = index % 2048;
	h = &(table[index]);
	
	
	if(*h == stronglyTaken)
	{
		if(line[11] == 84)
		{
			correct++;
			globalHistory.b <<= 1;
			globalHistory.b |= 1UL << 0;
		}
		else
		{
			*h = weaklyTaken;
			globalHistory.b <<= 1;
			globalHistory.b &= ~(1UL << 0);
		}
	}else if(*h == weaklyTaken)
	{
		if(line[11] == 84)
		{	
			correct++;
			*h = stronglyTaken;
			globalHistory.b <<= 1;
			globalHistory.b |= 1UL << 0;
		}else
		{
			*h = weaklyNotTaken;
			globalHistory.b <<= 1;
			globalHistory.b &= ~(1UL << 0);
		}
	}else if(*h == weaklyNotTaken)
	{
		if(line[11] == 78)
		{
			correct++;
			*h = stronglyNotTaken;
			globalHistory.b <<= 1;
			globalHistory.b &= ~(1UL << 0);
		}else
		{
			*h = weaklyTaken;
			globalHistory.b <<= 1;
			globalHistory.b |= 1UL << 0;
		}
	}else
	{
		if(line[11] == 78)
		{
			correct++;
			globalHistory.b <<= 1;
			globalHistory.b &= ~(1UL << 0);
		}
		else
		{
			*h = weaklyNotTaken;
			globalHistory.b <<= 1;
			globalHistory.b |= 1UL << 0;
		}
	}
}

void gShare(std::vector<std::string> &list, std::fstream &outFile)
{
	long correct, total;
//	HistorySaturating *h;
	unsigned short bitMask = 0x7;
	HistorySaturating pTable[2048];
	std::vector<std::string>::iterator it;
	
	while(bitMask <= 0x7ff)
	{
		for(int i = 0; i < 2048; i++)
			pTable[i] = stronglyTaken;
		
		S globalHistory = {0};
		total = correct = 0;
		for(it = list.begin(); it != list.end(); it++)
		{
			gShareHelper(*it, bitMask, globalHistory, pTable, correct);
			total++;
		}
		if(bitMask != 0x7ff)
		{
			std::cout << correct << "," << total << "; ";
			outFile << correct << "," << total << "; ";
		}else
		{
			std::cout << correct << "," << total << ";";
			outFile << correct << "," << total << ";";
		}
		
		bitMask = (bitMask * 2) + 1;
	}
	std::cout << std::endl;
	outFile << std::endl;
}

void tournament(std::vector<std::string> &list, std::fstream &outFile)
{
	long correct, total, addr, index;
	bool bCorrect, gCorrect;

	HistorySaturating *h;
	Selector *s;

	HistorySaturating gTable[2048], bTable[2048];
	Selector sTable[2048];
	
	S globalHistory = {0};
	
	for(int i = 0; i < 2048; i++)	
	{
		gTable[i] = bTable[i] = stronglyTaken;
		sTable[i] = stronglyGShare;
	}
	
	std::vector<std::string>::iterator it;
	
	total = correct = bCorrect = gCorrect = 0;
	for(it = list.begin(); it != list.end(); it++)
	{
		bCorrect = false;
		gCorrect = false;
		
		std::string line = *it;
		std::string line_long = line.substr(0,10);
		addr = std::stoul(line_long, nullptr, 16);
		index = addr ^ globalHistory.b;
		index = index % 2048;
		h = &(gTable[index]);
		
		if(*h == stronglyTaken)
		{
			if(line[11] == 84)
			{
				gCorrect = true;
				globalHistory.b <<= 1;
				globalHistory.b |= 1UL << 0;
			}
			else
			{
				*h = weaklyTaken;
				globalHistory.b <<= 1;
				globalHistory.b &= ~(1UL << 0);
			}
		}else if(*h == weaklyTaken)
		{
			if(line[11] == 84)
			{	
				gCorrect = true;
				*h = stronglyTaken;
				globalHistory.b <<= 1;
				globalHistory.b |= 1UL << 0;
			}else
			{
				*h = weaklyNotTaken;
				globalHistory.b <<= 1;
				globalHistory.b &= ~(1UL << 0);
			}
		}else if(*h == weaklyNotTaken)
		{
			if(line[11] == 78)
			{
				gCorrect = true;
				*h = stronglyNotTaken;
				globalHistory.b <<= 1;
				globalHistory.b &= ~(1UL << 0);
			}else
			{
				*h = weaklyTaken;
				globalHistory.b <<= 1;
				globalHistory.b |= 1UL << 0;
			}
		}else
		{
			if(line[11] == 78)
			{
				gCorrect = true;
				globalHistory.b <<= 1;
				globalHistory.b &= ~(1UL << 0);
			}
			else
			{
				*h = weaklyNotTaken;
				globalHistory.b <<= 1;
				globalHistory.b |= 1UL << 0;
			}
		}
		
		index = addr % 2048;
		h = &(bTable[index]);
		
		if(*h == stronglyTaken)
		{
			if(line[11] == 84)
				bCorrect = true;
			else
			{
				*h = weaklyTaken;
			}
		}else if(*h == weaklyTaken)
		{
			if(line[11] == 84)
			{	
				bCorrect = true;
				*h = stronglyTaken;
			}else
				*h = weaklyNotTaken;
		}else if(*h == weaklyNotTaken)
		{
			if(line[11] == 78)
			{
				bCorrect = true;
				*h = stronglyNotTaken;
			}else
				*h = weaklyTaken;
		}else
		{
			if(line[11] == 78)
				bCorrect = true;
			else
				*h = weaklyNotTaken;
		}
		
		s = &(sTable[index]);
		
		if((bCorrect && gCorrect) || (!bCorrect && !gCorrect))
		{
			if(bCorrect && gCorrect)
				correct++;
		}else if(*s == stronglyGShare)
		{
			if(gCorrect)
			{
				correct++;
			}else
			{
				*s = weaklyGShare;
			}
		}else if(*s == weaklyGShare)
		{
			if(gCorrect)
			{
				correct++;
				*s = stronglyGShare;
			}else
			{
				*s = weaklyBimodal;
			}
		}else if(*s == weaklyBimodal)
		{
			if(bCorrect)
			{
				correct++;
				*s = stronglyBimodal;
			}else
			{
				*s = weaklyGShare;
			}
		}else
		{
			if(bCorrect)
			{
				correct++;
			}else
			{
				*s = weaklyBimodal;
			}
		}
		total++;
	}
	std::cout << correct << "," << total << ";" << std::endl;
	outFile << correct << "," << total << ";" << std::endl;
}

int main(int argc, char const* argv[])
{
	std::clock_t start;
	start = std::clock();
	
	std::vector<std::string> list;
	
	std::fstream inFile, outFile;
	inFile.open(argv[1], std::ios::in);
	outFile.open("output.txt", std::ios::out | std::ios::app);
	
	std::string line;
	while(std::getline(inFile, line))
	{
		list.push_back(line);
	}
	inFile.close();
	
	/* all contents of file are in vector<string> list */
	takeAll(list, outFile);
	notTakeAll(list, outFile);
	bimodalSingle(list, outFile);
	bimodalSaturating(list, outFile);
	gShare(list, outFile);
	tournament(list, outFile);
	
	std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) 
		<< " ms" << std::endl;
	
	outFile.close();
	
	return 0;
}

