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
        estimado es = PRIMERO(c); // busco al elemento más cercano a v
        c.erase(es); // lo saco de la cola
        nodo p = es.second; // p es el nodo en sí
        
        vistos[p] = true;
        forall(it, g[p]) { // por cada vecino de p
            eje e = *it;
            costo s = e.first;
            nodo w = e.second;
            
            if(vistos[w]) continue; // si ya sé la mejor distancia, no hago nada
            costo nuevo = dist[p] + s; // costo de ir hasta p, y usar e
            if(dist[w] <= nuevo) continue; // si no puedo mejorar a w con p, no hago nada
            UPDATE(c, w, dist[w], nuevo); // actualizo la cola
            dist[w] = nuevo; // actualizo el estimado del costo a w
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
	while(cin >> w) cout << "Distancia de " << v << " a " << w << ": " << dist[w] << endl;

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
