#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Flight {
	private: 
	    string flightName[5];//航班号 
	    string startStation[5];//起点 
	    string endStation[5];//终点 
	    string airName[5];//飞机型号 
	    string flightDate[5];//飞行日期
	    int remainTickets[5]; //余票量
	public:
		Flight() {} //无参构造函数 
	    Flight(string f[],string s[],string end[],string air[],string fd[],int r[]){
		    for(int i=0;i<5;i++){
		    	flightName[i]=f[i];
		    	startStation[i]=s[i];
		    	endStation[i]=end[i];
		    	airName[i]=air[i];
		    	flightDate[i]=fd[i];
		    	remainTickets[i]=r[i];
			}			
		};  
		void readFlight();
		void sign();
		void find(); 
		void book();
		void refund();
};//航班类

void Flight::readFlight() {
    ifstream infile("flight.txt");

    if (infile.is_open()){
        for (int i=0;i<5;++i) {
            infile>>flightName[i]>>startStation[i]>>endStation[i]>>airName[i]>>flightDate[i]>>remainTickets[i];
        }
        infile.close();
    }
	else {
        std::cout << "无法打开文件" << std::endl;
    }

}//录入航班信息库 

void Flight::sign(){
	int a;
	cout<<"选择您所需要的服务："<<endl;
	cout<<"1.查询航班；"<<endl;
	cout<<"2.订票；"<<endl;
	cout<<"3.退票；"<<endl;
	cout<<"输入您的选择：";
	cin>>a;
	switch(a){
		case 1:
			find();
			break;
		case 2:
			book();
			break;
		case 3:
			refund();
			break;
		default:
			break;
	}			
}

void Flight::find(){  
    string start,end;
    cout<<"输入您的始发站："<<endl;
    cin>>start;
    cout<<"输入您的终点站："<<endl;
    cin>>end;
    int found=0;
    for(int i=0; i<5;++i) {
        if (startStation[i] == start && endStation[i] == end) {
            found=1;
            cout<<"航班号:"<<flightName[i]<< endl;
            cout<<"起点站:"<<startStation[i]<< endl;
            cout<<"终点站:"<<endStation[i]<< endl;
            cout<<"飞机号:"<<airName[i]<<endl;
            cout<<"飞行日期:"<<flightDate[i]<<endl;
            cout<<"剩余票数:"<<remainTickets[i]<<endl;
            cout<<"--------------------------"<<endl;
            break;
        }
    }
    if(found==0){
        cout<<"没有相应航班"<<endl;
    }
}//查询航班

void Flight::book(){
    string name,flight,id;
    int l;
    cout<<endl<<"输入您所需要乘坐的航班：";
    cin>>flight;
    cout<<"输入您的姓名：";
    cin>>name;
    cout<<"输入您的id：";
	cin>>id; 
	cout<<"输入您所选择的舱位等级：";
    int found=0;
    for (int i=0;i<5;i++) {
        if (flightName[i]==flight&&remainTickets[i]>0) {
            found = 1;
            remainTickets[i]--;
            ofstream bookingFile("booking.txt", ios::app);
            if (bookingFile.is_open()){
                bookingFile<<id<<" "<<flight<<" "<<name<<" "<<l<<endl;
                bookingFile.close();
                cout<<"订票成功！"<<endl;
            } else {
                cout<<"无法打开订票文件"<<endl;
            }
            break;
        }
    }
    if(found==0||remainTickets[0]==0){
        cout<<"订票失败，没有该航班或票数不足。"<<endl;
        int choice;
        cout<<"如果要选择进行候补，请按 1："<<endl;
        cin>>choice;
        if(choice==1){
            cout<<"确认您所选择的候补航班是："<<flight<<endl;
            cout<<"确认您的姓名是："<<name<<endl;
            int num;
            cout<<"请输入您需要的候补车票数量："<<endl;
            cin>>num;
            ofstream waitingFile("waiting.txt",ios::app);
            if (waitingFile.is_open()){
                waitingFile<<flight<<" "<<name<<" "<<num<<endl;
                waitingFile.close();
                cout<< "候补成功！"<<endl;
            }
			else{
                cout<< "无法打开候补文件"<<endl;
            }
        }
    }
}//订票系统 

void Flight::refund(){
    string name;
    cout<<"输入您的姓名：";
    cin>>name;
    int found=0;
    // 打开 booking.txt 文件进行读取
    ifstream inFile("booking.txt");
    // 创建一个临时文件 temp.txt 用于写入未退票的乘客信息
    ofstream outFile("temp.txt");

    if(inFile.is_open()&&outFile.is_open()){ 
        string flight,passenger;
        while (inFile>>flight>>passenger){  // 逐行读取文件内容
            if(passenger!=name){  
                outFile<<flight<<" "<<passenger<<endl;  // 将信息写入临时文件
            }
			else{// 如果是要退票的乘客
                found = 1;  // 标记找到退票乘客
            }
        }
        inFile.close();
        outFile.close(); 
    }
	else{
        cout<<"无法打开文件" << endl;
        return; // 直接返回，结束函数
    }
    
    remove("booking.txt");//删除原 booking.txt 文件并且将临时文件重命名为 booking.txt
    rename("temp.txt", "booking.txt");
    if(found){//根据标记判断是否找到退票乘客
        cout<<"退票成功！"<<endl;
    }
	else {
        cout<<"未找到您的订票记录，退票失败。"<<endl;
    }
}


class Passenger{
	private:
		string passengerid[25];
		string flightname[25];
	    string passengername[25];//乘客姓名名单
	    string bookingtickets[25];//每位乘客的订票量
	    int level[25];//所选择的舱位等级
	public:
		Passenger() {}//无参构造函数 
	    Passenger(string pi[],string f[],string p[],string b[],int l[]){
		    for(int i=0;i<25;i++){
		    	passengerid[i]=pi[i];
		    	flightname[i]=f[i];
		    	passengername[i]=p[i];
		    	bookingtickets[i]=b[i];
		    	level[i]=l[i];
			}
		};
		void readPassenger();//录入乘客信息
		void showpassenger();//展示顾客信息 	
};//乘客类 

void Passenger::readPassenger() {
    ifstream infile("booking.txt");

    if (infile.is_open()){
        for (int i=0;i<25;++i) {
            infile>>passengerid[i]>>flightname[i]>>passengername[i]>>bookingtickets[i]>>level[i];
        }
        infile.close();
    }
	else {
        std::cout << "无法打开文件" << std::endl;
    }

}//录入乘客信息库

void Passenger::showpassenger(){
	string b;
	cin>>b;
	cout<<"输入顾客id:"<<b<<endl; 
	for(int j=0;j<10;j++){
		if(b==passengerid[j]){
			cout<<"乘客航班："<<flightname[j]<<endl;
			cout<<"乘客id:"<<passengerid[j]<<endl;
			cout<<"乘客姓名："<<passengername[j]<<endl;
			cout<<"乘客所需票量："<<bookingtickets[j]<<endl;
			cout<<"乘客所在舱位等级："<<level[j]<<endl; 
		}
		else{
			cout<<"该乘客未购票！"<<endl;
		}
	}	
}


class waitPassenger{
	private:
		string waitflight[10];//乘客候补航班
		string waitid[10];//候补乘客身份 
	    string waitname[10];//每一班候补乘客名字
	    string indeedtickets[10];//候补乘客所需票数量
	public:
		waitPassenger() {}//无参构造函数 
		waitPassenger(string fl[],string wi[],string w[],string id[]){
			for(int i=0;i<5;i++){
				waitflight[i]=fl[i];
				waitid[i]=wi[i];
				waitname[i]=w[i];
				indeedtickets[i]=id[i];
			}
	    };
	    void readwaitPassenger();//录入候补信息库
	    void showwait();//展示候补乘客信息 
};//候补类 

void waitPassenger::readwaitPassenger(){
    std::ifstream infile("waitting.txt");

    if (infile.is_open()){
        for (int i=0;i<10;++i) {
            infile>>waitflight[i]>>waitid[i]>>waitname[i]>>indeedtickets[i];
        }
        infile.close();
    }
	else {
        cout<<"无法打开文件"<<endl;
    }
}//录入候补信息库

void waitPassenger::showwait(){
	string b;
	cin>>b;
	cout<<"输入顾客id:"<<b<<endl; 
	for(int j=0;j<10;j++){
		if(b==waitid[j]){
			cout<<"乘客候补航班："<<waitflight[j]<<endl;
			cout<<"候补乘客id:"<<waitid[j]<<endl;
			cout<<"候补乘客姓名："<<waitname[j]<<endl;
			cout<<"候补乘客所需票量："<<indeedtickets[j]<<endl; 
		}
		else{
			cout<<"该乘客未候补！"<<endl;
		}
	}
}


class Manager:public Flight,public Passenger,public waitPassenger{
	private:
	    string managername[5]; // 管理者姓名数组
	    string privateid[5];   // 管理者私人ID数组
	public:
	    Manager() : Flight(), Passenger(), waitPassenger() {
	        // 这里可以进行其他初始化操作，如果没有需要，可以留空
	    }
	    Manager(string f[],string s[],string end[],string air[],string fd[],int r[],
		        string pi[],string fp[], string p[], string b[], int l[],
				string wt[],string wi[],string w[], string id[], 
	            string m[], string pr[])
	        :Flight(f,s,end,air,fd,r),Passenger(pi,fp,p,b,l),waitPassenger(wt,wi,w,id) {
	        for (int j=0;j<5;j++){
	            managername[j]=m[j];
	            privateid[j]=pr[j];
	        }
	    }
	    void readmanager();
	    void manager();
	    void welcome();
};

void Manager::readmanager(){
    ifstream infile("manager.txt");

    if(infile.is_open()){
        for (int i=0;i<5;++i) {
            infile>>managername[i]>>privateid[i];
        }
        infile.close();
    }
	else{
        cout<<"无法打开文件"<<endl;
    }

}//录入管理员信息库

void Manager::manager(){
	string m,n; 
	cout<<"输入你的管理者账号：";
	cin>>m; 
	cout<<"输入您的密码：";
	cin>>n;
	int found=0;
	for(int i=0;i<5;i++){
		if(m==managername[i]&&n==privateid[i]){
			cout<<"身份验证正确！"<<endl;
			int a;
			cout<<"选择您所需要的业务工作："<<endl;
			cout<<"1.查询航班信息；"<<endl;
			cout<<"2.查询顾客信息；"<<endl;
			cout<<"输入您的选择：";
			cin>>a;
			switch(a){
				case 1:
					find();
					break;
				case 2:
					showpassenger();
					showwait();
					break; 
			}
		}
		else{
			found++;
		}
	}
	if(found==5){
		cout<<"未查到您的身份信息！"<<endl;
	}
} 

void Manager::welcome(){
	cout<<"         ———————————     "<<endl; 
	cout<<"     |    欢迎来到航空订票系统   |     "<<endl; 
	cout<<"     |       请选择您的身份      |     "<<endl; 
	cout<<"     |        1.管理员           |     "<<endl; 
	cout<<"     |        2.顾客             |     "<<endl; 
	cout<<"         ———————————     "<<endl;
	cout<<"请输入您的身份选择：";
    int a;
    cin>>a;  
	int b;
	do{
		switch(a){
			case 1:
				manager();
				break;
			case 2:
				sign();
				break;
			default:
				break;
		}
		cout<<"你是否要继续进行服务？（1.是 2.否）：";
		cin>>b;
		cout<<"请再次输入您的身份选择：";
	    int c;
	    cin>>c;
	    if(c==1){
	    	manager();
		}
		else{
			sign();
		} 
	}while(b=1);
}

int main(){
    Manager a; 
    a.welcome();
	return 0; 
}

