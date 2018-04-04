cd FileMgrComp
& "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\MSBuild.exe" .\FileMgrComp.vcxproj /t:Clean

cd ..\TextSearchComp
& "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\MSBuild.exe" .\TextSearchComp.vcxproj /t:Clean

cd ..\TextSearchClient
& "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\MSBuild.exe" .\TextSearchClient.vcxproj /t:Clean

cd ..