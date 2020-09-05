#include<assert.h>
#include<iostream>
#include<map>
#include <vector>
#include<iterator>
#include <string>
using namespace std;

struct vitalsinfo {
	string name;
	float upperlimit;
	float lowerlimit;
	float singlelimit;

	vitalsinfo(string vtname, float upper, float lower, float single) {
		this->name = vtname;
		this->upperlimit = upper;
		this->lowerlimit = lower;
		this->singlelimit = single;
	}

}; vector<vitalsinfo> vitaldetails;

void addVitalDetails() {

	struct vitalsinfo bpmobj("Bpm", 150, 70, 0);
	struct vitalsinfo spo2obj("Spo2", 0, 0, 90);
	struct vitalsinfo respobj("Resp", 95, 30, 0);

	vitaldetails.push_back(bpmobj);
	vitaldetails.push_back(spo2obj);
	vitaldetails.push_back(respobj);
}

int getVitalIndex(string name) {
	for(size_t index = 0; index < vitaldetails.size(); index++){
		if (vitaldetails[index].name == name)
			return index;
	}
}

class Alert {
public:
	virtual void getAlertMessage(const std::map<string, int>& printresults) = 0;
};

class AlertInSMS :public Alert {
public:
	void getAlertMessage(const std::map<string, int>& printresults) {
		std::map<string, int>::const_iterator itr;
		for (itr = printresults.begin(); itr != printresults.end(); itr++) {
			if (itr->second == 1)
				cout << "Alert in SMS: " << itr->first << endl;
		}
	}
};

class AlertInSound :public Alert {
public:
	void getAlertMessage(const std::map<string, int>& printresults) {
		std::map<string, int>::const_iterator itr;
		for (itr = printresults.begin(); itr != printresults.end(); itr++) {
			if (itr->second == 1)
				cout << "Alert in Sound: " << itr->first << endl;
		}
	}
};

class Bpm {
public:
	bool isBpmHigh(string name,float bpmvalue) {
		    int index = getVitalIndex(name);
			return(bpmvalue > vitaldetails[index].upperlimit);
	}

	bool isBpmLow(string name, float bpmvalue) {
		   int index = getVitalIndex(name);
			return(bpmvalue < vitaldetails[index].lowerlimit);
	}

	bool isBpmNormal(string name, float bpmvalue) {
		    int index = getVitalIndex(name);
			return(bpmvalue >= vitaldetails[index].lowerlimit && bpmvalue <= vitaldetails[index].upperlimit);
	}
	 void checkBpm(Alert *alert,string name, float bpmvalue) {
		std::map<string, int> bpmresults; 

		int bpmhighresult = isBpmHigh(name, bpmvalue);
		int bpmlowresult = isBpmLow(name, bpmvalue);
		int bpmnormalresult = isBpmNormal(name, bpmvalue);

		bpmresults.insert(pair<string, int>("High BPM rate", bpmhighresult));
		bpmresults.insert(pair<string, int>("Low BPM rate", bpmlowresult));
		bpmresults.insert(pair<string, int>("Normal BPM rate", bpmnormalresult));

		alert->getAlertMessage(bpmresults);
	}
};
class Spo2
{
public:
	bool isSpo2High(string name, float spo2value) {
		int index = getVitalIndex(name);
		return(spo2value > vitaldetails[index].singlelimit);
	}

	bool isSpo2Low(string name, float spo2value) {
		int index = getVitalIndex(name);
		return(spo2value < vitaldetails[index].singlelimit);
	}

	bool isSpo2Normal(string name, float spo2value) {
		int index = getVitalIndex(name);
		return(spo2value == vitaldetails[index].singlelimit);
	}
	void checkSpo2(Alert* alert, string name, float spo2value) {
		std::map<string, int> spo2results;

		int spo2highresult = isSpo2High(name, spo2value);
		int spo2lowresult = isSpo2Low(name, spo2value);
		int spo2normalresult = isSpo2Normal(name, spo2value);

		spo2results.insert(pair<string, int>("High Spo2 rate", spo2highresult));
		spo2results.insert(pair<string, int>("Low Spo2 rate", spo2lowresult));
		spo2results.insert(pair<string, int>("Normal Spo2 rate", spo2normalresult));

		alert->getAlertMessage(spo2results);
	}

};
class Resp{
public:
	bool isRespHigh(string name, float respvalue) {
		int index = getVitalIndex(name);
		return(respvalue > vitaldetails[index].upperlimit);
	}

	bool isRespLow(string name, float respvalue) {
		int index = getVitalIndex(name);
		return(respvalue < vitaldetails[index].lowerlimit);
	}

	bool isRespNormal(string name, float respvalue) {
		int index = getVitalIndex(name);
		return(respvalue >= vitaldetails[index].lowerlimit && respvalue <= vitaldetails[index].upperlimit);
	}
	void checkResp(Alert* alert, string name, float respvalue) {
		std::map<string, int> respresults;

		int resphighresult = isRespHigh(name, respvalue);
		int resplowresult = isRespLow(name, respvalue);
		int respnormalresult = isRespNormal(name, respvalue);

		respresults.insert(pair<string, int>("High Resp rate", resphighresult));
		respresults.insert(pair<string, int>("Low Resp rate", resplowresult));
		respresults.insert(pair<string, int>("Normal Resp rate", respnormalresult));

		alert->getAlertMessage(respresults);
	}

};

int main() {
	AlertInSMS alertsms;
	AlertInSound alertsound;

	addVitalDetails();

	Bpm bpmobj;
	bpmobj.checkBpm(&alertsms, "Bpm", 89);
	bpmobj.checkBpm(&alertsms, "Bpm", 20);
	bpmobj.checkBpm(&alertsms, "Bpm", 200);

	bpmobj.checkBpm(&alertsound, "Bpm", 12);
	bpmobj.checkBpm(&alertsound, "Bpm", 105);
	bpmobj.checkBpm(&alertsound, "Bpm", 229);

	Spo2 spo2obj;
	spo2obj.checkSpo2(&alertsms, "Spo2", 95);
	spo2obj.checkSpo2(&alertsms, "Spo2", 20);
	spo2obj.checkSpo2(&alertsms, "Spo2", 90);

	spo2obj.checkSpo2(&alertsound, "Spo2", 12);
	spo2obj.checkSpo2(&alertsound, "Spo2", 90);
	spo2obj.checkSpo2(&alertsound, "Spo2", 105);

	Resp respobj;
	respobj.checkResp(&alertsms, "Resp", 95);
	respobj.checkResp(&alertsms, "Resp", 30);
	respobj.checkResp(&alertsms, "Resp", 190);

	respobj.checkResp(&alertsound, "Resp", 12);
	respobj.checkResp(&alertsound, "Resp", 103);
	respobj.checkResp(&alertsound, "Resp", 94);

	cout << "Bpm Test" << endl;

	assert(bpmobj.isBpmHigh("Bpm", 90) == false);
	assert(bpmobj.isBpmHigh("Bpm", 190) == true);

	assert(bpmobj.isBpmLow("Bpm", 170) == false);
	assert(bpmobj.isBpmLow("Bpm", 19) == true);

	assert(bpmobj.isBpmNormal("Bpm", 15) == false);
	assert(bpmobj.isBpmNormal("Bpm", 129) == true);

	cout << "Spo2 Test" << endl;

	assert(spo2obj.isSpo2High("Spo2", 10) == false);
	assert(spo2obj.isSpo2High("Spo2", 96) == true);

	assert(spo2obj.isSpo2Low("Spo2", 102) == false);
	assert(spo2obj.isSpo2Low("Spo2", 18) == true);

	assert(spo2obj.isSpo2Normal("Spo2", 99) == false);
	assert(spo2obj.isSpo2Normal("Spo2", 90) == true);

	cout << "Resp Test" << endl;

	assert(respobj.isRespHigh("Resp", 10) == false);
	assert(respobj.isRespHigh("Resp", 109) == true);

	assert(respobj.isRespLow("Resp", 125) == false);
	assert(respobj.isRespLow("Resp", 21) == true);

	assert(respobj.isRespNormal("Resp", 23) == false);
	assert(respobj.isRespNormal("Resp", 45) == true);
}
