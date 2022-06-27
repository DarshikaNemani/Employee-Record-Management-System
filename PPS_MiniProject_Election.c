#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#define CANDIDATE_COUNT 4

char CANDIDATES[][50] = {"Nelson Canella","Christopher Maximus","Jim Brar","Ronald Rump"};

struct candidate {
    char name[50];
    int votes;
} person[CANDIDATE_COUNT];

int spoiledtvotes=0;

FILE *fp;

void holdScreen(){
	printf("\n\n Press a key to continue the program ");
    char c= getchar();
    system("cls");
}

void castVote(){
    int i, choice;
    printf("\n\n #### Please choose your Candidate ####\n\n");

    for (i = 0; i < CANDIDATE_COUNT; i++)
    {
        printf("\n %d. %s",i + 1, person[i].name);
    }
    printf("\n %d. %s",CANDIDATE_COUNT + 1, "None of These");

    printf("\n\n Input your choice (1 - %d) : ", CANDIDATE_COUNT + 1);
    scanf("%d",&choice);
    fflush(stdin);
    if (choice >= 1 && choice <= CANDIDATE_COUNT)
    {
        person[choice - 1].votes++;
        printf("\n Thanks for vote !!");
    }
    else if (choice == CANDIDATE_COUNT + 1)
    {
        spoiledtvotes++;
        printf("\n Thanks for vote !!");
    }
    else
	{
        printf("\n Error: Wrong Choice !! Please retry");
    }
    fp=fopen("Election.txt","w");
    for(i=0;i<CANDIDATE_COUNT;i++)
    {
        fwrite(&person[i],sizeof(struct candidate),1,fp); 
    }
    putw(spoiledtvotes,fp);
    fclose(fp);
    free(fp);
    //hold the screen
    holdScreen();
}

void votesCount(){
    int i;
    fp=fopen("Election.txt","r");
    for(i=0;i<CANDIDATE_COUNT;i++)
    {
        fread(&person[i],sizeof(struct candidate),1,fp);
    }
    spoiledtvotes=getw(fp);
    printf("\n\n ##### Voting Statistics #####");
    for (i = 0; i < CANDIDATE_COUNT; i++)
    {
        printf("\n %s - %d ", person[i].name, person[i].votes);
    }
    printf("\n %s - %d ", "Spoiled Votes", spoiledtvotes); 
    fclose(fp);
    free(fp);
    //hold the screen
    holdScreen();
}

void getLeadingCandidate(){
    int i, max = 0, maxPeople = 0, maxPerson;
    fp=fopen("Election.txt","r");
    for(i=0;i<CANDIDATE_COUNT;i++)
    {
        fread(&person[i],sizeof(struct candidate),1,fp);
    }
    
    printf("\n\n #### Leading Candidate ####\n\n");

    for (i = 0; i < CANDIDATE_COUNT; i++)
    {
        if (person[i].votes > max)
        {
            max = person[i].votes;
            maxPerson = i;
        }
    }
    for (i = 0; i < CANDIDATE_COUNT; i++)
    {
        if (person[i].votes == max)
            maxPeople++;  
    }
    if (maxPeople > 1)
        printf(" ------- Warning !!! No-win situation --------");  
    else
        printf(" Leading Candidate is : %s", person[maxPerson].name);
	
	fclose(fp);
    free(fp);
    //hold the screen
    holdScreen();
}

int main()
{
    int i;
    int choice;
    for (i = 0; i < CANDIDATE_COUNT; i++)
    {
        person[i].votes = 0;
    }
    for (i = 0; i < CANDIDATE_COUNT; i++)
    {
        strcpy(person[i].name, CANDIDATES[i]);
    }

    do
	{
        printf("\n\n ---------------------------------------------");
        printf("\n\n ###### Welcome to Election/Voting 2022 ######");
        printf("\n\n 1. Cast the Vote");
        printf("\n 2. Find Vote Count");
        printf("\n 3. Find leading Candidate");
        printf("\n 0. Exit");

        printf("\n\n Please enter your choice : ");
        scanf("%d", &choice);
        fflush(stdin);
        switch(choice)
        {
        case 1: castVote();break;
        case 2: votesCount();break;
        case 3: getLeadingCandidate();break;
        case 0: break;
        default: 
			printf("\n Error: Invalid Choice");
			//hold the screen
			holdScreen();
        }

    } while(choice != 0);

    return 0;
}
