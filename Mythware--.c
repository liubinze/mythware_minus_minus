#include<conio.h>
int main()
{
	puts("1 for move shutdown.exe");
	puts("2 for kill NetFilter");
	puts("3 for kill FileFilter");
	while(1)
	{
		char c=_getch();
		if(c=='1')
			system("takeown /f %WinDir%\\System32\\shutdown.exe & icacls %WinDir%\\System32\\shutdown.exe /grant Users:F & move %WinDir%\\System32\\shutdown.exe .");
		else if(c=='2')
			system("sc stop TDNetFilter & taskkill /f /im MasterHelper.exe");
		else if(c=='3')
			system("sc stop TDFileFilter & taskkill /f /im MasterHelper.exe");
		else if(c==3)
			return 0;
	}
	return 0;
}
