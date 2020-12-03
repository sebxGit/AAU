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
   Syntax and functionality:
     typedef struct, struct, struct and struct-array as pointer, struct as parameter, 

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

Team make_team(char *team_name, int tournament_points, int goals_scored, int goals_received){
  Team make;
  strcpy(make.team_name, team_name);
  make.tournament_points = tournament_points;
  make.goals_scored = goals_scored;
  make.goals_received = goals_received;
  return make;
}

int give_points(int team_1_goals, int team_2_goals){
  return (team_1_goals > team_2_goals) ? 3 : (team_1_goals == team_2_goals) ? 1 : 0;
}

void show_team(Team t){
  if (strcmp(t.team_name,"OB") == 0)
    printf("%s:  %d points. Goals scored: %d, Goals received: %d\n", t.team_name, t.tournament_points, t.goals_scored, t.goals_received);
  else
    printf("%s: %d points. Goals scored: %d, Goals received: %d\n", t.team_name, t.tournament_points, t.goals_scored, t.goals_received);
}

void update_Teams(Team* t, int* teams_assigned, char* team_name, int team_goals, int otherTeam_goals){
  int i;
  for(i = 0; i <= *teams_assigned; i++){
    if(strcmp(team_name, t[i].team_name) == 0){
      t[i].tournament_points += give_points(team_goals, otherTeam_goals);
      t[i].goals_scored += team_goals;
      t[i].goals_received += otherTeam_goals;
    }
    else if (i == *teams_assigned){
      *teams_assigned += 1;
      t[i] = make_team(team_name, give_points(team_goals, otherTeam_goals), team_goals, otherTeam_goals);
    }
    else if (team_name != t->team_name){
      continue;
    }
    break;
  }
}

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

void give_standings(Match* m, Team* t){
  FILE *fp;
  char str[MAX_CHARACTERS_READ];
  int teams_assigned = 0, matches_played = 0;

  fp = fopen("kampe-2019-2020.txt", "r");
  if (fp == NULL){
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  while (fgets(str, MAX_CHARACTERS_READ, fp) != NULL){
    sscanf(str, "%s     %d/%d %lf     %s - %s     %d - %d     %d", 
    &m->weekday, &m->date_day, &m->date_month, &m->time_match_start, &m->team_a, &m->team_b, &m->team_a_goals, &m->team_b_goals, &m->spectator_count);
    update_Teams(t, &teams_assigned, m->team_a, m->team_a_goals, m->team_b_goals);
    update_Teams(t, &teams_assigned, m->team_b, m->team_b_goals, m->team_a_goals);
    if (matches_played == MAX_MATCHES_PLAYED){
      break;
    }
  }
}

int main(void){
  Match *m = (Match *) malloc(MAX_MATCHES_PLAYED_SEASON * sizeof(Match));
  Team *t = (Team *) malloc(MAX_MATCHES_PLAYED_SEASON * sizeof(Team));

  if (m == NULL || t == NULL){
    printf("Cannot allocate memory. Exit.");
    exit(EXIT_FAILURE);
  }

  give_standings(m, t);

  qsort(t, MAX_TEAMS, sizeof(Team), cmpfunc);

  for(int i = 0; i < MAX_TEAMS; i++){
    show_team(t[i]);
  }

  printf("Matches played: %d\n", MAX_MATCHES_PLAYED);

  free(m);
  free(t);
}
