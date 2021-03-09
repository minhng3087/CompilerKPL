#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH_WORD 100
#define LIST_WORD 10000007

typedef struct Word{
  char* word;
  int count;
  char *line;
}Word;

typedef struct StopWords{
  char* words[LENGTH_WORD];
  int size;
}StopWords;

typedef struct ListWord{
  Word table[LIST_WORD];
  int size;
}ListWord;

StopWords stop;
ListWord listWord;


void strlwr(char* s) {
  int c = 0;
   while (s[c] != '\0') {
      if (s[c] >= 'A' && s[c] <= 'Z') {
         s[c] = s[c] + 32;
      }
      c++;
   }
}

int checkChar(char c){
  int i;
  char* str_check = ".?!";
  for(i=0;i<strlen(str_check);i++){
    if(c == str_check[i])
      return 1;
  }
  return 0;
}

char* convertString(int num){
  char str[10];
  sprintf(str,"%d",num);
  size_t len = strlen(str);
  char* result = (char*)malloc(len+1);
  strcpy(result,str);
  return result;
}

char* concat(char* s1, char* s2){
   const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1); 
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1); 
    return result;
}


int findWordStop(char *str){
  int i;
  for(i = 0; i < stop.size; i++){
    int k = strcmp(str,stop.words[i]);
    if(k == 0){
      return 0;
    }
  }
  return 1;
}

int split (char *str, char c, char ***arr)
{
    int count = 1;
    int token_len = 1;
    int i = 0;
    char *p;
    char *t;
 
    p = str;
    while (*p != '\0')
    {
        if (*p == c)
            count++;
        p++;
    }
 
    *arr = (char**) malloc(sizeof(char*) * count);
    if (*arr == NULL)
        exit(1);
 
    p = str;
    while (*p != '\0')
    {
        if (*p == c)
        {
            (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
            if ((*arr)[i] == NULL)
                exit(1);
 
            token_len = 0;
            i++;
        }
        p++;
        token_len++;
    }
    (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
    if ((*arr)[i] == NULL)
        exit(1);
 
    i = 0;
    p = str;
    t = ((*arr)[i]);
    while (*p != '\0')
    {
        if (*p != c && *p != '\0')
        {
            *t = *p;
            t++;
        }
        else
        {
            *t = '\0';
            i++;
            t = ((*arr)[i]);
        }
        p++;
    }
 
    return count;
}

void init(){
  stop.size = 0;
  listWord.size = 0;
}

int checkWord(char* str, int new_word){ //Kiem tra chu cai dau la chu in hoac co phai bat dau cua 1 cau khong??
  if (strlen(str) < 1 || ('A' <= str[0] && 'Z'>= str[0]) && !new_word){
    return 0;
  }
  strlwr(str);
  return findWordStop(str);
}
      
void addWord(char* str,int line){ //Them tu moi
  int i, j, c = 0;
  char **arr = NULL;
  for(i=0; i < listWord.size; i++){ //Kiem tra trong list tu hien co 
    int k = strcmp(str,listWord.table[i].word);
    if (k == 0){// xuat hien tu do
      listWord.table[i].count++;
      c = split(listWord.table[i].line, ',', &arr);
      if(strcmp(arr[c-1], convertString(line)) !=0) {
        char* buff = concat(listWord.table[i].line,concat(",",convertString(line)));
        listWord.table[i].line = buff;
      } 
      return;
    } else if (k < 0){  // sap xep lai theo thu tu bang chu cai
      for (j = listWord.size; j > i ; j--){
        listWord.table[j] = listWord.table[j-1];
      }
      Word word;
      word.word = str;
      word.count = 1;
      word.line = convertString(line);
      listWord.table[i] = word;
      listWord.size++;
      return;
    }
  }
  Word word;
  word.word = str;
  word.count = 1;
  word.line = convertString(line);
  listWord.table[(listWord.size)++] = word;
}

void readFile(char* textfile, char* stopfile) {
  FILE *file;
  int line=1,new_word_char=1,i=0; 
  char c,word[100];

  if((file = fopen(stopfile,"r")) == NULL){
    printf("Error\n");
  }
  while(fscanf(file,"%s",word) == 1){
    char* buff = (char*)malloc((strlen(word)+1)*sizeof(char));
    strcpy(buff,word);
    strlwr(buff);
    stop.words[(stop.size)++] = buff;
  }
  fclose(file);
  if((file = fopen(textfile,"r")) == NULL){
    printf("Error\n");
  }
  while((c=fgetc(file)) != EOF){
    if(isalpha(c)){
      word[i++] = c;
    } else {
      word[i] = (char)(0);
      if(checkWord(word,new_word_char)){
        char* buff = (char*)malloc(sizeof(char)*(strlen(word)+1));
        strcpy(buff,word);
        addWord(buff,line);
      }
      if (c == '\n'){
        line++;
      }
      new_word_char = checkChar(c);
      i = 0; //restart word
    }
  }
  fclose(file);
}

int main(){
  init();
  int i;
  readFile("vanban.txt", "stopw.txt");
  for(i = 0; i < listWord.size; i++){
    Word word = listWord.table[i];
    printf("%s %d %s\n",word.word,word.count,word.line);
  }
}