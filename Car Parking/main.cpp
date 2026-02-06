#include <bits/stdc++.h>
using namespace std;

class Car{
public:
  string numberPlate;

  Car(string numPlate): numberPlate(numPlate){}
};

struct ParkingSpot{
public:
  int row;
  int col;
  bool isOccupied;
  Car* car;

  ParkingSpot(int r, int c): row(r), col(c), isOccupied(false), car(nullptr){}
};

//only stores state, no parking logic, no searching rules, just data
class ParkingLot{
private:
  vector<vector<ParkingSpot>> parkingLot;

public:
  ParkingLot(int rows, int cols){
    for(int i=0; i<rows; i++){
      vector<ParkingSpot> row;
      for(int j=0; j<cols; j++){
        row.emplace_back(i, j);
      }
      parkingLot.push_back(row);
    }
  }

  vector<vector<ParkingSpot>>& getSpots(){
    return parkingLot;
  }
};

/* we can add nearest spot logic, VIP Parking etc easily
class NearestSpotStrategy {};
 */

// business logic, Because rules change, data doesn’t.
class ParkingService{
  ParkingLot& parkingLot;

public:
  ParkingService(ParkingLot& lot) : parkingLot(lot) {}

  bool parkCar(Car& car){
    for(auto& row : parkingLot.getSpots()){
      for(auto& spot : row){
        if(!spot.isOccupied){
          spot.car = &car;
          spot.isOccupied = true;
          return true;
        }
      }
    }
    return false;
  }
  
  bool unparkCarByPlate(string numPlate){
    for(auto& row : parkingLot.getSpots()){
      for(auto& spot : row){
        if(spot.isOccupied && spot.car->numberPlate == numPlate){
          spot.car = nullptr;
          spot.isOccupied = false;
          return true;
        }
      }
    }
    return false;
  }
};

int main(){
  ParkingLot lot(3, 4);
  ParkingService service(lot);

  Car car1("ABC123");
  Car car2("XYZ789");

  service.parkCar(car1);
  service.parkCar(car2);

  service.unparkCarByPlate("ABC123");

  return 0;
}