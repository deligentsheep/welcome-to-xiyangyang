#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Flight {
	private: 
	    string flightName[5];//����� 
	    string startStation[5];//��� 
	    string endStation[5];//�յ� 
	    string airName[5];//�ɻ��ͺ� 
	    string flightDate[5];//��������
	    int remainTickets[5]; //��Ʊ��
	public:
		Flight() {} //�޲ι��캯�� 
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
};//������

void Flight::readFlight() {
    ifstream infile("flight.txt");

    if (infile.is_open()){
        for (int i=0;i<5;++i) {
            infile>>flightName[i]>>startStation[i]>>endStation[i]>>airName[i]>>flightDate[i]>>remainTickets[i];
        }
        infile.close();
    }
	else {
        std::cout << "�޷����ļ�" << std::endl;
    }

}//¼�뺽����Ϣ�� 

void Flight::sign(){
	int a;
	cout<<"ѡ��������Ҫ�ķ���"<<endl;
	cout<<"1.��ѯ���ࣻ"<<endl;
	cout<<"2.��Ʊ��"<<endl;
	cout<<"3.��Ʊ��"<<endl;
	cout<<"��������ѡ��";
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
    cout<<"��������ʼ��վ��"<<endl;
    cin>>start;
    cout<<"���������յ�վ��"<<endl;
    cin>>end;
    int found=0;
    for(int i=0; i<5;++i) {
        if (startStation[i] == start && endStation[i] == end) {
            found=1;
            cout<<"�����:"<<flightName[i]<< endl;
            cout<<"���վ:"<<startStation[i]<< endl;
            cout<<"�յ�վ:"<<endStation[i]<< endl;
            cout<<"�ɻ���:"<<airName[i]<<endl;
            cout<<"��������:"<<flightDate[i]<<endl;
            cout<<"ʣ��Ʊ��:"<<remainTickets[i]<<endl;
            cout<<"--------------------------"<<endl;
            break;
        }
    }
    if(found==0){
        cout<<"û����Ӧ����"<<endl;
    }
}//��ѯ����

void Flight::book(){
    string name,flight,id;
    int l;
    cout<<endl<<"����������Ҫ�����ĺ��ࣺ";
    cin>>flight;
    cout<<"��������������";
    cin>>name;
    cout<<"��������id��";
	cin>>id; 
	cout<<"��������ѡ��Ĳ�λ�ȼ���";
    int found=0;
    for (int i=0;i<5;i++) {
        if (flightName[i]==flight&&remainTickets[i]>0) {
            found = 1;
            remainTickets[i]--;
            ofstream bookingFile("booking.txt", ios::app);
            if (bookingFile.is_open()){
                bookingFile<<id<<" "<<flight<<" "<<name<<" "<<l<<endl;
                bookingFile.close();
                cout<<"��Ʊ�ɹ���"<<endl;
            } else {
                cout<<"�޷��򿪶�Ʊ�ļ�"<<endl;
            }
            break;
        }
    }
    if(found==0||remainTickets[0]==0){
        cout<<"��Ʊʧ�ܣ�û�иú����Ʊ�����㡣"<<endl;
        int choice;
        cout<<"���Ҫѡ����к򲹣��밴 1��"<<endl;
        cin>>choice;
        if(choice==1){
            cout<<"ȷ������ѡ��ĺ򲹺����ǣ�"<<flight<<endl;
            cout<<"ȷ�����������ǣ�"<<name<<endl;
            int num;
            cout<<"����������Ҫ�ĺ򲹳�Ʊ������"<<endl;
            cin>>num;
            ofstream waitingFile("waiting.txt",ios::app);
            if (waitingFile.is_open()){
                waitingFile<<flight<<" "<<name<<" "<<num<<endl;
                waitingFile.close();
                cout<< "�򲹳ɹ���"<<endl;
            }
			else{
                cout<< "�޷��򿪺��ļ�"<<endl;
            }
        }
    }
}//��Ʊϵͳ 

void Flight::refund(){
    string name;
    cout<<"��������������";
    cin>>name;
    int found=0;
    // �� booking.txt �ļ����ж�ȡ
    ifstream inFile("booking.txt");
    // ����һ����ʱ�ļ� temp.txt ����д��δ��Ʊ�ĳ˿���Ϣ
    ofstream outFile("temp.txt");

    if(inFile.is_open()&&outFile.is_open()){ 
        string flight,passenger;
        while (inFile>>flight>>passenger){  // ���ж�ȡ�ļ�����
            if(passenger!=name){  
                outFile<<flight<<" "<<passenger<<endl;  // ����Ϣд����ʱ�ļ�
            }
			else{// �����Ҫ��Ʊ�ĳ˿�
                found = 1;  // ����ҵ���Ʊ�˿�
            }
        }
        inFile.close();
        outFile.close(); 
    }
	else{
        cout<<"�޷����ļ�" << endl;
        return; // ֱ�ӷ��أ���������
    }
    
    remove("booking.txt");//ɾ��ԭ booking.txt �ļ����ҽ���ʱ�ļ�������Ϊ booking.txt
    rename("temp.txt", "booking.txt");
    if(found){//���ݱ���ж��Ƿ��ҵ���Ʊ�˿�
        cout<<"��Ʊ�ɹ���"<<endl;
    }
	else {
        cout<<"δ�ҵ����Ķ�Ʊ��¼����Ʊʧ�ܡ�"<<endl;
    }
}


class Passenger{
	private:
		string passengerid[25];
		string flightname[25];
	    string passengername[25];//�˿���������
	    string bookingtickets[25];//ÿλ�˿͵Ķ�Ʊ��
	    int level[25];//��ѡ��Ĳ�λ�ȼ�
	public:
		Passenger() {}//�޲ι��캯�� 
	    Passenger(string pi[],string f[],string p[],string b[],int l[]){
		    for(int i=0;i<25;i++){
		    	passengerid[i]=pi[i];
		    	flightname[i]=f[i];
		    	passengername[i]=p[i];
		    	bookingtickets[i]=b[i];
		    	level[i]=l[i];
			}
		};
		void readPassenger();//¼��˿���Ϣ
		void showpassenger();//չʾ�˿���Ϣ 	
};//�˿��� 

void Passenger::readPassenger() {
    ifstream infile("booking.txt");

    if (infile.is_open()){
        for (int i=0;i<25;++i) {
            infile>>passengerid[i]>>flightname[i]>>passengername[i]>>bookingtickets[i]>>level[i];
        }
        infile.close();
    }
	else {
        std::cout << "�޷����ļ�" << std::endl;
    }

}//¼��˿���Ϣ��

void Passenger::showpassenger(){
	string b;
	cin>>b;
	cout<<"����˿�id:"<<b<<endl; 
	for(int j=0;j<10;j++){
		if(b==passengerid[j]){
			cout<<"�˿ͺ��ࣺ"<<flightname[j]<<endl;
			cout<<"�˿�id:"<<passengerid[j]<<endl;
			cout<<"�˿�������"<<passengername[j]<<endl;
			cout<<"�˿�����Ʊ����"<<bookingtickets[j]<<endl;
			cout<<"�˿����ڲ�λ�ȼ���"<<level[j]<<endl; 
		}
		else{
			cout<<"�ó˿�δ��Ʊ��"<<endl;
		}
	}	
}


class waitPassenger{
	private:
		string waitflight[10];//�˿ͺ򲹺���
		string waitid[10];//�򲹳˿���� 
	    string waitname[10];//ÿһ��򲹳˿�����
	    string indeedtickets[10];//�򲹳˿�����Ʊ����
	public:
		waitPassenger() {}//�޲ι��캯�� 
		waitPassenger(string fl[],string wi[],string w[],string id[]){
			for(int i=0;i<5;i++){
				waitflight[i]=fl[i];
				waitid[i]=wi[i];
				waitname[i]=w[i];
				indeedtickets[i]=id[i];
			}
	    };
	    void readwaitPassenger();//¼�����Ϣ��
	    void showwait();//չʾ�򲹳˿���Ϣ 
};//���� 

void waitPassenger::readwaitPassenger(){
    std::ifstream infile("waitting.txt");

    if (infile.is_open()){
        for (int i=0;i<10;++i) {
            infile>>waitflight[i]>>waitid[i]>>waitname[i]>>indeedtickets[i];
        }
        infile.close();
    }
	else {
        cout<<"�޷����ļ�"<<endl;
    }
}//¼�����Ϣ��

void waitPassenger::showwait(){
	string b;
	cin>>b;
	cout<<"����˿�id:"<<b<<endl; 
	for(int j=0;j<10;j++){
		if(b==waitid[j]){
			cout<<"�˿ͺ򲹺��ࣺ"<<waitflight[j]<<endl;
			cout<<"�򲹳˿�id:"<<waitid[j]<<endl;
			cout<<"�򲹳˿�������"<<waitname[j]<<endl;
			cout<<"�򲹳˿�����Ʊ����"<<indeedtickets[j]<<endl; 
		}
		else{
			cout<<"�ó˿�δ�򲹣�"<<endl;
		}
	}
}


class Manager:public Flight,public Passenger,public waitPassenger{
	private:
	    string managername[5]; // ��������������
	    string privateid[5];   // ������˽��ID����
	public:
	    Manager() : Flight(), Passenger(), waitPassenger() {
	        // ������Խ���������ʼ�����������û����Ҫ����������
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
        cout<<"�޷����ļ�"<<endl;
    }

}//¼�����Ա��Ϣ��

void Manager::manager(){
	string m,n; 
	cout<<"������Ĺ������˺ţ�";
	cin>>m; 
	cout<<"�����������룺";
	cin>>n;
	int found=0;
	for(int i=0;i<5;i++){
		if(m==managername[i]&&n==privateid[i]){
			cout<<"�����֤��ȷ��"<<endl;
			int a;
			cout<<"ѡ��������Ҫ��ҵ������"<<endl;
			cout<<"1.��ѯ������Ϣ��"<<endl;
			cout<<"2.��ѯ�˿���Ϣ��"<<endl;
			cout<<"��������ѡ��";
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
		cout<<"δ�鵽���������Ϣ��"<<endl;
	}
} 

void Manager::welcome(){
	cout<<"         ����������������������     "<<endl; 
	cout<<"     |    ��ӭ�������ն�Ʊϵͳ   |     "<<endl; 
	cout<<"     |       ��ѡ���������      |     "<<endl; 
	cout<<"     |        1.����Ա           |     "<<endl; 
	cout<<"     |        2.�˿�             |     "<<endl; 
	cout<<"         ����������������������     "<<endl;
	cout<<"�������������ѡ��";
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
		cout<<"���Ƿ�Ҫ�������з��񣿣�1.�� 2.�񣩣�";
		cin>>b;
		cout<<"���ٴ������������ѡ��";
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

