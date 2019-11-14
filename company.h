#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <list>

#include "client.h"
#include "service.h"
#include "truck.h"

class Truck;
class Service;
class Client;
using namespace std;

class Company
{
public:
/**
* @brief Gets Company
*
* Retrieves the Company instance
*
* @return Returns a pointer to the company
*/
    static Company *getCompany();
/**
*
* Default Destructor
*/
    ~Company();
    bool services_finished_changed=false,services_on_transit_changed=false,services_on_queue_changed=false;
    bool clients_changed=false;
    bool trucks_changed=false;
    list<Service*> *getVectorServicesFinished();
    vector<Service*> *getVectorServicesOnTransit();
    vector<Service*> *getVectorServicesOnQueue();
    vector<Client*> *getVectorClients();
    vector<Truck*> *getVectorTrucks();
    Client *getClient(unsigned nif);
    Truck *getTruck(string license);
    Service *getService(unsigned id);
    void updateTruckSituation();
    void updateServicesSituation();
    void loadStats();
    void saveStats();
	vector<pair<int, float>> getStatCong() { return statCong; }
	vector<pair<int, float>> getStatHaz() { return statHaz; }
	vector<pair<int, float>> getStatAnim() { return statAnim; }
	vector<pair<int, float>> getStatNorm() { return statNorm; }

private:
    static Company *company;
    Company();
    int generalRevenue; // lucro geral
    int dangerousRevenue; //lucro caminhao perigoso
    int freezeRevenue;
    list<Service*> services_finished;
    vector<Service*> services_on_transit,services_on_queue;
    vector<Client*> clients;
    vector<Truck*> trucks;
    vector<pair<int, float>> statCong;
    vector<pair<int, float>> statHaz;
    vector<pair<int, float>> statNorm;
    vector<pair<int, float>> statAnim;
};
