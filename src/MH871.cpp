//
//  MH871.cpp
//  xmlSettingsExample
//
//  Created by dantheman on 2/9/16.
//
//

#include "MH871.h"

void MH871::setup(float min, float max){
    this->min = min;
    this->max = max;
    device.setup("/dev/tty.USA19H141P1.1", 19200);
    initCut();
    penUp();
}
void MH871::update(){
    if(cache.size() > 0){
        sendCommand(cache.front());
        cache.pop_front();
    }
}

void MH871::setScaleMinMax(float x, float y){
    minX = x;
    minY = y;
}
void MH871::addPoint(ofPoint pt){
    ofVec2f fooP = mapPoint(pt);
    int x = (int)fooP.x;
    int y = (int)fooP.y;
    cout<<"x/y "<<x<<" "<<y<<endl;
    cache.push_back("PA"+ofToString(x)+","+ofToString(y)+";");
}
void MH871::addPoint(ofVec2f pt){
    ofVec2f fooP = mapPoint(pt);
    int x = (int)fooP.x;
    int y = (int)fooP.y;
    cache.push_back("PA"+ofToString(x)+","+ofToString(y)+";");
}
void MH871::addPolyline(ofPolyline line){
//    line = line.getResampledBySpacing(1);
    vector<ofPoint> verts = line.getVertices();
    for(int i = 0; i < verts.size(); i++){
        if(i == 0){
            startPlot(verts[i]);
        }else{
            addPoint(verts[i]);
        }
    }
    endPlot();
}
void MH871::endPlot(){
    cache.push_back("PU;");
    cache.push_back("PA0,0;");

}
void MH871::startPlot(ofPoint pt){
    ofVec2f fooP = mapPoint(pt);
    int x = (int)fooP.x;
    int y = (int)fooP.y;
    cache.push_back("PA"+ofToString(x)+","+ofToString(y)+";");
    cache.push_back("PD;");
}
void MH871::startPlot(ofVec2f pt){
    ofVec2f fooP = mapPoint(pt);
    int x = (int)fooP.x;
    int y = (int)fooP.y;
    cache.push_back("PA"+ofToString(x)+","+ofToString(y)+";");
    cache.push_back("PD;");
}

void MH871::initPlotter(){
    sendCommand("IN;");
}

void MH871::penDown(){
    sendCommand("PD;");
}

void MH871::penUp(){
    sendCommand("PU;");
}

ofVec2f MH871::mapPoint(ofPoint pt){
    return ofVec2f(ofMap(pt.x, 0, minX, min, max, true), ofMap(pt.y, 0, minY, min, max*minY/minX, true));
}

ofVec2f MH871::mapPoint(ofVec2f pt){
    return ofVec2f(ofMap(pt.x, 0, minX, min, max), ofMap(pt.y, 0, minY, min, max*minY/minX, true));
}

void MH871::sendCommand(string command){
    ofBuffer buf;
    buf.set(command);
    device.writeBytes(buf);
//    device.flush();
}
