#include <Windows.h>
#include <WinUser.h>
#include <string>
#include <iostream>

HWND FindWindowRecursive(HWND hParent, LPCWSTR szClass, LPCWSTR szCaption);
BOOL CALLBACK printWindowClassName(HWND hwnd, LPARAM lParam);

int main(char* argv[], int argc)
{
    HWND oParentHandle = FindWindow(TEXT("SpotifyMainWindow"), NULL);

    HWND oChildHandle = FindWindowRecursive(oParentHandle, NULL, TEXT("Chrome Legacy Window"));

    LRESULT oResult = SendMessage(oChildHandle,
                                  WM_LBUTTONDOWN,
                                  MK_LBUTTON,
                                  0x03BC0080); // 128, 956

    oResult = SendMessage(oChildHandle,
                          WM_LBUTTONUP,
                          MK_LBUTTON,
                          0x03BC0080); // 128, 956
}

HWND FindWindowRecursive(HWND hParent, LPCWSTR szClass, LPCWSTR szCaption)
{
    HWND hResult = FindWindowEx(hParent, NULL, szClass, szCaption);
    if (hResult != NULL)
    {
        return hResult; // found it
    }

    // enumerate all childs and if found one that has childs go in
    HWND hChild = FindWindowEx(hParent, NULL, NULL, NULL); // first child

    if (hChild != NULL)
    {
        // let's enumerate
        do
        {
            hResult = FindWindowRecursive(hChild, szClass, szCaption);
            if (hResult != NULL)
            {
                return hResult;  // found it
            }
        } while ((hChild = GetNextWindow(hChild, GW_HWNDNEXT)) != NULL);
    }
    else
    {
        return NULL; // no childs, so no window was found
    }
}

void ListAllChildWindows(HWND p_hParent)
{
    EnumChildWindows(p_hParent, printWindowClassName, 0);
}

BOOL CALLBACK printWindowClassName(HWND hwnd, LPARAM lParam)
{
    
    std::cout <<  
    return TRUE;
}