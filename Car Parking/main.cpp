#include <bits/stdc++.h>
using namespace std;



class CarParkingSystem{
private:
  vector<vector<string>> parkingLot;
public:
  CarParkingSystem(int rows, int cols){
    parkingLot.resize(rows, vector<string>(cols, ""));
  }

  bool validateSpot(int spot){
    int row = spot / 10;
    int col = spot % 10;
    return (row < parkingLot.size() && row >= 0 && col < parkingLot[0].size() && col >= 0);
  }

  pair<int, int> findCarSpot(string numPlate){
    for(int i=0; i<parkingLot.size(); i++){
      for(int j=0; j<parkingLot[i].size(); j++){
        if(parkingLot[i][j] == numPlate){
          cout << "Your Car found at spot: " << i*10 + j << endl;
          return {i, j};
        }
      }
    }
    cout << "Car with number plate " << numPlate << " not found" << endl;
    return {-1, -1};
  }

  string park(string numPlate){
    // park the car at the first available spot, if spot is not available return -1
    for(int i=0; i<parkingLot.size(); i++){
      for(int j=0; j<parkingLot[i].size(); j++){
        if(parkingLot[i][j] == ""){
          parkingLot[i][j] = numPlate;
          return "Car parked at spot: " + to_string(i*10 + j);
        }
      }
    }
    return "Sorry, parking lot is full";
  }

  string unpark(string x){
    try{
      int spot = stoi(x);
      return unparkBySpot(spot);
    } catch(exception e){
      return unparkByNumPlate(x);
    }
  }

  string unparkBySpot(int spot){
    int row = spot / 10;
    int col = spot % 10;
    if(!validateSpot(spot)){
      return "Sorry, spot is already empty or invalid";
    }
    parkingLot[row][col] = "";
    return "Car successfully unparked";
  }

  string unparkByNumPlate(string numPlate){
    pair<int, int> pos = findCarSpot(numPlate);
    if(pos.first != -1 && pos.second != -1){
      parkingLot[pos.first][pos.second] = "";
      return "Car successfully unparked";
    }
    return "Sorry, car with number plate " + numPlate + " not found";
  }



};

int main(){
  CarParkingSystem cps(3, 4); // 3 rows and 4 columns
  while(true){
    cout << "1. Park Car\n2. Unpark Car\n3. Find Car\n4. Exit\n";
    int choice;
    cin >> choice;
    if(choice == 1){
      string numPlate;
      cout << "Enter car number plate: ";
      cin >> numPlate;
      cout<<cps.park(numPlate)<<endl;
    } else if(choice == 2){
      string x;
      cout << "Enter spot/Car Plate number to unpark: ";
      cin >> x;
      cout<<cps.unpark(x)<<endl;
    } else if(choice == 3){
      string numPlate;
      cout << "Enter car number plate to find: ";
      cin >> numPlate;
      cps.findCarSpot(numPlate);
    } else if(choice == 4){
      break;
    } else {
      cout << "Invalid choice, try again." << endl;
    }
  }

  return 0;
}