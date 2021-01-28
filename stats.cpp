#include "Stats.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

namespace Statistics {

    //Class to hold the Stats values
    class Stats {
    public://Made variables as public as it is directly accessed in testcases.
        double average = NAN;
        double min = NAN;
        double max = NAN;
    };

    Stats Statistics::ComputeStatistics(const std::vector<double>& vectorList) {

        //declaration of Stats object
        Stats statsObject = Stats();

        if (vectorList.size() != 0) {
            //Calculate Average
            double sum = accumulate(vectorList.begin(), vectorList.end(), 0.0/*to represent double value type*/);
            statsObject.average = sum / vectorList.size();

            //Calculate Minimum of Vector list
            auto minimumValue = min_element(vectorList.begin(), vectorList.end());
            statsObject.min = *minimumValue;

            //Calculate Maximum of vector list
            auto maximumValue = max_element(vectorList.begin(), vectorList.end());
            statsObject.max = *maximumValue;
        }

        return statsObject;
    }

}

//parent Alerter class
class IAlerter {
public:
    virtual void setAlert(bool alert) {  }
};

//derived class of IAlerter class
class EmailAlert : public IAlerter{
public:
    bool emailSent = false;//by default alert is false
    virtual void setAlert(bool alert){
        emailSent = alert;
    }
};

//derived class of IAlerter class
class LEDAlert : public IAlerter{
public:
    bool ledGlows = false;//by default alert is false
    virtual void setAlert(bool alert){
        ledGlows = alert;
    }
};

class StatsAlerter{
private:
    std::vector<IAlerter*> alerters;
    float thresholdValue = 0.0;

public:
    StatsAlerter(float pThresholdValue, std::vector<IAlerter*> pAlerters) {
        alerters = pAlerters;
        thresholdValue = pThresholdValue;
    }

    void checkAndAlert(const std::vector<double>& vectorList) {
        //Calculate Maximum of vector list
        auto maxValue = max_element(vectorList.begin(), vectorList.end());
        if (*maxValue > thresholdValue) {
            std::vector<IAlerter*>::iterator iterator;
            for (iterator = alerters.begin(); iterator != alerters.end(); iterator++) {
                (*iterator)->setAlert(true);
            }
        }
    }
};
