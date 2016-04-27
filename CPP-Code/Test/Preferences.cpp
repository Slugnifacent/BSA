#include <string>
#include <fstream>
#include "Debug.cpp"

using namespace std;

class Preferences
{
	private:
		string bmweditDirectory;
		string extension;
		string outputDirectory;
		bool printConversionFile;
		bool renameConvertedFiles;

		void ExtractBMWEditDirectory(string Line);
		void ExtractExtension(string Line);
		void ExtractOutputDirectory(string Line);
		void ExtractPrintConversionFile(string Line);
		void ExtractRenameConvertedFiles(string Line);
		Preferences();

	public:
		Preferences(string FilePath);
		string getBMWEditDirectory();
		string getExtension();
		string getOutputDirectory();
		bool getPrintConversionFile();
		bool getRenameConvertedFiles();
		string ToString();
};

Preferences::Preferences(){}

Preferences::Preferences(string Filepath)
{
	// Setting Defaults
	bmweditDirectory="bmweditDirectory";
	extension = ".wav";
	outputDirectory  = "To-SFX-Library-Remamed";
	printConversionFile  = false;
	renameConvertedFiles = false;

	VERBOSE("");
	string line;
	ifstream txtFile(Filepath.c_str(),ifstream::in);
	if(txtFile.is_open())
	{
	    while(txtFile.good())
	    {
	        getline(txtFile, line);
			int index = line.find_first_of("=");
			if(index != string::npos)
			{
				// Splitting with "=" Delimiter
		        string key = line.substr(0, index);
		        string value = line.substr(index+1, line.length()-index);
		        if (key.compare("bmweditDirectory") == 0) ExtractBMWEditDirectory(value);
		        if (key.compare("extension") == 0) ExtractExtension(value);
		        if (key.compare("outputDirectory") == 0) ExtractOutputDirectory(value);
		        if (key.compare("printConversionFile") == 0) ExtractPrintConversionFile(value);
		        if (key.compare("renameConvertedFiles") == 0) ExtractRenameConvertedFiles(value);
		    }
		}
	    txtFile.close();
	}else LOG("Unable to find Preferences. Continuing without it.");
}



void Preferences::ExtractBMWEditDirectory(string Line)
{
	VERBOSE("");
	LOG(Line.c_str());
	bmweditDirectory = Line;
}

void Preferences::ExtractExtension(string Line)
{
	VERBOSE("");
	LOG(Line.c_str());
	extension = Line;
}

void Preferences::ExtractOutputDirectory(string Line)
{
	VERBOSE("");
	LOG(Line.c_str());
	outputDirectory = Line;
}

void Preferences::ExtractPrintConversionFile(string Line)
{
	VERBOSE("");
	LOG(Line.c_str());
	printConversionFile = (Line.compare("true") == 0) ? true : false;
}

void Preferences::ExtractRenameConvertedFiles(string Line)
{
	VERBOSE("");
	LOG(Line.c_str());
	renameConvertedFiles = (Line.compare("true") == 0) ? true : false;
}


string Preferences::getBMWEditDirectory()
{
	VERBOSE("");
	return bmweditDirectory; 
}

string Preferences::getExtension()
{
	VERBOSE("");
	return extension;
}

string Preferences::getOutputDirectory()
{
	VERBOSE("");
	return outputDirectory;
}

bool Preferences::getPrintConversionFile()
{
	VERBOSE("");
	return printConversionFile;
}

bool Preferences::getRenameConvertedFiles()
{
	VERBOSE("");
	return renameConvertedFiles;
}

string Preferences::ToString()
{
	VERBOSE("");
	const int BUFFERCOUNT=512;
	char buff[BUFFERCOUNT];
 	snprintf(buff, sizeof(buff), "BMWEditDirectory: %s, Extension: %s, OutputDirectory: %s, PrintConversionFile: %s, RenameConvertedFiles: %s\n", 
 		bmweditDirectory.c_str(),extension.c_str(),outputDirectory.c_str(), printConversionFile ? "true" : "false",renameConvertedFiles ? "true" : "false");
 	string temp(buff);
	return temp;	
}