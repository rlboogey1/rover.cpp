#include <iostream> 
#include <string>
using namespace std;

void printCommandSuccess(int x, int y, string f, int b) {
    cout << "Command Succeeded. Current Coordinates: (" << x << " , "<< y << ") Heading: " << f << " Battery: " << b << endl;
}

void scan (int x,int y,int &b) {
    if (b < 3) {
        cout << "Command S rejected: insufficient battery" << endl;
    }
    else {
        cout << "Scanning... " << endl;
        b-=3;
    }
}

void charge(int x,int y, int &b) {
    if (b <= 0) {
        cout << "Command C rejected: insufficient battery" << endl;
    }
    else {
        if (x == 0 && y == 0) {
            b = 40;
            cout << "Charging! Battery: " << b << endl;
        }
        else {
            cout << "You are not at a charging station. Battery: " << b << " Current Coordinates:(" << x << " , " << y << ")" << endl;
        }
    }
}  

bool checkGoal (int x, int y, int goalX, int goalY) {
    if (x == goalX && y == goalY) {
        return true;
    }
    else {
        return false; 
    }
}

void forward(int &x, int &y, int &b, string f) {
    if (b < 2){
        cout << "Command F rejected: insufficient battery. " << endl;
    }
    else {
        if (f == "east") {
            if (x >= 9) {
                cout << "Command F rejected: out of bounds. " << endl;
            }
            else{
                x += 1;
                b -= 2;
                printCommandSuccess(x,y,f,b);
            }
        }
        else if (f == "west") {
            if (x <= 0) {
                cout << "Command F rejected: out of bounds. " << endl;
            }
            else {
                x -= 1;
                b-= 2;
                printCommandSuccess(x,y,f,b);
            }
        }
        else if (f == "north") {
            if (y >= 9) {
                cout << "Command F rejected: out of bounds. " << endl;
            }      
            else {
                y +=1;
                b-=2;
                printCommandSuccess(x,y,f,b);
            }
        }
        else if (f == "south") {
            if (y <= 0) {
                cout << "Command F rejected: out of bounds. " << endl;
            }
            else {
                y -=1;
                b -=2;
                printCommandSuccess(x,y,f,b);
            }
        }
    }
    
}

void left(string &f, int &b) {
    if (b < 1) {
        cout << "Command L rejected: insufficient battery. " << endl;
    }
    else {
        if (f == "east"){
            f = "north";
            b-=1;
        }
        else if (f == "west") {
            f = "south";
            b-=1;
        }
        else if (f == "north") {
            f = "west";
            b-=1;
        }
        else if (f == "south") {
            f = "east";
            b-=1;
        }
    }
}

void right(string &f, int &b) {
    if (b < 1) {
        cout << "Command R rejected: insufficient battery. " << endl;
    }
    else {
        if (f == "east"){
            f = "south";
            b-=1;
        }
        else if (f == "west") {
            f = "north";
            b-=1;
        }
        else if (f == "north") {
            f = "east";
            b-=1;
        }
        else if (f == "south") {
            f = "west";
            b-=1;
        }
    }
}

void moveRover(string m, int &x, int &y, int &goalX, int &goalY, string &f, int &b) {
    bool reachedGoal = false; 
    for (int i = 0; i < m.length(); i++) {
        char c = m[i];
        switch (c) {
            case 'F':
                forward(x,y,b,f);
                break;
            case 'L':
                left(f,b);
                break;
            case 'R':
                right(f,b);
                break;
            case 'S':
                scan(x,y,b);
                break;
            case 'C': 
                charge(x,y,b);
                break;
        }
        if (checkGoal(x,y,goalX,goalY)) {
            reachedGoal = true; 
        }
    }
    if(reachedGoal == true) {
        cout << "Mission Complete!" << endl;
        cout << "Mission Complete at coordinates: (" << x << " , " << y << ") with heading: " << f << " and Battery: " << b << endl;
        cout << "Goal Reached and rover reset. " << endl; 
        x = 0;
        y = 0; 
        f = "east";
        b = 40;
        }
    else {
        cout << "Mission Complete! " << endl;
        cout << "Mission Complete at coordinates: (" << x << " , " << y << ") with heading: " << f << " and Battery: " << b << endl;
        cout << "Goal has not been reached and rover does not reset. " << endl;
    }

}

string inputMission(string m, bool &r) {
    bool validM = false;
    while (validM == false) {
        cout << "Enter Mission: "; 
        cin >> m; 
        validM = true; 
        if (m == "quit" || m == "Quit") {
            r = true;
            return m; 
        }
        else {
            r = false;
            for (int i = 0; i < m.length(); i++) {
                if (m[i] != 'F' && m[i] != 'L' && m[i] != 'R' && m[i] != 'S' && m[i] != 'C') {
                    cout << "Invalid Input" << endl; 
                    validM = false;
                    break;
                }
            }
        }
    }
    return m;
}

int goalXCoords() {
    int goalX = 0; 
    bool validX= false;
    while (validX == false) {
        cout << "Enter goal X Coordinate: ";
        cin >> goalX;
        if (goalX < 10 && goalX > 0) { // goal x coordinate is within range
            validX = true; 
        }
        else {
            cout << "Invalid Input" << endl; 
            validX = false;
        }
    }
    return goalX;
}

int goalYCoords() {
    int goalY = 0; 
    bool validY = false; 
    while (validY == false) {
        cout << "Enter goal Y coordinate: ";
        cin >> goalY;
        if (goalY< 10 && goalY > 0) { // goal y is within range
            validY = true;
        }
        else {
            cout << "Invalid Input" << endl; 
            validY = false;
        }
    }
    return goalY;
}


int main() {
    string mission;  
    int xCoord = 0; 
    int yCoord = 0; 
    string direction = "east"; 
    int battery = 40;
    int goalX = goalXCoords();
    int goalY = goalYCoords();
    bool r = false; 
    while (r == false) {//main loop so it will continue after mission is completed
        mission = inputMission(mission, r);
        if (r == true) {
            break;
        }

        moveRover(mission,xCoord,yCoord,goalX,goalY,direction,battery);  //void moveRover(string m, int x, int y, int goalX, int goalY, string f, int b)

    }

    return 0; 
}