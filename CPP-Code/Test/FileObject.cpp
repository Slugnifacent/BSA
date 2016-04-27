#include <string>
#include <iostream>
#include <stdlib.h>
#include "Debug.cpp"

using namespace std;

class FileObject {
	
	private:
		static string delimeter;
		string originalFilename;
		string filename;
		string description;
		string extension;
		void ExtractNameAndDesc();
		void ExtractFilename(const string Filename);
		void ExtractDescription(const string Filename);
		void ExtractExtension(const string Filename);
		int instance;

	public:
		FileObject(const string File);
		string getFilename();
		string getDescription();
		string getOriginalFilename();
		string getExtension();
		string ToString();
		int  getInstance();
		void IncrementInstance();

};

string FileObject::delimeter = "-";

FileObject::FileObject(const string File)
{
	VERBOSE("");
	originalFilename = File;
	instance = 0;
    ExtractFilename(File);
    ExtractDescription(File);
    ExtractExtension(File);
}

void FileObject::ExtractFilename(const string Filename)
{
	VERBOSE("");
	// Grabbing Extension
	size_t lastindex = Filename.find_first_of(delimeter); 
	if(lastindex == string::npos)
	{
		// Removing Exension and using the entire filename as the Filename
		lastindex = Filename.find_last_of("."); 
	}
	
	filename = Filename.substr(0, lastindex);
}


void FileObject::ExtractDescription(const string Filename)
{
	VERBOSE("");
	// Get "-" Location
	size_t index = Filename.find_first_of(delimeter); 
	if(index == string::npos)
	{
		// No Description. return
		return;
	}
	index++; // To remove "-" from description
	// Get extension Start Location
	size_t lastindex = Filename.find_last_of("."); 

	description = Filename.substr(index,lastindex - index);

}


void FileObject::ExtractExtension(const string Filename)
{
	VERBOSE("");
	// Grabbing Extension
	size_t lastindex = Filename.find_last_of("."); 
	if(lastindex == string::npos)
	{
		// No Exension?
		return;
	}
	extension = Filename.substr(lastindex, Filename.length()-lastindex);
}

void FileObject::IncrementInstance()
{
	VERBOSE("");
	instance++;
}

string FileObject::getFilename()
{
	VERBOSE("");
	return filename;
}

string FileObject::getDescription()
{
	VERBOSE("");
	return description;
}

string FileObject::getOriginalFilename()
{
	VERBOSE("");
	return originalFilename;
}

string FileObject::getExtension()
{
	VERBOSE("");
	return extension;
}

int  FileObject::getInstance()
{
	VERBOSE("");
	return instance;
}

string FileObject::ToString()
{
	VERBOSE("");
	const int BUFFERCOUNT=512;
	char buff[BUFFERCOUNT];
 	snprintf(buff, sizeof(buff), "Original Filename: %s, Filename: %s, Extension: %s, Instance: %d, Description: %s\n", 
 		originalFilename.c_str(),filename.c_str(),extension.c_str(),instance,description.c_str());
 	string temp(buff);
	return temp;
}
