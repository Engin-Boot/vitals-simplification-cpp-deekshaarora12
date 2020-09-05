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

	/*for (const auto& elem : vitaldetails)
	{
		std::cout << elem.name << " " << elem.upperlimit << " " << elem.lowerlimit << " "<< elem.singlelimit<< "\n";
	}*/
}

int getVitalIndex(string name) {
	int index = 0;
	for(int i=0;i<vitaldetails.size();i++){
		if (vitaldetails[i].name == name)
			return i;
	}
	return index;
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
private:
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
public:
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
class Spo2{

};
class Resp{

};

int main() {
	AlertInSMS alertsms;
	AlertInSound alertsound;

	addVitalDetails();

	Bpm bpmobj;
	bpmobj.checkBpm(&alertsms,"Bpm", 20);

	
}
