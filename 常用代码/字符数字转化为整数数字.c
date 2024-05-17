
char ch[] = "600";
int a, s = 0;
for (a = 0; ch[a] >= '0' && ch[a] <= '9'; a++)
    s = 10 * s + ch[a] - '0';
printf("%d", s);

