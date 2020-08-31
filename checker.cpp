#include<assert.h>
#include<iostream>
#include<map>
using namespace std;

const int bpmUpperLimit=150;
const int bpmLowerLimit=70;
const int spo2limit = 90;
const int respRateLowerLimit = 30;
const int respRateUpperLimit = 95;


class alert{
public:
	void getAlertMessage(const std::map<string, int> &printresults) {
		std::map<string, int>::const_iterator itr;
		for (itr = printresults.begin(); itr != printresults.end(); itr++) {
			if (itr->second == 1)
				cout << itr->first << endl;		
		}
		
	}

};

class bpm{
private:
	alert* alertmessage;
public:
	
	bool isBpmHigh(int bpmvalue) {
		return(bpmvalue > bpmUpperLimit);
	}
	bool isBpmLow(int bpmvalue) {
		return(bpmvalue < bpmLowerLimit);
	}
	bool isBpmNormal(int bpmvalue) {
		return(bpmvalue >= bpmLowerLimit && bpmvalue <= bpmUpperLimit);
	}
	void addToMap(int high,int low,int normal) {
		alert alertobj;
		std::map<string, int> bpmresults;  

		bpmresults.insert(pair<string, int>("High BPM rate", high));
		bpmresults.insert(pair<string, int>("Low BPM rate", low));
		bpmresults.insert(pair<string, int>("Normal BPM rate", normal));

		this->alertmessage = &alertobj;
		alertmessage->getAlertMessage(bpmresults);
	}

	void isBpmOk(int bpmvalue) {
		bool checkNormal = isBpmNormal(bpmvalue);
		bool checkHigh = isBpmHigh(bpmvalue);	
		bool checkLow = isBpmLow(bpmvalue);	
		addToMap(checkHigh,checkLow,checkNormal);
	}
};


class spo2{
private:
	alert* alertmessage;
public:
	bool isSpo2High(int spo2value) {
		return(spo2value > spo2limit);
	}
	bool isSpo2Low(int spo2value) {
		return(spo2value < spo2limit);
	}
	bool isSpo2Normal(int spo2value) {
		return(spo2value == spo2limit);
	}
	
	void addToMap(int high, int low,int normal) {
		alert alertobj;
		std::map<string, int> spo2results;

		spo2results.insert(pair<string, int>("High Spo2 rate", high));
		spo2results.insert(pair<string, int>("Low Spo2 rate", low));
		spo2results.insert(pair<string, int>("Normal Spo2 rate", normal));

		this->alertmessage = &alertobj;
		alertmessage->getAlertMessage(spo2results);
	}
	void isSpo2Ok(int spo2value) {
		int checkHigh = isSpo2High(spo2value);
		int checkLow = isSpo2Low(spo2value);
		int checkNormal = isSpo2Normal(spo2value);
		addToMap(checkHigh,checkLow,checkNormal);
}
};

class resp {
private:
	alert* alertmessage;
public:
	bool isRespHigh(int respvalue) {
		return(respvalue > respRateUpperLimit);
	}
	bool isRespLow(int respvalue) {
		return(respvalue < respRateLowerLimit);
	}
	bool isRespNormal(int respvalue) {
		return(respvalue >= respRateLowerLimit && respvalue <= respRateUpperLimit);
	}
	void addToMap(int high, int low, int normal) {
		alert alertobj;
		std::map<string, int> respresults;

		respresults.insert(pair<string, int>("High Resp rate", high));
		respresults.insert(pair<string, int>("Low Resp rate", low));
		respresults.insert(pair<string, int>("Normal Resp rate", normal));

		this->alertmessage = &alertobj;
		alertmessage->getAlertMessage(respresults);
	}

	void isRespOk(int respvalue) {
		bool checkNormal = isRespNormal(respvalue);
		bool checkHigh = isRespHigh(respvalue);
		bool checkLow = isRespLow(respvalue);
		addToMap(checkHigh, checkLow, checkNormal);
	}

};


class vitals{
private:
	 bpm* bpmrate;
	 spo2* spo2rate;
	 resp* resprate;

public:
	void checkVitals(int bpmvalue,int spo2value,int respvalue) {
		checkBpm(bpmvalue);
		checkSpo2(spo2value);
		checkResp(respvalue);
	}
	void checkBpm(int bpmvalue) {
		bpm bpmobj;
		this->bpmrate = &bpmobj;
		bpmrate->isBpmOk(bpmvalue);
	}
	void checkSpo2(int spo2value){
		spo2 spo2obj;
		this->spo2rate = &spo2obj;
		spo2rate->isSpo2Ok(spo2value);
	}
	void checkResp(int respvalue) {
		resp respobj;
		this->resprate = &respobj;
		resprate->isRespOk(respvalue);

	}
};



int main() {
	vitals vt;
	vt.checkVitals(12, 20, 100);
	vt.checkVitals(80, 95, 60);
	vt.checkVitals(60, 90, 40);

	vt.checkVitals(100, 120, 12);
	vt.checkVitals(89, 110, 23);
	vt.checkVitals(14, 95, 120);

}
