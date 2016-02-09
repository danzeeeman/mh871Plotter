//
//  MH871.hpp
//  xmlSettingsExample
//
//  Created by dantheman on 2/9/16.
//
//
#pragma once
#include "ofMain.h"
class MH871{
public:
    void setup(float min = 0, float max = 20000);
    void setScaleMinMax(float min, float max);
    void update();
    void addPoint(ofPoint pt);
    void addPoint(ofVec2f pt);
    void addPolyline(ofPolyline line);
    void penDown();
    void penUp();
    void initPlotter();
    void startPlot(ofPoint pt);
    void startPlot(ofVec2f pt);
    void endPlot();
private:
    ofPolyline polyline;
    deque<string> cache;
    void sendCommand(string command);
    ofVec2f mapPoint(ofVec2f pt);
    ofVec2f mapPoint(ofPoint pt);
    ofSerial device;
    float min, max;
    float minX, minY;
};

