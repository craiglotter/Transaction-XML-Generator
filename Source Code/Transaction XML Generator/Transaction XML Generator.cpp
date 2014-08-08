// Transaction XML Generator.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include<fstream.h>


//structure used in print credit binary.rec file
struct _CURRENTXACTION
{
	unsigned long ShiftNumber;
	unsigned long TransactionNumber;
	unsigned long Amount;
	unsigned long DateTime;
	unsigned char CardNumber[10];
	bool TransactionDataAvailable;
};

//program entry point. reads binary transaction file and generates more user-friendly xml file.
int main(int argc, char* argv[])
{
	//execute code only if two program arguments are supplied, namely input binary file and 
	//output path to write to. (Remember, 1st argument contains program name)
	if (argc >= 3)
	{
		//read binary file (file is expected to contain an instance of CurrentXAction
		cout << "Reading Binary File...";      
	  	_CURRENTXACTION p_Data;
		FILE* in;
		in = fopen(argv[1], "rb");
		if (in!=NULL)
		{
			fread(&p_Data, sizeof(_CURRENTXACTION), 1, in); 
			fclose(in);
			cout << " Ok" << endl;

			//generate XML file
			cout << "Writing XML File...";   
			fstream file_op(argv[2],ios::out);
			file_op<<"<Transaction_File>"<<endl;
			file_op<<"<Transaction>"<<endl;
			file_op<<"<ShiftNumber>"<< p_Data.ShiftNumber <<"</ShiftNumber>"<<endl;
			file_op<<"<Amount>"<< p_Data.Amount <<"</Amount>"<<endl;
			file_op<<"<CardNumber>"<< p_Data.CardNumber <<"</CardNumber>"<<endl;
			file_op<<"<DateTime>"<< p_Data.DateTime <<"</DateTime>"<<endl;
			file_op<<"<TransactionDataAvailable>"<< p_Data.TransactionDataAvailable <<"</TransactionDataAvailable>"<<endl;
			file_op<<"<TransactionNumber>"<< p_Data.TransactionNumber <<"</TransactionNumber>"<<endl;
			file_op<<"</Transaction>"<<endl;
			file_op<<"</Transaction_File>"<<endl;
			file_op.close();
			cout << " Ok" << endl;

			//print success message
			cout << "Operation Successful. (" << argv[2] << " generated)" <<endl;
		}
		else
		{
			//in case binary file cannot be opened/located
			cout << " Fail" << endl;
			cout << "Error: Input binary file cannot be opened" << endl;
			cout << "Operation Failed." << endl;
		}
	}
	else
	{
		//incorrect number of arguments supplied to the program
		cout << "Usage: <Transaction XML Generator.exe> <binary input file> <xml output file>" << endl;
		cout << "Where <binary input file> is filename of binary transaction file to read and <xml output file> is the file path for the generated xml transaction file." << endl;
	}
	return 0;
}

