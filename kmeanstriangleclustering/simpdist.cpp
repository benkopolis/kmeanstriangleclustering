#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char** argv)
{
	float a, b, c, d;
	while(true)
	{
		cin >> a;
		cin >> b;
		cin >> c;
		cin >> d;
		cout << sqrt(pow(a-c, 2.0) + pow(b-d, 2.0)) << endl;
	}
	return 0;
}
