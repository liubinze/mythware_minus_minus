#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char s[1001];
int main()
{
	puts("Detecting student client...");
	FILE*getproc=popen("wmic process where name=\"StudentMain.exe\" get executablepath","r");
	fgets(s,1000,getproc);
	fgets(s,1000,getproc);
	if(s[0]>32)
		printf("Detected: %s\n",s);
	else
	{
		puts("Failed to detect student client. Please provide it underneath:");
		fgets(s,1000,stdin);
		s[1000]=0;
		for(int i=0;i<1000;i++)
			if(s[i]<32)
				s[i]=0;
			else if(s[i]>='A'&&s[i]<='Z')
				s[i]|=32;
		FILE*tmp=fopen(s,"rb");
		if(tmp==NULL)
			return 0;
		fclose(tmp);
		int len=strlen(s);
		if(len<15||strcmp(s+len-15,"studentmain.exe"))
			return 0;
		s[len-15]=0;
	}
	puts("1 for move shutdown.exe");
	puts("2 for kill NetFilter");
	puts("3 for kill FileFilter");
	puts("4 for never fullscreen");
	while(1)
	{
		char c=_getch();
		if(c=='1')
			system("takeown /f %WinDir%\\System32\\shutdown.exe & icacls %WinDir%\\System32\\shutdown.exe /grant Users:F & move %WinDir%\\System32\\shutdown.exe .");
		else if(c=='2')
			system("sc stop TDNetFilter & taskkill /f /im MasterHelper.exe");
		else if(c=='3')
			system("sc stop TDFileFilter & taskkill /f /im MasterHelper.exe");
		else if(c=='4')
		{
			system("taskkill /f /im StudentMain.exe");
			//Todo
			system(s);
		}
		else if(c==3)
			return 0;
	}
	return 0;
}
