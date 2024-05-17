#include <stdio.h>
void inverp(char *a)
{
    if ( *a == '\0' )
        return;
    inverp(a+1);
    printf("%c",*a);
}
int main()
{
    char s[10] = "hello!";
    inverp(s);

    return 0;
}