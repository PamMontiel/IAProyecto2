#pragma once
#pragma once
#include <iostream>
#include <stack>
#include "GraphNode.h"
#include "Queue.h"
#include "Stack.h"
using std::cout; using std::endl;

template <class T>
class Graph {
    typedef GraphNode<T> NG;
public:
    std::vector<NG*> yellowRoad;
    Queue<NG*> qv;
    NG* padre = nullptr;
    Graph() {}
    Graph(T data, int v) {
        if (!padre) {
            padre = new NG(data, v);
        }
    }

    void addEdge(T dataParend, T data, int cost) {
        NG* tmp = DSearch(dataParend);
        if (tmp != nullptr && dataParend != data) {
            if (DSearch(data) == nullptr) {
                tmp->adyacentes.push_back(new NG(data, 10000));
                tmp->costoAdyacentes.push_back(cost);
            }
            else if (searchPadre(tmp, data) == nullptr) {
                tmp->adyacentes.push_back(DSearch(data));
                tmp->costoAdyacentes.push_back(cost);
            }
            //NG* tmpD = DSearch(data);
            //tmpD->adyacentes.push_back(tmp);
            //tmpD->costoAdyacentes.push_back(cost);
        }
    }

    NG* search(T data) {
        Queue<NG*> qs;
        NG* tmp = padre;
        while (tmp) {
            qv.push(tmp);
            if (tmp->getData() == data) {
                resetVisitados();
                return tmp;
                break;
            }
            else if (tmp->visitado != true) {
                tmp->visitado = true;
                for (int i = 0; i < tmp->adyacentes.size(); i++) {
                    qs.push(tmp->adyacentes.at(i));
                }
            }
            if (qs.first == nullptr) {
                resetVisitados();
                return nullptr;
                break;
            }
            tmp = qs.first->value;
            qs.pop();
        }
        return nullptr;
    }

	NG* WSearchLimit(T data) {
		Queue<NG*> qs;
		NG* tmp = padre;
		int attempts = 0;
		while (tmp && attempts < 10) {
			qv.push(tmp);
			if (tmp->getData() == data) {
				resetVisitados();
                std::cout << "found" << std::endl;
				return tmp;
				break;
			}
			else if (tmp->visitado != true) {
				tmp->visitado = true;
				attempts++;
                for (int i = 0; i < tmp->adyacentes.size(); i++) {
                    if(tmp->adyacentes.at(i)->visitado == false)
                        qs.push(tmp->adyacentes.at(i));
				}
			}
			if (qs.first == nullptr) {
				resetVisitados();
				return nullptr;
				break;
			}
            tmp = qs.first->value;
			qs.pop();
		}
        if (attempts >= 10) {
            
            std::cout << "attemps exceeded" << std::endl;
        }
		return nullptr;
	}

    bool DSuperSearch(NG* start, NG* end) {
        Stack<NG*> ss;
        NG* tmp = start;
        ss.push(tmp);
        while (tmp) {
            //cout << tmp->visitado << endl;
            if (tmp->getData() == end->getData()) {
                resetVisitados();
                return true;
                break;
            }
            else if (tmp->visitado != true) {
                tmp->visitado = true;
                qv.push(tmp);
                ss.pop();
                for (int i = 0; i < tmp->adyacentes.size(); i++) {
                    if (tmp->adyacentes.at(i)->visitado != true) {
                        ss.push(tmp->adyacentes.at(i));
                    }
                }
            }
            else {
                ss.pop();
            }
            if (ss.last == nullptr) {
                resetVisitados();
                //cout << "nop" << endl;
                return false;
                break;
            }
            tmp = ss.last->value;
        }
        resetVisitados();
        return false;
    }
   
    NG* DSearch(T data) {
        Stack<NG*> ss;
        NG* tmp = padre;
        ss.push(tmp);
        while (tmp) {
            //cout << tmp->visitado << endl;
            if (tmp->getData() == data) {
                resetVisitados();
                return tmp;
                break;
            }
            else if (tmp->visitado != true) {
                tmp->visitado = true;
                qv.push(tmp);
                ss.pop();
                for (int i = 0; i < tmp->adyacentes.size(); i++) {
                    if (tmp->adyacentes.at(i)->visitado != true) {
                        if (tmp->adyacentes.at(i)->visitado != true)
                            ss.push(tmp->adyacentes.at(i));
                    }
                }
            }
            else {
                ss.pop();
            }
            if (ss.last == nullptr) {
                resetVisitados();
                //cout << "nop" << endl;
                return nullptr;
                break;
            }
            tmp = ss.last->value;
        }
        resetVisitados();
        return nullptr;
    }

    NG* searchPadre(NG* head, T data) {
        NG* tmp = head;
        while (tmp) {
            qv.push(tmp);
            if (tmp->visitado == false) {
                tmp->visitado = true;
                for (int i = 0; i < tmp->adyacentes.size(); i++) {
                    tmp->adyacentes.at(i)->visitado = true;
                    qv.push(tmp->adyacentes.at(i));
                    if (tmp->adyacentes.at(i)->getData() == data) {
                        resetVisitados();
                        tmp = tmp->adyacentes.at(i);
                        return tmp;
                        break;
                    }
                }
                resetVisitados();
                return nullptr;
                break;
            }
        }
        return nullptr;
    }

    void printBFS() {
        Queue<NG*> qs;
        NG* tmp = padre;
        //resetVisitados();
        while (tmp) {
            qv.push(tmp);
            if (tmp->visitado != true) {
                tmp->visitado = true;
                cout << tmp->getData() << endl;
                for (int i = 0; i < tmp->adyacentes.size(); i++) {
                    if (tmp->adyacentes.at(i)->visitado == false)
                        qs.push(tmp->adyacentes.at(i));
                }
            }
            if (qs.first == nullptr) {
                resetVisitados();
                break;
            }
            tmp = qs.first->value;
            qs.pop();
        }
    }
    std::vector<NG*> hillClimb(NG* start, NG* end)
    {
        NG* tmp2 = start;
        NG* tmp = start;
        bool onVector = false;
        start->val = 0;
        for (int i = 0; i < yellowRoad.size(); i++)
        {
            if (yellowRoad.at(i) == start)
            {
                onVector = true;
            }
        }
        if (!onVector)
        {
            yellowRoad.push_back(start);
        }
            for (int i = 0; i < tmp->adyacentes.size(); i++)
            {
                int costeConexion = tmp->costoAdyacentes.at(i) + tmp->val;
                if (DSuperSearch(tmp->adyacentes.at(i),end) == true)
                {
                    tmp->adyacentes.at(i)->val = costeConexion;

                    if (tmp2->val == 0 || tmp2->val > tmp->adyacentes.at(i)->val)
                    {
                        tmp2 = tmp->adyacentes.at(i);
                    }
                }
            }
            yellowRoad.push_back(tmp2);
            if (tmp2 != end)
            {
                hillClimb(tmp2, end);
            }

            return yellowRoad;
    }

    void printHillClimb(NG* start,NG* end)
    {
        hillClimb(start, end);
        for (int i = 0; i < yellowRoad.size(); i++)
        {
        cout << yellowRoad.at(i)->getData()<< "\n";

        }


    }

    std::vector<NG*> Dijkstra(NG* start, NG* end) {
        Queue<NG*> qd;
        std::vector<NG*> pathToVictory;
        NG* tmp = start;
        start->val = 0;
        qd.push(tmp);
        while (qd.size() > 0) {
            for (int i = 0; i < tmp->adyacentes.size(); i++) {
                int costeConexion = tmp->costoAdyacentes.at(i) + tmp->val;
                
                    if (tmp->adyacentes.at(i)->val > costeConexion) {
                        tmp->adyacentes.at(i)->val = costeConexion;
                        tmp->adyacentes.at(i)->padre = tmp;
                    }
                    if (tmp->adyacentes.at(i)->visitado == false) {
                        tmp->adyacentes.at(i)->visitado = true;
                        qd.push(tmp->adyacentes.at(i));
                    }
                    //cout << tmp->adyacentes.at(i)->getData() << endl;
            }
            tmp = qd.front();
            qd.pop();
        }

        tmp = end;
        do  {
            cout << tmp->getData() << endl;
            pathToVictory.push_back(tmp);
            tmp = tmp->padre;
            //cout << tmp->getData() << endl;
        } while (tmp != start);
        cout << tmp->getData() << endl;
        resetVisitados();
        //cout << end->val << endl;

        return pathToVictory;

    }

    void resetVisitados() {
        while (qv.size() > 0) {
            qv.first->value->visitado = false;
            qv.pop();
        }
    }

    /*
    *Recibe el nodo en el que se encutra y el nodo final al que se quiere llegar
    *Regresa un valor para saber si tu nodo cumple con la condición de la función
    */
    int HeuristicFunction(NG* current, NG* end) {
         
        int heuristic=end->val;
        if (current->val > end->val) {
            heuristic *= current->val / current->adyacentes.size(); 
            cout << heuristic;
            return heuristic;
        }
        return heuristic

    }

};