#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <cmath>
using namespace std;


void DevolverCambio(double p, vector<double> c, vector<double> &x, int n) {
	double act= 0;
	double j = n;
	while (act != p) {
		while (c[j] > (p-act) && j > 0 ){
			j--;
		}
		if (j==0) {
			cout << "No existe solucion" << endl;
		}
		x[j]=floor((p-act)/c[j]);
		act = act + c[j]*x[j];
	}
}



int main(){
	vector<double> c = {0.01,0.02,0.05,0.1,0.2,0.5,1,2};
	vector<double> ans = {0,0,0,0,0,0,0,0};
	DevolverCambio(3.89, c, ans, 7);
	for(int i = 0; i < 8; ++i){
		cout << ans[i] << " ";
	}	
	cout << endl;
	return 0;
}
