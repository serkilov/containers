#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

typedef long long int int64;

int64 get_tickt(){
    struct timeval now;
    gettimeofday(&now, NULL);
    int64 sec = now.tv_sec;
    int64 usec = now.tv_usec;
    return sec*1000000 + usec;
}

void do_it(float usage) {
    int total = 30000;
    int busy = (int)(total*(usage+0.15)/100.0);
    int idle = total - busy;
    if(idle < 0) {
        idle = 1;
    }
    while(1) {
        int64 start = get_tickt();
        while(get_tickt() < (start + busy)) {
            ;
        }
        usleep(idle);
    }
}

void do_sleep() {
    int idle = 1024;
    printf("In long sleep, cpu.usage will be 0.0\n");
    while(1) {
        sleep(idle);
    }
}

unsigned long long total_memory() {
    long long pages = sysconf(_SC_PHYS_PAGES);
    long long page_size = sysconf(_SC_PAGE_SIZE);

    return (pages * page_size);
}

void use_it(float usage, char *mbuf, size_t size) {
    int total = 30000;
    int busy = (int)(total*(usage+0.15)/100.0);
    int idle = total - busy;
    if(idle < 0) {
        idle = 1;
    }
    unsigned long idx = 0;
    for(idx = 0; idx < size; idx ++) {
        mbuf[idx] = 3;
    }
    printf("%lu bytes memory is in use.\n", size);
    while(1) {
        usleep(1000);
        idx = (rand() * rand()) % size;
        char ch = 'a' + idx % 26;
        //printf("\ridx=%lu", idx);
        mbuf[idx] = ch;
        int64 start = get_tickt();
        while(get_tickt() < (start + busy)) {
            ;
        }
        usleep(idle);
    }
}

int main(int argc, char* argv[]) {
    setbuf(stdout, NULL);
    printf("Usage:%s [Memory in MB] (default=200MB)\n", argv[2]);
    size_t default_num = 200;
    if(argc > 1) {
        default_num = atoi(argv[2]);
        if(default_num < 1) {
            default_num = 1;
        }
    }

    srand(time(NULL));
    unsigned long long total = total_memory();
    int mb = 1024*1024;
    printf("total.memory=%llu MB\n", total/mb);

    size_t needed = default_num * mb;
    char *mbuf = (char*)malloc(needed);
    if(mbuf == NULL) {
        printf("failed to alloc %lu MB memory.\n", needed);
        return -1;
    }

    printf("total:%llu MB memory, requested: %lu MB\n", total/mb, needed/mb);

    float usage = 10;
    if(argc > 1) {
        usage = atof(argv[1]);
    }

    if (usage > 100) {
        usage = 100;
    }

    printf("Expected CPU usage is: %.2f%%\n", usage);

    if((int)usage < 1) {
        do_sleep();
    }

    use_it(usage, mbuf, needed);

    free(mbuf);
    return 0;
}

