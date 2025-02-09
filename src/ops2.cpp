#if defined(_WIN32)
#include <windows.h>

int WINAPI WinMain(HINSTANCE , HINSTANCE , LPSTR , int )
#else
int main()
#endif
{
    return 0;
}
