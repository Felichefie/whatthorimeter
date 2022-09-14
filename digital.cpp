#include "digital.h"

void ledToggle(void){
  digitalWrite(led_testigo, !digitalRead(led_testigo));
}
