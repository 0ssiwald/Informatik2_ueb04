#include <stdio.h>
#include <stdlib.h>
#include "teams.h"
#include "datastructure.h"
#include "tools.h"
#include "datetime.h"



//MAXTEAMS defined in datastructure.h
   int TeamCounter = 0;
   sTeam Teams[MAXTEAMS];

void createTeam()
{
   sTeam *NewTeam = Teams + TeamCounter;

  // muss geprüft werden ob get Text sucessfull ist?
   if(TeamCounter < MAXTEAMS) // to ensure that there is still space in the array
   {
      NewTeam->NumberOfPlayers = 0;
      getText("Geben Sie bitte den Namen der Mannschaft ein \n -> ", 100, 0, &(NewTeam->Name)); //Teams + TeamCounter Zeigerschreibweise für Teams[TeamCounter]
      getText("Geben Sie bitte den Namen des Trainers ein \n -> ", 100, 1, &(NewTeam->Trainer));
      do{
         if(NewTeam->NumberOfPlayers < MAXPLAYER) // to ensure that there is still space in the array
         {
            createPlayer(NewTeam);
         }
      } while(askYesOrNo("Moechten Sie einen weiteren Spieler eingeben (j/n) ? \n"));
      clearScreen();
      TeamCounter++;
   }
}

void createPlayer(sTeam *NewTeam)
{
   sPlayer *NewPlayer = NewTeam->Players + NewTeam->NumberOfPlayers;
   char *Date_as_text = NULL;
   int Valid_Date;

   getText("Bitte geben Sie den Namen eines Spielers ein: \n -> ", 50, 0, &(NewPlayer->Name));
   do{
      getText("Geben Sie bitte das Geburtsdatum des Spielers ein: \n -> ", 50, 1, &Date_as_text);
      if(Date_as_text) // if Date_as_text is still NULL pointer dont get Date from String
         Valid_Date = getDateFromString(Date_as_text, &(NewPlayer->Birthday));
      else
         Valid_Date = 1;
   } while(!Valid_Date); // to allow empty Date input
   getNumber("Geben Sie bitte die Trikotnr. des Spilers ein: \n -> ", &(NewPlayer->ShirtNumber), 0, 99);
   NewPlayer->GoalNumber = 0;
   (NewTeam->NumberOfPlayers)++;
}

void deleteTeam()
{
   printf("deleteTeam");
   waitForEnter();
}
void deletePlayer()
{
   printf("deletePlayer");
   waitForEnter();
}
void searchPlayer()
{
   printf("searchPlayer");
   waitForEnter();
}
void sortTeams()
{
   printf("sortTeams");
   waitForEnter();
}
void listTeams()
{
   if(TeamCounter == 0)
      printf("\nKeine Mannschaften gefunden");
   else
   {
      printf("\nListe der Mannschaften\n");
      printf("======================\n \n");
      int i;
      for(i = 0; i < TeamCounter; i++)
      {
         listOneTeam(i);
         printLine('-', 21);
      }
   }
   waitForEnter();

}

void listOneTeam(int Team_Number)
{
   sTeam *current_team = Teams + Team_Number;
   sPlayer *current_player = current_team->Players;

   printf("Name               : %s \n", current_team->Name);
   if((Teams + Team_Number)->Trainer) //if not NULL
      printf("Trainer            : %s \n", current_team->Trainer);
   else
      printf("Trainer            : <dieser Posten ist verkant> \n");
   printf("Anzahl der Spieler : %d \n", current_team->NumberOfPlayers);
   printf("Spieler: \n");
   int i;
   for(i = 0; i < current_team->NumberOfPlayers; i++)
   {
      printf("%02d. %s (%d", (i + 1), current_player->Name, current_player->ShirtNumber);
      if(current_player->Birthday) //if not NULL
      {
         printf("; * ");
         printDate(current_player->Birthday);
      }
      printf(") \n");
      current_player++;
   }
}

void freePlayer(sPlayer *Player)
{
   free(Player->Name);
   free(Player->Birthday);
}

void freeTeam(sTeam *Team)
{
   int i;

   free(Team->Name);
   free(Team->Trainer);
   for (i = 0; i < Team->NumberOfPlayers; i++)
      freePlayer(Team->Players + i);
}

void freeTeams()
{
   int i;
   for (i = 0; i < TeamCounter; i++)
      freeTeam(Teams + i);
}
