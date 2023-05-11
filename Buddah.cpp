/*******************************************************************************
*                                                                              *
* Project Start Date: 5/9/2023                                                 *
* Project End Date: 5/11/2023                                                  *
*                                                                              *
* License: https://opensource.org/license/mit/                                 *
*                                                                              *
* Programmed By: Joseph R. Shumaker                                            *
*                                                                              *
* Purpose: This project was made to appeal to a possible internship            *
* at JPL, This project is a demonstration of my current abillities in C++      *
* reguarding functions, i/o, and memory allocation. This project was made      *
* purely in C++ and features the system function to execute linux commands     *
* that are used on a regular basis for networking operations.                  *
*                                                                              *
* All code seen below is my original work and all information regarding the    *
* use of library-specific methods and attributes were learned directly from    *
* the libraries' documentation.                                                *
*                                                                              *
* If you have any questions or would like to get in contact with me, my email  *
* and phone number is listed below...                                          *
*                                                                              *
* Phone: (805) 701 - 3171                                                      *
*                                                                              *
* Email: josephshumaker11@gmail.com                                            *
*                                                                              *
*******************************************************************************/

//Standard Librarys for C++
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//Using the standard namespace (No need for resolution scope operator)
using namespace std;

//Vector used as dynamic array to store our logo
vector < string > Logo_reference;

//String for IP address input (referenced through pointers)
string Ip_Address;

//Integer used for our answer to the prompt (referenced through pointers)
int Prompt_Answer;

//String for IP address input (referenced through pointers)
string command;

//File used to denote the ASCII logo of the program (Can be changed)
ifstream Logo("Logo.txt");


//Function used to display the logo
void Display_Logo() {

  //System command used to clear the CLI
  system("clear");

  //Iterates through the dynamic array and outputs the corresponding lines.
  for (int i = 0; i < Logo_reference.size(); i++) {
    cout << Logo_reference.at(i);
  }
}

//Function for loading the logo into the dynamic array
void Load_Logo() {

  //Used to store the lines as string
  string line;

  //Logic check to see if our file was found
  if (Logo.is_open()) {

    //Appends line to dynamic array
    while (getline(Logo, line)) {
      Logo_reference.push_back(line + "\n");
    }

    Logo.close();

    //If the logic check fails, display unable.
  } else cout << "Unable to open file";
}

//Custom object for our menu
class Menu_Object {

  //Used as a switch for determining which menu we are in
  //(Acts as a 2 layer binary tree)
  private: bool Sub_Menu;

  //Used to store the menu name
  string Class_Title;

  //Used for our pretty output '*' + ("")*12-size + title + ("")*12-size + '*'
  int Decor_Holder = 12 - Class_Title.size();

  //Used as the space between the stars and the menu name
  public: void Spacer() {
    for (int i = 0; i < Decor_Holder; i++) {
      cout << " ";
    }
  }

  //Used to display the Menu name with the stars
  void Decor() {
    cout << "\n*";
    Spacer();

    //\033 (Escape Character) [1;37m (text type; color + m) then Escape and reset
    //Basically just colors the text
    cout << "\033[1;37m" << Class_Title << "\033[0m";
    Spacer();
    cout << "*\n";
  }

  //Initalization method for private variables
  Menu_Object(string Title, bool Menu_Type) {
    Class_Title = Title;
    Sub_Menu = Menu_Type;
  }

  //returns the menu condition for the selection loop
  bool return_menu_condition() {
    return (Sub_Menu);
  }

  //sets the condition of the loop (i.e false -> exit)
  void set_condition(bool new_value) {
    Sub_Menu = new_value;
  }
};

//Function used for IP Scanning through N-Map
void Ip_Scan(string Scan_Type) {

  //Pointers to reference IP address and command c string.
  string * IP_Assign, * command_p;

  //Points to the address of the respective variables
  IP_Assign = & Ip_Address;
  command_p = & command;

  //Asks the user for input
  cout << "Ip Address: ";
  cin >> * IP_Assign;

  //Why diden't I use a switch statement? Ease of reading the parameter.
  if (Scan_Type == "Local") {

    //Scans through all posible connected clients (N-Map)
    * command_p = "nmap -sn " + Ip_Address + "/24";
  } else if (Scan_Type == "External") {

    //Scans with probe blocking argument (N-Map)
    * command_p = "nmap -Pn " + Ip_Address;
  } else if (Scan_Type == "Port") {

    //Runs a scan to see TCP Ports
    * command_p = "nmap -V -A " + Ip_Address + " -Pn";
  }

  //Converts command to c_str() as needed for the system parameter
  system(command.c_str());
}

//Function for all of our OS networking info
void Basic_Net_Commands(string command_Input) {

  //Again, allocating pointers
  string * IP_Assign, * command_p;

  //Setting pointers to respective variable address
  IP_Assign = & Ip_Address;
  command_p = & command;

  //Why diden't I use a switch statement? Ease of reading the parameter.
  if (command_Input == "Ping") {

    //Input and output for setting IP address.
    cout << "IP Address >: ";
    cin >> Ip_Address;

    //Asigns c string to pointer which points to address &command
    * command_p = "ping " + Ip_Address;

    //Executes command as c string.
    system(command.c_str());

  } else if (command_Input == "Config") {
    system("ifconfig");
  }
}

//Function to act as our Nmap menu
void Nmap_Menu(Menu_Object Menu_Parameter) {

  //Checks to see if our Nmap menu object is activated
  if (Menu_Parameter.return_menu_condition() == false) {
    Menu_Parameter.set_condition(true);
  }

  //Allocates pointer to point to prompt answer
  int * answer;
  answer = & Prompt_Answer;

  //Used in combination to print the logo and menu name
  Display_Logo();
  Menu_Parameter.Decor();

  //Loop for menu
  while (Menu_Parameter.return_menu_condition()) {

    //Outputs the different options that exist for Nmap
    cout << "\n[0: Ip Scanner, 1: Port Scanner, 2: Exit]\n";

    //Takes user input and stores it in the pointer value that points to Prompt_Answer
    cout << "Operation >: ";
    cin >> * answer;

    //Looks at the value stored in the variable
    switch (Prompt_Answer) {
    case 0:

      //Lists Options
      cout << "[0: Local, 1: External]\n";

      //Takes user input and assigns anser to value stored at &Prompt_Answer
      cout << "Operation >: ";
      cin >> * answer;

      //Runs an IP scan with the respective option
      if (Prompt_Answer == 0) {

        //Pretty good reason to have a string as the parameter ;)
        Ip_Scan("Local");
      } else {
        Ip_Scan("External");
      }
      break;
    case 1:
      Ip_Scan("Port");
      break;
    case 2:

      //Sets the sub menu condition to false thus exiting the loop and returning
      //to the root node
      Menu_Parameter.set_condition(false);
      break;
    default:
      cout << "Unknwon Command please refer to above options\n";
      break;
    }
  }
}

//Used as the menu for basic network commands
void Net_Info_Menu(Menu_Object Net_Parameter) {

  //Checks to see if our menu object is activated
  if (Net_Parameter.return_menu_condition() == false) {
    Net_Parameter.set_condition(true);
  }

  //Assigns pointer to the Prompt_Answer
  int * answer;
  answer = & Prompt_Answer;

  //Displays Logo + Menu title
  Display_Logo();
  Net_Parameter.Decor();

  //Loop used for menu selection
  while (Net_Parameter.return_menu_condition()) {

    //Displays options and io for value at &Prompt_Answer
    cout << "\n[0: Info, 1: Ping, 2: Exit]\n";
    cout << "Operation >: ";
    cin >> * answer;

    //Checks the value of *answer (answer = &Prompt_Answer)
    switch ( Prompt_Answer ) {
    case 0:

      //Pretty good reason to have a string as the parameter ;)
      Basic_Net_Commands("Config");
      break;
    case 1:
      Basic_Net_Commands("Ping");
      break;
    case 2:

      //Exits out of the loop
      Net_Parameter.set_condition(false);
      break;
    default:
      cout << "Unknwon Command please refer to above options\n";
      break;
    }
  }
}

//Function used for holding the nodes and running the root node as main menu
void Main_Menu(Menu_Object Main_Menu, Menu_Object Nmap_Me, Menu_Object Net_Me) {

  //Same setup for obtaining user input
  int * answer;
  answer = & Prompt_Answer;

  //Procedure for displaying logo and menu title
  Display_Logo();
  Main_Menu.Decor();

  //Loop for simulating main menu
  while (Main_Menu.return_menu_condition()) {
    cout << "\n[0: Version, 1: Nmap, 2: TCP Dump, 3: Net information, 4: Exit]\n";
    cout << "Operation >: ";

    //Stores input as reference to value stored at address &Prompt_Answer
    cin >> * answer;
    switch ( Prompt_Answer ) {
    case 0:

      //Case for Nmap version
      system("nmap -V");
      break;
    case 1:

      //Case for Nmap menu
      Nmap_Menu(Nmap_Me);

      //Procedure for displaying logo and menu title after stopping loop
      Display_Logo();
      Main_Menu.Decor();
      break;
    case 2:

      //Command fot starting TCP dump
      system("sudo tcpdump -v");
      break;
    case 3:

      //Case for basic network operations
      Net_Info_Menu(Net_Me);

      //Procedure for displaying logo and menu title after stopping loop
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

  //Initalizes our menu object
  Menu_Object mainMen("Main Menu", true);
  Menu_Object nmap_Menu("Nmap", true);
  Menu_Object net_Menu("Basic Interface", true);

  //Starts our main menu with respective menu nodes
  Main_Menu(mainMen, nmap_Menu, net_Menu);
  return (0);
}
