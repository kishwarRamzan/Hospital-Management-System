 #include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// Prototypes
void display();
string mainMenue();

// Admin
bool adminLogin();
string adminMenu();
string addDoctor();
string addReceptionist();
string viewAllAppointments();
string deleteDoctor();
string deleteReceptionist();

// Doctor
string doctorLogin();
string viewAppointments(const string &doctorName);

// Receptionist
string receptionistLogin();
string receptionistMenu();
string addAppointment();
string receptionistViewAllAppointments();

// Patient
string patientEntry();
string patientSignup();
string patientSignin();
string patientPanel(const string &patientName);
string addMedicalHistory(const string &patientName);
string viewMedicalHistory(const string &patientName);

// validation helpers (added)
bool validName(string);
bool validPassword(string);
bool hasSpecial(string);

int main() {
    string choice;

    while (true) {
        system("cls");
        display();
        choice = mainMenue();

        if (choice == "1") {
            if (!adminLogin()) {
                cout << "\t\tInvalid admin credentials\n";
                system("pause");
                continue;
            }

            string state = "MENU";
            while (state != "LOGOUT") {
                if (state == "MENU")
                    state = adminMenu();
                else if (state == "ADD_DOCTOR") {
                    cout << addDoctor();
                    system("pause");
                    state = "MENU";
                }
                else if (state == "ADD_RECEPTIONIST") {
                    cout << addReceptionist();
                    system("pause");
                    state = "MENU";
                }
                else if (state == "VIEW_APPOINTMENTS") {
                    cout << viewAllAppointments();
                    system("pause");
                    state = "MENU";
                }
                else if (state == "DELETE_DOCTOR") {
                    cout << deleteDoctor();
                    system("pause");
                    state = "MENU";
                }
                else if (state == "DELETE_RECEPTIONIST") {
                    cout << deleteReceptionist();
                    system("pause");
                    state = "MENU";
                }
                else state = "LOGOUT";
            }
        }
        else if (choice == "2") {
            cout << doctorLogin();
            system("pause");
        }
        else if (choice == "3") {
            cout << receptionistLogin();
            system("pause");
        }
        else if (choice == "4") {
            cout << patientEntry();
            system("pause");
        }
        else if (choice == "5") return 0;
        else {
            cout << "\t\tInvalid choice\n";
            system("pause");
        }
    }
}

void display() {
    cout << "\n\n\t\t###############################################\n";
    cout << "\t\t#       HOSPITAL MANAGEMENT SYSTEM             #\n";
    cout << "\t\t###############################################\n";
}

string mainMenue() {
    string choice;
    cout << "\n\t\t1. Admin Login\n";
    cout << "\t\t2. Doctor Login\n";
    cout << "\t\t3. Receptionist Login\n";
    cout << "\t\t4. Patient\n";
    cout << "\t\t5. Exit\n";
    cout << "\t\tEnter choice: ";
    cin >> setw(10) >> choice;
    return choice;
}

//validation
bool validName(string name) {
    for (int i = 0; i < name.length(); i++)
        if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z')))
            return false;
    return true;
}

bool hasSpecial(string password) {
    for (int i = 0; i < password.length(); i++)
        if (!((password[i] >= 'A' && password[i] <= 'Z') || (password[i] >= 'a' && password[i] <= 'z') || (password[i] >= '0' && password[i] <= '9')))
            return true;
    return false;
}

bool validPassword(string password) {
    return hasSpecial(password);
}

//admin
bool adminLogin() {
    system("cls");
    display();
    string user_name, Password;

    do {
        cout << "\t\tUsername: ";
        cin >> setw(20) >> user_name;
    } while (!validName(user_name));

    do {
        cout << "\t\tPassword: ";
        cin >> setw(20) >> Password;
    } while (!validPassword(Password));

    return (user_name == "admin" && Password == "admin@123");
}

string adminMenu() {
    system("cls");
    display();
    int choice;
    cout << "\n\t\tAdmin Panel\n";
    cout << "\t\t1. Add Doctor\n";
    cout << "\t\t2. Add Receptionist\n";
    cout << "\t\t3. View All Appointments\n";
    cout << "\t\t4. Delete Doctor\n";
    cout << "\t\t5. Delete Receptionist\n";
    cout << "\t\t6. Logout\n";
    cout << "\t\tChoice: ";
    cin >> choice;

    if (choice == 1) return "ADD_DOCTOR";
    if (choice == 2) return "ADD_RECEPTIONIST";
    if (choice == 3) return "VIEW_APPOINTMENTS";
    if (choice == 4) return "DELETE_DOCTOR";
    if (choice == 5) return "DELETE_RECEPTIONIST";
    return "LOGOUT";
}

//doctor
string addDoctor() {
    system("cls");
    display();
    string doctor_name, doctor_password;

    do {
        cout << "\t\tDoctor Name: ";
        cin >> setw(20) >> doctor_name;
        
        if (!validName(doctor_name)) {
        cout << "\t\tInvalid input! Name should not contain anyspecial character.\n";
    }
    } while (!validName(doctor_name));

    do {
    cout << "\t\tPassword: ";
    cin >> setw(20) >> doctor_password;

    if (!validPassword(doctor_password)) {
        cout << "\t\tInvalid input! Password must contain at least one special character.\n";
    }

    } while (!validPassword(doctor_password));

    ofstream doctor_file((doctor_name + ".txt").c_str());
    doctor_file << doctor_password;
    doctor_file.close();

    //create a file that can store all available doctord so that will be shoen to receptionist while booking appointment
    ofstream list("doctors_list.txt", ios::app);
    list << doctor_name << endl;
    list.close();

    return "\t\tDoctor added successfully\n";
}

//receptionist
string addReceptionist() {
    system("cls");
    display();
    string receptionist_name, receptionist_passsword;

    do {
        cout << "\t\tReceptionist Name: ";
        cin >> setw(20) >> receptionist_name;
        
        if (!validName(receptionist_name)) {
        cout << "\t\tInvalid input! Name should not contain any special character.\n";
    }
    } while (!validName(receptionist_name));

    do {
        cout << "\t\tPassword: ";
        cin >> setw(20) >> receptionist_passsword;
        
        if (!validPassword(receptionist_passsword)) {
        cout << "\t\tInvalid input! Password must contain at least one special character.\n";
    }
    } while (!validPassword(receptionist_passsword));

    ofstream receptionist_file((receptionist_name + ".txt").c_str());
    receptionist_file << receptionist_passsword;
    return "\t\tReceptionist added successfully\n";
}

//delete functionalitie
string deleteDoctor() {
    system("cls");
    display();
    string doctor_name;
    cout << "\t\tEnter Doctor Name to Delete: ";
    cin >> doctor_name;
    remove((doctor_name + ".txt").c_str());
    return "\t\tDoctor deleted successfully\n";
}

string deleteReceptionist() {
    system("cls");
    display();
    string receptionist_name;
    cout << "\t\tEnter Receptionist Name to Delete: ";
    cin >> receptionist_name;
    remove((receptionist_name + ".txt").c_str());
    return "\t\tReceptionist deleted successfully\n";
}

//appointments
string viewAllAppointments() {
    ifstream appointment_file("all_appointments.txt");
    if (!appointment_file) return "\t\tNo appointments found\n";

    string date[100], patient[100], doctor[100], time[100];
    int count = 0;

    while (appointment_file >> date[count] >> patient[count] >> doctor[count] >> time[count])
        count++;

    string out = "\n\t\tALL APPOINTMENTS\n";
    for (int i = 0; i < count; i++)
        out += "\t\t" + date[i] + " | " + patient[i] + " | Dr. " + doctor[i] + " | " + time[i] + "\n";

    return out;
}
//doctor login
string doctorLogin() {
    system("cls");
    display();
    string doctorName, doctorPassword, passwrod_in_file;

    cout << "\t\tDoctor Name: ";
    cin >> setw(20) >> doctorName;
    cout << "\t\tPassword: ";
    cin >> setw(20) >> doctorPassword;

    ifstream File((doctorName + ".txt").c_str());
    if (!File) 
	  return "\t\tDoctor not found\n";

    File >> passwrod_in_file;
    if (doctorPassword != passwrod_in_file) 
	  return "\t\tInvalid password\n";

    return viewAppointments(doctorName);
}

string viewAppointments(const string &doctorName) {
    ifstream file("all_appointments.txt");
    if (!file) return "\t\tNo appointments\n";

    string date[100], patient[100], doctor[100], time[100];
    int count = 0;

    while (file >> date[count] >> patient[count] >> doctor[count] >> time[count])
        count++;

    string out = "\n\t\tAppointments for Dr. " + doctorName + ":\n";
    for (int i = 0; i < count; i++)
        if (doctor[i] == doctorName)
            out += "\t\t" + date[i] + " | " + patient[i] + " | " + time[i] + "\n";

    return out;
}

//receptionist
string receptionistLogin() {
    system("cls");   
	display();
    string ReceptionistName, ReceptionistPassword, Password_In_File;

    cout << "\t\tReceptionist Name: ";
    cin >> setw(20) >> ReceptionistName;
    cout << "\t\tPassword: ";
    cin >> setw(20) >> ReceptionistPassword;

    ifstream file((ReceptionistName + ".txt").c_str());
    if (!file) return "\t\tReceptionist not found\n";

    file >> Password_In_File;
    if (ReceptionistPassword != Password_In_File)
        return "\t\tInvalid password\n";

    return receptionistMenu();
}

string receptionistMenu() {
    system("cls");
    display();
    int choice;
    cout << "\n\t\tReceptionist Panel\n";
    cout << "\t\t1. Add Appointment\n";
    cout << "\t\t2. View All Appointments\n";
    cout << "\t\t3. Logout\n";
    cout << "\t\tChoice: ";
    cin >> choice;

    if (choice == 1) return addAppointment();
    if (choice == 2) return receptionistViewAllAppointments();
    return "\t\tLogged out\n";
}

string addAppointment() {
    system("cls");
    display();
    string date, patient, doctor, time;

    cout << "\n\t\t Appointment Date: ";
    cin >> date;
    cout << "\t\tPatient Name: ";
    cin >> patient;
    cout << "\t\tDoctor: ";
    cin >> doctor;
    cout << "\t\tTime: ";
    cin >> time;

    ofstream file("all_appointments.txt", ios::app);
    file << date << " " << patient << " " << doctor << " " << time << endl;

    return "\t\tAppointment added successfully\n";
}

string receptionistViewAllAppointments() {
    ifstream file("all_appointments.txt");
    if (!file) return "\t\tNo appointments found\n";

    string date[100], patient[100], doctor[100], time[100];
    int count = 0;

    while (file >> date[count] >> patient[count] >> doctor[count] >> time[count])
        count++;

    string out = "\n\t\tALL APPOINTMENTS (Doctor-wise)\n";
    for (int i = 0; i < count; i++)
        out += "\t\tDr. " + doctor[i] + " | " + date[i] + " | " + patient[i] + " | " + time[i] + "\n";

    return out;
}

//patient
string patientEntry() {
    system("cls");
    display();
    int choice;
    cout << "\n\t\tPatient\n";
    cout << "\t\t1. Sign In\n";
    cout << "\t\t2. Sign Up\n";
    cout << "\t\tChoice: ";
    cin >> choice;

    if (choice == 1) return patientSignin();
    if (choice == 2) return patientSignup();
    return "\t\tInvalid choice\n";
}

string patientSignup() {
    system("cls");
    display();
    string name, password;

    cout << "\t\tChoose Username: ";
    cin >> name;
    cout << "\t\tChoose Password: ";
    cin >> password;

    ofstream file((name + ".txt").c_str());
    file << password;
    return "\t\tSignup successful\n";
}

string patientSignin() {
    system("cls");
    display();
    string name, password, file_password;

    cout << "\t\tUsername: ";
    cin >> name;
    cout << "\t\tPassword: ";
    cin >> password;

    ifstream file((name + ".txt").c_str());
    if (!file) return "\t\tPatient not found\n";

    file >> file_password;
    if (password != file_password) return "\t\tInvalid password\n";

    return patientPanel(name);
}

string patientPanel(const string &patientName) {
    system("cls");
    display();
    int choice;
    cout << "\n\t\tPatient Panel\n";
    cout << "\t\t1. Add Medical History\n";
    cout << "\t\t2. View Medical History\n";
    cout << "\t\t3. Logout\n";
    cout << "\t\tChoice: ";
    cin >> choice;

    if (choice == 1) return addMedicalHistory(patientName);
    if (choice == 2) return viewMedicalHistory(patientName);
    return "\t\tLogged out\n";
}

string addMedicalHistory(const string &patientName) {
    system("cls");
    display();
    string doctor, date, medicine, dosage;

    cout << "\t\tDoctor: ";
    cin >> doctor;
    cout << "\t\tDate: ";
    cin >> date;
    cout << "\t\tMedicine: ";
    cin >> medicine;
    cout << "\t\tDosage: ";
    cin >> dosage;

    ofstream file((patientName + "_history.txt").c_str(), ios::app);
    file << date << " " << doctor << " " << medicine << " " << dosage << endl;

    return "\t\tMedical history added successfully\n";
}

string viewMedicalHistory(const string &patientName) {
	display();
    ifstream File((patientName + "_history.txt").c_str());
    if (!File) return "\t\tNo medical history found\n";

    string line, out = "\n\t\tMedical History:\n";
    while (getline(File, line))
        out += "\t\t" + line + "\n";
    return out;
}

