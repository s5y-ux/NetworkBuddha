#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> Logo_reference;

ifstream Logo ("Logo.txt");
string test;

void Display_Logo(){
  system("clear");
  for(int i = 0; i< Logo_reference.size(); i++){
    cout<<Logo_reference.at(i);
  }
}

void Load_Logo() {
  string line;
  if(Logo.is_open()){
    while ( getline (Logo,line) )
    {
      Logo_reference.push_back(line+"\n");
    }
    Logo.close();
  }

  else cout << "Unable to open file";
}

class Menu_Object {
  private: bool Sub_Menu;
  string Class_Title;
  int Decor_Holder = 12 - Class_Title.size();

  public: void Spacer() {
    for (int i = 0; i < Decor_Holder; i++) {
      cout << " ";
    }
  }

  void Decor() {
    cout << "\n*";
    Spacer();
    cout <<"\033[1;37m"<< Class_Title<<"\033[0m";
    Spacer();
    cout << "*\n";
  }

  Menu_Object(string Title, bool Menu_Type) {
    Class_Title = Title;
    Sub_Menu = Menu_Type;
  }

  bool return_menu_condition(){
    return(Sub_Menu);
  }
};

void Ip_Scan(){
  string Ip_Address;
  cout<<"Ip Address: ";
  cin>>Ip_Address;
  string command = "nmap -sn "+Ip_Address+"/24";
  system(command.c_str());
}

void Nmap_Menu(Menu_Object Menu_Parameter){
  int answer;
  Display_Logo();
  Menu_Parameter.Decor();
  cout<<"\n[0: Ip Scanner, 1: Port Scanner, 2: Exit]\n";
  while(Menu_Parameter.return_menu_condition()){
    cout<<"Operation >: ";
    cin>>answer;
    switch(answer){
      case 0:
      Ip_Scan();
      break;
      case 1:
      break;
      case 2:
      exit(1);
      break;
      default:
      cout<<"Unknwon Command please refer to above options;\n";
      break;
    }
  }
}

void Main_Menu(Menu_Object Main_Menu, Menu_Object Nmap_Me){
  int answer;
  Display_Logo();
  Main_Menu.Decor();
  cout<<"\n[0: Help, 1: Nmap, 2: TCP Dump, 3: Net information, 4: Exit]\n";
  while(Main_Menu.return_menu_condition()){
    cout<<"Operation >: ";
    cin>>answer;
    switch(answer){
      case 0:
      cout<<"\n[0: Help, 1: Nmap, 2: TCP Dump, 3: Net information, 4: Exit]\n";
      break;
      case 1:
      Nmap_Menu(Nmap_Me);
      break;
      case 2:
      break;
      case 3:
      break;
      case 4:
      exit(1);
      default:
      cout<<"Unknwon Command, type 0 for list of commands\n";
      break;
    }
  }
}

int main() {
  Load_Logo();
  Menu_Object mainMen("Main Menu", true);
  Menu_Object nmap_Menu("Nmap", true);
  Main_Menu(mainMen, nmap_Menu);
  return (0);
}
