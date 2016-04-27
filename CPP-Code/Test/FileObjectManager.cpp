#include <string>
#include "FileObject.cpp"
#include "ShellCommands.cpp"
#include "Debug.cpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class FileObjectManager
{
	private:
		vector<FileObject> files;
		vector< string > NameOccourances;
		void CheckFilenameOccourance();
		string ShellCommandOutputDirectory;
		bool UseRenameFeature;
		bool CreateConversionMap;

	public:
		FileObjectManager();
		void AddFileObject(string Filename);
		void PrintList();
		void PerformShellCommand();
		void setShellOutputDirectory(string Location);
		void setRenameFeature(bool Value);
		void setCreateConversionMap(bool Value);
};

FileObjectManager::FileObjectManager()
{
	VERBOSE("");
	UseRenameFeature = false;
	CreateConversionMap = false;
}	

void FileObjectManager::AddFileObject(const string Filename)
{
	VERBOSE("");
	// insert into List
	FileObject fileobject(Filename);
	files.push_back(fileobject);

	// Check Filename Occourance
	string filename = fileobject.getFilename();
	for(std::vector<string>::iterator it = NameOccourances.begin(); it != NameOccourances.end(); ++it) {
		string tempFilename = *it;
		if (tempFilename.compare(filename) == 0)
		{
			fileobject.IncrementInstance();
		} 
	}
	NameOccourances.push_back(filename);

}


void FileObjectManager::PrintList()
{
	VERBOSE("");
	for(std::vector<FileObject >::iterator it = files.begin(); it != files.end(); ++it) {
		FileObject fileobject = *it;
		string result = fileobject.ToString();
    	LOG(result.c_str());
	}
}

void FileObjectManager::setShellOutputDirectory(string Location)
{
	ShellCommandOutputDirectory = Location;
}

void FileObjectManager::setRenameFeature(bool Value)
{
	UseRenameFeature = Value;
}

void FileObjectManager::setCreateConversionMap(bool Value)
{
	CreateConversionMap = Value;
}

void FileObjectManager::PerformShellCommand()
{
	VERBOSE("");
	const int BUFFERCOUNT=256;
	char OriginalFilenameBuffer[BUFFERCOUNT];
	char NewFileNameBuffer[BUFFERCOUNT];

	ShellCommands::MakeDirectory(ShellCommandOutputDirectory);

	for(std::vector<FileObject >::iterator it = files.begin(); it != files.end(); it++) {	
		FileObject fileobject = *it;

		// Construct New File Name
		if(UseRenameFeature){
			// FEATURE: Appened integer to name clashes
			// if Instance Greater than 1 Add rename Modifier
			int instance = fileobject.getInstance();
			if( instance > 0) sprintf(NewFileNameBuffer,"\"%s/$(basename \"%s\")_%d%s\" ", ShellCommandOutputDirectory.c_str(),fileobject.getFilename().c_str(),instance,fileobject.getExtension().c_str());
			else sprintf(NewFileNameBuffer,"\"%s/$(basename \"%s\")%s\" ", ShellCommandOutputDirectory.c_str(),fileobject.getFilename().c_str(),fileobject.getExtension().c_str());
		}else 
		{
			// FEATURE: Use Old filename		
			sprintf(NewFileNameBuffer,"\"%s/$(basename \"%s\")\" ", ShellCommandOutputDirectory.c_str(),fileobject.getOriginalFilename().c_str());
		}

		// Wrap string in Parentheses to handle spaces
		sprintf(OriginalFilenameBuffer,"\"%s\"", fileobject.getOriginalFilename().c_str());

		ShellCommands::Copy(OriginalFilenameBuffer, NewFileNameBuffer);
		ShellCommands::InjectMetaDataDescription(NewFileNameBuffer,fileobject.getDescription());

		if(CreateConversionMap)
		{
			// FEATURE Create Conversion map
			ShellCommands::EchoToConversionMap(OriginalFilenameBuffer , NewFileNameBuffer,"Conversion_Map.txt");
		}

	}
}