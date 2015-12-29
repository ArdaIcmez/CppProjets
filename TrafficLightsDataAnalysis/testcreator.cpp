#include <iostream>
#include <fstream>
using namespace std;
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
int main () {
  ofstream myfile;
  myfile.open ("test1.txt");
  int year=2014,month=0,day=1,hour=0,minute=0,second=0,d7=1,traffic=0;
  int counter;
  int minMinute = 1;
  int maxMinute=5;
  int minTraf = 0;
  int maxTraf = 3;
  int idCapteur=1;
  //int count[3][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0}};
  char trafficC='V';
  for(counter=0;counter<186963;counter++)
  {
	  myfile << "ADD " << idCapteur << " " << year << " " << month << " " << day << " " <<hour<<" "<<minute<<" "<<second<<" "<<d7<<" "<<trafficC<<endl;
	  //count[idCapteur-1][traffic]++;
	  minute += minMinute + (rand() % (int)(maxMinute - minMinute + 1));
	  if(minute >= 60)
	  {
		  hour++;
		  if(hour>23)
		  {
			  hour=0;
			  d7++;
			  if(d7>7)
			  {
				  d7=1;
			  }
			  day++;
			  if(day>30)
			  {
				  day=1;
				  month++;
			  }
		  }
		  minute%=60;  
	  }
	  traffic = (rand() % (int)(maxTraf + 1));
	  switch(traffic)
	  {
		  case 0:
		  trafficC = 'V';
		  break;
		  
		  case 1:
		  trafficC = 'J';		  
		  break;
		  
		  case 2:
		  trafficC = 'R';		  
		  break;
		  
		  case 3:
		  trafficC = 'N';		  
		  break;
	  }
	  idCapteur = 1 + (rand() % 1500);
  }
 /*for(int j(0);j<3;j++)
  {
	  for(int k(0);k<4;k++)
	  {
		  cout << count[j][k] << " " ;
	  }
	  cout << endl;
}  */
  myfile.close();
  return 0;
}
