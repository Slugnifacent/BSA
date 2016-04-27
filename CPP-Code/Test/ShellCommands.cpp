#include <stdlib.h>
#include <string>
#include "Debug.cpp"

#define COMMANDBUFFER_SIZE 512
 
class ShellCommands{
	private:
		char static CommandBuffer[COMMANDBUFFER_SIZE];
		void static ClearBuffer();

	public:
		static string BMWEDITDirectory;
		void static Custom(string Command);
		void static Copy(string Filename, string Location);
		void static InjectMetaDataDescription(string Filename, string Description);
		void static MakeDirectory(string Command);
		void static EchoTofile(string Text,string Filename);
		void static EchoToConversionMap(string OriginalFile, string Newfile, string Filename);
};

char ShellCommands::CommandBuffer[COMMANDBUFFER_SIZE];
string ShellCommands::BMWEDITDirectory="";

void ShellCommands::Custom(string Command)
{
	VERBOSE("");
	ClearBuffer();
}

void ShellCommands::EchoTofile(string Text,string Filename)
{
	VERBOSE("");
	ClearBuffer();
	sprintf(CommandBuffer,"echo %s >> %s", Text.c_str(),Filename.c_str());
	system(CommandBuffer);
}

void ShellCommands::Copy(string Filename, string Location)
{
	VERBOSE("");
	ClearBuffer();
	sprintf(CommandBuffer,"cp %s %s", Filename.c_str(),Location.c_str());
	system(CommandBuffer);

}

void ShellCommands::MakeDirectory(string Directory)
{
	VERBOSE("");
	ClearBuffer();
	sprintf(CommandBuffer,"mkdir %s", Directory.c_str());
	system(CommandBuffer);
}


void ShellCommands::InjectMetaDataDescription(string Filename, string Description)
{
	VERBOSE("");
	ClearBuffer();
	string BMWEDIT=BMWEDITDirectory + "/bwfmetaedit --Description=";
	sprintf(CommandBuffer,"%s\"%s\" %s", BMWEDIT.c_str(),Description.c_str(),Filename.c_str());
	system(CommandBuffer);
	LOG(CommandBuffer);

}

void ShellCommands::EchoToConversionMap(string OriginalFile, string Newfile, string Filename)
{
	VERBOSE("");
	ClearBuffer();
	sprintf(CommandBuffer,"echo %s \"->\" %s >> %s", OriginalFile.c_str(), Newfile.c_str(),Filename.c_str());
	system(CommandBuffer);
}

void ShellCommands::ClearBuffer()
{
	VERBOSE("");
	CommandBuffer[0]=0;
}