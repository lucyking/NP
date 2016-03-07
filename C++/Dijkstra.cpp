#include "Dijkstra.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>

void microseconds_sleep(unsigned long uSec){
	struct timeval tv;
	tv.tv_sec = uSec/1000000;
	tv.tv_usec = uSec%1000000;
	int err;
	do{
		err=select(0,NULL,NULL,NULL,&tv);
	}while(err<0 && errno==EINTR);
}

void dijkstra(const digrafo_pesado& g, int v, vcosto& dist) {
    int n = g.size();
    cola c;
    vbool vistos(n, false);

    dist[v] = 0;
    c.insert(estimado(dist[v], v));
    while(!c.empty()) {
        estimado es = PRIMERO(c); // look for the nearest element
        c.erase(es); // tail it out
        nodo p = es.second; // p is the node itself

        vistos[p] = true;
        forall(it, g[p]) { // for each neighbor p
            eje e = *it;
            costo s = e.first;
            nodo w = e.second;

            if(vistos[w]) continue; // if you already know the best distance, I do nothing
            costo nuevo = dist[p] + s; //cost of going to p, and use and
            if(dist[w] <= nuevo) continue; // if I can not improve w p, I do nothing
            UPDATE(c, w, dist[w], nuevo); // I update the tail
            dist[w] = nuevo; // I update the estimate of the cost to w
        }

    }
}

int main(int argc,char* argv[]) {
    printf(">>>INFINITO:%lf\n",numeric_limits<double>::infinity());
    int n, m;
    nodo v, w;
    costo c;
    time_t start,end=0;
    start = clock();

    cin >> n;
    digrafo_pesado G(n);
    vcosto dist(n, INFINITO);

    cin >> m;
    while(m--) {
        cin >> v >> w >> c;
        G[v].push_back(eje(c, w));
    }

    cin >> v;
    dijkstra(G, v, dist);
    while(cin >> w) cout << "distance " << v << " to " << w << ": " << dist[w] << endl;

    //sleep(10);
    printf("%ld\n",clock());
    //microseconds_sleep(1900000);
    printf("%ld\n",clock());
    printf("%ld\n",CLOCKS_PER_SEC);
    end = clock();
    printf(">>>%f\n",(double)(end-start)/CLOCKS_PER_SEC);
    //printf(">>>%.10lf\n",(double)(end-start)/CLOCKS_PER_SEC);
    return 0;

}
