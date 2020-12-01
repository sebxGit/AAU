#include <stdio.h>
#include <string.h>
#define MAX_MATCHES_PLAYED 182
#define MAX_CHARACTERS_READ 70
#define WKD_MAX 5
#define TM_NAME_MAX 5

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

int main(void){
  Team array[MAX_MATCHES_PLAYED];
  FILE *fp;
  char str[MAX_CHARACTERS_READ];

  fp = fopen("kampe-2019-2020.txt", "r");
  if (fp == NULL){
    perror("Error opening file");
    return -1;
  }

  while (fgets(str, MAX_CHARACTERS_READ, fp) != NULL){
    Match m;
    sscanf(str, "%s     %d/%d %lf     %s - %s     %d - %d     %d", &m.weekday, &m.weekday, &m.date_month, &m.time_match_start, &m.team_a, &m.team_b, &m.team_a_goals, &m.team_b_goals, &m.spectator_count);
    printf("%s", str);
    printf("%s     %d/%d %.2lf     %s - %s     %d - %d     %d", m.weekday, m.weekday, m.date_month, m.time_match_start, m.team_a, m.team_b, m.team_a_goals, m.team_b_goals, m.spectator_count);
    break;
  }
}