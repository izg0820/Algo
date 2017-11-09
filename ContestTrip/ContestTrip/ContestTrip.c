#include<stdio.h>
#include<string.h>
#define IN 100
#define MAX 1000

int dijkstra(int cost[][IN], int path[IN], int target, int city_count);
int search(struct info set[IN], int set_count, int city_count);
int match(struct NODE city[IN], struct term str[10], int city_count, int m);
int match2(struct NODE city[IN], char str[10], int city_count);
int check(struct term2 schedule[IN], int a, int target, int term[10]);
int find_index(struct term2 schedule[IN], int a, int target, int term[10]);
void print(int path[IN], int j, int a, struct term2 schedule[IN], struct NODE city[IN], int city_count);

struct NODE {
	int city_id;
	char city[10];
};
struct info {
	int departure;
	int arrival;
};
struct term {
	int time;
	char name[10];
};
struct term2 {
	int time;
	int id;
};

void main()
{
	int tc_count, city_count, line_count, pc_count, start_time;
	struct NODE city[IN];
	struct info set[IN];
	struct term schedule[IN];
	struct term2 schedule2[IN];
	int set_size = 1;
	int cost[IN][IN];
	char departure[10];
	char arrival[10];
	int schedule_size = 0;
	int depar_id, arrival_id;
	int term[10], term2[10];
	int c, d, path_size;
	int path[10];
	int real_cityCount;

	set[0].arrival = 0;
	set[0].departure = 0;
	for (int i = 0; i < IN; i++) {
		for (int j = 0; j < IN; j++) {
			cost[i][j] = MAX;
		}
	}

	scanf("%d", &tc_count);
	for (int i = 0; i < tc_count; i++) {
		scanf("%d", &city_count);
		real_cityCount = city_count;
		printf("Input the name of the city\n");
		for (int j = 0; j < city_count; j++) {
			scanf("%s", &city[j].city);
			city[j].city_id = j + 1;
		}
		
		scanf("%d", &line_count);
		for (int k = 0; k < line_count; k++) {
			scanf("%d", &pc_count);
			for (int n = 0; n < pc_count; n++) {
				scanf("%d %s", &schedule[n].time, &schedule[n].name);
				schedule2[schedule_size].time = schedule[n].time;
				schedule2[schedule_size++].id = match(city, schedule, city_count, n);
			}

			//check  whether the input schedule  is duplicated 
			for (int m = 0; m < pc_count - 1; m++) {
				set[set_size].departure = match(city, schedule, city_count, m);
				set[set_size].arrival = match(city, schedule, city_count, m + 1);
				if (search(set, set_size, city_count) == 1) {
					city[city_count].city_id = city_count++;
					strcpy(city[set[set_size].arrival].city, schedule[m].name);
				}
				cost[set[set_size].departure][set[set_size].arrival] = schedule[m + 1].time - schedule[m].time;
				set_size++;
			}
		}

		
		scanf("%d", &start_time);
		set[set_size].departure = 0;
		scanf("%s", &departure);

		//check that there are more than two ways to go from home to departure 
		depar_id = match2(city, departure, real_cityCount);
		c = check(schedule2, schedule_size, depar_id, term);

		if (c == 1) {
			cost[0][depar_id] = term[0] - start_time;
		}
		else if (c > 1) {
			strcpy(city[city_count++].city, departure);
			city[city_count-1].city_id = city_count;
			cost[0][depar_id] = term[0] - start_time;
			for (int i = 1; i < c; i++) {
				cost[0][city_count] = term[i] - start_time;
			}
			for (int i = 1; i < c; i++) {
				d = find_index(schedule2, schedule_size, depar_id, term2);
				cost[city_count][schedule2[d + 1].id] = cost[depar_id][schedule2[d + 1].id];
				cost[depar_id][schedule2[d + 1].id] = MAX;
			}
		}
		scanf("%s", &arrival);
		arrival_id = match2(city, arrival, real_cityCount);

		path_size = dijkstra(cost, path, arrival_id, city_count);
		print(path, path_size, schedule_size, schedule2, city, city_count);
	}
}

/*
*purpose: calculation shortest path
*input : cost table, path table, target, the number of cities
*output : path table size
*/
int dijkstra(int cost[][IN], int path[IN], int target, int city_count)
{
	int dist[IN], prev[IN], selected[IN] = { 0 }, i, m, min, start, d, j;

	for (i = 0; i < city_count + 1; i++) {
		dist[i] = MAX;
		prev[i] = -1;
	}
	start = 0;
	selected[start] = 1;
	dist[start] = 0;

	while (selected[target] == 0) {
		min = MAX;
		m = 0;
		for (i = 1; i < city_count + 1; i++) {
			d = dist[start] + cost[start][i];
			if (d < dist[i] && selected[i] == 0) {
				dist[i] = d;
				prev[i] = start;
			}
			if (min > dist[i] && selected[i] == 0) {
				min = dist[i];
				m = i;
			}
		}
		start = m;
		selected[start] = 1;
	}
	start = target;
	j = 0;

	while (start != -1) {
		path[j++] = start;
		start = prev[start];
	}
	path[j] = 0;
	return j;
}

/*
*purpose: check  whether the input schedule  is duplicated
*input : set table,set size, the number of cities
*output : none
*/
int search(struct info set[IN], int set_count, int city_count)
{
	int m = city_count;
	for (int i = 0; i < set_count; i++) {
		if ((set[set_count].arrival == set[i].arrival) && (set[set_count].departure == set[i].departure))
			return 1;
		else
			return 0;
	}
}

/*
*purpose: Returns an id that matches the name
*input : city struct table, schedule struct, the number of cities, curr_schedule point
*output : city_id
*/
int match(struct NODE city[IN], struct term schedule[10], int city_count, int m)
{
	for (int i = 0; i < city_count; i++) {
		if (strcmp(city[i].city, schedule[m].name) == 0)
			return city[i].city_id;
	}
}

/*
*purpose: Returns an id that matches the name
*input : city struct table, city_name, the number of cities,
*output : city_id
*/
int match2(struct NODE city[IN], char str[10], int city_count)
{
	for (int i = 0; i < city_count; i++) {
		if (strcmp(city[i].city, str) == 0)
			return city[i].city_id;
	}
}

/*
*purpose:  check if there are any targets on this schedule.
*input : schedule struct table, schedule table size , target_id, term table
*output : term table size
*/
int check(struct term2 schedule[IN], int a, int target, int term[10])
{
	int b = 0;
	for (int i = 0; i < a; i++) {
		if (schedule[i].id == target)
			term[b++] = schedule[i].time;
	}
	return b;
}

/*
*purpose: Returns a index of target in schedule  struct table
*input : schedule struct table, schedule table size , target_id, term table
*output : index of target
*/
int find_index(struct term2 schedule[IN], int a, int target, int term[10])
{
	int b = 0;
	for (int i = 0; i < a; i++) {
		if (schedule[i].id == target)
			term[b++] = i;
	}
	return term[b - 1];
}

/*
*purpose: Print the result
input: path table, path table size, schedule2 table size,struct city table, the number of cities
output: none
*/
void print(int path[IN], int j, int a, struct term2 schedule[IN], struct NODE city[IN], int city_count)
{
	int arrival_time;
	int depart_time = schedule[0].time;
	int arrival_id = path[0];
	int depart_id = path[j - 2];
	char arrival[10];
	char depart[10];

	for (int i = 0; i < a - 1; i++) {
		if (path[0] == schedule[i + 1].id&&path[1] == schedule[i].id)
			arrival_time = schedule[i + 1].time;
	}
	for (int i = 0; i < city_count; i++) {
		if (city[i].city_id == arrival_id)
			strcpy(arrival, city[i].city);
		if (city[i].city_id == depart_id)
			strcpy(depart, city[i].city);
	}
	
	printf("\n\n");
	printf("%d %s\n", depart_time, depart);
	printf("%d %s\n", arrival_time, arrival);
}
