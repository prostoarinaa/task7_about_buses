/*
 Задача#7: Есть 3 вида товаров поставляемые в магазины через склад: мясо, фрукты, овощи. Склад с 5 воротами для загрузки/разгрузки, каждые ворота работают для одного вида товара, который разгружают/загружают первым. Вначале 3 ворот зарезервированны для разгрузки каждого вида товара, 2 остальных ворот свободны и могут использоваться и для разгрузки и для загрузки. Ворота могут переключиться  на другой вип товара при загрузке если текущий вид закончился или превышает на 50 тонн текущий. Товары развозят фурами вместимостью по 10 тонн. Скорость разгрузки/загрузки 1 машины 2 тонны в час. Машины, привозящие товар, можно генерировать, к примеру по 15 штук каждые 24 часа.*/


#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <queue>

using namespace std;
using namespace chrono;
mutex mtx, mtx1;
struct Bus {
    int countOfTonInABus;
    int numberOfTypeProduct;
};

struct Product {
    int howMuch;
    int whatProduct;
};

struct Gate {
    int whatProduct = 0; //1,2,3
    int howMuch = 0;
    bool LoadingOrUploading = 0;
};

vector <Gate> Gat(vector <Gate> Gates);
vector <Product> Prod(vector <Product> Products);

vector <Gate> Gates ;
vector <Product> Products ;
queue <Bus> Buses1 = {};
int TIME = 0;

class BUSES {
public:
    queue <Bus> GenerateBuses (queue <Bus>& Buses);
    queue <Bus> GenerateBuses2 (queue <Bus>& Buses);
    queue <Bus> AddNewBus(queue <Bus> Buses);
    Bus ReturnFirstBus(queue <Bus> Buses);
    void WhatEnter (Bus bus);
    void WhatExit();
};

void thread1();
void thread2();
void thread3();
void START();

int main() {
    setlocale(LC_ALL, "Russian");
    START();
    return 0;
}
//  thread th(print, a, b);
//  th.detach();//по очереди каждая итерация оборвется th если разное количество итераций
//  th.join();//если после вызывать то как будто в одном потоке будет надо ставить где нужн
//  cout<<this_thread::get_id()<<"  "<<i<<endl;   //вывод текущего потока
//  this_thread::sleep_for(chrono::milliseconds(1000));
//  th.join();
//  this_thread::sleep_for(chrono::milliseconds(1000));  //приостанавливает работу текущего потока на нек время


/*------------------------------------------------------------------------------------------------*/


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
        gate.howMuch = 0;
        gate.LoadingOrUploading = 0;
        Gates.push_back(gate);

    }
    return Gates;
};

vector <Product> Prod(vector <Product> Products) {
    for (int i =0;i < 3;i++) {
        Product product;
        if (i == 0) {
            product.whatProduct = 0;
        }
        if (i == 1) {
            product.whatProduct = 1;
        }
        if (i == 2) {
            product.whatProduct = 2;
        }
        product.howMuch = 0;
        Products.push_back(product);

    }
    return Products;
};


/*------------------------------------------------------------------------------------------------*/


void thread1() {
    int count = 0;
    BUSES B;
    Gates = Gat(Gates);
    Products = Prod(Products);
    while(true) {
        cout << "////////////////Начало работы 1 потока///////////////" << endl;
        count++;
        B.GenerateBuses(Buses1);
        TIME = 24;
        for (int i =0 ; i<24;i++) {
            this_thread::sleep_for(chrono::milliseconds(1000));
            TIME--;
        }
        TIME = 0;
        cout << "////////////////Конец работы 1 потока///////////////" << endl;
    }
}

void thread2() {
    int count = 0;
    BUSES B;
    this_thread::sleep_for(chrono::milliseconds(1000));
    while(true) {
        
        count++;
        if(Buses1.size() != 0) {
            cout<< "////////////////Начало работы 2 потока///////////////"<< endl;
            B.GenerateBuses2(Buses1);
            this_thread::sleep_for(chrono::milliseconds(2000));
        }
        else {
            for ( int i = 0; i < TIME; i++){
                this_thread::sleep_for(chrono::milliseconds(1000));
            }
            cout<< "////////////////Конец работы 2 потока///////////////"<< endl;
        }
    }
};
void thread21() {
    int count = 0;
    BUSES B;
    this_thread::sleep_for(chrono::milliseconds(1000));
    while(true) {
        
        count++;
        if(Buses1.size() != 0) {
            cout<< "////////////////Начало работы 21 потока///////////////"<< endl;
            B.GenerateBuses2(Buses1);
            this_thread::sleep_for(chrono::milliseconds(2000));
        }
        else {
            for ( int i = 0; i < TIME; i++){
                this_thread::sleep_for(chrono::milliseconds(1000));
            }
            cout<< "////////////////Конец работы 21 потока///////////////"<< endl;
        }
    }
};

void thread3() {
    BUSES B;
    this_thread::sleep_for(chrono::milliseconds(1000));
    int count = 0;
    while(true) {
        count++;
        if(Buses1.size() != 0) {
            cout<< "////////////////Начало работы 3 потока///////////////"<< endl;
            B.WhatExit();
            this_thread::sleep_for(chrono::milliseconds(2000));
        }
        else {
            for ( int i = 0; i < TIME; i++){
                this_thread::sleep_for(chrono::milliseconds(1000));
            }
            cout<< "////////////////Конец работы 3 потока///////////////"<< endl;
        }
    }
};

void START() {
    thread t1(thread1);
    thread t2(thread2);
    thread t21(thread21);
    thread t3(thread3);
    t2.join();
    t21.join();
    t3.join();
    t1.join();
}


/*------------------------------------------------------------------------------------------------*/


queue <Bus> BUSES::GenerateBuses (queue <Bus>& Buses) {
    mtx.lock();
    this_thread::sleep_for(chrono::milliseconds(10));
    int countOfBus = rand()%30 + 1;
    cout << "----Количество автобусов, генерируемых каждые 24 часа = " << countOfBus <<"-----"<< endl;
    for (int i = 0; i < countOfBus; i++) {
        Buses = AddNewBus(Buses);
    }
    mtx.unlock();
return Buses;
};

queue <Bus> BUSES::GenerateBuses2 (queue <Bus>& Buses) {
    mtx.lock();
    mtx1.lock();
        unsigned long k = Buses.size();
        unsigned long g = Gates.size();
    mtx1.unlock();
        for (int i = 0; i < k; i++) {
            
            
            Bus B = Buses.front();
            
            WhatEnter(B);
            
            Buses.pop();
           
            cout << "---------Текущее положение ворот, машины и склада с продуктами--------" << endl;
            this_thread::sleep_for(chrono::milliseconds(10));
            cout << "BUS № " << i << ", Тонн " << B.countOfTonInABus << ", Продукт № " << B.numberOfTypeProduct << endl << endl;
            for (int i = 0; i < 3; i++) {
                Product product = Products[i];
                cout <<"---PRODUCT на складе, тип №: " << product.whatProduct << " , в количестве " << product.howMuch << " ----" << endl;
            }
            for (int i = 0; i < g; i++) {
                Gate G = Gates[i];
                this_thread::sleep_for(chrono::milliseconds(10));
                cout << "GATE № " << i << ", Продукт № " << G.whatProduct  << ", положение " << G.LoadingOrUploading << endl;
                this_thread::sleep_for(chrono::milliseconds(10));
            }
            cout << "-------------------------------------------------------------------" << endl << endl<< endl;
//            Buses.pop();
        }
    mtx.unlock();
    return Buses;
};

queue <Bus> BUSES::AddNewBus(queue <Bus> Buses) {
    Bus bus;
    bus.countOfTonInABus = 10;
    bus.numberOfTypeProduct = rand()%3 + 1;
    Buses.push(bus);
    return Buses;
};

Bus BUSES::ReturnFirstBus(queue <Bus> Buses) {
    Bus firstBus = Buses.front();
    return firstBus;
};

void BUSES::WhatEnter (Bus bus) {
    this_thread::sleep_for(chrono::milliseconds(1000));
    if (bus.numberOfTypeProduct == 1) {
        
        if (Products[0].howMuch < 50) {
            Gates[1].whatProduct = 1;
            Gates[1].LoadingOrUploading = 1;
            Products[0].howMuch += bus.countOfTonInABus;
            bus.countOfTonInABus = 0;
        }
        else if ((Products[0].howMuch < 50 && Gates[0].whatProduct == 1) || Gates[0].howMuch == 0) {
            Gates[0].whatProduct = 1;
            Gates[0].LoadingOrUploading = 1;
            Products[0].howMuch += bus.countOfTonInABus;
            bus.countOfTonInABus = 0;
        }
        else if ((Products[0].howMuch < 50 && Gates[4].whatProduct == 1) || Gates[4].howMuch == 0) {
            Gates[4].whatProduct = 1;
            Gates[4].LoadingOrUploading = 1;
            Products[0].howMuch += bus.countOfTonInABus;
            bus.countOfTonInABus = 0;
        }
    }
    else if (bus.numberOfTypeProduct == 2) {
        if (Products[1].howMuch < 50) {
            Gates[2].whatProduct = 2;
            Gates[2].LoadingOrUploading = 1;
            Products[1].howMuch += bus.countOfTonInABus;
            bus.countOfTonInABus = 0;
        }
        else if ((Products[1].howMuch < 50 && Gates[0].whatProduct == 2) || Gates[0].howMuch == 0) {
            Gates[0].whatProduct = 2;
            Gates[0].LoadingOrUploading = 1;
            Products[1].howMuch += bus.countOfTonInABus;
            bus.countOfTonInABus = 0;
        }
        else if ((Products[1].howMuch < 50 && Gates[4].whatProduct == 2) || Gates[4].howMuch == 0) {
            Gates[4].whatProduct = 2;
            Gates[4].LoadingOrUploading = 1;
            Products[1].howMuch += bus.countOfTonInABus;
            bus.countOfTonInABus = 0;
        }
    }
    else if (bus.numberOfTypeProduct == 3) {
        if (Products[2].howMuch < 50) {
            Gates[3].whatProduct = 3;
            Gates[3].LoadingOrUploading = 1;
            Products[2].howMuch += bus.countOfTonInABus;
            bus.countOfTonInABus = 0;
        }
        else if ((Products[2].howMuch < 50 && Gates[0].whatProduct == 3) || Gates[0].howMuch == 0) {
            Gates[0].whatProduct = 3;
            Gates[0].LoadingOrUploading = 1;
            Products[2].howMuch += bus.countOfTonInABus;
            bus.countOfTonInABus = 0;
        }
        else if ((Products[2].howMuch < 50 && Gates[4].whatProduct == 3) || Gates[4].howMuch == 0) {
            Gates[4].whatProduct = 3;
            Gates[4].LoadingOrUploading = 1;
            Products[2].howMuch += bus.countOfTonInABus;
            bus.countOfTonInABus = 0;
        }
    }
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << endl << "/////////------Машина выгружена за 2 часа------/////////" << endl << endl;
    
};
void BUSES::WhatExit() {
    this_thread::sleep_for(chrono::milliseconds(2000));
    int maxOfGates = 0;
    int max = 0;
        for (int i=0; i<5; i++){
            if (Products[i].howMuch >= max) {
                max = Products[i].howMuch;
                maxOfGates = i;
            }
        }
    if (Products[maxOfGates].howMuch >= 50) {
        Products[maxOfGates].howMuch -= 10;
       // Products[maxOfGates].LoadingOrUploading = 0;
    }
};
