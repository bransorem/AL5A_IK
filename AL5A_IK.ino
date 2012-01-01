#include "arm.h"
 
Arm al5a;
int i = 0;
int j = 0;
const int len = 6;
char arr[len][len];

void setup(){
  Serial.begin(115200);
  delay(500);
  al5a.cancel();
  delay(500);
}

void loop(){
  
  i = 0;
  j = 0;
  
  // Zero out array
  for (int w=0; w<len; w++){
    for (int v=0; v<len; v++)
      arr[w][v] = 0;
  }
  
  //arm.test();
  
  if (Serial.available()){
    // Read in all characters
    while (Serial.available()){
      char in = Serial.read();
      // CSV's
      if (in != ','){
        arr[i][j] = in;
        j++;
      }
      // for each value
      else { i++; j=0; }
      delay(10);
    }
    if (DEBUG) { Serial.println("Testing for loop"); Serial.println(i); }
    if (i > 3){
      // WRITE AS SERVOS
      int a = atoi(arr[0]);
      int b = atoi(arr[1]);
      int c = atoi(arr[2]);
      int d = atoi(arr[3]);
      int e = atoi(arr[4]);
      int f = atoi(arr[5]);
      int t = atoi(arr[6]);
      
      al5a.move(a, b, c, d, e, f, t);
    }
    else {
      // WRITE AS X,Y,Z
      int x = atoi(arr[0]);
      int y = atoi(arr[1]);
      int z = atoi(arr[2]);
      int t = atoi(arr[3]);
      
      al5a.move(x, y, z, t);
    }
  }
}


