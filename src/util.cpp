///
/// @file   util.cpp
/// @author Yinghai
/// @date   Fri Sep 12 14:05:16 2008
/// 
/// @brief  Implementation of the utility functions
/// 
/// 
///

#include "util.h"
#include "mat.h"
#include <fstream>
#include <iostream>
#include <map>

string tokenizer(string& line, const string& delims){
	string toke;

	// find the beginning position of first token
	string::size_type idx_begin = line.find_first_not_of(delims);

	if (idx_begin != string::npos) {
		string::size_type idx_end = line.find_first_of(delims, idx_begin);

		// last word
		if (idx_end == string::npos) {
			idx_end = line.length();
		}

		// extract the first token and erase it from the input string
		toke = line.substr(idx_begin, idx_end - idx_begin);
		capitalize(toke);
		line.erase(0, idx_end - 0);
	} // end if

	return toke;
}

void capitalize(string &token) {
  for (size_t i = 0; i< token.length(); ++i) {
    token[i] = toupper(token[i]);
  }
}


double to_double(string &str) {
	string delims = "0123456789+-E.";
	string::size_type fig_end = str.find_first_not_of(delims);
	if (fig_end == string::npos) {
		return atof(str.c_str());	
	}
	else {
		double fig = atof(str.substr(0, fig_end).c_str());
		double scale = 1.0;
		string unit = str.substr(fig_end, str.length() - fig_end);
		if (unit == "P") {
			scale = 1e-12;	
		}
		else if (unit == "N" || unit == "NS") {
			scale = 1e-9;	
		}
		else if (unit == "U") {
			scale = 1e-6;	
		}
		else if (unit == "M") {
			scale = 1e-3;	
		}
		else if (unit == "K") {
			scale = 1e3;
		}
		else if (unit == "MEG"){
			scale = 1e6;     
		} 
		// TODO 
		else {}
		return fig*scale;
	}	

}

void matStamp(int r[], int c[], Matrix& matSrc, Matrix& matDst)
{
	int matRow = matSrc.row();
	int matCol = matSrc.column();
	for (int i = 0; i < matRow; i++)
	{
		for (int j = 0; j < matCol; j++)
		{
			if (r[i] < 0 || r[j] <0)
				continue;
			double tmp = matDst.get(r[i], c[j]);
			matDst.set(r[i], c[j], tmp + matSrc.get(i, j));
		}
	}
}

void matOutput(string fileName, Matrix& mat)
{
	std::ofstream outfile(fileName, std::ios::binary | std::ios::out);
	int32_t rows = mat.row();
	int32_t cols = mat.column();
	outfile.write((char*)&rows, sizeof(rows));
	outfile.write((char*)&cols, sizeof(rows));
	for (int i = 0; i < mat.row(); i++)
	{
		for (int j = 0; j < mat.column(); j++)
		{
			double tmp = mat.get(i, j);
			outfile.write((char*)&tmp, sizeof(tmp));
		}
	}
}

void printNodeList(std::ostream& stm, std::map<std::string, int>& list,bool outZero)
{
	std::vector<string> listInv(list.size());
	std::map<std::string, int>::iterator iter;
	for (iter = list.begin(); iter != list.end(); iter++)
	{
		listInv[iter->second] = iter->first;
	}
	int i = 0;
	if (outZero == false)
	{
		i++;
	}
	for (; i < listInv.size(); i++)
	{
		string str = listInv[i];
		if (str.substr(0, 2) != "i:")
		{
			stm << " " << 'V' << "<" << str << ">";
		}
		else
		{
			stm << " " << "I" << "<" << str.substr(2) << ">";
		}

	}
}

	void printProbeList(std::ostream& stm, std::vector<int> & probeList, std::map<string, int> & nodeList)
	{
		std::vector<string> listInv(nodeList.size());
		std::map<std::string, int>::iterator iter;
		for (iter = nodeList.begin(); iter != nodeList.end(); iter++)
		{
			listInv[iter->second] = iter->first;
		}

		for (int i = 0; i < probeList.size(); i++)
		{
			string str = listInv[probeList[i]];
			if (str.substr(0, 2) != "i:")
			{
				stm << " " << 'V' << "<" << str << ">";
			}
			else
			{
				stm << " " << "I" << "<" << str.substr(2) << ">";
			}
		}
	}

	void subCircuitUnfold(string inFileName, string outFileName)
	{
		std::ifstream inFileStream(inFileName);
		std::ofstream outFileStream(outFileName);
		std::map<string, int> subCktList;
		string line;
		string delims(" \n\r()\t");
		int pos;

		// Record the position of the subcircuit
		while (!inFileStream.eof())
		{
			pos = inFileStream.tellg();
			std::getline(inFileStream, line);
			capitalize(line);
			string tmp = tokenizer(line, delims);
			if(tmp == ".SUBCKT")
			{
				tmp = tokenizer(line,delims);
				subCktList[tmp] = pos;
			}
			
		}
		
		inFileStream.clear();
		inFileStream.seekg(0);
		string lineCopy;
		string name;
		std::vector<string> portList;
		while (!inFileStream.eof())
		{
			pos = inFileStream.tellg();
			if (!std::getline(inFileStream, line))
			{
				//break;
				;
			}
			capitalize(line);
			lineCopy = line;
			string tmp = tokenizer(line, delims);

			if (tmp == ".SUBCKT")
			{
				while(tokenizer(line,delims) != ".ENDS")
					std::getline(inFileStream, line);
				continue;

			}
			else if (tmp[0] != 'X')
			{
				outFileStream << lineCopy << std::endl;
			}
			else
			{
				name = tmp;
				// Parse the ports of the subcircuit
				portList.clear();
				while (1)
				{
					tmp = tokenizer(line, delims);
					if (line.find_first_not_of(delims) != string::npos)
					{
						portList.push_back(tmp);

					}
					else
					{
						break;
					}

					

				}
				insertSubCircuit(name,inFileStream,outFileStream,subCktList[tmp],portList);



			}

		}
		outFileStream.close();

}

	static void insertSubCircuit(string& name,std::ifstream &inFileStream,std::ofstream& outFileStream, int subCktPos, std::vector<string>& portList)
	{
		int initialPos = inFileStream.tellg();
		inFileStream.seekg(subCktPos);
		string tmp;
		string line;
		string delims(" \n\r()\t");
		std::map<string, string> portToNode;
		
		
		getline(inFileStream, line);
		tmp	= tokenizer(line, delims);
		tmp = tokenizer(line, delims);
		for (int i = 0; i < portList.size(); i++)
		{
			tmp = tokenizer(line, delims);
			portToNode[tmp] = portList[i];
		}
		portToNode["0"] = "0";


		do
		{
			std::getline(inFileStream, line);
			capitalize(line);
			tmp = tokenizer(line, delims);
			if (tmp == ".ENDS")
			{
				break;
			}
			else
			{
				outFileStream << tmp << ":" << name<<" ";
			}
			std::map<string, string>::iterator iter;
			tmp = tokenizer(line, delims);
			iter = portToNode.find(tmp);
			if (iter != portToNode.end())
				outFileStream << iter->second << " ";
			else
				outFileStream << tmp << ":" << name << " ";
			tmp = tokenizer(line, delims);
			iter = portToNode.find(tmp);
			if (iter != portToNode.end())
				outFileStream << iter->second << " ";
			else
				outFileStream << tmp << ":" << name << " ";
			tmp = tokenizer(line, delims);
			outFileStream << tmp << std::endl;
		} while (1);
		inFileStream.seekg(initialPos);

}