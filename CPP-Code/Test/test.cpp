#include <iostream>
#include <string>
#include <map>
#include <Vector>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include "FileObjectManager.cpp"
#include "Debug.cpp"
#include "Preferences.cpp"

using std::cout;
using namespace boost::filesystem;
using namespace std;

int main(int argc , char * argv[]) {
 VERBOSE("");
 path p (argv[1]);
 FileObjectManager filemanager;
 
 Preferences preferences("preferences.txt");

 string searchFileExtension=preferences.getExtension();
 string outputDirectory=preferences.getOutputDirectory();

 filemanager.setShellOutputDirectory(preferences.getOutputDirectory());
 filemanager.setRenameFeature(preferences.getRenameConvertedFiles());
 filemanager.setCreateConversionMap(preferences.getPrintConversionFile());

 ShellCommands::BMWEDITDirectory=preferences.getBMWEditDirectory();


 LOG(preferences.ToString().c_str());

  try
  {
    if (exists(p))
    {
      if (is_regular_file(p))
        cout << p << " size is " << file_size(p) << '\n';

      else if (is_directory(p))
      {
        cout << p << " is a directory containing:\n";

		  recursive_directory_iterator it(p);
		  while (it != recursive_directory_iterator())

		  	if(!is_directory(*it))
		  	{
          directory_entry& directory  = *it++;
		    	string filename = directory.path().string();
          if(directory.path().extension().string().compare(searchFileExtension) == 0)
          {
            filemanager.AddFileObject(filename);
          }

		    } else {

          if (it->path().filename().string().compare(outputDirectory) == 0)
          {
              string temp("Output Directory:" + outputDirectory + " Found");
              LOG(temp.c_str());
              it.no_push();
          } 

          *it++;
        }
		}
      else
        cout << p << " exists, but is not a regular file or directory\n";
    }
    else
      cout << p << " does not exist\n";
  }

  catch (const filesystem_error& ex)
  {
    cout << ex.what() << '\n';
  }

  filemanager.PrintList();
  filemanager.PerformShellCommand();
  cout << "Success\n";
  return 0;
}

