Description: 
This is the Windows part of the TextSearchTool - CSE775 Distributed Object, Project #1

Author: 
Zihao Xing

Date: 
Apr 3, 2018

Overview:
1, This is project implement a text search tool that given on the command line: 

	a regular-expression search string, a path, and a set of file name patterns, 

identifies by name and path all those files matching one or more of the patterns and which contain an instance of the search string.  
2, The C++11 Threading feature is demonstrated in this version.

Environment:
Windows 10 Education

IDE:
Visual Studio 2017 Community

***************************************
Compile and Run from Command Line
***************************************
Compile & Clean:
1, start PowerShell as Adminsitrator
2, cd path\to\project
3, .\compile.ps1 # compile
4, .\clean.ps1 # clean

Run:
1, start PowerShell as Adminsitrator
2, cd path\to\project
3, .\run.ps1 # run

***************************************
Compile and Run from IDE
***************************************
You have to compile the solution by the following order:
1, Build "FileMgrComp" 
2, Build "TextSearchComp"
3, Build "TextSearchClient"


Notes:
1, Currently supports searching "*.txt", "*.h", "*.cpp", etc
2, To start Powershell as Administrator, you can firstly run cmd as Administrator
and then type "PowerShell"
**************IMPORTANT IMPORTANT IMPORTANT*************************
3, If the powershell script is not working, probably your
MSBuild.exe - the build tool for windows - is resided in a different
location on your computer!!!!!!!!!!!!!!!! 
just check the *.ps1 files, and modify the MSBuild.exe's location to 
the right one.

for example, on my computer, the MSBuild.exe's location is:
"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\MSBuild.exe"
*******************************************************************

Requirements:
Your Text Search Program:
1, Shall be implemented in C++11 using Visual Studio 2017 for the COM-on-Windows program and g++ ver 5.3 for the Components-on-Linux program1.
2, Shall, on each platform, provide a console application that, given on the command line: a regular-expression search string, a path, and a set of file name patterns, identifies by name and path all those files matching one or more of the patterns and which contain an instance of the search string. It does this using the services of two components, described below.
3, The previous requirement shall be interpreted to include all common text formats, e.g., *.txt, *.h, *.cpp, *.cs, etc. It optionally2 will also be interpreted to include Microsoft Word doc and docx files on Windows. And, it optionally2 will also be interpreted to include Libre Office Writer odf files on Linux.
4, Shall provide a text search component that accepts a fully qualified file name and regular-expression text pattern. If the file matches the text pattern in one or more locations, it returns a list of line numbers where the matches occur. If no matches occur, it returns an empty list.
5, Shall provide a FileMgr component that finds the fully qualified names of all files residing in a directory tree rooted at a specified path and matching one or more of the filename patterns. It exposes these results by providing a get(...) method that retrieves each result from an internal thread-safe blocking queue, and returns the result with a success code of true. When its search has ended, the get(...) method returns a success code with value false.
6, Shall use a Powershell script on windows and a Bash script on Linux to demonstrate that the application, and its components, implement their required functionality. The combination of scripts and console applications should clearly show the initial requests, the output of the FileMgr, and the output of the file search processing.

LISENCE:
MIT LISENCE
