#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

const char * currentTime() {
    time_t mytime = time(0);
    char * time_str = ctime(&mytime);
    time_str[strlen(time_str)-1] = '\0';
    return time_str;
}


int currentMonth() {
    time_t mytime = time(0);
    struct tm *current_time;
    current_time = localtime(&mytime);
    return (current_time->tm_mon)+1;
}


int currentYear() {
    time_t mytime = time(0);
    struct tm *current_time;
    current_time = localtime(&mytime);
    return (current_time->tm_year)+1900;
}


int currentDayOfMonth() {
    time_t mytime = time(0);
    struct tm *current_time;
    current_time = localtime(&mytime);
    return (current_time->tm_mday);
}


double executionTime(void (*function)()){
    time_t begin = time(NULL);
    (* function)();
    time_t end = time(NULL);
    return (double)(end - begin) * 1000000 / CLOCKS_PER_SEC;
}


void sleep10sec(){
    sleep(10);
}


void changeTime(time_t time, int days) {
    struct tm *tm = localtime(&time);
    tm->tm_mday+=days;
    mktime(tm);
    printf("%s\n", asctime(tm));
}


const char * laterHour(char * time1, char * time2){
    int H1, M1, S1, H2, M2, S2;
    sscanf(time1, "%d:%d:%d", &H1, &M1, &S1);
    sscanf(time2, "%d:%d:%d", &H2, &M2, &S2);
    if (H1*3600+M1*60+S1 > H2*3600+M2*60+S2) return time1;
    else return time2;
}

int main() {
    time_t mytime = time(0);
    printf("current time: %s\n", currentTime());
    printf("current month: %d\n", currentMonth());
    printf("current year: %d\n", currentYear());
    printf("current day of month: %d\n", currentDayOfMonth());
    printf("execution time of sleep10sec function: %f\n", executionTime(sleep10sec));
    changeTime(mytime, 365);
    printf("later hour: %s\n", laterHour("21:37:00", "15:21:30"));
}
