#ifndef STATIONTRACK_H
#define STATIONTRACK_H

#include <iostream>
#include <vector>
#include <string>


class Track;

/************************* Station  **************************/

class Station {
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::string line;

    // auxiliary fields
    int id;                // identifier
    std::vector<Track*> adj;  // outgoing edges

    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    Track *path = nullptr;

    std::vector<Track*> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS
public:
    Station(const std::string &name, const std::string &district, const std::string &municipality, const std::string &township, const std::string &line);

    bool operator<(Station *station) const; // // required by MutablePriorityQueue

    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getDistrict() const;
    [[nodiscard]] std::string getMunicipality() const;
    [[nodiscard]] std::string getTownship() const;
    [[nodiscard]] std::string getLine() const;
    // auxiliary get functions
    [[nodiscard]] int getId() const;
    [[nodiscard]] std::vector<Track*> getAdj() const;
    [[nodiscard]] bool isVisited() const;
    [[nodiscard]] bool isProcessing() const;
    [[nodiscard]] unsigned int getIndegree() const;
    [[nodiscard]] double getDist() const;
    [[nodiscard]] Track *getPath() const;
    [[nodiscard]] std::vector<Track*> getIncoming() const;


    void setName(const std::string &name);
    void setDistrict(const std::string &district);
    void setMunicipality(const std::string &municipality);
    void setTownship(const std::string &township);
    void setLine(const std::string &line);
    // auxiliary set functions
    void setId(int id);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Track *path);
    Track *addTrack(Station *dest, int capacity, const std::string &service);
    bool removeTrack(int destID);
};

/********************** Track  ****************************/

class Track {
    Station *src;
    Station *dest;
    int capacity;
    double flow;
    std::string service;
    bool selected = false;
    Track *reverse = nullptr;

public:
    Track(Station *src, Station *dest, int capacity, const std::string &service);

    [[nodiscard]] Station *getDestination() const;
    [[nodiscard]] int getCapacity() const;
    [[nodiscard]] bool isSelected() const;
    [[nodiscard]] Station *getSource() const;
    [[nodiscard]] Track *getReverse() const;
    [[nodiscard]] double getFlow() const;
    [[nodiscard]] std::string getService() const;

    void setSelected(bool selected);
    void setReverse(Track* reverse);
    void setFlow(double flow);
    void setService(const std::string &service);
};

#endif //STATIONTRACK_H
