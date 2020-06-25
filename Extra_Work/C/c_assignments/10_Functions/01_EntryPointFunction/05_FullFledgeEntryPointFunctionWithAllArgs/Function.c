#include<stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	int i;
	printf("\n No. of command line arguments : %d", argc);
	
	printf("\n Command line arguments : ");
	for(i = 0; i < argc; i++)
	{
		printf("\n Command line argument no : %d, and argument : %s", (i + 1), argv[i]);
	}
	
	printf("\n First 20 environment variables passed to this program are :");
	for(i = 0; i < 20; i++)
	{
		printf("\n Environmental variable no : %d =  %s", (i + 1), envp[i]);
	}
	return(0);
	
}

/* output *
 No. of command line arguments : 1
 Command line arguments :
 Command line argument no : 1, and argument : Function.exe
 First 20 environment variables passed to this program are :
 Environmental variable no : 1 =  ALLUSERSPROFILE=C:\ProgramData
 Environmental variable no : 2 =  APPDATA=C:\Users\Gauri\AppData\Roaming
 Environmental variable no : 3 =  CommandPromptType=Native
 Environmental variable no : 4 =  CommonProgramFiles=C:\Program Files (x86)\Common Files
 Environmental variable no : 5 =  CommonProgramFiles(x86)=C:\Program Files (x86)\Common Files
 Environmental variable no : 6 =  CommonProgramW6432=C:\Program Files\Common Files
 Environmental variable no : 7 =  COMPUTERNAME=DESKTOP-30VU2T0
 Environmental variable no : 8 =  ComSpec=C:\WINDOWS\system32\cmd.exe
 Environmental variable no : 9 =  DevEnvDir=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\
 Environmental variable no : 10 =  DriverData=C:\Windows\System32\Drivers\DriverData
 Environmental variable no : 11 =  ExtensionSdkDir=C:\Program Files (x86)\Microsoft SDKs\Windows Kits\10\ExtensionSDKs
 Environmental variable no : 12 =  FPS_BROWSER_APP_PROFILE_STRING=Internet Explorer
 Environmental variable no : 13 =  FPS_BROWSER_USER_PROFILE_STRING=Default
 Environmental variable no : 14 =  Framework40Version=v4.0
 Environmental variable no : 15 =  FrameworkDir=C:\Windows\Microsoft.NET\Framework\
 Environmental variable no : 16 =  FrameworkDIR32=C:\Windows\Microsoft.NET\Framework\
 Environmental variable no : 17 =  FrameworkVersion=v4.0.30319
 Environmental variable no : 18 =  FrameworkVersion32=v4.0.30319
 Environmental variable no : 19 =  FSHARPINSTALLDIR=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\FSharp\
 Environmental variable no : 20 =  HOMEDRIVE=C:
 
 */