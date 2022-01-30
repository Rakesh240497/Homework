#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct variables
{
   char* keywords;
   int keyword_count;
};

void Update_Table(char* word,struct variables KW_Table[], int argc)  
{
    int i; 
    while(word!=NULL){
        for(i=0;i<argc-1;i++){
            if(strstr(word,"\n")){
                word[strlen(word)-1] = '\0';
            }
            if(strcmp(word, KW_Table[i].keywords)==0){
                KW_Table[i].keyword_count++;
            }
        }
        word = strtok(NULL," ");
    }
}
 
void init(struct variables KW_Table[], int argc){
    char *line = NULL;
    char *words;
    size_t maxlen = 0;
    ssize_t n;
    while ((n = getline(&line, &maxlen, stdin)) > 0)
    {
        char *word = strtok(line," ");
        Update_Table(word, KW_Table, argc);
    }
    free(line);
}

void display(struct variables KW_Table[], int argc){
    int i; 
    for(i=0;i<argc-1;i++){
        printf("%s\t%d\n",KW_Table[i].keywords,KW_Table[i].keyword_count);
    }
}

int main(int argc, char *argv[])
{
    int i;
    struct variables *KW_Table = malloc (argc * sizeof (struct variables)); 

    if (argc >= 1)
    {
        for (i = 0; i < argc-1; i++)
        {
            KW_Table[i].keywords = argv[i+1]; 
            KW_Table[i].keyword_count= 0; 
        }
    }

    init(KW_Table, argc);
    display(KW_Table, argc);
    free(KW_Table);
    return 0;
}