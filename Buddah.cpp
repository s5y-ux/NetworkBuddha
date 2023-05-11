#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector < string > Logo_reference;

ifstream Logo("Logo.txt");

void Display_Logo() {
  system("clear");
  for (int i = 0; i < Logo_reference.size(); i++) {
    cout << Logo_reference.at(i);
  }
}

void Load_Logo() {
  string line;
  if (Logo.is_open()) {
    while (getline(Logo, line)) {
      Logo_reference.push_back(line + "\n");
    }
    Logo.close();
  } else cout << "Unable to open file";
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
    cout << "\033[1;37m" << Class_Title << "\033[0m";
    Spacer();
    cout << "*\n";
  }

  Menu_Object(string Title, bool Menu_Type) {
    Class_Title = Title;
    Sub_Menu = Menu_Type;
  }

  bool return_menu_condition() {
    return (Sub_Menu);
  }

  void set_condition(bool new_value) {
    Sub_Menu = new_value;
  }
};

void Ip_Scan(string Scan_Type) {
  string Ip_Address;
  string command;
  cout << "Ip Address: ";
  cin >> Ip_Address;
  if (Scan_Type == "Local") {
    command = "nmap -sn " + Ip_Address + "/24";
  } else if (Scan_Type == "External") {
    command = "nmap -Pn " + Ip_Address;
  } else if (Scan_Type == "Port") {
    command = "nmap -V -A " + Ip_Address + " -Pn";
  }
  system(command.c_str());
}

void Basic_Net_Commands(string command_Input) {
  string command_referencer;
  string Ip_Address_for_Net;
  if (command_Input == "Ping") {
    cout << "IP Address >: ";
    cin >> Ip_Address_for_Net;
    command_referencer = "ping " + Ip_Address_for_Net;
    system(command_referencer.c_str());

  } else if (command_Input == "Config") {
    system("ifconfig");
  }
}

void Nmap_Menu(Menu_Object Menu_Parameter) {
  if (Menu_Parameter.return_menu_condition() == false) {
    Menu_Parameter.set_condition(true);
  }
  int answer;
  Display_Logo();
  Menu_Parameter.Decor();

  while (Menu_Parameter.return_menu_condition()) {
    cout << "\n[0: Ip Scanner, 1: Port Scanner, 2: Exit]\n";
    cout << "Operation >: ";
    cin >> answer;
    switch (answer) {
    case 0:
      int Option;
      cout << "[0: Local, 1: External]\n";
      cout << "Operation >: ";
      cin >> Option;
      if (Option == 0) {
        Ip_Scan("Local");
      } else {
        Ip_Scan("External");
      }
      break;
    case 1:
      Ip_Scan("Port");
      break;
    case 2:
      Menu_Parameter.set_condition(false);
      break;
    default:
      cout << "Unknwon Command please refer to above options\n";
      break;
    }
  }
}

void Net_Info_Menu(Menu_Object Net_Parameter) {
  if (Net_Parameter.return_menu_condition() == false) {
    Net_Parameter.set_condition(true);
  }
  int answer;
  Display_Logo();
  Net_Parameter.Decor();

  while (Net_Parameter.return_menu_condition()) {
    cout << "\n[0: Info, 1: Ping, 2: Exit]\n";
    cout << "Operation >: ";
    cin >> answer;
    switch (answer) {
    case 0:
      Basic_Net_Commands("Config");
      break;
    case 1:
      Basic_Net_Commands("Ping");
      break;
    case 2:
      Net_Parameter.set_condition(false);
      break;
    default:
      cout << "Unknwon Command please refer to above options\n";
      break;
    }
  }
}

void Main_Menu(Menu_Object Main_Menu, Menu_Object Nmap_Me, Menu_Object Net_Me) {
  int answer;
  Display_Logo();
  Main_Menu.Decor();
  while (Main_Menu.return_menu_condition()) {
    cout << "\n[0: Help, 1: Nmap, 2: TCP Dump, 3: Net information, 4: Exit]\n";
    cout << "Operation >: ";
    cin >> answer;
    switch (answer) {
    case 0:
      cout << "\n[0: Help, 1: Nmap, 2: TCP Dump, 3: Net information, 4: Exit]\n";
      break;
    case 1:
      Nmap_Menu(Nmap_Me);
      Display_Logo();
      Main_Menu.Decor();
      break;
    case 2:
      system("sudo tcpdump -v");
      break;
    case 3:
      Net_Info_Menu(Net_Me);
      Display_Logo();
      Main_Menu.Decor();
      break;
    case 4:
      exit(1);
    default:
      cout << "Unknwon Command, type 0 for list of commands\n";
      break;
    }
  }
}

int main() {
  Load_Logo();
  Menu_Object mainMen("Main Menu", true);
  Menu_Object nmap_Menu("Nmap", true);
  Menu_Object net_Menu("Basic Interface", true);
  Main_Menu(mainMen, nmap_Menu, net_Menu);
  return (0);
}
