#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

long quantize(float value) {
  return lroundf(value * 10.0f);
}
