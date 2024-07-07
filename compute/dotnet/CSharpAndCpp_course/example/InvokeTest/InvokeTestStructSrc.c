 

#include<stdio.h>

//gcc -shared -fPIC  InvokeTestStructSrc.c  -o libpoint.dll

typedef struct {
    int x;
    int y;
} Point;


Point* create_point(int x, int y);
void print_point(Point* p);


 // 实现
Point* create_point(int x, int y) {
    static Point p;
    p.x = x;
    p.y = y;
    return &p;
}

void print_point(Point* p){
    printf("Point coordinates: (%d, %d)\n", p->x, p->y);
}