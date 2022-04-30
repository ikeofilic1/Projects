/*
Ikechukwu Ofili.
ikeofilic1@gmail.com

This is my take on the popular hangman game. Enjoy!!
The user has to guess a word only given the length of the word. The guessed characters that are correct are revealed.

Guidelines for the text files:
File should preferrably be of type TXT
Each file must have the number of words in it as the first string in the file itself

Edit:
New "loading" line.
Files no longer need to be in a folder.
Stopped stray letters from counting as a bad guess.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> // for call to time() in srand(time(NULL))

#define DEBUG 0 // 1-development mode, prints more info; 0 - user mode, prints less
int game_end(int win,char word[]);
int play_session(int level);
void print_scaffold(int fails,int level,int guesses);
int playing(int fails,int guesses,char word[],char used[],char choice[]);

int main(){
     int repeat=0,score,games;
     char level=1,c;

     if (DEBUG==1) {
         srand(1); // the same sequence of random numbers will be generated for each run
     }
     else {
         srand(time(NULL)); // a different sequence of random numbers will be generated with each run
     }
     while (level!=0){
         if(repeat==0){
             do{
                 printf("Choose difficulty level (exit the game: 0, easy: 1, medium: 2, hard: 3): ");
                 scanf(" %c", &level);
                 scanf("%c", &c);//edit: stray letter fix
             }while(!(48<=level)||!(level<52)||c!='\n');//level is compared with ASCII for 0-3
            score=0;
            games=0;
            level=level-48;//level is changed to characters with ASCII code 0-3 for better int casting
         }
         if(level!=0){
            repeat=play_session((int)level);
            games++;
            if(repeat==0||repeat==1)
                score++;
            if(repeat==3)
                repeat=0;
            if(repeat==0){
                printf("\n*****************************\n");
                printf("*  Session score:%4d/%4d  *\n",score,games);
                printf("*****************************\n");
            }
         }
     }
     printf("\nThanks for playing my game! Goodbye!\n");
}

int play_session(int level){
    int ct=0,r,N,guesses,fails=0,win=0,lenw;
    char word[51],choice[51],used[31]="\0";
    FILE *f;

    if(level==1){
        f=fopen("lost.txt","r"); //replace this with file for easy
        fscanf(f,"%d",&N);
        guesses=10;
        printf("\nLoading file: easy.txt....\n");
    }
    if(level==2){
        f=fopen("lost.txt","r"); //replace this with file for medium
        fscanf(f,"%d",&N);
        guesses=8;
        printf("Loading file: medium.txt....\n");
    }
    if(level==3){
        f=fopen("lost.txt","r"); //replace this with file for hard
        fscanf(f,"%d",&N);
        guesses=5;
        printf("Loading file: hard.txt....\n");
    }

    r=rand()%N+1;
    while(ct<r){
        fscanf(f,"%s",word);
        ct++;
    }
    lenw=strlen(word);
    for (int i=0;i<lenw;i++){
      if(word[i]>96&&word[i]<123)
          word[i]=word[i]-32;
    }
    if (DEBUG) printf("-----Hidden word: |%s|",word);
    choice[lenw]='\0';
    fclose(f);

    for(ct=0;ct<lenw;ct++)
        choice[ct]='-';

    while(fails<=guesses&&!win){//Loop needs to be working for fails=guesses to print hanged man scaffold
        win=!strcmp(word,choice);//Case insensitive
        print_scaffold(fails,level,guesses);
        printf("Used letters: %s\n",used);
        printf("Number of bad guesses: %d (out of %d)\n",fails,guesses);
        printf("%s\n",choice);

        if(fails==guesses)//To exit the loop if user loses.
            fails++;

        if(win||(fails>=guesses)){
            ct=game_end(win,word);
        }
        if(!win&&(fails<guesses)){
            fails=playing(fails,guesses,word,used,choice);
        }
    }
    return ct;
}

void print_scaffold(int fails,int level,int guesses){
    printf("\n\n\n\n\n\n\n\n\n\nLevel: %d\n\n\n",level);
    if(fails==0&&level==1){
        printf("------|\n|     \n|\n");
        printf("|\n|\n|\n|\n-------------\n\n");
    }
    else if((fails==1&&level==1)||fails==0){
        printf("------|\n|     |\n|\n");
        printf("|\n|\n|\n|\n-------------\n\n");
    }
    if((fails==1&&level==2)||(fails==3&&level==1)){
        printf("------|\n|     |\n|     O\n");
        printf("|\n|\n|\n|\n-------------\n\n");
    }
    if(fails==2&&level==1){
        printf("------|\n|     |\n|    (\n");
        printf("|\n|\n|\n|\n-------------\n\n");
    }
    if((fails==2&&level==2)||(fails==4&&level==1)||(fails==1&&level==3)){
        printf("------|\n|     |\n|     O\n");
        printf("|     |\n|\n|\n|\n");
        printf("-------------\n\n");
    }
    if((fails==3&&level==2)||(fails==5&&level==1)){
        printf("------|\n|     |\n|     O\n");
        printf("|     |\n|     |\n|\n|\n");
        printf("-------------\n\n");
    }
    if((fails==4&&level==2)||(fails==6&&level==1)||(fails==2&&level==3)){
        printf("------|\n|     |\n|     O\n");
        printf("|     |\n|     |\n|     |\n|\n");
        printf("-------------\n\n");
    }
    if((fails==5&&level==2)||(fails==7&&level==1)||(fails==3&&level==3)){
        printf("------|\n|     |\n|     O\n");
        printf("|     |\n|    /|\n|     |\n|\n");
        printf("-------------\n\n");
    }
    if((fails==6&&level==2)||(fails==8&&level==1)||(fails==4&&level==3)){
        printf("------|\n|     |\n|     O\n");
        printf("|     |\n|    /|\\\n|     |\n|\n");
        printf("-------------\n\n");
    }
    if((fails==7&&level==2)||(fails==9&&level==1)){
        printf("------|\n|     |\n|     O\n");
        printf("|     |\n|    /|\\\n|     |\n|    /\n");
        printf("-------------\n\n");
    }
    if(fails==guesses){
        printf("------|\n|     |\n|     O\n");
        printf("|     |\n|    /|\\\n|     |\n|    / \\\n");
        printf("-------------\n\n");
    }
}

int playing(int fails,int guesses,char word[],char used[],char choice[]){
    int lenu=strlen(used),lenw=strlen(word),ct,i;
    char ch,c;
    printf("\nEnter a letter (0 to quit game): ");
    scanf(" %c",&ch);
    if(ch=='0'){
        do{
            printf("\nAre you sure, you will lose current game (0-no 1-yes,quit)");
            scanf(" %c",&ch);
            scanf("%c",&c);
        }while((ch!='0'&&ch!='1')||c!='\n');
        if(ch=='1'){
            fails=guesses;
            ch='0';
        }
    }
    else{
        if(ch>64&&ch<91)//Converts capital letters to lowercase for uniformity(Robust system 2)
            ch=ch+32;
        if(lenu==0){
           used[0]=ch;
           used[1]='\0';
        }

        for(i=0;i<lenu;i++){//Code to add the user-inputed letter to used letters and checks if it's already there
            if(ch==used[i])
                break;
            if(i==lenu-1){
                used[lenu]=ch;
                used[lenu+1]='\0';
            }
        }
        for(i=0;i<lenw;i++){
            if(ch-32==choice[i]){//Converts ch to uppercase and then checks if it's already revealed before and counts as fail if true.
                fails++;
                break;
            }
        }
        for(i=0,ct=0;i<lenw;i++){//Loop to check if ch is in word
            if(ch-32==word[i])
                choice[i]=word[i];
            else
                ct++;
        }
        if(ct==lenw)
            fails++;
    }
    return fails;
}

int game_end(int win,char word[]){
    int N;
    char again,c;
    if(win)
        printf("\nYou won!\n");
    else
        printf("\nYou lost.\nThe word was: %s\n",word);
    do{
        printf("\nDo you want to play this level again?(0-no 1-yes) ");
        scanf(" %c",&again);
        scanf("%c",&c);
    }while((again!='0'&&again!='1')||c!='\n');

    if(win&&(again=='0'))
        N=0;
    else if(win&&(again=='1'))
        N=1;
    else if(again=='1')
        N=2;
    else
        N=3;
    return N;
}
