#include <Arduino.h>
#include <iostream>
// Test Test
// test test test
// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
  
}

// Your First C++ Program



int main() {
    std::cout << "Hello World!";
    return 0;
}
