/*
 Задача#7: Есть 3 вида товаров поставляемые в магазины через склад: мясо, фрукты, овощи. Склад с 5 воротами для загрузки/разгрузки, каждые ворота работают для одного вида товара, который разгружают/загружают первым. Вначале 3 ворот зарезервированны для разгрузки каждого вида товара, 2 остальных ворот свободны и могут использоваться и для разгрузки и для загрузки. Ворота могут переключиться  на другой вип товара при загрузке если текущий вид закончился или превышает на 50 тонн текущий. Товары развозят фурами вместимостью по 10 тонн. Скорость разгрузки/загрузки 1 машины 2 тонны в час. Машины, привозящие товар, можно генерировать, к примеру по 15 штук каждые 24 часа.*/
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <queue>

using namespace std;
struct Bus {
    int countOfTonInABus;
    int numberOfTypeProduct;
};
struct Gate {
    int whatProduct = 0; //1,2,3
    int howMuch = 0;
    bool LoadingOrUploading = 0;
};
vector <Gate> Gat(vector <Gate> Gates) {
    for (int i =0;i < 5;i++) {
        Gate gate;
        if (i == 1) {
            gate.whatProduct = 1;
        }
        if (i == 2) {
            gate.whatProduct = 2;
        }
        if (i == 3) {
            gate.whatProduct = 3;
        }

        Gates.push_back(gate);

    }
    return Gates;
};
vector <Gate> Gates;
queue <Bus> Buses1 = {};
int TIMEG = 24;
vector <int> TIME = {24, 24, 24, 24, 24};

class BUSES {
public:
    queue <Bus> Buses = {};
    queue <Bus> GenerateBuses (queue <Bus> Buses) {
        int timeForUploationOneBus = 0;
 //       cout <<"1 "<< TIMEG << endl;
//        if (TIME == 24) {
            int countOfBus = rand()%15 + 1;
         //   cout << "countOfBus"<<countOfBus<< endl;
//            TIME = 0;
            for (int i = 0; i < countOfBus; i++) {
                Buses = AddNewBus(Buses);
            }
            unsigned long k = Buses.size();
            unsigned long g = Gates.size();
            for (int i = 0; i < k; i++) {
                Bus B = Buses.front();
                WhatEnter(B);
                //   cout << endl<<endl;
                timeForUploationOneBus = B.countOfTonInABus/2;
                for (int i = 0;i < timeForUploationOneBus;i++) {
                    if (TIMEG < 24) {
                        TIMEG += 2;
                    }
                    else
                        TIMEG = 0;
                }
                //  cout << i<<"  "<<B.countOfTonInABus <<"  "<<B.numberOfTypeProduct<<endl;
                    for (int i = 0; i < g; i++) {
                    Gate G = Gates[i];
                //    cout << i<<"  "<<G.whatProduct <<"  "<<G.howMuch << "  "<<G.LoadingOrUploading<<endl;
                }
              //  cout << endl<< endl<< endl;
                Buses.pop();
                Buses.push(B);
            }
//            else {
//                TIME = 0;
//            }
        
//
//        for (int i = 0; i < g; i++) {
//            Gate G = Gates[i];
//            cout << i<<"  "<<G.whatProduct <<"  "<<G.howMuch << "  "<<G.LoadingOrUploading<<endl;
//           // Gates.pop();
//           // Gates.push(G);
//        }
        
        return Buses;
    };
    
    queue <Bus> AddNewBus(queue <Bus> Buses) {
        Bus bus;
        bus.countOfTonInABus = 10;
        bus.numberOfTypeProduct = rand()%3 + 1;
        Buses.push(bus);
        return Buses;
    };
    
    Bus ReturnFirstBus(queue <Bus> Buses) {
        Bus firstBus = Buses.front();
        //Buses.pop();
        return firstBus;
    };
    void WhatEnter (Bus bus) {
     //   Gate gate;
        if (bus.numberOfTypeProduct == 1) {
            
            if (Gates[1].howMuch < 50) {
//                gate = Gates[1];
                TIME[1] += 2;
                Gates[1].whatProduct = 1;
                Gates[1].LoadingOrUploading = 1;
                Gates[1].howMuch += bus.countOfTonInABus;
                bus.countOfTonInABus = 0;
            }
            else if ((Gates[0].howMuch < 50 && Gates[0].whatProduct == 1) || Gates[0].howMuch == 0) {
//                gate = Gates[0];
                TIME[0] += 2;
                Gates[0].whatProduct = 1;
                Gates[0].LoadingOrUploading = 1;
                Gates[0].howMuch += bus.countOfTonInABus;
                bus.countOfTonInABus = 0;
            }
            else if ((Gates[4].howMuch < 50 && Gates[4].whatProduct == 1) || Gates[4].howMuch == 0) {
//                gate = Gates[4];
                TIME[4] += 2;
               Gates[4].whatProduct = 1;
                Gates[4].LoadingOrUploading = 1;
                Gates[4].howMuch += bus.countOfTonInABus;
                bus.countOfTonInABus = 0;
            }
        }
        else if (bus.numberOfTypeProduct == 2) {
            if (Gates[2].howMuch < 50) {
//                gate = Gates[2];
                TIME[2] += 2;
                Gates[2].whatProduct = 2;
                Gates[2].LoadingOrUploading = 1;
                Gates[2].howMuch += bus.countOfTonInABus;
                bus.countOfTonInABus = 0;
            }
            else if ((Gates[0].howMuch < 50 && Gates[0].whatProduct == 2) || Gates[0].howMuch == 0) {
//                gate = Gates[0];
                TIME[0] += 2;
                Gates[0].whatProduct = 2;
                Gates[0].LoadingOrUploading = 1;
                Gates[0].howMuch += bus.countOfTonInABus;
                bus.countOfTonInABus = 0;
            }
            else if ((Gates[4].howMuch < 50 && Gates[4].whatProduct == 2) || Gates[4].howMuch == 0) {
//                gate = Gates[4];
                TIME[4] += 2;
              Gates[4].whatProduct = 2;
                Gates[4].LoadingOrUploading = 1;
                Gates[4].howMuch += bus.countOfTonInABus;
                bus.countOfTonInABus = 0;
            }
        }
        else if (bus.numberOfTypeProduct == 3) {
            if (Gates[3].howMuch < 50) {
//                gate = Gates[3];
                TIME[3] += 2;
                Gates[3].whatProduct = 3;
                Gates[3].LoadingOrUploading = 1;
                Gates[3].howMuch += bus.countOfTonInABus;
                bus.countOfTonInABus = 0;
            }
            else if ((Gates[0].howMuch < 50 && Gates[0].whatProduct == 3) || Gates[0].howMuch == 0) {
//                gate = Gates[0];
                Gates[0].whatProduct = 3;
                TIME[0] += 2;
                Gates[0].LoadingOrUploading = 1;
                Gates[0].howMuch += bus.countOfTonInABus;
                bus.countOfTonInABus = 0;
            }
            else if ((Gates[4].howMuch < 50 && Gates[4].whatProduct == 3) || Gates[4].howMuch == 0) {
//                gate = Gates[4];
                TIME[4] += 2;
               Gates[4].whatProduct = 3;
                Gates[4].LoadingOrUploading = 1;
                Gates[4].howMuch += bus.countOfTonInABus;
                bus.countOfTonInABus = 0;
            }
           
        }
        //  WhatExit();
    };
    void WhatExit() {
        int maxOfGates = 0;
        int max = Gates[0].howMuch;
            for (int i=0; i<5; i++){
                if (Gates[i].howMuch > max) {
                    max = Gates[i].howMuch;
                    maxOfGates = i;
                }
            }
        if (Gates[maxOfGates].howMuch >= 50) {
            TIME[maxOfGates] += 2;
            TIMEG += 2;
            Gates[maxOfGates].howMuch -= 5;
          //  Buses.push(bus);
        }
        for (int i=0; i<5; i++){
            cout << "G " << i << " =  " << Gates[i].howMuch<< endl;
        }
    };
    
    
};
void thread1(){
    int count = 0;
    BUSES B;
    Gates = Gat(Gates);
    while(true) {
   // if (TIME <= 24) {
//        TIME = 0;
        count++;
        Buses1 = B.GenerateBuses(Buses1);
        if (count == 5)
            break;
        
     //   cout << "TIME  "<<TIME<< endl;
   // }
    
    }
}
void thread2(){
    BUSES B;
    
    int count = 0;
    while(true) {
   // if (TIME <= 24) {
//        TIME = 0;
        count++;
        B.WhatExit();
        if (count == 20)
            break;
        
     //   cout << "TIME  "<<TIME<< endl;
   // }
    
    }
}
int main() {
   
//  thread th(print);
//  th.detach();//по очереди каждая итерация оборвется th если разное количество итераций
//  th.join();//если после вызывать то как будто в одном потоке будет надо ставить где нужн
//  cout<<this_thread::get_id()<<"  "<<i<<endl;   //вывод текущего потока
//  this_thread::sleep_for(chrono::milliseconds(1000));
//  th.join();
//  this_thread::sleep_for(chrono::milliseconds(1000));  //приостанавливает работу текущего потока на нек время
    
//    int count = 0;
//    BUSES B;
//    Gates = Gat(Gates);
//    while(true) {
//   // if (TIME <= 24) {
////        TIME = 0;
//        count++;
//        Buses1 = B.GenerateBuses(Buses1);
//        if (count == 5)
//            break;
//
//     //   cout << "TIME  "<<TIME<< endl;
//   // }
////
//    }
    
    thread t1(thread1);
    thread t2(thread2);
 //   this_thread::sleep_for(chrono::milliseconds(1000));
  //  thread t2(thread2);
  //  this_thread::sleep_for(chrono::milliseconds(1000));
    
    t1.join();
    t2.join();

  //  bus = B.ReturnFirstBus(Buses1);
   // cout <<"A "<< bus.countOfTonInABus <<"  "<<bus.numberOfTypeProduct << endl;
    return 0;
}
