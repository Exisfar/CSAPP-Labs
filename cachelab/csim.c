#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cachelab.h"

// ? 要编写缓存模拟器（csim.c），需要模拟一个直接映射缓存的行为，解析内存访问的 trace 文件，并统计 hits（命中）、misses（未命中）和 evictions（替换）。

/* 缓存模拟器的基本结构
 * 缓存模拟器的核心是模拟缓存的行为，包括：
 *  缓存行（Cache Line）：包含有效位（valid bit）、标记（tag）和数据块。
 *  直接映射缓存：每个内存地址映射到一个固定的缓存行。
 */

// 定义缓存行结构
typedef struct {
    int valid;  // 有效位
    int tag;    // 标记
    int lru;    // 用于 LRU 替换策略
} CacheLine;

// 定义缓存结构
typedef struct {
    CacheLine *lines;  // 缓存行数组
} CacheSet;

typedef struct {
    CacheSet *sets;    // 缓存组数组
    int s;             // 组索引位数
    int E;             // 每组的缓存行数
    int b;             // 块偏移位数
} Cache;

Cache initCache(int s, int E, int b) {
    Cache cache;
    int S = 1 << s;  // 组数 = 2^s
    cache.s = s;
    cache.E = E;
    cache.b = b;
    cache.sets = (CacheSet *)malloc(S * sizeof(CacheSet));
    for (int i = 0; i < S; i++) {
        cache.sets[i].lines = (CacheLine *)malloc(E * sizeof(CacheLine));
        for (int j = 0; j < E; j++) {
            cache.sets[i].lines[j].valid = 0;
            cache.sets[i].lines[j].tag = -1;
            cache.sets[i].lines[j].lru = 0;
        }
    }
    return cache;
}

void parseAddress(unsigned long address, int s, int b, int *setIndex, int *tag) {
    *setIndex = (address >> b) & ((1 << s) - 1);  // 提取组索引
    *tag = address >> (s + b);                   // 提取标记
}

void accessCache(Cache *cache, int setIndex, int tag, int *hits, int *misses, int *evictions) {
    CacheSet set = cache->sets[setIndex];
    int E = cache->E;

    // 检查是否命中
    for (int i = 0; i < E; i++) {
        if (set.lines[i].valid && set.lines[i].tag == tag) {
            (*hits)++;
            set.lines[i].lru = 0;  // 更新 LRU
            return;
        }
    }

    // 未命中
    (*misses)++;

    // 查找空闲缓存行
    for (int i = 0; i < E; i++) {
        if (!set.lines[i].valid) {
            set.lines[i].valid = 1;
            set.lines[i].tag = tag;
            set.lines[i].lru = 0;
            return;
        }
    }

    // 替换（LRU 策略）
    (*evictions)++;
    int maxLRU = -1, evictIndex = -1;
    for (int i = 0; i < E; i++) {
        if (set.lines[i].lru > maxLRU) {
            maxLRU = set.lines[i].lru;
            evictIndex = i;
        }
    }
    set.lines[evictIndex].tag = tag;
    set.lines[evictIndex].lru = 0;
}

/* 解析Trace文件 */
void replayTrace(Cache *cache, const char *traceFile, int *hits, int *misses, int *evictions) {
    FILE *file = fopen(traceFile, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open %s\n", traceFile);
        exit(1);
    }

    char operation;
    unsigned long address;
    int size;
    while (fscanf(file, " %c %lx,%d", &operation, &address, &size) > 0) {
        if (operation == 'I') continue;  // 忽略指令加载
        int setIndex, tag;
        parseAddress(address, cache->s, cache->b, &setIndex, &tag);
        accessCache(cache, setIndex, tag, hits, misses, evictions);
        if (operation == 'M') {  // 修改操作需要额外访问一次
            accessCache(cache, setIndex, tag, hits, misses, evictions);
        }
    }

    fclose(file);
}

int main(int argc, char **argv) {
    int s = 0, E = 0, b = 0;
    char *traceFile = NULL;

    // 解析命令行参数
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-s")) s = atoi(argv[++i]);
        else if (!strcmp(argv[i], "-E")) E = atoi(argv[++i]);
        else if (!strcmp(argv[i], "-b")) b = atoi(argv[++i]);
        else if (!strcmp(argv[i], "-t")) traceFile = argv[++i];
    }

    // 初始化缓存
    Cache cache = initCache(s, E, b);

    // 模拟缓存
    int hits = 0, misses = 0, evictions = 0;
    replayTrace(&cache, traceFile, &hits, &misses, &evictions);

    // 输出结果
    printSummary(hits, misses, evictions);

    return 0;
}
