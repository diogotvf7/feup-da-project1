//
// Created by Daniel Rebelo on 08/03/2023.
//

#ifndef PROJECT_SEGMENT_H
#define PROJECT_SEGMENT_H

#include <iostream>
#include <string>

class Segment {
private:
    std::string src;
    std::string dest;
    int capacity;
    std::string service;
public:
    Segment(std::string src, std::string dest, int capacity, std::string service);
    std::string getSource() const;
    std::string getDestination() const;
    int getCapacity() const;
    std::string getService() const;

    void setSource(const std::string &source);
    void setDestination(const std::string &destination);
    void setCapacity(int capacity);
    void setService(const std::string &s);
};


#endif //PROJECT_SEGMENT_H
