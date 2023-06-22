#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_MATCHES_PLAYED 26
#define MAX_MATCHES_PLAYED_SEASON 182
#define MAX_CHARACTERS_READ 70
#define MAX_TEAMS 14
#define WKD_MAX 5
#define TM_NAME_MAX 5

/* Sebastian Truong, struon20@student.aau.dk, Grp. A409, Aalborg Universitet Software 1. semester 2020 
   
   Syntax and functionality from the internet:
     struct-array as pointer, struct as parameter, cmpfunc (to qsort)
   
   Help from other student:
     from qsort -> cmpfunc: get access to the whole struct array (tried t->tournament_points  
                            as if tournament_points are arrays in struct arrays)
*/

typedef struct {
  char weekday[WKD_MAX];
  int date_day;
  int date_month;
  double time_match_start;
  char team_a[TM_NAME_MAX];
  char team_b[TM_NAME_MAX];
  int team_a_goals;
  int team_b_goals;
  int spectator_count;
} Match;

typedef struct {
  char team_name[TM_NAME_MAX];
  int tournament_points;
  int goals_scored;
  int goals_received;
} Team;

Team make_team(char *team_name, int tournament_points, int goals_scored, int goals_received);
int give_points(int team_1_goals, int team_2_goals);
void show_team(Team t);
void update_Teams(Team* t, int* teams_assigned, char* team_name, int team_goals, int otherTeam_goals);
int cmpfunc(const void *a, const void *b);
void give_standings(Team* t);

int main(void){
  int i;
  Team *t = (Team *) malloc(MAX_MATCHES_PLAYED_SEASON * sizeof(Team));
  if (t == NULL){
    printf("Cannot allocate memory. Exit.");
    exit(EXIT_FAILURE);
  }

  give_standings(t);

  qsort(t, MAX_TEAMS, sizeof(Team), cmpfunc);

  for(i = 0; i < MAX_TEAMS; i++){
    show_team(t[i]);
  }
  free(t);
  return 0;
}

/* Creates a Team struct as an element of a Team struct array. */
Team make_team(char *team_name, int tournament_points, int goals_scored, int goals_received){
  Team make;
  strcpy(make.team_name, team_name);
  make.tournament_points = tournament_points;
  make.goals_scored = goals_scored;
  make.goals_received = goals_received;
  return make;
}

/* Assigns points: win: 3 points, tie: 1 point, loss: 0 points. */
int give_points(int team_1_goals, int team_2_goals){
  return (team_1_goals > team_2_goals) ? 3 : (team_1_goals == team_2_goals) ? 1 : 0;
}

/* Displays the stats of a team */
void show_team(Team t){
  if (strcmp(t.team_name,"OB") == 0)
    printf("%s:  %d points. Goals scored: %d, Goals received: %d\n", t.team_name, t.tournament_points, t.goals_scored, t.goals_received);
  else
    printf("%s: %d points. Goals scored: %d, Goals received: %d\n", t.team_name, t.tournament_points, t.goals_scored, t.goals_received);
}

/* Creates a new team or updates stats */
void update_Teams(Team* t, int* teams_assigned, char* team_name, int team_goals, int otherTeam_goals){
  int i;
  for(i = 0; i <= *teams_assigned; i++){
    /* Updates score if name found. */
    if(strcmp(team_name, t[i].team_name) == 0){
      t[i].tournament_points += give_points(team_goals, otherTeam_goals);
      t[i].goals_scored += team_goals;
      t[i].goals_received += otherTeam_goals;
    }
    /* Creates new team if name not found. */
    else if (i == *teams_assigned){
      *teams_assigned += 1; /* Not val++ because of pointer arithmetic.*/
      t[i] = make_team(team_name, give_points(team_goals, otherTeam_goals), team_goals, otherTeam_goals);
    }
    else if (team_name != t->team_name){
      continue;
    }
    break;
  }
}

/* Returns a comparison to qsort. Compares points and if equal goals scored. */
int cmpfunc(const void *a, const void *b){
  /* Gets the addresses of the Team array elements*/  
  Team l = *(const Team *)a; 
  Team r = *(const Team *)b;
  int result = r.tournament_points - l.tournament_points;

  /*If points are equal: Check goal difference instead.*/
  if(result == 0)
    result = r.goals_scored - l.goals_scored;
  return result;
}

void give_standings(Team* t){
  FILE *fp;
  Match m;
  char str[MAX_CHARACTERS_READ];
  int teams_assigned = 0, matches_played = 0;

  fp = fopen("kampe-2019-2020.txt", "r");
  if (fp == NULL){
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  
  /* Reads a line continuously until EOF, error or max matches played reached*/
  while (fgets(str, MAX_CHARACTERS_READ, fp) != NULL){
    /* Assigns all data from file to variable names in the struct m*/
    sscanf(str, "%s     %d/%d %lf     %s - %s     %d - %d     %d", 
    &m.weekday, &m.date_day, &m.date_month, &m.time_match_start, &m.team_a, 
    &m.team_b, &m.team_a_goals, &m.team_b_goals, &m.spectator_count);

    /* Updates teams score for one team at a time. */
    update_Teams(t, &teams_assigned, m.team_a, m.team_a_goals, m.team_b_goals);
    update_Teams(t, &teams_assigned, m.team_b, m.team_b_goals, m.team_a_goals);
    if (matches_played == MAX_MATCHES_PLAYED)
      break;
  }
}
