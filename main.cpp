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
* at JPL, This project is a demonstration of my current abilities in C++       *
* regarding functions, i/o, and memory allocation. This project was made      *
* purely in C++ and features the system function to execute Linux commands     *
* that are used regularly for networking operations.                           *
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

//Using the standard name-space (No need for resolution scope operator)
using namespace std;

//Vector used as dynamic array to store our logo
vector < string > Logo_Variable;

//String for IP address input (referenced through pointers)
string GLOBAL_IP_Reference;

//Integer used for our answer to the prompt (referenced through pointers)
int GLOBAL_Prompt_Response;

//String for IP address input (referenced through pointers)
string GLOBAL_System_Command;

//File used to denote the ASCII logo of the program (Can be changed)
ifstream Logo("Logo.txt");

//Custom object for our menu
class Menu_Object {

  //Used as a switch for determining which menu we are in
  //(Acts as a 2 layer binary tree)
  private: bool In_Selection;

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

  //Initialization method for private variables
  Menu_Object(string Title, bool Menu_Type) {
    Class_Title = Title;
    In_Selection = Menu_Type;
  }

  //returns the menu condition for the selection loop
  bool return_menu_condition() {
    return (In_Selection);
  }

  //sets the condition of the loop (i.e false -> exit)
  void set_condition(bool new_value) {
    In_Selection = new_value;
  }
};

//Function used to display the logo
void Display_Logo() {

  //System GLOBAL_System_Command used to clear the CLI
  system("clear");

  //Iterates through the dynamic array and outputs the corresponding lines.
  for (int i = 0; i < Logo_Variable.size(); i++) {
    cout << Logo_Variable.at(i);
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
      Logo_Variable.push_back(line + "\n");
    }

    Logo.close();

    //If the logic check fails, display unable.
  } else cout << "Unable to open file";
}

void Title_Procedure(Menu_Object Menu_Parameter){
  Display_Logo();
  Menu_Parameter.Decor();
}

//Function used for IP Scanning through N-Map
void Ip_Scan(string Scan_Type) {

  //Pointers to reference IP address and GLOBAL_System_Command c string.
  string * IP_Assign, * System_Pointer;

  //Points to the address of the respective variables
  IP_Assign = & GLOBAL_IP_Reference;
  System_Pointer = & GLOBAL_System_Command;

  //Asks the user for input
  cout << "Ip Address: ";
  cin >> * IP_Assign;

  //Why didn't I use a switch statement? Ease of reading the parameter.
  if (Scan_Type == "Local") {

    //Scans through all possible connected clients (N-Map)
    * System_Pointer = "nmap -sn " + GLOBAL_IP_Reference + "/24";
  } else if (Scan_Type == "External") {

    //Scans with probe blocking argument (N-Map)
    * System_Pointer = "nmap -Pn " + GLOBAL_IP_Reference;
  } else if (Scan_Type == "Port") {

    //Runs a scan to see TCP Ports
    * System_Pointer = "nmap -v -Pn " + GLOBAL_IP_Reference;
  }

  //Converts GLOBAL_System_Command to c_str() as needed for the system parameter
  system(GLOBAL_System_Command.c_str());
}

//Function for all of our OS networking info
void Basic_Net_Commands(string GLOBAL_System_Command_Input) {

  //Again, allocating pointers
  string * IP_Assign, * System_Pointer;

  //Setting pointers to respective variable address
  IP_Assign = & GLOBAL_IP_Reference;
  System_Pointer = & GLOBAL_System_Command;

  //Why didn't I use a switch statement? Ease of reading the parameter.
  if (GLOBAL_System_Command_Input == "Ping") {

    //Input and output for setting IP address.
    cout << "IP Address >: ";
    cin >> GLOBAL_IP_Reference;

    //Assigns c string to pointer which points to address &GLOBAL_System_Command
    * System_Pointer = "ping " + GLOBAL_IP_Reference;

    //Executes GLOBAL_System_Command as c string.
    system(GLOBAL_System_Command.c_str());

  } else if (GLOBAL_System_Command_Input == "Config") {
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
  answer = & GLOBAL_Prompt_Response;

  //Used in combination to print the logo and menu name
  Title_Procedure(Menu_Parameter);

  //Loop for menu
  while (Menu_Parameter.return_menu_condition()) {

    //Outputs the different options that exist for Nmap
    cout << "\n[0: Ip Scanner, 1: Port Scanner, 2: Exit]\n";

    //Takes user input and stores it in the pointer value that points to GLOBAL_Prompt_Response
    cout << "Operation >: ";
    cin >> * answer;

    //Looks at the value stored in the variable
    switch (GLOBAL_Prompt_Response) {
    case 0:

      //Lists Options
      cout << "[0: Local, 1: External]\n";

      //Takes user input and assigns answer to value stored at &GLOBAL_Prompt_Response
      cout << "Operation >: ";
      cin >> * answer;

      //Runs an IP scan with the respective option
      if (GLOBAL_Prompt_Response == 0) {

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

//Used as the menu for basic network GLOBAL_System_Commands
void Net_Info_Menu(Menu_Object Menu_Parameter) {

  //Checks to see if our menu object is activated
  if (Menu_Parameter.return_menu_condition() == false) {
    Menu_Parameter.set_condition(true);
  }

  //Assigns pointer to the GLOBAL_Prompt_Response
  int * answer;
  answer = & GLOBAL_Prompt_Response;

  //Displays Logo + Menu title
  Title_Procedure(Menu_Parameter);

  //Loop used for menu selection
  while (Menu_Parameter.return_menu_condition()) {

    //Displays options and I/O for value at &GLOBAL_Prompt_Response
    cout << "\n[0: Info, 1: Ping, 2: Exit]\n";
    cout << "Operation >: ";
    cin >> * answer;

    //Checks the value of *answer (answer = &GLOBAL_Prompt_Response)
    switch ( GLOBAL_Prompt_Response ) {
    case 0:

      //Pretty good reason to have a string as the parameter ;)
      Basic_Net_Commands("Config");
      break;
    case 1:
      Basic_Net_Commands("Ping");
      break;
    case 2:

      //Exits out of the loop
      Menu_Parameter.set_condition(false);
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
  answer = & GLOBAL_Prompt_Response;

  //Procedure for displaying logo and menu title
  Title_Procedure(Main_Menu);

  //Loop for simulating main menu
  while (Main_Menu.return_menu_condition()) {
    cout << "\n[0: Version, 1: Nmap, 2: TCP Dump, 3: Net information, 4: Exit]\n";
    cout << "Operation >: ";

    //Stores input as reference to value stored at address &GLOBAL_Prompt_Response
    cin >> * answer;
    switch ( GLOBAL_Prompt_Response ) {
    case 0:

      //Case for Nmap version
      system("nmap -V");
      break;
    case 1:

      //Case for Nmap menu
      Nmap_Menu(Nmap_Me);

      //Procedure for displaying logo and menu title after stopping loop
      Title_Procedure(Main_Menu);
      break;
    case 2:

      //Command fot starting TCP dump
      system("sudo tcpdump -v");
      break;
    case 3:

      //Case for basic network operations
      Net_Info_Menu(Net_Me);

      //Procedure for displaying logo and menu title after stopping loop
      Title_Procedure(Main_Menu);
      break;
    case 4:
      exit(1);
    default:
      cout << "Unknown Command, type 0 for list of GLOBAL_System_Commands\n";
      break;
    }
  }
}

int main() {
  Load_Logo();

  //Initializes our menu object
  Menu_Object mainMen("Main Menu", true);
  Menu_Object nmap_Menu("Nmap", true);
  Menu_Object net_Menu("Basic Interface", true);

  //Starts our main menu with respective menu nodes
  Main_Menu(mainMen, nmap_Menu, net_Menu);
  return (0);
}
