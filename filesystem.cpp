#ifndef UNICODE
#define UNICODE
#endif 

#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <cstring>

#include <windows.h>
using namespace std;
HWND hwnd;
int size(wchar_t str[512]){
    int i = 0;
    while(true){
        if (str[i] == '\0'){
            return i;
        }
        i++;
    }
}
void ClearForMath(wchar_t (&num)[512]){
        for(int i = 0; i < 513; i++)
        {
            num[i] = '\0';
        }
}
void CreateButton(int x, int y,int width, int height, int id, wchar_t *text){
CreateWindowEx(WS_EX_CLIENTEDGE,L"button", text, WS_CHILD|WS_VISIBLE|WB_LEFT,
     x, y, width, height, hwnd, (HMENU) id, NULL, NULL);
}
void CreateLabel(int x, int y,int width, int height, int id, wchar_t *text){
CreateWindow(L"STATIC", text, WS_CHILD|WS_VISIBLE|WB_LEFT,
     x, y, width, height, hwnd, (HMENU) id, NULL, NULL);
}
HWND hListBox;
vector<vector<string>> AllFilesFind(string path){
    DIR *dir;
    struct dirent *entry;
    vector<vector<string>> DirsAndFiles;
    vector<string> Dirs;
    vector<string> Files;
    const char *pathConst= path.c_str();
    Files.push_back("");
    Dirs.push_back("");
    dir = opendir(pathConst);
    if (!dir) {
        DirsAndFiles.push_back(Dirs);
        DirsAndFiles.push_back(Files);
        return DirsAndFiles;
    }
    while ( (entry = readdir(dir)) != NULL)
    {
        string s = entry->d_name;
        if (s=="." || s==".." ){
            continue;
        }
        DIR *dir2;
        string path2 = path+s;
        const char *pathConst2= path2.c_str();
        dir2 = opendir(pathConst2);
        if (!dir2) {
            string sStr = s;
            Files.push_back(sStr);
            continue;
        }
        string sStr = s;
        Dirs.push_back(sStr);
        closedir(dir2);

    }
    DirsAndFiles.push_back(Dirs);
    DirsAndFiles.push_back(Files);
    closedir(dir);
    return DirsAndFiles;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstances, LPSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Sample Window Class";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_CAPTION | WS_SYSMENU,           // Window style

        // Size and position
        100, 100, 500, 400,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }
    CreateWindowEx(WS_EX_CLIENTEDGE,L"edit", L"c:/", WS_CHILD|WS_VISIBLE|WB_LEFT,
     10, 10, 400, 20, hwnd, (HMENU) 10, NULL, NULL);
    CreateWindow(L"button", L"Open", WS_CHILD|WS_VISIBLE|WB_LEFT,
     410, 10, 60, 20, hwnd, (HMENU) 30, NULL, NULL);
   hListBox = CreateWindow(L"listbox", NULL,WS_CHILD | WS_VISIBLE | LBS_STANDARD |LBS_NOTIFY|
   LBS_WANTKEYBOARDINPUT,
     10, 40, 480, 330, hwnd, (HMENU) 40, NULL, NULL);
    
    ShowWindow(hwnd, SW_SHOW );//ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{   
    char Buffer[512];
    wchar_t Math[512];
    int doornotdo = 0;
    int uSelectedItem;
    switch (uMsg)
    {
    case WM_COMMAND:
    
    if(LOWORD(wParam) == 30){
        doornotdo = 1;
    }
        if(HIWORD(wParam) == LBN_DBLCLK){
            uSelectedItem = (int)SendMessage(hListBox,
            LB_GETCURSEL, 0, 0L);
            int lenght =SendMessage(hListBox, LB_GETTEXT,
            uSelectedItem, (LPARAM)Buffer);
            GetDlgItemText(hwnd,10,Math, 512);
            int l = size(Math);
            if (lenght == 2 && Buffer[0] == '.' && Buffer[2] == '.'){
                Math[l-1] = '\0';
                for(int p = l-2;;p--)
                {
                    if (p < 0){
                        Math[0] = '/';
                        break;
                    }
                    if (Math[p] != '/'){
                       Math[p] = '\0';
                       continue; 
                    }
                    break;
                }
            }
            else
            {
                for(int p = 0;p<lenght*2;p+=2)
                {
                    Math[l] = Buffer[p];
                    l++;
                }
                Math[l++] = '/';
                Math[l] = '\0';
            }
            SetDlgItemText(hwnd,10,Math);
            doornotdo = 1;
            
        }

        if(doornotdo){

            SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
            wchar_t Math[512];
            GetDlgItemText(hwnd,10,Math, 512);
            char *between = new char[512];
            wcstombs(between, Math, 512);
            string path = between;
            vector<vector<string>> dirsAndFiles = AllFilesFind(path);
            // for(int r = 0; r < dirsAndFiles[1].size();r++)
            //     {
            //      cout<<"File: " <<dirsAndFiles[1][r]<<endl;
            //     }
            // for(int r = 0; r < dirsAndFiles[0].size();r++)
            //     {
            //      cout<<"Dir: " <<dirsAndFiles[0][r]<<endl;
            //     }
            if (dirsAndFiles[1][0] == "ItIsAFile"){
                SendMessage(hListBox, LB_ADDSTRING, 0,
                    (LPARAM)L"..");
                SendMessage(hListBox, LB_ADDSTRING, 0,
                    (LPARAM)L"Error");
            }
            else
            {
                SendMessage(hListBox, LB_ADDSTRING, 0,
                    (LPARAM)L"..");
                for(int r = 0; r< dirsAndFiles.size();r++)
                {
                    for(int i = 0; i < dirsAndFiles[r].size();i++){

                        // CreateButton(int x, int y,int width, int height, int id, wchar_t *text)
                        wchar_t text[512];
                        const char *CDAF = dirsAndFiles[r][i].c_str();
                        mbstowcs(text,CDAF, 512);
                        if (text[0] == '$'){
                            continue;
                        }
                        SendMessage(hListBox, LB_ADDSTRING, 0,
                    (LPARAM)text);
                    }
                }
            }
            // const char *between2 = text.c_str();
            // mbstowcs(Math,between2, 512); 
            // SetDlgItemText(hwnd,20,Math);

        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);



            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

            EndPaint(hwnd, &ps);
        }
        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
