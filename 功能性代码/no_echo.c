//
//  other linker flag adding "-lcurses"

#include <curses.h>



int main(int argc, const char * argv[])
{
    char test[50];
    printf("input without echo:");
    initscr();
    noecho();
    scanf("%s", test);
    echo();
    printf("%s\n", test);
    return 0;
}

