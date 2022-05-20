#include <iostream>
#include <map>
#include <stdlib.h>
#include <algorithm>
#include <string>

using namespace std;

//条件编译，可修改_PDADD_为_PDLIST_, _PDSHOW_, _PDREMOVE_得到四个执行文件
#define _PDREMOVE_
class Date{
    private:
        int year;
        int month;
        int day;
    public:
        Date(){
            year = 1900;
            month = 1;
            day = 1;
        }
        Date(int year, int month, int day){
            setYear(year);
            setMonth(month);
            setDay(day);   
        }
        int  const getYear(){
            return year;
        }
        void setYear(int year){
            this->year = year;
        }
        int const getMonth(){
            return month;
        }
        void setMonth(int month){
            if(month < 1){
                this->month = 1;
            } else if (month <= 12){
                this->month = month;
            } else {
                this->month = 12;
            }
        }
        int const getDay(){
            return day;
        }
        void setDay(int day){
            int maxDay;
            if((2 * this->month - 15) % 2 == 1){
                maxDay = 31;
            } else if (this->month == 2){
                maxDay = ((this->year % 4 != 0) || ((this->year % 100 == 0) & (this->year % 400 != 0))) ? 28 : 29;
            } else {
                maxDay = 30;
            }
            if(day < 1){
                this->day = 1;
            } else if (day <= maxDay){
                this->day = day;
            } else {
                this->day = maxDay;
            }
        }
        void showDate() const{
             cout << "Year: " << year << ", Month: " << month
                 << ", Day: " << day << endl;
        }
        void printDate() const{
            cout << year << "-" << month << "-" << day << endl;
        }
        static Date str2date(string str)
        {
            int numyear = 0, nummonth = 0, numday = 0, i, len;
            for(i=0; i<4; i++){
                if(str[i]>='0' && str[i]<='9'){
                    numyear = 10 * numyear + str[i] - '0';
                } else {
                    break;
                }
            }
            len = i;
            for(i=len; i<len+2; i++){
                if(str[i]>='0' && str[i]<='9'){
                    nummonth = 10 * nummonth + str[i] - '0';
                } else {
                    break;
                }
            }
            len = i;
            for(i=len; i<len+2; i++){
                if(str[i]>='0' && str[i]<='9'){
                    numday = 10 * numday + str[i] - '0';
                } else {
                    break;
                }
            }
            return Date(numyear, nummonth, numday);
        }
        int DateCmp(Date odate) const
        {
            long vs = this->year * 400 + this->month * 32 + this->day;
            long vo = odate.year * 400 + odate.month * 32 + odate.day;
            if(vs < vo) {
                return -1;
            } else if(vs == vo) {
                return 0;
            } else {
                return 1;
            }
        }
};
struct CmpDate{
    bool operator()(const Date& d1, const Date& d2) const{  
        return d1.DateCmp(d2) == -1;  
    }  
};
class Entity{
    private:
        int id;
        string log;
    public:
        int getId(){
            return id;
        }
        void setId(int id){
            this->id = id;
        }
        string getLog(){
            return log;
        } 
        void updateLog(string log){
            this->log = log;
        }
        void appendLog(string alog){
            this->log += alog;
        }
        void showContent(){
            cout << log << endl;
        }
        void printContent(){
            cout << log << endl;
        }
};
class PersonalDiary{       
    public:
        map<Date, Entity, CmpDate> diary;
        void pdread();//把标准格式的文件中读取map对存储到diary
        void pdwrite();//将diary的内容标准格式写到文件中
};
//保证了就算有重复日期记录，也会保留最后的那条，与pdadd执行文件相照应。
void PersonalDiary::pdread()
{
    string line;
    Date date;
    Entity entity;
    while(getline(cin, line)){
        date = Date::str2date(line);
        //若已有date和entity创建，则只更新其entity内容，否则新建一个date和entity的map对
        if(diary.count(date) == 1){
            entity = diary[date];
            entity.updateLog("");
            while(getline(cin, line)){
                if(line == "."){
                    break;
                } else {
                    entity.appendLog(line);
                }
            }
        } else {
            entity = Entity();
            while(getline(cin, line)){
                if(line == "."){
                    break;
                } else {
                    entity.appendLog(line);
                }
            }
            diary.insert(pair<Date, Entity>(date, entity));
        }
    }
}
void PersonalDiary::pdwrite(){
    for(map<Date, Entity>::iterator iter = diary.begin(); iter != diary.end(); iter++){
        iter->first.printDate();
        iter->second.printContent();
        cout << "." << endl;  
    }
}


//条件编译实现四个不同的执行文件
int main(int argc, char** argv)
{
    PersonalDiary pd = PersonalDiary();
    //通过管道命令将cout变成文件pd.txt, 以追加格式写入
    #ifdef _PDADD_
    string line;
    getline(cin, line);
    Date date = Date::str2date(line);
    Entity entity = Entity();
    while(getline(cin, line) && line != "."){   
        entity.appendLog(line);
    }
    pd.diary.insert(pair<Date, Entity>(date, entity));
    pd.pdwrite();
    #endif
    //通过管道命令将cin变成文件pd.txt, 即读入pd.txt中保存的pd信息
    #ifdef _PDLIST_
    pd.pdread();
    if(argc < 3){
        for(map<Date, Entity>::iterator iter = pd.diary.begin(); iter != pd.diary.end(); iter++){
            iter->first.showDate();
            iter->second.showContent();
        }
    } else {
        Date beginDate = Date::str2date(argv[1]), endDate = Date::str2date(argv[2]);
        for(map<Date, Entity>::iterator iter = pd.diary.begin(); iter != pd.diary.end(); iter++){
            if(iter->first.DateCmp(beginDate) >= 0 && iter->first.DateCmp(endDate) <= 0) {
                iter->first.showDate();
                iter->second.showContent();
            }     
        }
    }
   #endif    
     //通过管道命令将cin变成文件pd.txt, 即读入pd.txt中保存的pd信息
    #ifdef _PDSHOW_
    pd.pdread();
    Date date = Date::str2date(argv[1]);
    if(pd.diary.count(date) == 1){
        pd.diary[date].showContent();
    } else {
        cout << "This date has no entity." << endl;
    }
   #endif
    //通过管道命令将cin和cout变成文件pd.txt, 若成功完成删除操作则重写pd.txt
    #ifdef _PDREMOVE_
    pd.pdread();
    Date date = Date::str2date(argv[1]);
    if(pd.diary.count(date) == 1){
        pd.diary.erase(date);
        pd.pdwrite();
    }else{
        return -1;
    }
   #endif
    return 0;
}
