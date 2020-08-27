#include <assert.h>

bool vitalsAreOk(float bpm, float spo2, float respRate) {
  if(bpm < 70 || bpm > 150) {
    return false;
  } else if(spo2 < 90) {
    return false;
  } else if(respRate < 30 || respRate > 95) {
    return false;
  }
  return true;
}

int main() {
  assert(vitalsAreOk(80, 95, 60) == true);
  assert(vitalsAreOk(60, 90, 40) == false);
}
