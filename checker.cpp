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


	vitalsinfo(string vtname, float upper, float lower) {
		this->name = vtname;
		this->upperlimit = upper;
		this->lowerlimit = lower;
	}

}; vector<vitalsinfo> vitaldetails;

void addVitalDetails() {

	struct vitalsinfo bpmobj("Bpm", 150, 70);
	struct vitalsinfo spo2obj("Spo2", 90, 90);
	struct vitalsinfo respobj("Resp", 95, 30);

	vitaldetails.push_back(bpmobj);
	vitaldetails.push_back(spo2obj);
	vitaldetails.push_back(respobj);
}

size_t getVitalIndex(string name) {
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

class Vitals {
public:
	bool isVitalHigh(string name,float value) {
		    int index = getVitalIndex(name);
			return(value > vitaldetails[index].upperlimit);
	}

	bool isVitalLow(string name, float value) {
		   int index = getVitalIndex(name);
			return(value < vitaldetails[index].lowerlimit);
	}

	bool isVitalNormal(string name, float value) {
		    int index = getVitalIndex(name);
			return(value >= vitaldetails[index].lowerlimit && value <= vitaldetails[index].upperlimit);
	}
	 void checkVital(Alert *alert,string name, float bpmvalue) {
		std::map<string, int> vitalresults; 

		int highresult = isVitalHigh(name, bpmvalue);
		int lowresult = isVitalLow(name, bpmvalue);
		int normalresult = isVitalNormal(name, bpmvalue);

		vitalresults.insert(pair<string, int>("High BPM rate", highresult));
		vitalresults.insert(pair<string, int>("Low BPM rate", lowresult));
		vitalresults.insert(pair<string, int>("Normal BPM rate", normalresult));

		alert->getAlertMessage(vitalresults);
	}
};

int main() {
	AlertInSMS alertsms;
	AlertInSound alertsound;

	addVitalDetails();

	Vitals bpmobj;
	bpmobj.checkVital(&alertsms, "Bpm", 89);
	bpmobj.checkVital(&alertsms, "Bpm", 20);
	bpmobj.checkVital(&alertsms, "Bpm", 200);

	bpmobj.checkVital(&alertsound, "Bpm", 12);
	bpmobj.checkVital(&alertsound, "Bpm", 105);
	bpmobj.checkVital(&alertsound, "Bpm", 229);

	Vitals spo2obj;
	spo2obj.checkVital(&alertsms, "Spo2", 95);
	spo2obj.checkVital(&alertsms, "Spo2", 20);
	spo2obj.checkVital(&alertsms, "Spo2", 90);

	spo2obj.checkVital(&alertsound, "Spo2", 12);
	spo2obj.checkVital(&alertsound, "Spo2", 90);
	spo2obj.checkVital(&alertsound, "Spo2", 105);

	Vitals respobj;
	respobj.checkVital(&alertsms, "Resp", 95);
	respobj.checkVital(&alertsms, "Resp", 30);
	respobj.checkVital(&alertsms, "Resp", 190);

	respobj.checkVital(&alertsound, "Resp", 12);
	respobj.checkVital(&alertsound, "Resp", 103);
	respobj.checkVital(&alertsound, "Resp", 94);

	cout << "Bpm Test" << endl;

	assert(bpmobj.isVitalHigh("Bpm", 90) == false);
	assert(bpmobj.isVitalHigh("Bpm", 190) == true);

	assert(bpmobj.isVitalLow("Bpm", 170) == false);
	assert(bpmobj.isVitalLow("Bpm", 19) == true);

	assert(bpmobj.isVitalNormal("Bpm", 15) == false);
	assert(bpmobj.isVitalNormal("Bpm", 129) == true);

	cout << "Spo2 Test" << endl;

	assert(spo2obj.isVitalHigh("Spo2", 10) == false);
	assert(spo2obj.isVitalHigh("Spo2", 96) == true);

	assert(spo2obj.isVitalLow("Spo2", 102) == false);
	assert(spo2obj.isVitalLow("Spo2", 18) == true);

	assert(spo2obj.isVitalNormal("Spo2", 99) == false);
	assert(spo2obj.isVitalNormal("Spo2", 90) == true);

	cout << "Resp Test" << endl;

	assert(respobj.isVitalHigh("Resp", 10) == false);
	assert(respobj.isVitalHigh("Resp", 109) == true);

	assert(respobj.isVitalLow("Resp", 125) == false);
	assert(respobj.isVitalLow("Resp", 21) == true);

	assert(respobj.isVitalNormal("Resp", 23) == false);
	assert(respobj.isVitalNormal("Resp", 45) == true);
}
