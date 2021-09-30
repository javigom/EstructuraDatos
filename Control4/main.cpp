/*	
	Javier Gómez Moraleda
	Mario Alcolea Alcolea
*/

#include <iostream>
#include "cola.h"

using namespace std;

unsigned int afortunado(unsigned int n, unsigned int m) { //n>=1  m>=2 
      
	Cola <unsigned int> q;
	unsigned int afortunados = n;

	//Rellenamos la cola con todos los alumnos
	for (unsigned int i = 1; i <= n; i++) {
		q.pon(i);
	}

	int i = 1;

	//Cuando solo quede un alumno, será el afortunado
	while (afortunados > 1) {
		int actual = q.primero();
		q.quita();

		if (i % m != 0) {
			q.pon(actual);
		}

		else {
			afortunados--;
		}

		i++;
	}

	return q.primero();
}


int main() {
    int n,m;
	while((cin >> n)) {
	   cin >> m;
       cout << afortunado(n,m) << endl;	   
	}
	return 0;
}	
