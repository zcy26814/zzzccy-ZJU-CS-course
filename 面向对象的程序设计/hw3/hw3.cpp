#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;

//部分说明查看readme.docx

//定义关于房间的类
class Room{ 
    private:
        int roomType;
        //-1    0       1           2           3           4  
        //out   loddy   mainRoom    commonRoom  one-way     jump       函数Room *enterRoom中会用到
        int roomFloor; //楼高
        int roomId; //房间号，用于找到公主后原路出去
        map<string, Room*> roomExit;
        string roomMessage;
        double hasMonster;
        double hasPrincess;
        bool valid;
    public:
        Room(){
            hasMonster = false;
            hasPrincess = false;
        } //初始化房间信息
        Room(int type, int floor, int id){
            roomType = type;
            roomFloor = floor;
            roomId = id;
            hasMonster = 0;
            hasPrincess = 0;
            valid = true;
            switch(type){
                case -1:
                roomMessage = "You are go outside. ";
                break;
                case 0:
                roomMessage = "Welcome to the loddy of the castle: ";
                break;
                default:
                valid = false;
                roomMessage = "Welcome to new room: ";
                break;
            }
            
        }
        static string Direction[8];
        int getRoomType(){
            return roomType;
        }
        void setRoomType(int type){
            roomType = type;
        } //房间类型
        int getRoomFloor(){
            return roomFloor;
        }
        void setRoomFloor(int floor){
            roomFloor = floor;
        } //房间层数
        int getRoomId(){
            return roomId;
        }
        void setRoomId(int id){
            roomId = id;
        } //房间序号
        bool isValid(){
            return valid;
        }
        void setValid(bool v){
            valid = v;
        }
        map<string, Room*> getRoomExit(){
            return roomExit;
        }
        void addRoomExit(string dir, Room *nextRoom){
            roomExit.insert(pair<string, Room*>(dir, nextRoom));
        } //房间出口
        string getRoomMessage(){
            return roomMessage;
        }
        void setRoomMessage(string message){
            roomMessage = message;        
        } //房间信息
        double isMonster(){
            return hasMonster;
        } 
        void setMonster(double pro){
            hasMonster = pro;
        } //判断是否是怪我
        double isPrincess(){
            return hasPrincess;
        }
        void setPrincess(double pro){
            hasPrincess = pro;
        } //判断是否是公主
        bool showRoomMessage(){
            cout << roomMessage << "Floor " << roomFloor << ", id " << roomId << endl;
        }
        bool showRoomExit(){
            cout << "The room has " << roomExit.size() << " exits: ";
            for(map<string, Room*>::iterator iter = roomExit.begin(); iter != roomExit.end(); ) {
                cout << iter->first <<((++iter != roomExit.end()) ? ", " : ".") ;
            }
            cout << endl;
        } //显示每个房间对应拥有的出口
        Room* nextRoom(string cmd){
            map<string, Room*>::iterator iter = roomExit.find(cmd);
            return iter->second;
        }
        void linkRoom(string dir, Room *otherRoom){
            roomExit.insert(pair<string, Room*>(dir, otherRoom));
        }
};

string Room::Direction[8] = {"west", "up", "north", "in", "east", "down", "south", "out"}; 
//房间一共有 进入、离开、东、南、西、北、上、下 总共8个出口
//不代表每个房间都有这么多出口

//定义关于层的类
class Floor{ 
    private:
        int numFloor, cntRoom;
        Room *mainRoom;
        Room *curRoom;
        vector<Room> rooms;
    public:
        Floor();
        Floor(int num);
        ~Floor();
        int getFloorNum(){
            return numFloor;
        }
        void setFloorNum(int num){
            numFloor = num;
        }
        int getCntRoom(){
            return cntRoom;
        }
        Room *getMainRoom(){
            return mainRoom;
        }
        void setMainRoom(){
            mainRoom = new Room(1, numFloor, 1);
            curRoom = mainRoom;
            for(int i = 0; i < 8; i+=2){
                if(rand()%2)  addRoom(mainRoom, i);
            }
        }
        Room* getCurRoom(){
            return curRoom;
        }
        void setCurRoom(Room *room){
            curRoom = room;
        }
        Room *addRoom(Room *room, int i);
        Room *addRoom(Room *room, int type, int i);
        Room *enterRoom(string cmd){
            if(curRoom->getRoomExit().find(cmd) != (curRoom->getRoomExit().end())){
                Room *nextRoom = curRoom->getRoomExit().find(cmd)->second;
               	int i; 
                switch(nextRoom->getRoomType()){
                case -1:
                case 0:
                case 1:
                    curRoom = nextRoom;
                    return nextRoom;
                case 2:
                    if(!nextRoom->isValid()){
                        for(i = 0; i < 8; i+=2){
                            if(Room::Direction[i].compare(cmd)==0) break;
                        }
                        if(i==8){
                            return NULL;
                        }else{
                            i = (i+4)%8;
                            nextRoom->addRoomExit(Room::Direction[i], curRoom);
                            for(int j = 0; j < 8; j+=2){
                                if(j!=i){
                                    if(rand()%4==0) addRoom(nextRoom, j);
                                }
                            }
                        }
                        nextRoom->setValid(true);
                    }
                    curRoom = nextRoom;
                    return curRoom;
                case 3:
                    if(!nextRoom->isValid()){
                        int j;
                	    for(i = 0; i < 8; i+=2){
                            if(Room::Direction[i].compare(cmd)==0) break;
                        }
                        i = (i+4)%8;
                        for(j = 0; j < 8; j+=2){                            
                            if(j!=i){
                                if(rand()%4==0) addRoom(nextRoom, j);
                            }
                        }
                        if(nextRoom->getRoomExit().size() == 0)
                            addRoom(nextRoom, 4, (i+4)%8);
                        nextRoom->setValid(true);
                    }
                	curRoom = nextRoom;
                    return curRoom;
                case 4:
                    if(!nextRoom->isValid()){
                        nextRoom->addRoomExit("out", mainRoom); //当一层里没有房间时输入go out返回当层第一个房间
                        nextRoom->setValid(true);
                    }
                    curRoom = nextRoom;
                    return curRoom;
                }
            }else{
                return NULL;
            }            
            
        }
        void initFloor(int num);
};

Floor::Floor(int num){
    numFloor = num;
    setMainRoom();
}

Floor::~Floor(){
    cntRoom = 1;
    srand((unsigned)time(0));
}

Room *Floor::addRoom(Room *room, int i){
    if(cntRoom>15) {
        return NULL;
    }
    Room *newRoom = new Room(rand()%3+2, numFloor, ++cntRoom);
    newRoom->setMonster((double)rand()/RAND_MAX/(newRoom->getRoomType()+2));
    newRoom->setPrincess((double)rand()/RAND_MAX/(newRoom->getRoomType())); //设置碰到公主或者怪物的概率
    room->addRoomExit(Room::Direction[i], newRoom);
    rooms.push_back(*newRoom);
    return newRoom;
}

Room *Floor::addRoom(Room *room, int type, int i){
    Room *newRoom = new Room(type, numFloor, ++cntRoom);
    room->addRoomExit(Room::Direction[i], newRoom);
    rooms.push_back(*newRoom);
    return newRoom;
}

//定义关于城堡构成的类
class Castle{
    private:
    public:
        Room loddy, outside;
        int cntFloor;
        vector<Floor> floors;
        Room currentRoom;
        string currentCmd;
        void initCastle();
}; 

void Castle::initCastle(){
    srand((unsigned)time(0));
    cntFloor = rand() % 5 + 3;
    for(int i = 1; i <= cntFloor; i++){
        floors.push_back(*(new Floor(i)));
    }
    loddy = *(new Room(0, 1, 0));
    outside = *(new Room(-1, 0, 0));
    loddy.addRoomExit("out", &outside);
    outside.addRoomExit("in", &loddy);
    loddy.addRoomExit("in", floors[0].getMainRoom());
    floors[0].getMainRoom()->addRoomExit("out", &loddy);
    floors[0].setCurRoom(&loddy);
    for(int i = 0; i < cntFloor - 1; i++){
        floors[i].getMainRoom()->addRoomExit("up", floors[i+1].getMainRoom());
        floors[i+1].getMainRoom()->addRoomExit("down", floors[i].getMainRoom()); //输入up上楼则floor+1，down则-1
    }
}

//定义冒险游戏的类
class Adventure{
    private:
        Room* currentRoom;
        bool savePrincess;
        Castle castle;
        string command;
    public:
        Adventure();
        Room* getCurrentRoom();
        int updateAdventure(string cmd);
}; 

Adventure::Adventure()
{
    castle.initCastle();
    currentRoom = &castle.loddy;
    savePrincess = false;

    cout << "Welcome to the castle. " << endl;
    cout << "You need save the princess with avoiding killed by the monster." << endl;
    cout << "Best wishes. Game start." << endl;
    currentRoom->showRoomMessage();
    currentRoom->showRoomExit(); //初始化游戏界面信息
}

Room* Adventure::getCurrentRoom()
{
    return currentRoom;
}

int Adventure::updateAdventure(string cmd)
{
    system("cls"); //清屏
    double r = (double)rand()/RAND_MAX;
    if(cmd[0] == 'r'){
        currentRoom->showRoomMessage();
    } else if(cmd[0] == 'm'){
        currentRoom->showRoomExit();
    } else {
        Room *nextRoom = castle.floors[currentRoom->getRoomFloor()-1].enterRoom(cmd);
        if(nextRoom == NULL) {
            cout << "Command is invaild. Please enter the feasible command." << endl; //输入进入不存在房间的情况
            return 0;
        } else {
            currentRoom = nextRoom;
        }
        cout << "You just have taken the command: " << cmd << endl;
        if(r < currentRoom->isMonster()) {
            cout << "You are killed by the Monster. Game Over." << endl; //遇到怪物的情况
            return -1;
        } else if (!savePrincess && r < currentRoom->isPrincess()) {
            savePrincess = true;
            cout << "Good Luck! You meet the princess. Now try to escape the castle." << endl; //遇到公主的情况
            return 0;
        } else if(savePrincess && (currentRoom->getRoomType() == -1)){
            cout << "You are get out of the castle." << endl;
            return 1;
        } else {
            currentRoom->showRoomMessage();
            currentRoom->showRoomExit();
        }    
    }
    return 0;
}

string getCommand() //操作指令
{
    string cmd, command;
    cout << "Enter your command: " << endl;
    getline(cin, cmd); //输入操作指令，并接受到cmd中
    for( int i = 0; i < cmd.size(); i++ ) {
        cmd[i] = tolower(cmd[i]); //处理大小写，化为小写
    }
    if(cmd[0] == 'g' && cmd[1] == 'o') {
        switch (cmd[3])
        {
        case 'e':
            command = "east";
            break;
        case 'w':
            command = "west";
            break;
        case 'n':
            command = "north";
            break;
        case 's':
            command = "south";
            break;
        case 'u':
            command = "up";
            break;
        case 'd':
            command = "down";
            break;
        case 'i':
            command = "in";
            break;
        case 'o':
            command = "out";
            break;
        default:
            break;
        }
    } 
    return command;
}

void printError()
{
    cout << "Please input correct command." << endl; //输入错误指令
}

void gameOver(int sign)
{
    if(sign > 0) {
        cout << "Victory! You have saved the princess and escape the castle." << endl; //游戏胜利
    } else {
        cout << "Loser! You lose the life." << endl; //游戏失败
    }
    cout << "Try again?" << endl;
}


int main()
{
    int sign, restart;
    while (1) {
    	string cmd;
        Adventure adventure;
        while (1) {
            cmd = getCommand();
            if(cmd == "") {
                printError();
            } else {
                sign = adventure.updateAdventure(cmd);
                if(sign != 0)   break;
            }
        }
        gameOver(sign);
        cin >> restart;
        if(restart == 0) {
            cout << "Game Over. See you." << endl;
            return 0;
        } else {
            cout << "Game Restart." << endl;
        } //输入0结束游戏，其余重新开始游戏
    }
}