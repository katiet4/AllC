#ifndef UNICODE
#define UNICODE
#endif 

#include <iostream>
#include <vector>

#include <windows.h>
using namespace std;
void ClearForMath(wchar_t (&num)[100]){
        for(int i = 0; i < 99; i++)
        {
            num[i] = '\0';
        }
}
class Polsk
{
private:
    vector <char> priorityAct = {'/','*','+','-','^', '(', ')'};
    vector <int> priorityNum = {4, 4, 3, 3, 5, 0, 0};
    int indexOfActions = -1, indexOfnumbers = -1, indexOfNum = 0;
    vector <int> numbers;
    vector <char> actions;
    
    
    void Counting()
    {
        int NumOne = numbers[indexOfnumbers-1];
        int NumTwo = numbers[indexOfnumbers];
        switch (actions[indexOfActions]){
            case '-':
            {
                
                indexOfnumbers--;
                numbers.pop_back();
                numbers.pop_back();
                numbers.push_back(NumOne-NumTwo);
                break;
            }
            case '+':
            {
                indexOfnumbers--;
                numbers.pop_back();
                numbers.pop_back();
                numbers.push_back(NumOne+NumTwo);
                break;
            }
            case '*':
            {
                indexOfnumbers--;
                numbers.pop_back();
                numbers.pop_back();
                numbers.push_back(NumOne*NumTwo);
                break;
            }
            case '/':
            {
                indexOfnumbers--;
                numbers.pop_back();
                numbers.pop_back();
                numbers.push_back(NumOne/NumTwo);
                break;
            }
            case '^':
            {
                indexOfnumbers--;
                numbers.pop_back();
                numbers.pop_back();
                int result = 1;
                for(int i = 0; i < NumTwo; i++){
                    result*=NumOne;
                }
                numbers.push_back(result);
                break;
            }

        }
        indexOfActions--;
        actions.pop_back();
    }
    void Clear(char (&num)[98]){
        for(int i = 0; i < 99; i++)
        {
            num[i] = '\0';
        }
    }

    int FindIndex(char action){
        int i = 0;
        for(;;i++){
            if(priorityAct[i] == action)
                return i;
            //Error
            if(i == 50)
                return 404;
        }
    }
public:

    int polsk(wchar_t Math[100])
    {
        
        int len = wcslen(Math)-1;
        char num[98]{};
        for(int i = 0; i <= len; i++)
        {
            // identification 
            if (Math[i] == '0' || Math[i] == '1' || Math[i] == '2' || Math[i] == '3' ||
                    Math[i] == '4' || Math[i] == '5' || Math[i] == '6' || Math[i] == '7' ||
                    Math[i] == '8' || Math[i] == '9')
                {
                    num[indexOfNum++] = Math[i];

                    continue;
                }

            else{
                if(strlen(num) != 0){
                numbers.push_back(atoi(num));
                Clear(num);
                indexOfNum=0;
                indexOfnumbers++;}

                if (indexOfActions == -1){
                    actions.push_back(Math[i]);
                    indexOfActions++;
                    continue;
                }

                int action = priorityNum[FindIndex(Math[i])];

                
                if(action > priorityNum[FindIndex(actions[indexOfActions])] && Math[i] != '(' && Math[i] != ')' )
                {
                    actions.push_back(Math[i]);
                    indexOfActions++;
                    continue;
                }

                else if(Math[i] == '('){
                    actions.push_back(Math[i]);
                    indexOfActions++;
                    continue;
                }

                else if(Math[i] == ')')
                {
                    while(actions[indexOfActions] != '(')
                    {
                        Counting();
                    }
                    actions.pop_back();
                    indexOfActions--;
                    continue;
                }

                else
                {
                    while(action <= priorityNum[FindIndex(actions[indexOfActions])])
                    {
                        Counting();
                    }
                    actions.push_back(Math[i]);
                    indexOfActions++;
                    continue;
                }

            }
            
        }
        if(strlen(num) != 0)
        {
            numbers.push_back(atoi(num));
            indexOfnumbers++;
        }

        while(numbers.size()>1)
                    {
                        Counting();
                    }
        return numbers[0];
    }
    
};
HWND hwnd;
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

wchar_t Polsc(wchar_t Math[100]){
 vector <int> numbers;
 vector <char> actions;

}

void CreateButton(int x, int y,int width, int height, int id, wchar_t *text){
CreateWindow(L"button", text, WS_CHILD|WS_VISIBLE|WB_LEFT,
     x, y, width, height, hwnd, (HMENU) id, NULL, NULL);
}

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

    hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_CAPTION | WS_SYSMENU,            // Window style

        // Size and position
        100, 100, 305, 240,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }
    CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"",WS_CHILD|WS_VISIBLE|WB_LEFT,
     10, 10, 280, 20, hwnd, (HMENU) 20, NULL, NULL);
    CreateButton(10, 40, 40, 40, 0, L"0");
    CreateButton(50, 40, 40, 40, 1, L"1");
    CreateButton(90, 40, 40, 40, 2, L"2");
    CreateButton(130, 40, 40, 40, 3, L"3");
    CreateButton(170, 40, 40, 40, 4, L"4");
    CreateButton(210, 40, 40, 40, 5, L"5");
    CreateButton(250, 40, 40, 40, 6, L"6");

    CreateButton(10, 80, 40, 40, 7, L"7");
    CreateButton(50, 80, 40, 40, 8, L"8");
    CreateButton(90, 80, 40, 40, 9, L"9");
    CreateButton(130, 80, 40, 40, 10, L"+");
    CreateButton(170, 80, 40, 40, 11, L"-");
    CreateButton(210, 80, 40, 40, 12, L"/");
    CreateButton(250, 80, 40, 40, 13, L"*");

    
    CreateButton(210, 120, 40, 40, 19, L"^");
    CreateButton(130, 120, 40, 40, 17, L"(");
    CreateButton(170, 120, 40, 40, 18, L")");
    CreateButton(10, 120, 40, 40, 14, L"=");
    CreateButton(50, 120, 40, 40, 15, L"Clear");
    CreateButton(90, 120, 40, 40, 16, L"Del");
    CreateButton(250, 120, 40, 40, 13, L"6");

    CreateButton(10, 160, 40, 40, 7, L"6");
    CreateButton(50, 160, 40, 40, 8, L"6");
    CreateButton(90, 160, 40, 40, 9, L"6");
    CreateButton(130, 160, 40, 40, 10, L"6");
    CreateButton(170, 160, 40, 40, 11, L"6");
    CreateButton(210, 160, 40, 40, 12, L"6");
    CreateButton(250, 160, 40, 40, 13, L"6");
    

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
    switch (uMsg)
    {
    case WM_COMMAND:{
            
            wchar_t Math[100];
            GetDlgItemText(hwnd,20,Math, 100);
            switch (LOWORD(wParam)){
            case 0:
                wcscat_s(Math,L"0");SetDlgItemText(hwnd,20,Math);
                break;
            case 1:
                wcscat_s(Math,L"1");SetDlgItemText(hwnd,20,Math);
                break;
            case 2:
                wcscat_s(Math,L"2");SetDlgItemText(hwnd,20,Math);
            break;
                case 3:
                wcscat_s(Math,L"3");SetDlgItemText(hwnd,20,Math);
            break;
                case 4:
                wcscat_s(Math,L"4");SetDlgItemText(hwnd,20,Math);
            break;
                case 5:
                wcscat_s(Math,L"5");SetDlgItemText(hwnd,20,Math);
            break;
                case 6:
                wcscat_s(Math,L"6");SetDlgItemText(hwnd,20,Math);
            break;
            case 7:
                wcscat_s(Math,L"7");SetDlgItemText(hwnd,20,Math);
                break;
            case 8:
                wcscat_s(Math,L"8");SetDlgItemText(hwnd,20,Math);
                break;
            case 9:
                wcscat_s(Math,L"9");SetDlgItemText(hwnd,20,Math);
                break;
            case 10:
                wcscat_s(Math,L"+");SetDlgItemText(hwnd,20,Math);
                break;
            case 11:
                wcscat_s(Math,L"-");SetDlgItemText(hwnd,20,Math);
                break;
            case 12:
                wcscat_s(Math,L"/");SetDlgItemText(hwnd,20,Math);
                break;
            case 13:
                wcscat_s(Math,L"*");SetDlgItemText(hwnd,20,Math);
                break;
            case 17:
                wcscat_s(Math,L"(");SetDlgItemText(hwnd,20,Math);
                break;
            case 18:
                wcscat_s(Math,L")");SetDlgItemText(hwnd,20,Math);
                break;
            case 19:
                wcscat_s(Math,L"^");SetDlgItemText(hwnd,20,Math);
                break;
            case 14:
            {
                Polsk P;
                char *num = new char[100];
                itoa(P.polsk(Math), num, 10);
                mbstowcs(Math,num, 100);
                SetDlgItemText(hwnd,20,Math);
                delete [] num;
                break;
            }
            case 15:
            {

               ClearForMath(Math);
               SetDlgItemText(hwnd,20,Math);
               break;
                
            }
            case 16:
            {

               int len = wcslen(Math);
               Math[len-1] = '\0';
               SetDlgItemText(hwnd,20,Math);
               break;
                
            }
           }
            
            
        break;}
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

