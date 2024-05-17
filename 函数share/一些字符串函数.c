//将字符数组中字母全部改为小写
void LOW(char *word){
  int i;
  int length=strlen(word);
  for(i=0;i<length;i++){
    if(isalpha(word[i])){
      word[i]=tolower(word[i]);
    }
  }
}

//将字符数组中的非字母字符删去
void remove_non_alpha(char* arr) {
    int i, j;
    int n=strlen(arr);
    for(i = 0; i < n; i++) {
        if(!isalpha(arr[i])) {
            for(j = i; j < n-1; j++) {
                arr[j] = arr[j+1];
            }
            arr[n-1] = '\0';
            n--;
            i--;
        }
    }
    for(i = 0; i < n; i++) {
        if(arr[i] == ' ' && arr[i+1] == ' ') {
            for(j = i; j < n-1; j++) {
                arr[j] = arr[j+1];
            }
            arr[n-1] = '\0';
            n--;
            i--;
        }
    }
}

//从外部文件中读取所有内容
void getArticle(FILE *fp1)
{
	ch=fgetc(fp1);
	i=0;
	while(ch!=EOF)
	{
		if(isalpha(ch)) Word[i]=tolower(ch);
		else Word[i]=ch;
		i++;
		ch=fgetc(fp1);
	}
}

//从读取的文章中提取出单词
void getWord()
{
	for(i=0;i<strlen(Word);i++)
	{
		if(isalpha(Word[i]))  //找到单词开头
		{
			for(j=i;j<strlen(Word);j++)
			{
				if(!isalpha(Word[j]))  //找到单词结尾
				{
					break;
				}
			}
			memset(tmp,'\0',sizeof(tmp));
			for(k=0;k<j-i;k++)
			{
				tmp[k]=Word[i+k]; //tmp存储的是单词;
			}

			root=DBST_insert(root,tmp); //通过根节点构造BST
			i=j;
		}
		else	continue;
	}
}
