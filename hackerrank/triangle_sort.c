#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
https://www.hackerrank.com/challenges/small-triangles-large-triangles/problem


Sample Input 0

3
7 24 25
5 12 13
3 4 5


Sample Output 0

3 4 5
5 12 13
7 24 25
 */

struct triangle
{
	int a;
	int b;
	int c;
};

typedef struct triangle triangle;
struct tarea { 
    int a, b, c;
    float area;
};
void get_areas ( struct tarea * ta, triangle * tr, int n ) {
    int k;
    float fa, fb, fc, p;
    for ( k=0; k<n; ++k ) {
        ta[k].a = tr[k].a;
        ta[k].b = tr[k].b;
        ta[k].c = tr[k].c;
        fa = (float)tr[k].a;
        fb = (float)tr[k].b;
        fc = (float)tr[k].c;
        p = (fa+fb+fc)/2.0;
        ta[k].area = sqrtf(p * (p-fa) * (p-fb) * (p-fc));
    }
}

int tarea_cmp ( const void * a, const void * b ) {
    struct tarea * ta = (struct tarea*)a;
    struct tarea * tb = (struct tarea*)b;
    if ( ta->area < tb->area ) {
        return -1;
    } else if ( ta->area > tb->area ) {
        return 1;
    }
    return 0;
}

void sort_by_area(triangle* tr, int n) {
	/**
	* Sort an array a of the length n
	*/
    int k,idx;
    struct tarea * ta = calloc(n,sizeof(*ta));

    get_areas(ta,tr,n);
    qsort(ta,n,sizeof(ta[0]),tarea_cmp);

    for ( k=0; k<n; ++k ) {
        tr[k].a = ta[k].a;
        tr[k].b = ta[k].b;
        tr[k].c = ta[k].c;
    }
}


int main()
{
	int n;
	scanf("%d", &n);
	triangle *tr = malloc(n * sizeof(triangle));
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
	}
	sort_by_area(tr, n);
	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
	}
	return 0;
}