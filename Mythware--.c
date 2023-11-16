#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char s[1001],t[1001];
int main()
{
	puts("Detecting student client...");
	FILE*getproc=popen("wmic process where name=\"StudentMain.exe\" get executablepath","r");
	fgets(s,1000,getproc);
	fgets(s,1000,getproc);
	if(s[0]>32)
	{
		for(int i=0;i<1001;i++)
			if(s[i]>0&&s[i]<32)
				s[i]=0;
		int len=strlen(s);
		while(len&&s[len-1]==32)
			s[len--]=0;
		printf("Detected: %s\n",s);
		s[len-15]=0;
	}
	else
	{
		puts("Failed to detect student client. Please provide it underneath:");
		fgets(s,1000,stdin);
		s[1000]=0;
		for(int i=0;i<1000;i++)
			if(s[i]>0&&s[i]<32)
				s[i]=0;
			else if(s[i]>='A'&&s[i]<='Z')
				s[i]|=32;
		FILE*tmp=fopen(s,"rb");
		if(tmp==NULL)
			return 0;
		fclose(tmp);
		int len=strlen(s);
		while(len&&s[len-1]==32)
			s[len--]=0;
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
			strcat(s,"LibDeskMonitor.dll");
			FILE*fin=fopen(s,"rb"),*fout=fopen("_libDeskMonitor.dll","wb");
			if(fin==NULL)
				puts("File not exist");
			else
			{
				_Bool f=0;
				while(1)
				{
					unsigned char buf[4]={0};
					int r=fread(buf,1,4,fin);
					if(r<4)
					{
						fwrite(buf,1,r,fout);
						break;
					}
					if(buf[0]==0x74&&buf[1]==0x1a&&buf[2]==0x33&&buf[3]==0xc0)
						buf[0]=0xeb,f=1;
					fwrite(buf,1,4,fout);
				}
				fclose(fin),fclose(fout);
				if(f)
				{
					system("taskkill /f /im StudentMain.exe");
					t[0]=0,strcat(t,"move \""),strcat(t,s),strcat(t,"\" ."),system(t);
					t[0]=0,strcat(t,"move _libDeskMonitor.dll \""),strcat(t,s),strcat(t,"\""),system(t);
					s[strlen(s)-18]=0;
					strcat(s,"StudentMain.exe");
					t[0]=0,strcat(t,"start \"\" \""),strcat(t,s),strcat(t,"\""),system(t);
					s[strlen(s)-15]=0;
				}
				else
				{
					puts("Already performed");
					s[strlen(s)-18]=0;
					system("del _libDeskMonitor.dll");
				}
			}
		}
		else if(c==3)
			return 0;
	}
	return 0;
}
