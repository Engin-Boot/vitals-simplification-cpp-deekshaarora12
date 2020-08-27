#include <assert.h>

const int bpmlimits[] = { 70,150 };
const int spo2limit = 90;
const int respRatelimits[] = { 30,95 };

bool isBpmOk(float bpm) {
    return (bpm > bpmlimits[0] && bpm < bpmlimits[1]);
};
bool isSpo2Ok(float spo2) {
    return (spo2 > spo2limit);
};

bool isRespRateOk(float respRate) {
    return(respRate > respRatelimits[0] && respRate < respRatelimits[1]);
};

bool vitalsAreOk(float bpm, float spo2, float respRate) {
    return(isBpmOk(bpm) && isSpo2Ok(spo2) && isRespRateOk(respRate));
}

int main() {
    assert(vitalsAreOk(80, 95, 60) == true);
    assert(vitalsAreOk(60, 90, 40) == false);
}
