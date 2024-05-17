/*下面程序的功能是将已按升序排好的两个字符串a和b中
的字符按升序并归到字符串c中。*/
#include <stdio.h>
#include <string.h>
int main()
{
    char a[] = "acegikm";
    char b[] = "bdfhjlnpq";
    char c[80], *p;
    int i = 0, j = 0, k = 0;
    while (a[i] != '\0' && b[j] != '\0')
    {
        if (a[i] < b[j])
        {
            c[k++]=a[i++];
        }
        else
        {
            c[k++]=b[j++];
        }
    }
    c[k] = '\0';
    if (a[i]=='\0')
        p = b + j;
    else
        p = a + i;
    strcat(c, p);
    puts(c);

    return 0;
}