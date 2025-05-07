#include "cachelab.h"
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Global settings
int verbose = 0;

// Cache declaration
struct CACHE {
    struct LINE {
        long valid;
        long tag;
        long lru;
    } *line;
    long tag_mask, set_index_mask, block_offset_mask;
    long hits, misses, evictions;
    long lru_counter;
    char* msg_hit, *msg_miss, *msg_miss_eviction;
    int s, E, b;
} cache;

// -h options
void print_help() 
{
    printf("Usage: ./csim [-hv] -s <num> -E <num> -b <num> -t <file>\n\
Options:\n\
  -h         Print this help message.\n\
  -v         Optional verbose flag.\n\
  -s <num>   Number of set index bits.\n\
  -E <num>   Number of lines per set.\n\
  -b <num>   Number of block offset bits.\n\
  -t <file>  Trace file.\n\
\n\
Examples:\n\
  linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace\n\
  linux>  ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
  exit(0);
}

// 2^s
int pow2(int s) {return 1 << s;}


// Initialize cache
void setup() 
{
    cache.line = (struct LINE *)malloc(sizeof(struct LINE) * pow2(cache.s) * cache.E);
    /*
    Tag: m - (s + b) bits
    Set index : s bits
    Block offset : b bits
    */
    // cache.tag_mask = (1 << (64 - cache.s - cache.b)) - 1;
    cache.set_index_mask = ((1 << cache.s) - 1);
    cache.block_offset_mask = (1 << cache.b) - 1;
    cache.hits = 0;
    cache.misses = 0;
    cache.evictions = 0;
    cache.lru_counter = 0;
    cache.msg_hit = "hit";
    cache.msg_miss = "miss";
    cache.msg_miss_eviction = "miss eviction";
}

// Cleanup cache
void cleanup() { free(cache.line); }

char* access(unsigned long addr, unsigned long size) {
    long tag = (addr >> (cache.s + cache.b));
    long set_index = (addr >> cache.b) & (cache.set_index_mask);

    // Wrteup of pdf doc.
    // 1. locate the set
    // 2. check if any line exists
    // 3. check if the tag matches
    // 4. check the valid bit
    // 5. locate data starting at the offset(ignoring in this simulation)
    // upon miss !(2 and 3 and 4)
    // type of miss: Compulsory, Capacity, Conflict

    // check hit
    for(int i = 0; i < cache.E; i++) {
        struct LINE *line = &cache.line[set_index * cache.E + i];
        if(line->valid && line->tag == tag) {
            line->lru = cache.lru_counter++;
            cache.hits++;
            return cache.msg_hit;
        }
    }

    // check miss (compulsory)
    for(int i = 0; i < cache.E; i++) {
        struct LINE *line = &cache.line[set_index * cache.E + i];
        if(!line->valid) {
            line->valid = 1;
            line->tag = tag;
            line->lru = cache.lru_counter++;
            cache.misses++;
            return cache.msg_miss;
        }
    }

    // eviction (conflict)
    long minlru = 0;
    for(int i = 0; i < cache.E; i++) {
        struct LINE *line = &cache.line[set_index * cache.E + i];
        if(line->lru < cache.line[set_index * cache.E + minlru].lru) {
            minlru = i;
        }
    }
    struct LINE *line = &cache.line[set_index * cache.E + minlru];
    line->tag = tag;
    line->lru = cache.lru_counter++;
    cache.misses++;
    cache.evictions++;
    return cache.msg_miss_eviction;

    // Capacity miss is not considered in this simulation (maybe...?)
    // Given trace files' size is small enough, 
    // and other commands like 'ls -al' also ok in my pc. 
}

int main(int argc, char* argv[])
{
    // Parsing options
    int opt;
    char *traceFile;
    bool flag[4] = {false, false, false, false};
    while((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
        switch(opt) {
            case 'h': {print_help(); break;}
            case 'v': {verbose = 1; break;}
            case 's': {cache.s = atoi(optarg); flag[0] = true; break;}
            case 'E': {cache.E = atoi(optarg); flag[1] = true; break;}
            case 'b': {cache.b = atoi(optarg); flag[2] = true; break;}
            case 't': {traceFile = optarg; flag[3] = true; break;}
            case ':': {
                printf("./csim: Missing required command line argument\n");
                print_help();
                break;
            }
            case '?': {
                printf("./csim: invalid option -- '%d'\n", opt);
                print_help();
                break;
            }
        }   
    }
    if(!flag[0] || !flag[1] || !flag[2] || !flag[3]) {
        printf("./csim: Missing required command line argument\n");
        print_help();
    }
    setup();
    FILE* f = fopen(traceFile, "r");
    char op;
    unsigned long addr, size;
    while(fscanf(f, "%c %lx,%ld", &op, &addr, &size) != EOF) {
        char *res1, *res2 = NULL;
        switch(op) {
            case 'L':
                res1 = access(addr, size);
                break;
            case 'M':
                res1 = access(addr, size);
                res2 = access(addr, size);
                break;
            case 'S':
                res1 = access(addr, size);
                break;
        }
        if(verbose) {
            printf("%c %lx,%ld %s", op, addr, size, res1);
            if(res2 != NULL) printf(" %s", res2);
            printf("\n");
        }
    }
    fclose(f);
    printSummary(cache.hits, cache.misses, cache.evictions);
    cleanup();
    return 0;
}