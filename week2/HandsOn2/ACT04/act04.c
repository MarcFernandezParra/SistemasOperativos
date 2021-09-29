#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    float x;
    float y;
} point ;

typedef struct {
    point p1;
    point p2;
} line;

float dist( line L ){
    return ( sqrt((L.p1.x - L.p2.x) * (L.p1.x - L.p2.x) + (L.p1.y - L.p2.y) * (L.p1.y - L.p2.y)));
}
 
int main(){
 
    line l;

    printf("The coordinates of the point A are: ");
    scanf("%f %f",&l.p1.x,&l.p1.y);
    
    printf("\nThe coordinates of the point B are: ");
    scanf("%f %f",&l.p2.x,&l.p2.y);
    
    printf("\nThe distance between A and B is %f\n", dist(l));

    exit (0);
}