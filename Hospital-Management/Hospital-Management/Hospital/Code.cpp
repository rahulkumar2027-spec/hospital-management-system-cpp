#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <limits>

using namespace std;

// ---------------------------------------------------------
// Safe input helpers.
// A plain "cin >> someInt" leaves the stream stuck in a failed
// state forever if the user types non-numeric text - every read
// after that silently does nothing, which spins the program into
// an infinite loop. These helpers detect that, reset the stream,
// and throw instead, so the existing try/catch blocks can handle it.
// ---------------------------------------------------------
int readInt()
{
	int value;
	cin >> value;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw invalid_argument("Please enter a valid whole number.");
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard rest of the line
	return value;
}

float readFloat()
{
	float value;
	cin >> value;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw invalid_argument("Please enter a valid number.");
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard rest of the line
	return value;
}

// Reads a full line (so names with spaces, like "Ramu Kumar", work correctly -
// a plain "cin >> name" would stop at the first space).
string readLine()
{
	string line;
	getline(cin, line);

	if (line.empty())
		throw invalid_argument("This field cannot be empty.");

	return line;
}

inline void WelcomeMessage1()
{
	cout<<"**********Welcome to XYZ Hospital**********"<<endl<<endl;
}

inline void WelcomeMessage2()
{
	cout<<"**********Welcome to the Pharmacy**********"<<endl<<endl;
}

inline void WelcomeMessage3()
{
	cout<<"**********Welcome to Billing**********"<<endl<<endl;
}

inline void WelcomeMessage4()
{
	cout<<"**********Welcome to the Cafeteria**********"<<endl<<endl;
}

const string PATIENT_FILE = "patients.txt";

// ---------------------------------------------------------
// Base class
// ---------------------------------------------------------
class hospital
{
	protected:
	string address;

	public:
	static int capacity; // static variable - shared by every object of this class

	hospital()
	{
		address = "4 Park Lane";
	}
};

int hospital::capacity = 500;

// ---------------------------------------------------------
// info -> shared fields for anyone in the hospital system
// ---------------------------------------------------------
class info: public hospital
{
	protected:
	string name;
	int age;

	public:
	info() // constructor
	{
		name = "N/A";
		age = 0;
	}

	void get()
	{
		cout<<"Enter Name: ";
		name = readLine();

		cout<<"Enter Age: ";
		age = readInt();

		if (age < 0 || age > 130)
			throw invalid_argument("Age must be between 0 and 130.");

		cout<<endl;
	}

	void show()
	{
		cout<<"Name: "<<name<<endl;
		cout<<"Age: "<<age;

		cout<<endl<<endl;
	}

	string getName() const { return name; }
	int getAge() const { return age; }
};

// ---------------------------------------------------------
// patient
// ---------------------------------------------------------
class patient: public info
{
	int id;

	public:
	patient()
	{
		id = 0;
	}

	void get(int newId, int currentCount)
	{
		if (currentCount >= capacity)
			throw runtime_error("Hospital is at full capacity. Cannot admit new patient.");

		cout<<"Patient Details...\n\n";

		info::get();

		id = newId;

		cout<<"\nAssigned Patient ID: "<<id;
		cout<<"\nRemaining Capacity: "<<capacity - currentCount - 1;

		cout<<endl<<endl;
	}

	void show()
	{
		cout<<"Patient Details...\n\n";

		info::show();

		cout<<"Patient ID: "<<id;

		cout<<endl<<endl;
	}

	int retid()
	{
		return id;
	}

	// simple, explainable file I/O: one patient per line
	void saveToFile(ofstream &fout)
	{
		fout << id << ' ' << getName() << ' ' << getAge() << '\n';
	}

	void loadFromFile(int fileId, const string &fileName, int fileAge)
	{
		id = fileId;
		name = fileName;
		age = fileAge;
	}
};

// ---------------------------------------------------------
// employee
// ---------------------------------------------------------
class employee: public info
{
	int id;
	int type;
	float sal;

	public:
	employee()
	{
		id = 0;
		sal = 0;
		type = 0;
	}

	void get()
	{
		cout<<"Employee Details...\n\n";

		info::get();

		cout<<"Enter Employee ID: ";
		id = readInt();

		cout<<"\n[1] Doctor\n[2] Admin\n[3] Housekeeping\n[4] Maintanence\n\n";
		cout<<"Enter Employee Type (1/2/3/4): ";

		type = readInt();

		if (type < 1 || type > 4)
			throw invalid_argument("Employee type must be between 1 and 4.");

		cout<<endl;
	}

	void show()
	{
		cout<<"\nEmployee Details...\n\n";

		info::show();

		cout<<"Employee ID: "<<id<<endl;
		cout<<"Employee Type: "<<type<<endl;
		cout<<"Calculated Monthly Salary: "<<sal;

		cout<<endl<<endl;
	}

	friend void calcsal(employee &);
};

void calcsal(employee &e)
{
	int hours;

	cout<<"Enter the Hours Clocked for the Month: ";
	hours = readInt();

	if (hours < 0)
		throw invalid_argument("Hours worked cannot be negative.");

	switch (e.type)
	{
		case 1:
		e.sal = 5000 * hours;
		break;

		case 2:
		e.sal = 2000 * hours;
		break;

		case 3:
		e.sal = 1000 * hours;
		break;

		case 4:
		e.sal = 500 * hours;
		break;

		default: cout<<"Unexpected Type";
	}
}

void add(int a, int b)
{
	cout<<"\nSum of Selected Tablets: "<<a+b<<endl<<endl;
}

void add(float a, float b)
{
	cout<<"\nSum of Selected Vials: "<<a+b<<endl<<endl;
}

class typesalone
{
	public:
	void display()
	{
		cout<<"Hourly Salary for Type 1 Employee: Rs. 5000"<<endl;
	}
};

class typesaltwo: public typesalone
{
	public:
	void display()
	{
		cout<<"Hourly Salary for Type 2 Employee: Rs. 2000"<<endl;
	}
};

class typesalthree
{
	public:
	virtual void display()
	{
		cout<<"Hourly Salary for Type 3 Employee: Rs. 1000"<<endl;
	}

	void show()
	{
		cout<<"Hourly Salary for Type 3 Employee: Rs. 1000"<<endl;
	}
};

class typesalfour: public typesalthree
{
	public:
	void display()
	{
		cout<<"Hourly Salary for Type 4 Employee: Rs. 500"<<endl;
	}

	void show()
	{
		cout<<"Hourly Salary for Type 4 Employee: Rs. 500"<<endl;
	}
};

// ---------------------------------------------------------
// Virtual Base Class demo (solves the "diamond problem")
//
//        Person
//     PatientRole   StaffRole   (both inherit Person)
//        DualRolePerson         (inherits both)
//
// Without the 'virtual' keyword below, DualRolePerson would end up
// with two separate copies of Person - and show() would be ambiguous.
// ---------------------------------------------------------
class Person
{
	public:
	string name = "Unknown";

	void show()
	{
		cout<<"Person Name: "<<name<<endl;
	}
};

class PatientRole: virtual public Person
{
	public:
	int patientId = 0;
};

class StaffRole: virtual public Person
{
	public:
	int staffId = 0;
};

class DualRolePerson: public PatientRole, public StaffRole
{
	public:
	void display()
	{
		cout<<"Dual Role Person (e.g. a doctor who is also a patient)\n";
		show(); // only ONE copy of Person exists, thanks to virtual inheritance
		cout<<"Patient ID: "<<patientId<<", Staff ID: "<<staffId<<endl<<endl;
	}
};

class bill
{
	int fixed;
	int variable;
	int days;

	public:
	bill()
	{
		fixed = 0;
		variable = 0;
		days = 0;
	}

	bill(int fixed, int variable, int days)
	{
		this->fixed = fixed;
		this->variable = variable;
		this->days = days;
	}

	void get()
	{
		cout<<"Enter Fixed Charges: ";
		fixed = readInt();

		cout<<"Enter Variable Charges: ";
		variable = readInt();

		cout<<"Enter Number of Days: ";
		days = readInt();

		if (fixed < 0 || variable < 0 || days < 0)
			throw invalid_argument("Charges and days cannot be negative.");

		fixed *= days;
		variable *= days;

		cout<<endl;
	}

	void show()
	{
		cout<<"Fixed: Rs. "<<fixed<<endl<<"Variable: Rs. "<<variable<<endl<<endl;
	}

	bill operator + (bill b) const
	{
		bill temp;

		temp.fixed = fixed + b.fixed;
		temp.variable = variable + b.variable;

		return temp;
	}
};

class scan
{
	public:
	void display()
	{
		cout<<"Imaging Solutions Available...\n\n[1] X-Ray\n[2] MRI\n[3] CT-Scan\n\n";
	}
};

class ptime
{
	public:
	void display()
	{
		cout<<"Time Taken...\n\n[1] X-Ray (10 Minutes) \n[2] MRI (30 Minutes) \n[3] CT-Scan (25 Minutes)\n\n";
	}
};

class scantime: public scan, public ptime
{
	int type;

	public:
	void get()
	{
		cout<<"Enter Type of Scan: ";
		type = readInt();

		if (type < 1 || type > 3)
			throw invalid_argument("Scan type must be 1, 2 or 3.");

		cout<<endl;
	}

	void show()
	{
		cout<<"Selected Type: Type "<<type<<endl<<endl;
	}
};

class cafe
{
	int type;
	float amount;

	public:
	cafe()
	{
		type = 0;
		amount = 0.0;
	}

	void get()
	{
		do
		{
			cout<<"Choose...\n\n[1] Tea \n[2] Coffee\n[3] Sandwich \n[4] Cookie\n[0] Exit\n\n";

			try
			{
				type = readInt();
			}
			catch (const exception &e)
			{
				cout<<e.what()<<endl<<endl;
				type = -1; // fall through to "Wrong Choice" below, keep the loop going
			}

			cout<<endl;

			switch (type)
			{
				case 1:
				amount += 450;
				break;

				case 2:
				amount += 550;
				break;

				case 3:
				amount += 600;
				break;

				case 4:
				amount += 400;
				break;

				case 0:
				break;

				default: cout<<"Wrong Choice...";
			}

		}
		while (type != 0);
	}

	void show()
	{
		cout<<"Final Amount: "<<amount<<endl;
		cout<<"Please Pay with Card or Cash. Thank You."<<endl<<endl;
	}
};

// ---------------------------------------------------------
// File Handling helpers
// One line per patient in patients.txt: "<id> <name> <age>"
// ---------------------------------------------------------
void loadPatients(vector<patient> &patients)
{
	ifstream fin(PATIENT_FILE);

	if (!fin) // file may not exist on first run - that's fine
		return;

	int id, age;
	string name;

	while (fin >> id >> name >> age)
	{
		patient p;
		p.loadFromFile(id, name, age);
		patients.push_back(p);
	}

	fin.close();

	if (!patients.empty())
		cout<<"Loaded "<<patients.size()<<" existing patient record(s) from "<<PATIENT_FILE<<".\n\n";
}

void savePatients(vector<patient> &patients)
{
	ofstream fout(PATIENT_FILE);

	if (!fout)
	{
		cout<<"Warning: could not save patient records to file.\n\n";
		return;
	}

	for (auto &p : patients)
		p.saveToFile(fout);

	fout.close();
}

int main()
{
	WelcomeMessage1();

	int k = 1; // non-zero so the loop below runs at least once
	vector<patient> patients; // dynamic list, no fixed-size array / capacity assumption in code

	loadPatients(patients);

	int nextId = static_cast<int>(patients.size()) + 1;

	do
	{
		cout<<"[1] Admission\n[2] View Patient Details\n[0] Exit\n\nYour Choice: ";

		try
		{
			k = readInt();
		}
		catch (const exception &e)
		{
			cout<<endl<<e.what()<<endl<<endl;
			continue; // re-show the menu instead of spinning
		}

		cout<<endl<<endl;

		switch (k)
		{
			case 0:
			break;

			case 1:

			try
			{
				patient p;
				p.get(nextId, static_cast<int>(patients.size()));
				patients.push_back(p);
				nextId++;
			}
			catch (const exception &e)
			{
				cout<<"Admission failed: "<<e.what()<<endl<<endl;
			}

			break;

			case 2:

			try
			{
				int id;
				cout<<"Enter ID: ";
				id = readInt();

				bool found = false;

				for (auto &p : patients)
				{
					if (p.retid() == id)
					{
						p.show();
						found = true;
						break;
					}
				}

				if (!found)
					throw runtime_error("No patient found with that ID.");
			}
			catch (const exception &e)
			{
				cout<<"Lookup failed: "<<e.what()<<endl<<endl;
			}

			break;

			default: cout<<"Wrong Choice...\n\n";
		}

	}
	while (k != 0);

	savePatients(patients); // File Handling: persist patient records for next run


	employee e;

	try
	{
		e.get();
		calcsal(e);
		e.show();
	}
	catch (const exception &ex)
	{
		cout<<"Could not process employee: "<<ex.what()<<endl<<endl;
	}


	WelcomeMessage2();

	try
	{
		int a, b;
		float x, y;

		cout<<"Enter Supplier Price of 15 Crocin: ";
		a = readInt();
		cout<<"Enter Supplier Price of 15 Azithromycin: ";
		b = readInt();

		add(a, b);

		cout<<"Enter Supplier Price of 10 Vial Cyclophosphamide: ";
		x = readFloat();

		cout<<"Enter Supplier Price of 10 Vial Methotrexate: ";
		y = readFloat();

		add(x, y);
	}
	catch (const exception &ex)
	{
		cout<<"Pharmacy error: "<<ex.what()<<endl<<endl;
	}


	typesalone t1; // base class' display() called (no overriding)
	t1.display();

	typesaltwo t2; // derived class' display() called and base class' display() overridden
	t2.display();

	t2.typesalone::display(); // scope resolution operator to call base class' display()


	typesalthree *ptr; // base class pointer
	typesalfour t4;

	ptr = &t4; // base class pointer referencing object of derived class

	ptr->display(); // virtual function -> derived class' display() called
	ptr->show(); // not virtual -> base class' show() called


	cout<<"---- Virtual Base Class Demo ----\n\n";

	DualRolePerson dp;
	dp.name = "Dr. Rao";
	dp.patientId = 101;
	dp.staffId = 55;
	dp.display();


	WelcomeMessage3();

	try
	{
		bill b1, b2, b3;

		cout<<"Charges for Stay in General Ward...\n\n";
		b1.get();

		cout<<"Charges for Stay in ICU Ward...\n\n";
		b2.get();

		cout<<"Total Charges for Stay...\n\n";
		b3 = b1 + b2;

		b3.show();
	}
	catch (const exception &ex)
	{
		cout<<"Billing error: "<<ex.what()<<endl<<endl;
	}


	try
	{
		scantime s;

		s.scan::display();
		s.ptime::display();

		s.get();
		s.show();
	}
	catch (const exception &ex)
	{
		cout<<"Scan booking error: "<<ex.what()<<endl<<endl;
	}

	WelcomeMessage4();

	cafe *c;
	c = new cafe;

	c->get();
	c->show();

	delete c;

	return 0;
}
