#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define maxlen 50
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"
// All of struct
struct player {
    char playerName[maxlen];
    int attackingPowers;
    int defaultAttackPowers;
    int defaultDefencePowers;
    int defencingPowers;
    int value, idPlayer;
    char teamPlayers[maxlen];
};
struct team {
    struct player teamPlayers[8];
    char emailCoach[maxlen];
    char teamName[maxlen];
    int idTeam, defaultValue, countOfChampions, completeTeam, countOfPlayers;

};
struct user {
    char username[maxlen];
    char password[maxlen];
};
struct leagueStanding {
    char TeamName[maxlen];
    int  played, won, drawn, lost, gf, ga, gd, points;
};
// All of functions
void welcomeMessage();
void encrypt(char p[maxlen]);
void login();
void id_team();
void id_player();
void arrangeGame(struct team t[4]);
void coachAccount(struct team myTeam);
void adminAccount();
// Essential number:
//index0 = endMidSession ,index1 = endSession,index2 = countOfWeeks , index3 = transferWindow .

int main() {
    int arr[4] = {0,0,0,1};
    FILE *f ;
    f = fopen("saveEssentialsNum.txt", "r");
    if(f == NULL){
        fclose(f);
        f = fopen("saveEssentialsNum.txt", "w");
        for(int i=0;i<4;i++){
            fwrite(&arr[i],4,1,f);
        }
    }
    else{
        fclose(f);
    }
    fclose(f);
    login();
    return 0;
}
void welcomeMessage() {
    system("clear");
    printf(BLU "\n****************** Welcome to football league management **************");
    printf("\n1.Login");
    printf("\n2.forgot your password ??? ");
    printf("\n3.Exit");
    printf("\nPlease  enter Your choice : " RESET);
}
//This function performs the login function .
void encrypt(char p[maxlen]){
    for(int i=0;i<strlen(p);i++){
        p[i] = p[i] +3;
    }
}
void login() {
    int opt;
    int flag = 0, condition = 0;
    struct user  user1 , user[100];
    struct team team[100] ;
    welcomeMessage();
    scanf("%d", &opt);
    FILE *file;
    FILE *fp;
    switch (opt) {
        //login .
        case 1:
            while (!flag) {
                system("clear");
                printf( BLU"\n****************************************");
                printf("\nEnter your username : ");
                char usrn[maxlen], pswd[maxlen];
                scanf("%s", &usrn);
                printf("\nEnter your password : ");
                scanf("%s"RESET, &pswd);
                if ((flag == 0 && !strcmp(usrn, "admin") && !strcmp(pswd, "admin")) ||(flag == 0 && !strcmp(usrn, "Admin") && !strcmp(pswd, "Admin"))) {
                    adminAccount();
                }else if (flag == 0 && strcmp(usrn, "admin") && strcmp(pswd, "admin")){
                    file = fopen("users.txt", "r");
                    encrypt(pswd);
                    while (fread(&user1, sizeof(struct user), 1, file)) {
                        if (!strcmp(user1.username, usrn) && !strcmp(user1.password, pswd)) {
                            fp = fopen("teams.txt", "r");
                            fseek(fp, 0, SEEK_SET);
                            int i=0;
                            while(fread(&team[i], sizeof(struct team), 1, fp)){
                                if (!strcmp(team[i].teamName, usrn)) {
                                    flag = 1;
                                    coachAccount(team[i]);
                                }
                                i++;
                            }
                        }
                        else{
                            continue;
                        }
                    }
                    if(flag == 0)
                        printf(RED"\n Username or password is wrong!!!!"RESET);
                }
            }
            fclose(fp);
            fclose(file);
            break;
            //forgot password
        case 2:
            while (!condition) {
                system("clear");
                printf( BLU"\n****************************************");
                printf("\nEnter team name: ");
                char nTeam[maxlen], eCoach[maxlen];
                scanf("%s", &nTeam);
                printf("\nEnter email coach : ");
                scanf("%s", &eCoach);
                file = fopen("teams.txt", "r");
                int j =0;
                while (fread(&team[j], sizeof(struct team), 1, file)) {
                    if (!strcmp(team[j].teamName, nTeam) && !strcmp(team[j].emailCoach, eCoach)) {
                        char newPassword[maxlen];
                        printf("\nPlease enter new password :");
                        scanf("%s"RESET, &newPassword);
                        encrypt(newPassword);
                        fp = fopen("users.txt", "a+");
                        fseek(fp, 0, SEEK_END);
                        int siz = ftell(fp)/sizeof(struct user);
                        rewind(fp);
                        int i=0;
                        while (fread(&user[i], sizeof(struct user), 1, fp) && i <siz) {
                            if (!strcmp(user[i].username, nTeam)) {
                                strcpy(user[i].password, newPassword);
                            }
                            i++;
                        }
                        fclose(fp);
                        fclose(file);
                        fp = fopen("temp.txt", "w+");
                        for(i=0;i<siz; i++){
                            fwrite(&user[i], sizeof(struct user), 1, fp);
                        }
                        fseek(fp, 0, SEEK_SET);
                        file= fopen("users.txt","w");
                        i=0;
                        while(fread(&user[i], sizeof(struct user), 1, fp)){
                            fwrite(&user[i],sizeof(struct user),1,file);
                            i++;
                        }
                        fclose(file);
                        fclose(fp);
                        condition = 1;
                        printf(GRN"\n password changed."RESET);
                        break;
                    }
                    j++;
                }
                if (condition == 0) {
                    printf(RED"something is wrong"RESET);
                    continue;
                }
            }
            login();
            break;
        case 3:
            printf(RED"\n good bye "RESET);
            system("pause");
            break;
        default:
            printf(RED"something is wrong"RESET);
            login();
            break;
    }
}
void arrangeGame(struct team t[4]) {
    FILE*f = fopen("games.txt","a");
    //week1
    fwrite(&t[0].teamName,maxlen,1,f);
    fwrite(&t[3].teamName,maxlen,1,f);
    fwrite(&t[1].teamName,maxlen,1,f);
    fwrite(&t[2].teamName,maxlen,1,f);
    //week2
    fwrite(&t[0].teamName,maxlen,1,f);
    fwrite(&t[1].teamName,maxlen,1,f);
    fwrite(&t[2].teamName,maxlen,1,f);
    fwrite(&t[3].teamName,maxlen,1,f);
    //week3
    fwrite(&t[0].teamName,maxlen,1,f);
    fwrite(&t[2].teamName,maxlen,1,f);
    fwrite(&t[1].teamName,maxlen,1,f);
    fwrite(&t[3].teamName,maxlen,1,f);
    //week4
    fwrite(&t[2].teamName,maxlen,1,f);
    fwrite(&t[3].teamName,maxlen,1,f);
    fwrite(&t[1].teamName,maxlen,1,f);
    fwrite(&t[0].teamName,maxlen,1,f);
    //week5
    fwrite(&t[2].teamName,maxlen,1,f);
    fwrite(&t[1].teamName,maxlen,1,f);
    fwrite(&t[3].teamName,maxlen,1,f);
    fwrite(&t[0].teamName,maxlen,1,f);
    //week6
    fwrite(&t[2].teamName,maxlen,1,f);
    fwrite(&t[0].teamName,maxlen,1,f);
    fwrite(&t[1].teamName,maxlen,1,f);
    fwrite(&t[3].teamName,maxlen,1,f);
    fclose(f);
}

void coachAccount(struct team  myTeam) {
    FILE *file;
    FILE *fp;
    FILE *f = fopen("saveEssentialsNum.txt", "r");
    int arr[4], i = 0, j;
    while (fread(&arr[i], 4, 1, f)) {
        i++;
    }
    fclose(f);
    int countOfWeeks = arr[2], transferWindow = arr[3], endMidSession = arr[0], endSession = arr[1];
    system("clear");
    printf(BLU"\n***********************");
    printf("\n1=> buy a player ");
    printf("\n2=> sell a player ");
    if (transferWindow == 1) {

        printf("\n3=> submit squad ");
    } else {
        printf("\n3=> select squad ");
    }
    printf("\n4=> league Standing ");
    printf("\n5=> Fixtures ");
    printf("\n6=> Upcoming Opponent ");
    printf("\n7=> Change Password ");
    printf("\n8=> Exit ");
    int command;
    printf("\nPlease enter command :");
    scanf("%d"RESET, &command);
    system("clear");
    switch (command) {
        case 1 :
            if (transferWindow == 0) {
                printf(RED"\nTransfer time is up!!!"RESET);
                coachAccount(myTeam);
            } else {
                // The first task is to sort the players by their price .
                file = fopen("players.txt", "r");
                struct player p1;
                struct player *p;
                fseek(file, 0, SEEK_END);
                int n = ftell(file) / sizeof(struct player);
                p = (struct player *) calloc(n, sizeof(struct player));
                rewind(file);
                for (i = 0; i < n; i++) {
                    fread(&p[i], sizeof(struct player), 1, file);
                }
                fclose(file);
                for (i = 0; i < n; i++) {
                    for (j = i + 1; j < n; j++) {
                        if (p[i].value < p[j].value) {
                            p1 = p[i];
                            p[i] = p[j];
                            p[j] = p1;
                        }
                    }
                }
                file = fopen("players.txt", "w");
                for (i = 0; i < n; i++) {
                    fwrite(&p[i], sizeof(struct player), 1, file);
                }
                fclose(file);
                // next .
                file = fopen("players.txt", "r");
                printf(BLU"\n******************************************************");
                printf("\n-Id----Name----Attackpower----Defensepower----Value :\n");
                for (i = 0; i < n; i++) {
                    fread(&p[i], sizeof(struct player), 1, file);
                    if (!strcmp(p[i].teamPlayers, "Free agent")) {
                        printf("%d       %s        %d        %d          %d  \n", p[i].idPlayer, p[i].playerName, p[i].defaultAttackPowers,
                               p[i].defaultDefencePowers, p[i].value);
                    }
                }
                fclose(file);
                int id;
                printf("\nEnter ID Player : ");
                scanf("%d"RESET, &id);
                for (i = 0; i < n; i++) {
                    if (p[i].idPlayer == id) {
                        if (p[i].value <= myTeam.defaultValue && myTeam.countOfPlayers <= 8) {
                            strcpy(p[i].teamPlayers, myTeam.teamName);
                            myTeam.defaultValue -= p[i].value;
                            myTeam.countOfPlayers += 1;
                            for(j=0;!strcmp(myTeam.teamPlayers[j].teamPlayers,myTeam.teamName);j++){}
                            myTeam.teamPlayers[j] = p[i];
                        } else {
                            printf(RED"sorry . you can not buy this player !!!"RESET);
                        }
                    }
                }
                // update file players.
                fp = fopen("temp.txt", "w");
                for (i = 0; i < n; i++) {
                    fwrite(&p[i], sizeof(struct player), 1, fp);
                }
                fclose(fp);
                fp = fopen("temp.txt", "r");
                file = fopen("players.txt", "w");
                i = 0;
                while (fread(&p[i], sizeof(struct player), 1, fp)) {
                    fwrite(&p[i], sizeof(struct player), 1, file);
                    i++;
                }
                fclose(fp);
                fclose(file);
                // update file teams .
                struct team updateTeam[100];
                file = fopen("teams.txt", "r");
                i=0 ;
                fseek(file,0,SEEK_END);
                int size = ftell(file) / sizeof(struct team) ;
                rewind(file);
                for(i=0;i<size;i++){
                    fread(&updateTeam[i], sizeof(struct team), 1, file);
                    if (!strcmp(updateTeam[i].teamName, myTeam.teamName) && !strcmp(updateTeam[i].emailCoach, myTeam.emailCoach)) {
                        updateTeam[i] = myTeam;
                    }
                }
                fclose(file);
                fp = fopen("temp.txt", "w");
                for(i=0;i<size; i++){
                    fwrite(&updateTeam[i], sizeof(struct team), 1, file);
                }
                fclose(fp);
                fp = fopen("temp.txt", "r");
                file = fopen("teams.txt", "w");
                i=0;
                while (fread(&updateTeam[i], sizeof(struct team), 1, fp)) {
                    fwrite(&updateTeam[i], sizeof(struct team), 1, file);
                    i++;
                }
                fclose(file);
                fclose(fp);
                coachAccount(myTeam);
                break;
            }
        case 2 :
            if (transferWindow == 0) {
                printf(RED"\n************************");
                printf("Transfer time is up!!!"RESET);
                coachAccount(myTeam);
            } else {
                file = fopen("teams.txt", "r");
                fseek(file, 0, SEEK_END);
                int size= ftell(file) /sizeof(struct team);
                rewind(file);
                struct team delTeam[size];
                i = 0;
                j=0;
                printf(BLU"\n******************************************************");
                printf("\n-Id----Name----Attackpower----Defensepower----Value :\n"RESET);
                while (fread(&delTeam[j], sizeof(struct team), 1, file)) {
                    if (!strcmp(delTeam[j].teamName, myTeam.teamName)) {
                        while (!strcmp(delTeam[j].teamPlayers[i].teamPlayers,myTeam.teamName)) {
                            printf(BLU"%d      %s         %d      %d         %d  \n"RESET, delTeam[j].teamPlayers[i].idPlayer,
                                   delTeam[j].teamPlayers[i].playerName, delTeam[j].teamPlayers[i].defaultAttackPowers,
                                   delTeam[j].teamPlayers[i].defaultDefencePowers, delTeam[j].teamPlayers[i].value);
                            i++;
                        }
                    }
                    j++;
                }
                fclose(file);
                file = fopen("teams.txt", "r");
                int id;
                fp = fopen("players.txt", "r");
                struct player p[800];
                fseek(fp,0,SEEK_END);
                int n = ftell(fp)/sizeof(struct player);
                rewind(fp);
                printf("\n Enter Id Player ");
                scanf("%d"RESET, &id);
                i = 0;
                j=0;
                while (fread(&delTeam[j], sizeof(struct team), 1, file)) {
                    if (!strcmp(delTeam[j].teamName, myTeam.teamName)) {
                        while (!strcmp(delTeam[j].teamPlayers[i].teamPlayers,myTeam.teamName)) {
                            if (delTeam[j].teamPlayers[i].idPlayer == id) {
                                strcpy(delTeam[j].teamPlayers[i].teamPlayers, "Free agent");
                                delTeam[j].defaultValue += delTeam[j].teamPlayers[i].value;
                                delTeam[j].countOfPlayers -= 1;
                                for (i=0; i < 8; i++) {
                                    delTeam[j].teamPlayers[i] = delTeam[j].teamPlayers[i + 1];
                                }
                                int h = 0;
                                while (fread(&p[h], sizeof(struct player), 1, fp)) {
                                    if (p[h].idPlayer == id) {
                                        strcpy(p[h].teamPlayers,"Free agent");
                                    }
                                    h++;
                                }
                            }
                        }
                    }
                }
                fclose(file);
                fclose(fp);
                //update player.
                fp = fopen("temp.txt", "w");
                for (i = 0; i < n; i++) {
                    fwrite(&p[i], sizeof(struct player), 1, fp);
                }
                fclose(fp);
                fp = fopen("temp.txt", "r");
                file = fopen("players.txt", "w");
                i = 0;
                while (fread(&p[i], sizeof(struct player), 1, fp)) {
                    fwrite(&p[i], sizeof(struct player), 1, file);
                    i++;
                }
                fclose(fp);
                fclose(file);
                //update team.
                struct team copy[size];
                file = fopen("temp.txt", "w");
                for(i=0;i<size; i++){
                    fwrite(&delTeam[i],sizeof(struct team), 1, file);
                }
                fclose(file);
                fp = fopen("teams.txt", "w");
                file = fopen("temp.txt", "r");
                i=0;
                while (fread(&copy[i], sizeof(struct team), 1, file)) {
                    fwrite(&copy[i], sizeof(struct team), 1, fp);
                }
                fclose(fp);
                fclose(file);
                coachAccount(myTeam);
            }
            break;
        case 3 :
            if (transferWindow == 1) { // Submit .
                if (myTeam.countOfPlayers == 8) {
                    i = 0;
                    file = fopen("teams.txt", "a+");
                    fseek(file,0,SEEK_END);
                    int size =ftell(file) / sizeof(struct team);
                    struct team subTeam[size], read[size];
                    rewind(file);
                    while (fread(&subTeam[i], sizeof(struct team), 1, file)) {
                        if (!strcmp(subTeam[i].teamName, myTeam.teamName)) {
                            subTeam[i].completeTeam = 1;
                        }
                        i++;
                    }
                    fclose(file);
                    fp = fopen("teams.txt", "w");
                    for(i=0;i<size;i++){
                        fwrite(&subTeam[i], sizeof(struct team), 1, fp);
                    }
                    fclose(fp);
                }
                printf(GRN"\nYour squad submited successfully"RESET);
                coachAccount(myTeam);
            } else {
                int id;
                struct player selectPlayer[5];
                printf(BLU"\n******************************************************");
                printf("\n-Id----Name----Attackpower----Defensepower----Value :\n"RESET);
                for (i = 0; i < 8; i++) {
                    printf(" %d     %s        %d           %d            %d  \n", myTeam.teamPlayers[i].idPlayer, myTeam.teamPlayers[i].playerName,
                           myTeam.teamPlayers[i].defaultAttackPowers, myTeam.teamPlayers[i].defaultDefencePowers,
                           myTeam.teamPlayers[i].value);
                }
                for (i = 0; i < 5; i++) {
                    printf(BLU"\n Enter the ID of the player you want to be in the squad :");
                    scanf("%d"RESET, &id);
                    for(j=0;j<8;j++){
                        if(myTeam.teamPlayers[j].idPlayer == id){
                            selectPlayer[i] = myTeam.teamPlayers[j] ;
                        }
                    }
                }
                switch (countOfWeeks) {
                    case 1 :
                        file = fopen("week1.txt", "a");
                        i = 0;
                        for (i; i < 5; i++) {
                            fwrite(&selectPlayer[i], sizeof(struct player),1,file);
                        }
                        fclose(file);
                    case 2 :
                        file = fopen("week2.txt", "a");
                        i = 0;
                        for (i; i < 5; i++) {
                            fwrite(&selectPlayer[i], sizeof(struct player),1,file);
                        }
                        fclose(file);
                    case 3 :
                        file = fopen("week3.txt", "a");
                        i = 0;
                        for (i; i < 5; i++) {
                            fwrite(&selectPlayer[i], sizeof(struct player),1,file);
                        }
                        fclose(file);
                    case 4 :
                        file = fopen("week4.txt", "a");
                        i = 0;
                        for (i; i < 5; i++) {
                            fwrite(&selectPlayer[i], sizeof(struct player),1,file);
                        }
                        fclose(file);
                    case 5 :
                        file = fopen("week5.txt", "a");
                        i = 0;
                        for (i; i < 5; i++) {
                            fwrite(&selectPlayer[i], sizeof(struct player),1,file);
                        }
                        fclose(file);
                    case 6 :
                        file = fopen("week6.txt", "a");
                        i = 0;
                        for (i; i < 5; i++) {
                            fwrite(&selectPlayer[i], sizeof(struct player),1,file);
                        }
                        fclose(file);
                }
                printf(GRN"\nYour squad for game has been successfully registered."RESET);
                coachAccount(myTeam);
            }
            break;
        case 4 :
            file = fopen("table.txt","r");
            fseek(file,0,SEEK_END);
            int size = ftell(file) / sizeof(struct leagueStanding) ;
            rewind(file);
            struct leagueStanding t[4];
            for (i=0; i < size; i++){
                fread(&t[i],sizeof(struct leagueStanding),1,file);
            }
            printf(BLU"\n***********************************************************************");
            printf("\n-Name----Played----Win----Drawn----Lost----Gf----Ga----Gd----Points : "RESET);
            for(i =0 ; i <4 ; i++){
                printf(BLU"\n %s      %d       %d      %d      %d      %d      %d      %d       %d"RESET,t[i].TeamName,t[i].played,t[i].won,t[i].drawn,t[i].lost,t[i].gf,t[i].ga,t[i].gd,t[i].points);
            }
            fclose(file);
            coachAccount(myTeam);
            break;
        case 5 :
            file = fopen("games.txt","r");
            fp = fopen("results.txt","r");
            fseek(fp,0,SEEK_END);
            int sizeResult = ftell(fp) / 4 ;
            rewind(fp);
            char read[24][maxlen];
            int res[24];
            i = 0;
            while(fread(&read[i], maxlen,1,file) && i<=24){
                i++;
            }
            for(i =0 ; i <sizeResult;i++){
                fread(&res[i],4,1,fp);
            }
            printf(BLU"\n**************************");
            printf("\n   Name  ---  Name");
            printf("\n**************************"RESET);

            if(sizeResult == 0 ){
                for(i =0 ; i <24 ; i++){
                    if(i%2 == 0 ){
                        printf(BLU"\n   %s  ---",read[i]);
                    }
                    else{
                        printf("  %s "RESET,read[i]);
                    }
                }
            }
            else{
                for(i =0 ; i <sizeResult ; i++){
                    if(i%2 == 0 ){
                        printf(BLU"\n   %s  %d ---",read[i],res[i]);
                    }
                    else{
                        printf(" %d  %s "RESET,res[i],read[i]);
                    }
                }
                for(i ; i>=sizeResult && i<24;i++){
                    if(i%2 == 0 ){
                        printf(BLU"\n   %s  ---",read[i]);
                    }
                    else{
                        printf("  %s "RESET,read[i]);
                    }
                }
            }
            fclose(file);
            fclose(fp);
            coachAccount(myTeam);
            break;
        case 6 :
            file = fopen("games.txt","r");
            char ch [4][maxlen] , opponent[maxlen];
            if(countOfWeeks == 1){
                i=0;
                while(fread(&ch[i], maxlen, 1, file)){i++;}
                for(i=0;i<4; i++){
                    if (!strcmp(ch[i], myTeam.teamName)){
                        if(i == 1 || i == 3)
                            strcpy(opponent,ch[i-1]);
                        else
                            strcpy(opponent,ch[i+1]);
                    }
                }
                fclose(file);
            }
            else{
                int seek = 4*maxlen*(countOfWeeks-1);
                fseek(file,seek, SEEK_CUR);
                i=0;
                while(fread(&ch[i], maxlen, 1, file)){i++;}
                for(i=0;i<4; i++){
                    if (!strcmp(ch[i], myTeam.teamName)){
                        if(i == 1 || i == 3)
                            strcpy(opponent,ch[i-1]);
                        else
                            strcpy(opponent,ch[i+1]);
                    }
                }
                fclose(file);
            }
            int sumAttack ,sumDefence ;
            file = fopen("teams.txt","r");
            fseek(file,0,SEEK_END);
            int si = ftell(file) / sizeof(struct team);
            struct team opponentTeam [100];
            rewind(file);
            j=0 ,i=0;
            printf(BLU"\n******************************************************");
            printf("\n-Id----Name----Attackpower----Defensepower----Value :");
            while(fread(&opponentTeam[j],sizeof(struct team),1,file) && j<=si){
                if(!strcmp(opponentTeam[j].teamName,opponent)){
                    while(i<8){
                        sumAttack +=  opponentTeam[j].teamPlayers[i].attackingPowers;
                        sumDefence += opponentTeam[j].teamPlayers[i].defencingPowers ;
                        printf(" %d      %s       %d       %d        %d    \n", opponentTeam[j].teamPlayers[i].idPlayer, opponentTeam[j].teamPlayers[i].playerName, opponentTeam[j].teamPlayers[i].attackingPowers, opponentTeam[j].teamPlayers[i].defencingPowers, opponentTeam[j].teamPlayers[i].value);
                        i++;
                    }
                }
                j++;
            }
            printf("\n******************************************************");
            printf("\n sum of attackingPowers opponent is : %d",sumAttack);
            printf("\n sum of defencingPowers opponent is : %d"RESET,sumDefence);
            coachAccount(myTeam);
            break;
        case 7 :
            printf(BLU"**********************************");
            printf("\n enter your email :");
            char email[maxlen];
            struct user change[100];
            scanf("%s", &email);
            printf("\n enter your password :");
            char pas[maxlen], newPas[maxlen];
            scanf("%s", &pas);
            encrypt(pas);
            system("clear");
            int flag = 0,a;
            if (!strcmp(myTeam.emailCoach, email)) {
                file = fopen("users.txt", "r");
                fseek(file, 0, SEEK_END);
                a = ftell(file) / sizeof(struct user);
                rewind(file);
                i = 0;
                while (fread(&change[i], sizeof(struct user), 1, file) && i<a) {
                    if (!strcmp(change[i].password, pas)) {
                        flag = 1;
                        printf("\n***************************************");
                        printf("\nenter new password :"RESET);
                        scanf("%s", &newPas);
                        encrypt(newPas);
                        strcpy(change[i].password, newPas);
                    }
                    i++;
                }
            }
            fclose(file);
            file = fopen("temp.txt", "w");
            for (i = 0; i < a; i++) {
                fwrite(&change[i], sizeof(struct user), 1, file);
            }
            fclose(file);
            file = fopen("temp.txt", "r");
            fp = fopen("users.txt", "w");
            i = 0;
            while (fread(&change[i], sizeof(struct user), 1, file) && i<a) {
                fwrite(&change[i], sizeof(struct user), 1, fp);
                i++;
            }
            fclose(file);
            fclose(fp);
            printf(GRN"\n Password changed .!!!!"RESET);
            coachAccount(myTeam);
            break;
        case 8 :
            login();
            break;
        default :
            printf(RED"\nInvalid command"RESET);
            coachAccount(myTeam);
            break;
    }
}
void id_team(struct team *t){
    int num ,n[100] ,counter =0 ;
    printf(BLU"\n***************************************");
    printf("\nPlease enter id number between 1 and 100:");
    scanf("%d"RESET,&num);
    FILE *fp = fopen("1to100.txt", "a+");
    fseek(fp,0,SEEK_END);
    int end = ftell(fp)/4;
    for( int i=0; i < end; i++ ) {
        fread(&n[i],4,1,fp);
        if(n[i] == num){
            printf(RED"\n Sorry , id is exist"RESET);
            id_team((struct team *) &t);
        }
        else{
            counter++;
        }
    }
    if(counter == end || end == EOF){
        putw(num,fp);
        t->idTeam = num ;
    }
    fclose(fp);
}
void id_player(struct player *p) {
    int num, n[800], counter = 0;
    printf(BLU"\n***************************************");
    printf("\nPlease enter id number between 1 and 800:");
    scanf("%d"RESET, &num);
    FILE *fp = fopen("1to800.txt", "a+");
    fseek(fp,0,SEEK_END);
    int end = ftell(fp) / 4;
    fseek(fp,0,SEEK_SET);
    for( int i=0; i < end; i++ ) {
        fread(&n[i],4,1,fp);
        if(n[i] == num){
            printf(RED"\n Sorry , id is exist"RESET);
            id_player((struct player *) p);
        }
        else{
            counter++;
        }
    }
    if(counter == end || end == EOF){
        putw(num,fp);
        p->idPlayer = num ;
    }
    fclose(fp);
}
void adminAccount() {
    system("clear");
    printf(BLU"\n1=>Add Team\n2=>Add Player\n3=>Show Teams\n4=>Show Players");
    FILE *f = fopen("saveEssentialsNum.txt", "r");
    int arr[4], i = 0;
    while (fread(&arr[i], 4, 1, f)) {
        i++;
    }
    fclose(f);
    int countOfWeeks = arr[2], transferWindow = arr[3], endMidSession = arr[0], endSession = arr[1];
    if (countOfWeeks == 0 && transferWindow == 1) {
        printf("\n5=>Start League ");
    } else if (countOfWeeks ==4 && endMidSession == 1) {
        printf("\n5=>Open or Close transfer Window");
    } else if ((countOfWeeks != 0 && transferWindow == 0 && endSession ==0)) {
        printf("\n5=>Start week %d-th Games",countOfWeeks);
    } else if (endSession == 1) {
        printf("\n5=>End session and announce The champion");
    }
    printf("\n6=>Exit");
    printf("\nPlease enter Your choice : ");
    FILE *file;
    FILE *fptr;
    int command, complete = 0;
    struct team newTeam , checkTm;
    struct player newPlayer , checkPl;
    struct team teamInLeague[4];
    scanf("%d"RESET, &command);
    struct user newUser;
    struct leagueStanding table[4];
    switch (command) {
        case 1:
            system("clear");
            file = fopen("teams.txt", "a+");
            int counter =0 ;
            while(fread(&checkTm, sizeof(struct team), 1, file)){
                counter++;
            }
            if(counter == 100){
                printf(RED"\n The number of teams is too much .!!!!"RESET);
                adminAccount();
            }
            printf(BLU"\n********************************");
            char copy[maxlen];
            printf(BLU"\nPlease enter your team name : ");
            scanf("%s", &newTeam.teamName);
            printf("\nPlease enter your email : ");
            scanf("%s"RESET, &newTeam.emailCoach);
            newTeam.defaultValue = 100;
            id_team(&newTeam);
            newTeam.countOfChampions = 0;
            newTeam.countOfPlayers = 0;
            newTeam.completeTeam = 0;
            fwrite(&newTeam, sizeof(struct team), 1, file);
            fclose(file);
            strcpy(newUser.username, newTeam.teamName);
            strcpy(copy, newTeam.emailCoach);
            encrypt(copy);
            strcpy(newUser.password,copy);
            fptr = fopen("users.txt", "a+");
            fwrite(&newUser, sizeof(struct user), 1, fptr);
            fclose(fptr);
            printf(GRN"\nTeam registered .Username is name team , and password is email coach !!!"RESET);
            adminAccount();
            break;

        case 2 :
            system("clear");
            file = fopen("players.txt", "a");
            int ctr =0 ;
            while(fread(&checkPl, sizeof(struct player), 1, file)){
                ctr++;
            }
            if(ctr == 800){
                printf(RED"\n The number of players is too much .!!!!"RESET);
                adminAccount();
            }
            id_player(&newPlayer);
            printf("\nPlease enter player name : ");
            scanf("%s", &newPlayer.playerName);
            printf("\nPlease enter attackingPowers : ");
            scanf("%d", &newPlayer.defaultAttackPowers);
            printf("\nPlease enter defencingPowers : ");
            scanf("%d", &newPlayer.defaultDefencePowers);
            while(1){
                printf("\nPlease enter player value : ");
                scanf("%d"RESET, &newPlayer.value);
                if(newPlayer.value > 100){
                    printf(RED"\n Sorry . The value of this player is more than one hundred dollars"RESET);
                    continue;
                }
                else{
                    break;
                }
            }
            newPlayer.attackingPowers = newPlayer.defaultAttackPowers ;
            newPlayer.defencingPowers = newPlayer.defaultDefencePowers ;
            strcpy(newPlayer.teamPlayers, "Free agent");
            fseek(file, 0, SEEK_END);
            fwrite(&newPlayer, sizeof(struct player), 1, file);
            fclose(file);
            printf(GRN"\nPlayer registered!!!"RESET);
            adminAccount();
            break;

        case 3:
            if(!(file = fopen("teams.txt", "r")))
            {
                printf(RED"open %s failed\n", "teams.txt"RESET);
                adminAccount();
            }
            struct team team;
            struct team readInTeam;
            printf(BLU"\n********************************");
            printf("\nName  ---   countofchampion");
            while (fread(&readInTeam, sizeof(struct team), 1, file)) {
                printf("%s  ---   %d\n", readInTeam.teamName, readInTeam.countOfChampions);
            }
            printf("Enter the team name to see player information :");
            char nameTest[maxlen];
            scanf("%s"RESET, &nameTest);
            system("clear");
            fseek(file, 0, SEEK_SET);
            printf(BLU"\n-Id---Name---Attackpower---Defencepower---Value"RESET);
            while (fread(&team, sizeof(struct team), 1, file)) {
                if (!strcmp(team.teamName, nameTest)) {
                    for(i=0;!strcmp(team.teamPlayers[i].teamPlayers,team.teamName);i++){
                        printf(BLU"%d      ", team.teamPlayers[i].idPlayer);
                        printf("%s       ", team.teamPlayers[i].playerName);
                        printf("%d      ", team.teamPlayers[i].defaultAttackPowers);
                        printf("%d      ", team.teamPlayers[i].defaultDefencePowers);
                        printf("%d       \n"RESET, team.teamPlayers[i].value);
                    }
                }
            }
            fclose(file);
            adminAccount();
            break;

        case 4 :
            if( ! (fptr= fopen("players.txt", "r") ) )
            {
                printf(RED"open %s failed\n", "players.txt"RESET);
                adminAccount();
            }
            printf(BLU"\n********************************");
            printf(BLU"\n-Id---Name---Attackpower---Defencepower---Value"RESET);
            struct player p;
            while (fread(&p, sizeof(struct player), 1, fptr)) {
                printf(BLU"%d     ", p.idPlayer);
                printf("%s       ", p.playerName);
                printf("%d     ", p.defaultAttackPowers);
                printf("%d     ", p.defaultDefencePowers);
                printf("%s     ", p.teamPlayers);
                printf("%d     \n"RESET, p.value);
            }
            fclose(fptr);
            adminAccount();
            break;
        case 5 :
            if (countOfWeeks == 0 && transferWindow == 1) {
                file = fopen("teams.txt", "r");
                fseek(file, 0, SEEK_SET);
                struct team newTeamInLeague[100];
                int j =0 ;
                i=0;
                while (fread(&newTeamInLeague[i], sizeof(struct team), 1, file)) {
                    if (newTeamInLeague[i].completeTeam == 1) {
                        teamInLeague[j] = newTeamInLeague[i];
                        i++;
                        complete++;
                        j++;
                    }
                    if (complete == 4)
                        break;
                }
                fclose(file);
                i = 0;
                while (i < 4) {
                    strcpy(table[i].TeamName, teamInLeague[i].teamName);
                    i++;
                }
                arrangeGame(teamInLeague);
                file = fopen("table.txt", "a");// table file save league leagueStanding .
                for(i=0;i<4;i++){
                    fwrite(&table[i], sizeof(table), 1, file);
                }
                fclose(file);
                file = fopen("league.txt", "a");  //league file save teams are in current league .
                for(i=0;i<4;i++){
                    fwrite(&teamInLeague[i], sizeof(struct team), 1, file);
                }
                fclose(file);
                f = fopen("saveEssentialsNum.txt", "r");
                fseek(f, 0, SEEK_SET);
                i = 0;
                while (fread(&arr[i], 4, 1, f)) {
                    i++;
                }
                fclose(f);
                arr[3] = 0;
                arr[2] = 1;
                f = fopen("saveEssentialsNum.txt", "w");
                for(i = 0; i <4; i++){
                    fwrite(&arr[i], 4, 1, f);
                }
                fclose(f);
                printf(GRN"\n league started !!!!!"RESET);
                adminAccount();
            } else if (countOfWeeks == 4 && endMidSession == 1) {
                system("clear");
                printf(BLU"\n1=>open 2=>close"RESET);
                int opt;
                scanf("%d", &opt);
                if (opt == 1) {
                    f = fopen("saveEssentialsNum.txt", "r");
                    i = 0;
                    while (fread(&arr[i], 4, 1, f)) {
                        i++;
                    }
                    fclose(f);
                    arr[3] = 1;
                    f = fopen("saveEssentialsNum.txt", "w");
                    for(i=0;i<4;i++){
                        fwrite(&arr[i], 4, 1, f);
                    }
                    fclose(f);
                    printf(RED"\nTransfer Window opened!!!"RESET);
                    adminAccount();
                } else {
                    f = fopen("saveEssentialsNum.txt", "r");
                    i = 0;
                    while (fread(&arr[i], 4, 1, f)) {
                        i++;
                    }
                    fclose(f);
                    arr[0]=0;
                    arr[3] = 0;
                    f = fopen("saveEssentialsNum.txt", "w");
                    for(i=0;i<4;i++){
                        fwrite(&arr[i], 4, 1, f);
                    }
                    fclose(f);
                    printf(RED"\nTransfer Window closed!!!"RESET);
                    adminAccount();
                }
            } else if (countOfWeeks != 0 && transferWindow == 0 && endSession ==0) {
                char nameTeam[4][maxlen];
                struct team A , B , C , D ,read[100];
                int goalA , goalB , goalC , goalD , s;
                int sumAttackA,sumAttackB,sumAttackC,sumAttackD;
                int sumDefenceA,sumDefenceB,sumDefenceC,sumDefenceD;
                struct player teamA[5],teamB[5] , teamC[5] , teamD[5] , readPlayer[20];
                struct player rA[5],rB[5],rC[5],rD[5] , rAll[20];
                switch(countOfWeeks){
                    case 1:
                        file = fopen("week1.txt","r");
                        if(file == NULL){
                            printf(RED"It is not possible to run games at this time."RESET);
                            adminAccount();
                            break;
                        }
                        fseek(file,0,SEEK_END);
                        if((ftell(file)/(20*sizeof(struct player))) != 1 ){
                            printf(RED"It is not possible to run games at this time."RESET);
                            adminAccount();
                            break;
                        }
                        rewind(file);
                        fptr = fopen("games.txt","r");
                        for (i=0;i<4; i++) {
                            fread(&nameTeam[i],maxlen,1,fptr);
                        }
                        fclose(fptr);
                        fptr = fopen("teams.txt","r");
                        fseek(fptr,0,SEEK_END);
                        int s =ftell(fptr)/sizeof(struct team);
                        rewind(fptr);
                        i =0 ;
                        while(fread(&read[i],sizeof(struct team),1,fptr)  && i<= s){
                            if(!strcmp(read[i].teamName,nameTeam[0])){
                                A = read[i];
                            }
                            else if (!strcmp(read[i].teamName,nameTeam[1])) {
                                B = read[i];
                            }
                            else if (!strcmp(read[i].teamName,nameTeam[2])){
                                C = read[i];
                            }
                            else if (!strcmp(read[i].teamName,nameTeam[3])){
                                D = read[i];
                            }
                            i++ ;
                        }
                        fclose(fptr);
                        i =0 ;
                        int a=0,b=0,c=0,d=0;
                        while (fread(&readPlayer[i],sizeof( struct player),1,file)){
                            if(!strcmp(readPlayer[i].teamPlayers,A.teamName)){
                                teamA[a] = readPlayer[i];
                                a++;
                            }
                            else if(!strcmp(readPlayer[i].teamPlayers,B.teamName)){
                                teamB[b] = readPlayer[i];
                                b++;
                            }
                            else if (!strcmp(readPlayer[i].teamPlayers,C.teamName)){
                                teamC[c] = readPlayer[i];
                                c++;
                            }
                            else if (!strcmp(readPlayer[i].teamPlayers,D.teamName)){
                                teamD[d] = readPlayer[i] ;
                                d++;
                            }
                            i++;
                        }
                        fclose(file);
                        for(i=0 ; i<5; i++){
                            sumAttackA+=teamA[i].attackingPowers;
                            sumDefenceA += teamA[i].defencingPowers;
                            sumAttackB+=teamB[i].attackingPowers;
                            sumDefenceB += teamB[i].defencingPowers;
                            sumAttackC+=teamC[i].attackingPowers;
                            sumDefenceC += teamC[i].defencingPowers;
                            sumAttackD+=teamD[i].attackingPowers;
                            sumDefenceD += teamD[i].defencingPowers;
                        }
                        goalA = (sumAttackA - sumDefenceB)/100 ;
                        goalB = (sumAttackB - sumDefenceA)/100 ;
                        goalC = (sumAttackC - sumDefenceD) /100;
                        goalD = (sumAttackD - sumDefenceC) /100;
                        if(goalA <0 ){
                            goalA = 0;
                        }
                        else if(goalB <0){
                            goalB = 0;
                        }
                        else if (goalC <0){
                            goalC =0 ;
                        }
                        else if(goalD <0){
                            goalD =0 ;
                        }
                        file = fopen("results.txt","a");
                        fwrite(&goalA,4,1,file);
                        fwrite(&goalB,4,1,file);
                        fwrite(&goalC,4,1,file);
                        fwrite(&goalD,4,1,file);
                        fclose(file);
                        if(goalA > goalB){
                            A.defaultValue+=5;
                            B.defaultValue+=1;
                        }else if(goalA < goalB){
                            A.defaultValue+=1;
                            B.defaultValue+=5;
                        }else{
                            A.defaultValue+=3;
                            B.defaultValue+=3;
                        }
                        if(goalC > goalD){
                            C.defaultValue+=5;
                            D.defaultValue+=1;
                        }else if(goalC < goalD){
                            C.defaultValue+=1;
                            D.defaultValue+=5;
                        }else{
                            C.defaultValue+=3;
                            D.defaultValue+=3;
                        }
                        for(i=0 ; i < 8 ; i++) {
                            for (int j = 0; j < 5; j++) {
                                if (A.teamPlayers[i].idPlayer == teamA[j].idPlayer) {
                                    A.teamPlayers[i].attackingPowers -= 5;
                                    A.teamPlayers[i].defencingPowers -= 5;
                                }
                            }
                        }
                        for(i=0 ; i < 8 ; i++) {
                            for (int j = 0; j < 5; j++) {
                                if (B.teamPlayers[i].idPlayer == teamB[j].idPlayer) {
                                    B.teamPlayers[i].attackingPowers -= 5;
                                    B.teamPlayers[i].defencingPowers -= 5;
                                }
                            }
                        }
                        for(i=0 ; i < 8 ; i++) {
                            for (int j = 0; j < 5; j++) {
                                if (C.teamPlayers[i].idPlayer == teamC[j].idPlayer) {
                                    C.teamPlayers[i].attackingPowers -= 5;
                                    C.teamPlayers[i].defencingPowers -= 5;
                                }
                            }
                        }
                        for(i=0 ; i < 8 ; i++) {
                            for (int j = 0; j < 5; j++) {
                                if (D.teamPlayers[i].idPlayer == teamD[j].idPlayer) {
                                    D.teamPlayers[i].attackingPowers -= 5;
                                    D.teamPlayers[i].defencingPowers -= 5;
                                }
                            }
                        }
                        int r[4];
                        file =fopen("saveEssentialsNum.txt","r");
                        i=0;
                        while(fread(&r[i],4,1,file)){
                            i++;
                        }
                        fclose(file);
                        r[2] +=1 ;
                        fptr = fopen("saveEssentialsNum.txt","w");
                        i=0;
                        while(i<4){
                            fwrite(&r[i],4,1,fptr);
                            i++;
                        }
                        fclose(fptr);
                        break;
                    case 2:
                        file = fopen("week2.txt","r");
                        if(file == NULL){
                            printf(RED"It is not possible to run games at this time."RESET);
                            adminAccount();
                            break;
                        }
                        fseek(file,0,SEEK_END);
                        if((ftell(file)/(20*sizeof(struct player))) != 1 ){
                            printf(RED"It is not possible to run games at this time."RESET);
                            adminAccount();
                            break;
                        }
                        rewind(file);
                        fptr = fopen("games.txt","r");
                        fseek(file,4*maxlen,SEEK_CUR);
                        for (i=0;i<4; i++) {
                            fread(&nameTeam[i],maxlen,1,fptr);
                        }
                        fclose(fptr);
                        fptr = fopen("teams.txt","r");
                        fseek(fptr,0,SEEK_END);
                        s =ftell(fptr)/sizeof(struct team);
                        rewind(fptr);
                        i =0 ;
                        while(fread(&read[i],sizeof(struct team),1,fptr) && i<=s){
                            if(!strcmp(read[i].teamName,nameTeam[0])){
                                A = read[i];
                            }
                            else if (!strcmp(read[i].teamName,nameTeam[1])) {
                                B = read[i];
                            }
                            else if (!strcmp(read[i].teamName,nameTeam[2])){
                                C = read[i];
                            }
                            else if (!strcmp(read[i].teamName,nameTeam[3])){
                                D = read[i];
                            }
                            i++ ;
                        }
                        fclose(fptr);
                        i =0 ;
                        a=0,b=0,c=0,d=0;
                        while (fread(&readPlayer[i],sizeof( struct player),1,file)){
                            if(!strcmp(readPlayer[i].teamPlayers,A.teamName)){
                                teamA[a] = readPlayer[i];
                                a++;
                            }
                            else if(!strcmp(readPlayer[i].teamPlayers,B.teamName)){
                                teamB[b] = readPlayer[i];
                                b++;
                            }
                            else if (!strcmp(readPlayer[i].teamPlayers,C.teamName)){
                                teamC[c] = readPlayer[i];
                                c++;
                            }
                            else if (!strcmp(readPlayer[i].teamPlayers,D.teamName)){
                                teamD[d] = readPlayer[i] ;
                                d++;
                            }
                            i++;
                        }
                        fclose(file);
                        for(i=0 ; i<5; i++){
                            sumAttackA+=teamA[i].attackingPowers;
                            sumDefenceA += teamA[i].defencingPowers;
                            sumAttackB+=teamB[i].attackingPowers;
                            sumDefenceB += teamB[i].defencingPowers;
                            sumAttackC+=teamC[i].attackingPowers;
                            sumDefenceC += teamC[i].defencingPowers;
                            sumAttackD+=teamD[i].attackingPowers;
                            sumDefenceD += teamD[i].defencingPowers;
                        }
                        goalA = (sumAttackA - sumDefenceB)/100 ;
                        goalB = (sumAttackB - sumDefenceA )/100;
                        goalC = (sumAttackC - sumDefenceD)/100 ;
                        goalD = (sumAttackD - sumDefenceC) /100;
                        if(goalA <0 ){
                            goalA = 0;
                        }
                        else if(goalB <0){
                            goalB = 0;
                        }
                        else if (goalC <0){
                            goalC =0 ;
                        }
                        else if(goalD <0){
                            goalD =0 ;
                        }
                        file = fopen("results.txt","a");
                        fwrite(&goalA,4,1,file);
                        fwrite(&goalB,4,1,file);
                        fwrite(&goalC,4,1,file);
                        fwrite(&goalD,4,1,file);
                        fclose(file);
                        if(goalA > goalB){
                            A.defaultValue+=5;
                            B.defaultValue+=1;
                        }else if(goalA < goalB){
                            A.defaultValue+=1;
                            B.defaultValue+=5;
                        }else{
                            A.defaultValue+=3;
                            B.defaultValue+=3;
                        }
                        if(goalC > goalD){
                            C.defaultValue+=5;
                            D.defaultValue+=1;
                        }else if(goalC < goalD){
                            C.defaultValue+=1;
                            D.defaultValue+=5;
                        }else{
                            C.defaultValue+=3;
                            D.defaultValue+=3;
                        }
                        fptr = fopen("week1.txt", "r");
                        i = 0 ,a=0,b=0,c=0,d=0;
                        while (fread(&rAll[i], sizeof(struct player), 1, fptr)) {
                            if (!strcmp(rAll[i].teamPlayers, A.teamName)) {
                                rA[a] = rAll[i];
                                a++;
                            } else if (!strcmp(rAll[i].teamPlayers, B.teamName)) {
                                rB[b] = rAll[i];
                                b++;
                            } else if (!strcmp(rAll[i].teamPlayers, C.teamName)) {
                                rC[c] = rAll[i];
                                c++;
                            } else if (!strcmp(rAll[i].teamPlayers, D.teamName)) {
                                rD[d] = rAll[i];
                                d++;
                            }
                            i++;
                        }
                        fclose(fptr);
                        file =fopen("saveEssentialsNum.txt","r");
                        i=0;
                        while(fread(&r[i],4,1,file)){
                            i++;
                        }
                        fclose(file);
                        r[2] +=1 ;
                        fptr = fopen("saveEssentialsNum.txt","w");
                        i=0;
                        while(i<4){
                            fwrite(&r[i],4,1,fptr);
                            i++;
                        }
                        fclose(fptr);
                        break;
                    case 3 :
                        file = fopen("week3.txt","r");
                        if(file == NULL){
                            printf(RED"It is not possible to run games at this time."RESET);
                            adminAccount();
                            break;
                        }
                        fseek(file,0,SEEK_END);
                        if((ftell(file)/(20*sizeof(struct player))) != 1 ){
                            printf(RED"It is not possible to run games at this time."RESET);
                            adminAccount();
                            break;
                        }
                        rewind(file);
                        fptr = fopen("games.txt","r");
                        fseek(file,8*maxlen,SEEK_CUR);
                        for (i=0;i<4; i++) {
                            fread(&nameTeam[i],maxlen,1,fptr);
                        }
                        fclose(fptr);
                        fptr = fopen("teams.txt","r");
                        fseek(fptr,0,SEEK_END);
                        s =ftell(fptr)/sizeof(struct team);
                        rewind(fptr);
                        i =0 ;
                        while(fread(&read[i],sizeof(struct team),1,fptr) && i <=s){
                            if(!strcmp(read[i].teamName,nameTeam[0])){
                                A = read[i];
                            }
                            else if (!strcmp(read[i].teamName,nameTeam[1])) {
                                B = read[i];
                            }
                            else if (!strcmp(read[i].teamName,nameTeam[2])){
                                C = read[i];
                            }
                            else if (!strcmp(read[i].teamName,nameTeam[3])){
                                D = read[i];
                            }
                            i++ ;
                        }
                        fclose(fptr);
                        i =0 ;
                        a=0,b=0,c=0,d=0;
                        while (fread(&readPlayer[i],sizeof( struct player),1,file)){
                            if(!strcmp(readPlayer[i].teamPlayers,A.teamName)){
                                teamA[a] = readPlayer[i];
                                a++;
                            }
                            else if(!strcmp(readPlayer[i].teamPlayers,B.teamName)){
                                teamB[b] = readPlayer[i];
                                b++;
                            }
                            else if (!strcmp(readPlayer[i].teamPlayers,C.teamName)){
                                teamC[c] = readPlayer[i];
                                c++;
                            }
                            else if (!strcmp(readPlayer[i].teamPlayers,D.teamName)){
                                teamD[d] = readPlayer[i] ;
                                d++;
                            }
                            i++;
                        }
                        fclose(file);
                        for(i=0 ; i<5; i++){
                            sumAttackA+=teamA[i].attackingPowers;
                            sumDefenceA += teamA[i].defencingPowers;
                            sumAttackB+=teamB[i].attackingPowers;
                            sumDefenceB += teamB[i].defencingPowers;
                            sumAttackC+=teamC[i].attackingPowers;
                            sumDefenceC += teamC[i].defencingPowers;
                            sumAttackD+=teamD[i].attackingPowers;
                            sumDefenceD += teamD[i].defencingPowers;
                        }
                        goalA = sumAttackA - sumDefenceB ;
                        goalB = sumAttackB - sumDefenceA ;
                        goalC = sumAttackC - sumDefenceD ;
                        goalD = sumAttackD - sumDefenceC ;
                        if(goalA <0 ){
                            goalA = 0;
                        }
                        else if(goalB <0){
                            goalB = 0;
                        }
                        else if (goalC <0){
                            goalC =0 ;
                        }
                        else if(goalD <0){
                            goalD =0 ;
                        }
                        file = fopen("results.txt","a");
                        fwrite(&goalA,4,1,file);
                        fwrite(&goalB,4,1,file);
                        fwrite(&goalC,4,1,file);
                        fwrite(&goalD,4,1,file);
                        fclose(file);
                        if(goalA > goalB){
                            A.defaultValue+=5;
                            B.defaultValue+=1;
                        }else if(goalA < goalB){
                            A.defaultValue+=1;
                            B.defaultValue+=5;
                        }else{
                            A.defaultValue+=3;
                            B.defaultValue+=3;
                        }
                        if(goalC > goalD){
                            C.defaultValue+=5;
                            D.defaultValue+=1;
                        }else if(goalC < goalD){
                            C.defaultValue+=1;
                            D.defaultValue+=5;
                        }else{
                            C.defaultValue+=3;
                            D.defaultValue+=3;
                        }
                        fptr = fopen("week2.txt", "r");
                        i = 0 ,a=0,b=0,c=0,d=0;
                        while (fread(&rAll[i], sizeof(struct player), 1, fptr)) {
                            if (!strcmp(rAll[i].teamPlayers, A.teamName)) {
                                rA[a] = rAll[i];
                                a++;
                            } else if (!strcmp(rAll[i].teamPlayers, B.teamName)) {
                                rB[b] = rAll[i];
                                b++;
                            } else if (!strcmp(rAll[i].teamPlayers, C.teamName)) {
                                rC[c] = rAll[i];
                                c++;
                            } else if (!strcmp(rAll[i].teamPlayers, D.teamName)) {
                                rD[d] = rAll[i];
                                d++;
                            }
                            i++;
                        }
                        fclose(fptr);
                        file =fopen("saveEssentialsNum.txt","r");
                        i=0;
                        while(fread(&r[i],4,1,file)){
                            i++;
                        }
                        fclose(file);
                        r[0] = 1 ;
                        r[2] +=1 ;
                        fptr = fopen("saveEssentialsNum.txt","w");
                        i=0;
                        while(i<4){
                            fwrite(&r[i],4,1,fptr);
                            i++;
                        }
                        fclose(fptr);
                        break;
                    case 4 :
                        file = fopen("week4.txt","r");
                        if(file == NULL){
                            printf(RED"It is not possible to run games at this time."RESET);
                            adminAccount();
                            break;
                        }
                        fseek(file,0,SEEK_END);
                        if((ftell(file)/(20*sizeof(struct player))) != 1 ){
                            printf(RED"It is not possible to run games at this time."RESET);
                            adminAccount();
                            break;
                        }
                        rewind(file);
                        fptr = fopen("games.txt","r");
                        fseek(file,12*maxlen,SEEK_CUR);
                        for (i=0;i<4; i++) {
                            fread(&nameTeam[i],maxlen,1,fptr);
                        }
                        fclose(fptr);
                        fptr = fopen("teams.txt","r");
                        fseek(fptr,0,SEEK_END);
                        s =ftell(fptr)/sizeof(struct team);
                        rewind(fptr);
                        i =0 ;
                        while(fread(&read[i],sizeof(struct team),1,fptr) && i<=s){
                            if(!strcmp(read[i].teamName,nameTeam[0])){
                                A = read[i];
                            }
                            else if (!strcmp(read[i].teamName,nameTeam[1])) {
                                B = read[i];
                            }
                            else if (!strcmp(read[i].teamName,nameTeam[2])){
                                C = read[i];
                            }
                            else if (!strcmp(read[i].teamName,nameTeam[3])){
                                D = read[i];
                            }
                            i++ ;
                        }
                        fclose(fptr);
                        i =0 ;
                        a=0,b=0,c=0,d=0;
                        while (fread(&readPlayer[i],sizeof( struct player),1,file)){
                            if(!strcmp(readPlayer[i].teamPlayers,A.teamName)){
                                teamA[a] = readPlayer[i];
                                a++;
                            }
                            else if(!strcmp(readPlayer[i].teamPlayers,B.teamName)){
                                teamB[b] = readPlayer[i];
                                b++;
                            }
                            else if (!strcmp(readPlayer[i].teamPlayers,C.teamName)){
                                teamC[c] = readPlayer[i];
                                c++;
                            }
                            else if (!strcmp(readPlayer[i].teamPlayers,D.teamName)){
                                teamD[d] = readPlayer[i] ;
                                d++;
                            }
                            i++;
                        }
                        fclose(file);
                        for(i=0 ; i<5; i++){
                            sumAttackA+=teamA[i].attackingPowers;
                            sumDefenceA += teamA[i].defencingPowers;
                            sumAttackB+=teamB[i].attackingPowers;
                            sumDefenceB += teamB[i].defencingPowers;
                            sumAttackC+=teamC[i].attackingPowers;
                            sumDefenceC += teamC[i].defencingPowers;
                            sumAttackD+=teamD[i].attackingPowers;
                            sumDefenceD += teamD[i].defencingPowers;
                        }
                        goalA = sumAttackA - sumDefenceB ;
                        goalB = sumAttackB - sumDefenceA ;
                        goalC = sumAttackC - sumDefenceD ;
                        goalD = sumAttackD - sumDefenceC ;
                        if(goalA <0 ){
                            goalA = 0;
                        }
                        else if(goalB <0){
                            goalB = 0;
                        }
                        else if (goalC <0){
                            goalC =0 ;
                        }
                        else if(goalD <0){
                            goalD =0 ;
                        }
                        file = fopen("results.txt","a");
                        fwrite(&goalA,4,1,file);
                        fwrite(&goalB,4,1,file);
                        fwrite(&goalC,4,1,file);
                        fwrite(&goalD,4,1,file);
                        fclose(file);
                        if(goalA > goalB){
                            A.defaultValue+=5;
                            B.defaultValue+=1;
                        }else if(goalA < goalB){
                            A.defaultValue+=1;
                            B.defaultValue+=5;
                        }else{
                            A.defaultValue+=3;
                            B.defaultValue+=3;
                        }
                        if(goalC > goalD){
                            C.defaultValue+=5;
                            D.defaultValue+=1;
                        }else if(goalC < goalD){
                            C.defaultValue+=1;
                            D.defaultValue+=5;
                        }else{
                            C.defaultValue+=3;
                            D.defaultValue+=3;
                        }
                        fptr = fopen("week3.txt", "r");
                        i = 0 ,a=0,b=0,c=0,d=0;
                        while (fread(&rAll[i], sizeof(struct player), 1, fptr)) {
                            if (!strcmp(rAll[i].teamPlayers, A.teamName)) {
                                rA[a] = rAll[i];
                                a++;
                            } else if (!strcmp(rAll[i].teamPlayers, B.teamName)) {
                                rB[b] = rAll[i];
                                b++;
                            } else if (!strcmp(rAll[i].teamPlayers, C.teamName)) {
                                rC[c] = rAll[i];
                                c++;
                            } else if (!strcmp(rAll[i].teamPlayers, D.teamName)) {
                                rD[d] = rAll[i];
                                d++;
                            }
                            i++;
                        }
                        fclose(fptr);
                        file =fopen("saveEssentialsNum.txt","r");
                        i=0;
                        while(fread(&r[i],4,1,file)){
                            i++;
                        }
                        fclose(file);
                        r[2] +=1 ;
                        fptr = fopen("saveEssentialsNum.txt","w");
                        i=0;
                        while(i<4){
                            fwrite(&r[i],4,1,fptr);
                            i++;
                        }
                        fclose(fptr);
                        break;
                    case 5 :
                        file = fopen("week5.txt","r");
                        if(file == NULL){
                            printf(RED"It is not possible to run games at this time."RESET);
                            adminAccount();
                            break;
                        }
                        fseek(file,0,SEEK_END);
                        if((ftell(file)/(20*sizeof(struct player))) != 1 ){
                            printf(RED"It is not possible to run games at this time."RESET);
                            adminAccount();
                            break;
                        }
                        rewind(file);
                        fptr = fopen("games.txt","r");
                        fseek(file,16*maxlen,SEEK_CUR);
                        i=0 ;
                        while(fread(&nameTeam[i][maxlen],maxlen,1,fptr)){
                            i++;
                        }
                        fclose(fptr);
                        fptr = fopen("teams.txt","r");
                        fseek(fptr,0,SEEK_END);
                        s =ftell(fptr)/sizeof(struct team);
                        rewind(fptr);
                        i =0 ;
                        while(fread(&read[i],sizeof(struct team),1,fptr) && i<=s){
                            if(!strcmp(read[i].teamName,nameTeam[0])){
                                A = read[i];
                            }
                            else if (!strcmp(read[i].teamName,nameTeam[1])) {
                                B = read[i];
                            }
                            else if (!strcmp(read[i].teamName,nameTeam[2])){
                                C = read[i];
                            }
                            else if (!strcmp(read[i].teamName,nameTeam[3])){
                                D = read[i];
                            }
                            i++ ;
                        }
                        fclose(fptr);
                        i =0 ;
                        a=0,b=0,c=0,d=0;
                        while (fread(&readPlayer[i],sizeof( struct player),1,file)){
                            if(!strcmp(readPlayer[i].teamPlayers,A.teamName)){
                                teamA[a] = readPlayer[i];
                                a++;
                            }
                            else if(!strcmp(readPlayer[i].teamPlayers,B.teamName)){
                                teamB[b] = readPlayer[i];
                                b++;
                            }
                            else if (!strcmp(readPlayer[i].teamPlayers,C.teamName)){
                                teamC[c] = readPlayer[i];
                                c++;
                            }
                            else if (!strcmp(readPlayer[i].teamPlayers,D.teamName)){
                                teamD[d] = readPlayer[i] ;
                                d++;
                            }
                            i++;
                        }
                        fclose(file);
                        for(i=0 ; i<5; i++){
                            sumAttackA+=teamA[i].attackingPowers;
                            sumDefenceA += teamA[i].defencingPowers;
                            sumAttackB+=teamB[i].attackingPowers;
                            sumDefenceB += teamB[i].defencingPowers;
                            sumAttackC+=teamC[i].attackingPowers;
                            sumDefenceC += teamC[i].defencingPowers;
                            sumAttackD+=teamD[i].attackingPowers;
                            sumDefenceD += teamD[i].defencingPowers;
                        }
                        goalA = sumAttackA - sumDefenceB ;
                        goalB = sumAttackB - sumDefenceA ;
                        goalC = sumAttackC - sumDefenceD ;
                        goalD = sumAttackD - sumDefenceC ;
                        if(goalA <0 ){
                            goalA = 0;
                        }
                        else if(goalB <0){
                            goalB = 0;
                        }
                        else if (goalC <0){
                            goalC =0 ;
                        }
                        else if(goalD <0){
                            goalD =0 ;
                        }
                        file = fopen("results.txt","a");
                        fwrite(&goalA,4,1,file);
                        fwrite(&goalB,4,1,file);
                        fwrite(&goalC,4,1,file);
                        fwrite(&goalD,4,1,file);
                        fclose(file);
                        if(goalA > goalB){
                            A.defaultValue+=5;
                            B.defaultValue+=1;
                        }else if(goalA < goalB){
                            A.defaultValue+=1;
                            B.defaultValue+=5;
                        }else{
                            A.defaultValue+=3;
                            B.defaultValue+=3;
                        }
                        if(goalC > goalD){
                            C.defaultValue+=5;
                            D.defaultValue+=1;
                        }else if(goalC < goalD){
                            C.defaultValue+=1;
                            D.defaultValue+=5;
                        }else{
                            C.defaultValue+=3;
                            D.defaultValue+=3;
                        }
                        fptr = fopen("week4.txt", "r");
                        i = 0 ,a=0,b=0,c=0,d=0;
                        while (fread(&rAll[i], sizeof(struct player), 1, fptr)) {
                            if (!strcmp(rAll[i].teamPlayers, A.teamName)) {
                                rA[a] = rAll[i];
                                a++;
                            } else if (!strcmp(rAll[i].teamPlayers, B.teamName)) {
                                rB[b] = rAll[i];
                                b++;
                            } else if (!strcmp(rAll[i].teamPlayers, C.teamName)) {
                                rC[c] = rAll[i];
                                c++;
                            } else if (!strcmp(rAll[i].teamPlayers, D.teamName)) {
                                rD[d] = rAll[i];
                                d++;
                            }
                            i++;
                        }
                        fclose(fptr);
                        file =fopen("saveEssentialsNum.txt","r");
                        i=0;
                        while(fread(&r[i],4,1,file)){
                            i++;
                        }
                        fclose(file);
                        r[2] +=1 ;
                        fptr = fopen("saveEssentialsNum.txt","w");
                        i=0;
                        while(i<4){
                            fwrite(&r[i],4,1,fptr);
                            i++;
                        }
                        fclose(fptr);
                        break;
                    case 6:
                        file = fopen("week6.txt","r");
                        if(file == NULL){
                            printf(RED"It is not possible to run games at this time."RESET);
                            adminAccount();
                            break;
                        }
                        fseek(file,0,SEEK_END);
                        if((ftell(file)/(20*sizeof(struct player))) != 1 ){
                            printf(RED"It is not possible to run games at this time."RESET);
                            adminAccount();
                            break;
                        }
                        rewind(file);
                        fptr = fopen("games.txt","r");
                        fseek(file,20*maxlen,SEEK_CUR);
                        i=0 ;
                        while(fread(&nameTeam[i],maxlen,1,fptr)){
                            i++;
                        }
                        fclose(fptr);
                        fptr = fopen("teams.txt","r");
                        fseek(fptr,0,SEEK_END);
                        s =ftell(fptr)/sizeof(struct team);
                        rewind(fptr);
                        i =0 ;
                        while(fread(&read[i],sizeof(struct team),1,fptr) && i<=s){
                            if(!strcmp(read[i].teamName,nameTeam[0])){
                                A = read[i];
                            }
                            else if (!strcmp(read[i].teamName,nameTeam[1])) {
                                B = read[i];
                            }
                            else if (!strcmp(read[i].teamName,nameTeam[2])){
                                C = read[i];
                            }
                            else if (!strcmp(read[i].teamName,nameTeam[3])){
                                D = read[i];
                            }
                            i++ ;
                        }
                        fclose(fptr);
                        i =0 ;
                        a=0,b=0,c=0,d=0;
                        while (fread(&readPlayer[i],sizeof( struct player),1,file)){
                            if(!strcmp(readPlayer[i].teamPlayers,A.teamName)){
                                teamA[a] = readPlayer[i];
                                a++;
                            }
                            else if(!strcmp(readPlayer[i].teamPlayers,B.teamName)){
                                teamB[b] = readPlayer[i];
                                b++;
                            }
                            else if (!strcmp(readPlayer[i].teamPlayers,C.teamName)){
                                teamC[c] = readPlayer[i];
                                c++;
                            }
                            else if (!strcmp(readPlayer[i].teamPlayers,D.teamName)){
                                teamD[d] = readPlayer[i] ;
                                d++;
                            }
                            i++;
                        }
                        fclose(file);
                        for(i=0 ; i<5; i++){
                            sumAttackA+=teamA[i].attackingPowers;
                            sumDefenceA += teamA[i].defencingPowers;
                            sumAttackB+=teamB[i].attackingPowers;
                            sumDefenceB += teamB[i].defencingPowers;
                            sumAttackC+=teamC[i].attackingPowers;
                            sumDefenceC += teamC[i].defencingPowers;
                            sumAttackD+=teamD[i].attackingPowers;
                            sumDefenceD += teamD[i].defencingPowers;
                        }
                        goalA = sumAttackA - sumDefenceB ;
                        goalB = sumAttackB - sumDefenceA ;
                        goalC = sumAttackC - sumDefenceD ;
                        goalD = sumAttackD - sumDefenceC ;
                        if(goalA <0 ){
                            goalA = 0;
                        }
                        else if(goalB <0){
                            goalB = 0;
                        }
                        else if (goalC <0){
                            goalC =0 ;
                        }
                        else if(goalD <0){
                            goalD =0 ;
                        }
                        file = fopen("results.txt","a");
                        fwrite(&goalA,4,1,file);
                        fwrite(&goalB,4,1,file);
                        fwrite(&goalC,4,1,file);
                        fwrite(&goalD,4,1,file);
                        fclose(file);
                        if(goalA > goalB){
                            A.defaultValue+=5;
                            B.defaultValue+=1;
                        }else if(goalA < goalB){
                            A.defaultValue+=1;
                            B.defaultValue+=5;
                        }else{
                            A.defaultValue+=3;
                            B.defaultValue+=3;
                        }
                        if(goalC > goalD){
                            C.defaultValue+=5;
                            D.defaultValue+=1;
                        }else if(goalC < goalD){
                            C.defaultValue+=1;
                            D.defaultValue+=5;
                        }else{
                            C.defaultValue+=3;
                            D.defaultValue+=3;
                        }
                        fptr = fopen("week5.txt", "r");
                        i = 0 ,a=0,b=0,c=0,d=0;
                        while (fread(&rAll[i], sizeof(struct player), 1, fptr)) {
                            if (!strcmp(rAll[i].teamPlayers, A.teamName)) {
                                rA[a] = rAll[i];
                                a++;
                            } else if (!strcmp(rAll[i].teamPlayers, B.teamName)) {
                                rB[b] = rAll[i];
                                b++;
                            } else if (!strcmp(rAll[i].teamPlayers, C.teamName)) {
                                rC[c] = rAll[i];
                                c++;
                            } else if (!strcmp(rAll[i].teamPlayers, D.teamName)) {
                                rD[d] = rAll[i];
                                d++;
                            }
                            i++;
                        }
                        fclose(fptr);
                        file =fopen("saveEssentialsNum.txt","r");
                        i=0;
                        while(fread(&r[i],4,1,file)){
                            i++;
                        }
                        fclose(file);
                        r[1] =1 ;
                        fptr = fopen("saveEssentialsNum.txt","w");
                        i=0;
                        while(i<4){
                            fwrite(&r[i],4,1,fptr);
                            i++;
                        }
                        fclose(fptr);
                        break;
                }
                // general task .
                if(countOfWeeks != 1){
                    for(i=0 ; i < 8 ; i++) {
                        for (int j = 0; j < 5; j++) {
                            if (A.teamPlayers[i].idPlayer == teamA[j].idPlayer) {
                                A.teamPlayers[i].attackingPowers -= 5;
                                A.teamPlayers[i].defencingPowers -= 5;
                            } else {
                                if (A.teamPlayers[i].idPlayer == rA[j].idPlayer) {
                                    A.teamPlayers[i].attackingPowers += 5;
                                    A.teamPlayers[i].defencingPowers += 5;
                                }
                            }
                        }
                    }
                    for(i=0 ; i < 8 ; i++) {
                        for (int j = 0; j < 5; j++) {
                            if (B.teamPlayers[i].idPlayer == teamB[j].idPlayer) {
                                B.teamPlayers[i].attackingPowers -= 5;
                                B.teamPlayers[i].defencingPowers -= 5;
                            } else {
                                if (B.teamPlayers[i].idPlayer == rB[j].idPlayer) {
                                    B.teamPlayers[i].attackingPowers += 5;
                                    B.teamPlayers[i].defencingPowers += 5;
                                }
                            }
                        }
                    }
                    for(i=0 ; i < 8 ; i++) {
                        for (int j = 0; j < 5; j++) {
                            if (C.teamPlayers[i].idPlayer == teamC[j].idPlayer) {
                                C.teamPlayers[i].attackingPowers -= 5;
                                C.teamPlayers[i].defencingPowers -= 5;
                            } else {
                                if (C.teamPlayers[i].idPlayer == rC[j].idPlayer) {
                                    C.teamPlayers[i].attackingPowers += 5;
                                    C.teamPlayers[i].defencingPowers += 5;
                                }
                            }
                        }
                    }
                    for(i=0 ; i < 8 ; i++) {
                        for (int j = 0; j < 5; j++) {
                            if (D.teamPlayers[i].idPlayer == teamD[j].idPlayer) {
                                D.teamPlayers[i].attackingPowers -= 5;
                                D.teamPlayers[i].defencingPowers -= 5;
                            } else {
                                if (D.teamPlayers[i].idPlayer == rD[j].idPlayer) {
                                    D.teamPlayers[i].attackingPowers += 5;
                                    D.teamPlayers[i].defencingPowers += 5;
                                }
                            }
                        }
                    }
                }
                file = fopen("teams.txt","r");
                i=0;
                while(fread(&read[i], sizeof(struct team), 1, file) && i <= s){
                    if(!strcmp(read[i].teamName,A.teamName)){
                        read[i] = A ;
                    }
                    else if(!strcmp(read[i].teamName,B.teamName)){
                        read[i] = B ;
                    }
                    else if (!strcmp(read[i].teamName,C.teamName)){
                        read[i] = C ;
                    }
                    else if (!strcmp(read[i].teamName,D.teamName)){
                        read[i] = D ;
                    }
                    i++;
                }
                fclose(file);
                fptr = fopen("temp.txt","w");
                for(i =0 ; i <100; i++){
                    fwrite(&read[i],sizeof(struct team),1,fptr);
                }
                fclose(fptr);
                fptr = fopen("temp.txt","r");
                file = fopen("teams.txt","w");
                i =0 ;
                while(fread(&read[i],sizeof(struct team),1,fptr)){
                    fwrite(&read[i],sizeof(struct team),1, file);
                    i++;
                }
                fclose(file);
                fclose(fptr);
                char tm[4][maxlen];
                strcpy(tm[0],A.teamName);
                strcpy(tm[1],B.teamName);
                strcpy(tm[2],C.teamName);
                strcpy(tm[3],D.teamName);
                file = fopen("table.txt","r");
                struct leagueStanding tmRead[4];
                i=0;
                while(fread(&tmRead[i],sizeof(struct leagueStanding),1,file) && i <4){
                    if(!strcmp(tmRead[i].TeamName,tm[0])){
                        tmRead[i].played += 1;
                        tmRead[i].gf += goalA ;
                        tmRead[i].ga += goalB ;
                        tmRead[i].gd += (goalA - goalB);
                        if(goalA > goalB){
                            tmRead[i].won +=1 ;
                            tmRead[i].points += 3;
                        }
                        else if(goalA == goalB){
                            tmRead[i].drawn += 1;
                            tmRead[i].points += 1;
                        }
                        else{
                            tmRead[i].lost += 1;
                        }
                    }
                    else if(!strcmp(tmRead[i].TeamName,tm[1])){
                        tmRead[i].played += 1;
                        tmRead[i].gf += goalB ;
                        tmRead[i].ga += goalA ;
                        tmRead[i].gd += (goalB - goalA);
                        if(goalB > goalA){
                            tmRead[i].won +=1 ;
                            tmRead[i].points += 3;
                        }
                        else if(goalA == goalB){
                            tmRead[i].drawn += 1;
                            tmRead[i].points += 1;
                        }
                        else{
                            tmRead[i].lost += 1;
                        }
                    }
                    else if(!strcmp(tmRead[i].TeamName,tm[2])){
                        tmRead[i].played += 1;
                        tmRead[i].gf += goalC ;
                        tmRead[i].ga += goalD ;
                        tmRead[i].gd += (goalC - goalD);
                        if(goalC > goalD){
                            tmRead[i].won +=1 ;
                            tmRead[i].points += 3;
                        }
                        else if(goalC == goalD){
                            tmRead[i].drawn += 1;
                            tmRead[i].points += 1;
                        }
                        else{
                            tmRead[i].lost += 1;
                        }
                    }
                    else if (!strcmp(tmRead[i].TeamName,tm[3])){
                        tmRead[i].played += 1;
                        tmRead[i].gf += goalD ;
                        tmRead[i].ga += goalC ;
                        tmRead[i].gd += (goalD - goalC);
                        if(goalD > goalC){
                            tmRead[i].won +=1 ;
                            tmRead[i].points += 3;
                        }
                        else if(goalC == goalD){
                            tmRead[i].drawn += 1;
                            tmRead[i].points += 1;
                        }
                        else{
                            tmRead[i].lost += 1;
                        }
                    }
                    i++;
                }
                fclose(file);
                file = fopen("temp.txt","w");
                for(i=0 ; i<4; i++){
                    fwrite(&tmRead[i],sizeof(struct leagueStanding), 1, file);
                }
                fclose(file);
                file = fopen("temp.txt","r");
                fptr = fopen("table.txt", "w");
                i=0;
                while(fread(&tmRead[i],sizeof(struct leagueStanding),1,file)){
                    fwrite(&tmRead[i],sizeof(struct leagueStanding),1,fptr);
                    i++;
                }
                //sort table league.
                fclose(file);
                fclose(fptr);
                file = fopen("table.txt","r");
                struct leagueStanding t[4];
                struct leagueStanding t1;
                i=0;
                while(fread(&t[i],sizeof(struct leagueStanding),1,file)){
                    i++;
                }
                fclose(file);
                for(i=0 ; i<4; i++){
                    for(int j=i+1 ; j<4 ;j++){
                        if(t[i].points < t[j].points){
                            t1 = t[i];
                            t[i] = t[j];
                            t[j] = t1 ;
                        }
                    }
                }
                for(i=0 ; i<4; i++){
                    for(int j=i+1 ; j<4 ;j++){
                        if(t[i].points == t[j].points){
                            if(t[i].gd < t[j].gd){
                                t1 = t[i];
                                t[i] = t[j];
                                t[j] = t1 ;
                            }
                        }
                    }
                }
                for(i=0 ; i<4; i++){
                    for(int j=i+1 ; j<4 ;j++){
                        if(t[i].points == t[j].points){
                            if(t[i].gd == t[j].gd){
                                if(t[i].gf < t[j].gf){
                                    t1 = t[i];
                                    t[i] = t[j];
                                    t[j] = t1 ;
                                }
                            }
                        }
                    }
                }
                for(i=0 ; i<4; i++){
                    for(int j=i+1 ; j<4 ;j++){
                        if(t[i].points == t[j].points){
                            if(t[i].gd == t[j].gd){
                                if(t[i].gf == t[j].gf){
                                    if(t[i].ga < t[j].ga){
                                        t1 = t[i];
                                        t[i] = t[j];
                                        t[j] = t1 ;
                                    }
                                }
                            }
                        }
                    }
                }
                file = fopen("table.txt","w");
                for(i = 0 ; i<4;i++){
                    fwrite(&t[i],sizeof(struct leagueStanding),1,file);
                }
                fclose(file);
                printf(GRN"\nThis week's games were successful!!"RESET);
                adminAccount();
            }
            else if (endSession == 1 && countOfWeeks ==6) {
                struct leagueStanding teamChampion[4];
                int ar[4];
                char champion[maxlen];
                file = fopen("table.txt", "r");
                i=0;
                printf(BLU"\n***********************************************************************");
                printf("\n-Name----Playes----Win----Drawn----Lost----Gf----Ga----Gd----Points : "RESET);
                while (fread(&teamChampion[i], sizeof(teamChampion), 1, file)) {
                    if (i==0) {
                        strcpy(champion, teamChampion[i].TeamName);
                    }
                    printf(BLU" %s      %d     %d     %d     %d      %d     %d     %d     %d    \n"RESET, teamChampion[i].TeamName,
                           teamChampion[i].played, teamChampion[i].won, teamChampion[i].drawn, teamChampion[i].lost,
                           teamChampion[i].gf, teamChampion[i].ga, teamChampion[i].gd, teamChampion[i].points);
                }
                fclose(file);
                printf(GRN"\nTabrik be to , Tabrik be man , Tabrik be hame !!! . %s  became the champion !!!"RESET,champion);
                struct team championTeam;
                file = fopen("teams.txt", "r");
                while (fread(&championTeam, sizeof(struct team), 1, file)) {
                    if (!strcmp(champion, championTeam.teamName)) {
                        championTeam.countOfChampions += 1;
                        break;
                    }
                }
                fclose(file);
                file = fopen("saveEssentialsNum.txt","r");
                for(i=0;i<4; i++){
                    fread(&ar[i],4,1,file);
                }
                fclose(file);
                ar[0]=0;
                ar[1]=0;
                ar[2]=0;
                ar[3]=1;
                file = fopen("saveEssentialsNum.txt","w");
                for(i=0;i<4;i++){
                    fwrite(&ar[i],4,1,file);
                }
                fclose(file);
                adminAccount();
                break;
            }
        case 6 :
            login();
            break;
        default :
            printf(RED"\nInvalid command"RESET);
            adminAccount();
            break;
    }

}

