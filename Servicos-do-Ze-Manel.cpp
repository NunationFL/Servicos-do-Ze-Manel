// Serviços do Zé Manel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <ctime>

#include "client.h"
#include "truck.h"
#include "service.h"
#include "company.h"

using namespace std;



/*
This function receives a name and returns true if it is valid
*/

template<class T> bool cmp_classes(T *a,T *b){
    return *a<*b;
}

Company *Company::company = nullptr;
int main()
{
    clearScreen();
    Company *Ze_Manel = nullptr;
    Ze_Manel=Company::getCompany();
    Truck::loadFromFile(Ze_Manel->getVectorTrucks());
    Client::loadClients(*Ze_Manel->getVectorClients());
    sort(((*Ze_Manel).getVectorTrucks())->begin(),((*Ze_Manel).getVectorTrucks())->end(),cmp_classes<Truck>);
    sort(((*Ze_Manel).getVectorClients())->begin(),((*Ze_Manel).getVectorClients())->end(),cmp_classes<Client>);
    Service::loadFromFile(Ze_Manel->getVectorServicesFinished(),Ze_Manel->getVectorServicesOnTransit(),Ze_Manel->getVectorServicesOnQueue());

    //vector<Truck*> a(*Ze_Manel->getVectorTrucks());
    unsigned opt=1;
    string temp;
    while (opt!=0) {
        cout<<"[1] See services"<<endl;
        cout<<"[2] Add service"<<endl;
        cout<<"[3] Remove service"<<endl;
        cout<<"[4] Edit service"<<endl;
        if(cin>>opt && opt<=5)
            switch (opt) {
            case 0:
                break;
            case 1:{
                clearBuffer();
                clearScreen();
                for(auto i=Ze_Manel->getVectorServicesOnQueue()->begin();i!=Ze_Manel->getVectorServicesOnQueue()->end();i++)
                    cout<<*i;
                if(!Ze_Manel->getVectorServicesOnQueue()->size())
                    cout<<"There is no info to show"<<endl;
                getline(cin,temp);
                clearScreen();
                break;
            }
            case 2:{
                Client *a=nullptr;
                clearScreen();
                clearBuffer();
                a =new Client("Margarida Cruz",121212121);
                try {
                    Service::addService(Ze_Manel->getVectorServicesOnQueue(),a);
                } catch (exception e) {

                }
                clearScreen();
                break;
            }

            case 3:{
                clearScreen();
                clearBuffer();
                for(auto i:*Ze_Manel->getVectorServicesOnQueue()){
                    cout<<i->getMaterial()<<", id: "<<i->getId()<<endl;
                }
                if(Ze_Manel->getVectorServicesOnQueue()->size()){
                    cout<<endl;
                    string id;
                    bool var_error=true;
                    while (var_error) {
                        cout<<"Which Service you want to remove ( write service's id ):"<<endl;
                        if(cin>>id){
                            var_error=false;
                            if(id=="!q")
                                var_error=false;
                            else if(!strIsNumber(id))
                                var_error=true;

                        }
                        else {
                            cout<<"Id not acceptable"<<endl;
                        }
                    }
                    if(id=="!q"){
                        clearScreen();
                        break;
                    }
                    try{
                        Service::removeService(Ze_Manel->getVectorServicesOnQueue(),unsigned(stoi(id)));
                        clearScreen();
                    }
                    catch(ServiceDoNotExist e){
                        cout<<e.erro<<endl;
                        clearBuffer();
                    }
                }
                else
                    cout<<"There are no services that can be removed"<<endl;
                string temp;
                getline(cin,temp);
                clearScreen();
                break;
            }
            case 4:{
                clearScreen();
                clearBuffer();
                stringstream out;
                for(auto i:*Ze_Manel->getVectorServicesOnQueue()){
                    out<<i->getMaterial()<<", id: "<<i->getId()<<endl;
                }
                cout<<out.str();
                if(Ze_Manel->getVectorServicesOnQueue()->size()){
                    cout<<endl;
                    string id;
                    bool var_error=true;
                    while (var_error) {
                        cout<<"Which Service you want to edit ( write service's id ):"<<endl;
                        if(cin>>id){
                            var_error=false;
                            if(id=="!q")
                                var_error=false;
                            else if(!strIsNumber(id))
                                var_error=true;
                        }
                        else {
                            clearScreen();
                            clearBuffer();
                            cout<<out.str();
                            cout<<"Id not acceptable"<<endl;
                        }
                    }
                    if(id=="q")
                        break;
                    clearBuffer();
                    //pesquisa binaria!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    bool h_found=false;
                    try{
                        for(auto i:*Ze_Manel->getVectorServicesOnQueue()){
                            if(unsigned(stoi(id))==i->getId()){
                                i->editService();
                                h_found=true;
                                break;
                            }
                        }

                    } catch (exception e) {

                    }
                    clearScreen();
                    if(!h_found)
                        cout<<"Couldn't find Service"<<endl;
                }
                else
                    cout<<"There are no services that can be edit"<<endl;
                string temp;
                getline(cin,temp);
                clearScreen();
                break;

            }
            case 5:{
                clearBuffer();
                cout << Ze_Manel->getVectorClients()->size() <<endl;
                for(auto i:*Ze_Manel->getVectorClients()){
                    cout<<*i<<endl;
                }
                string temp;
                getline(cin,temp);
                clearScreen();
                break;
            }

            default:
                opt=1;
            }
        else{
            opt=1;
            clearBuffer();
            clearScreen();
            cout<<"Not a valid option, please try again"<<endl;
        }
    }
    delete Ze_Manel;


    return 0;
}
