#include <iostream>

using namespace std;

class animal{
    private:
        int number_of_legs, number_of_eyes, number_of_ears;
    public:
        int average_speed, average_lifespan;
        void setData(int a, int b, int c);
        void printData(){
            cout << "Number of leg(s): " << number_of_legs << "\n";
            cout << "Number of eye(s): " << number_of_eyes << "\n";
            cout << "Number of ear(s): " << number_of_ears << "\n";
            cout << "Average speed: " << average_speed << " km/h" << "\n";
            cout << "Average lifespan: " << average_lifespan << " years" << "\n";
        }
};

void animal :: setData(int a, int b, int c){
    number_of_legs = a;
    number_of_eyes = b;
    number_of_ears = c;
}

int main(){
    animal cheetah, horse;
    cout << "Cheetah: \n";
    cheetah.average_speed = 64;
    cheetah.average_lifespan = 9;
    cheetah.setData(4, 2, 2);
    cheetah.printData();

    cout << "\nHorse: \n";
    horse.average_speed = 55;
    horse.average_lifespan = 27;
    horse.setData(4, 2, 2);
    horse.printData();
    return 0;
}