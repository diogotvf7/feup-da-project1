#include "headers/StationTrack.h"

using namespace std;

Station::Station(const string &name, const string &district, const string &municipality, const string &township, const string &line) {
    this->name = name;
    this->district = district;
    this->municipality = municipality;
    this->township = township;
    this->line = line;
}

bool Station::operator<(Station *station) const {
    return this->dist < station->dist;
}

string Station::getName() const {
    return name;
}

string Station::getDistrict() const {
    return district;
}

string Station::getMunicipality() const {
    return municipality;
}

string Station::getTownship() const {
    return township;
}

string Station::getLine() const {
    return line;
}

int Station::getId() const {
    return id;
}

vector<Track*> Station::getAdj() const {
    return adj;
}

bool Station::isVisited() const {
    return visited;
}

bool Station::isProcessing() const {
    return processing;
}

unsigned int Station::getIndegree() const {
    return indegree;
}

double Station::getDist() const {
    return dist;
}

Track *Station::getPath() const {
    return path;
}

vector<Track *> Station::getIncoming() const {
    return incoming;
}

void Station::setVisited(bool visited) {
    this->visited = visited;
}

void Station::setProcesssing(bool processing) {
    this->processing = processing;
}

void Station::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

void Station::setDist(double dist) {
    this->dist = dist;
}

void Station::setPath(Track *path) {
    this->path = path;
}

Track* Station::addTrack(Station *dest, int capacity, const string &service) {
    Track *newTrack = new Track(this, dest, capacity, service);
    adj.push_back(newTrack);
    dest->incoming.push_back(newTrack);
    return newTrack;
}

double Station::getFlow() const {
    double flow = 0;
    for (Track *track : incoming)
        flow += track->getFlow();
    return flow;
}

void Station::removeOutgoingTrack(const string &dest) {
    for (auto itr = adj.begin(); itr != adj.end(); itr++) {
        Track *track = *itr;
        if (track->getDestination()->getName() == dest) {
            adj.erase(itr);
            break;
        }
    }
}

void Station::removeIncomingTrack(const string &src) {
    for (auto itr = incoming.begin(); itr != incoming.end(); itr++) {
        Track *track = *itr;
        if (track->getSource()->getName() == src) {
            incoming.erase(itr);
            break;
        }
    }
}

void Station::removeOutgoingTracks() {
    while (!adj.empty()) {
        Track *track = adj.back();
        removeOutgoingTrack(track->getDestination()->getName());
        track->getDestination()->removeIncomingTrack(name);
    }
}

void Station::removeIncomingTracks() {
    while (!incoming.empty()) {
        Track *track = incoming.back();
        track->getSource()->removeOutgoingTrack(name);
        removeIncomingTrack(track->getSource()->getName());
    }
}

Track::Track(Station *src, Station *dest, int capacity, const string &service) {
    this->src = src;
    this->dest = dest;
    this->capacity = capacity;
    this->service = service;
}

Station *Track::getDestination() const {
    return dest;
}

int Track::getCapacity() const {
    return capacity;
}

bool Track::isSelected() const {
    return selected;
}

Station *Track::getSource() const {
    return src;
}

Track *Track::getReverse() const {
    return reverse;
}

int Track::getFlow() const {
    return flow;
}

string Track::getService() const {
    return service;
}

void Track::setSelected(bool selected) {
    this->selected = selected;
}

void Track::setReverse(Track *reverse) {
    this->reverse = reverse;
}

void Track::setFlow(int flow) {
    this->flow = flow;
}

void Track::setService(const string &service) {
    this->service = service;
}

