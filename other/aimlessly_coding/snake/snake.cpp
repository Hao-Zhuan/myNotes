#include<windows.h>
#include<commctrl.h>
#include<time.h>
#include<cstdio>

int main(){
  HWND zmHwnd;
  HWND bzHwnd;
  HWND tbHwnd;
  zmHwnd=FindWindow("Progman","Program Manager");
  bzHwnd=FindWindowEx(zmHwnd,0,"SHELLDLL_DefView",NULL);
  tbHwnd=FindWindowEx(bzHwnd,0,"SysListView32","FolderView");
  int icount =SendMessage(tbHwnd,LVM_GETITEMCOUNT,0,0);
  printf("%d\n",icount);
  int CX=GetSystemMetrics(SM_CXSCREEN);
  int CY=GetSystemMetrics(SM_CYSCREEN);
  return 0;
}