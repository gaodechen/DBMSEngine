#include "Database.h"

#include <iostream>

using namespace std;

int main() {

	Database* db = new Database();

	vector<string> attrs;
	attrs.push_back("name");
	attrs.push_back("kind");
	attrs.push_back("years");
	vector<string> key;
	key.push_back("name");
	key.push_back("kind");
	db->CreateTable("Animals", attrs, key);

	attrs.clear();
	attrs.push_back("name");
	attrs.push_back("kind");
	attrs.push_back("years");
	key.clear();
	key.push_back("name");
	key.push_back("kind");
	db->CreateTable("Animals2", attrs, key);

	attrs.clear();
	attrs.push_back("model");
	attrs.push_back("maker");
	attrs.push_back("year");
	key.clear();
	key.push_back("model");
	key.push_back("year");
	db->CreateTable("Cars", attrs, key);

	attrs.clear();
	attrs.push_back("employee name");
	attrs.push_back("employee id");
	attrs.push_back("dept");
	key.clear();
	key.push_back("employee id");
	db->CreateTable("Employees", attrs, key);

	attrs.clear();
	attrs.push_back("managers");
	attrs.push_back("dept");
	key.clear();
	key.push_back("dept");
	db->CreateTable("Dept", attrs, key);
	cout << endl << "FINISHED CREATING TABLE..." << endl << endl;

	vector<string> record;
	record.push_back("Heriberto");
	record.push_back("cat");
	record.push_back("3");
	db->InsertInto("Animals", record);
	
	record.clear();
	record.push_back("Christian");
	record.push_back("dog");
	record.push_back("4");
	db->InsertInto("Animals", record);

	record.clear();
	record.push_back("Joanne");
	record.push_back("dog");
	record.push_back("2");
	db->InsertInto("Animals", record);

	record.clear();
	record.push_back("Sara");
	record.push_back("elephant");
	record.push_back("6");
	db->InsertInto("Animals", record);

	record.clear();
	record.push_back("Heriberto");
	record.push_back("parrot");
	record.push_back("3");
	db->InsertInto("Animals2", record);
	
	record.clear();
	record.push_back("Christian");
	record.push_back("dog");
	record.push_back("4");
	db->InsertInto("Animals2", record);

	record.clear();
	record.push_back("Joanne");
	record.push_back("dawg");
	record.push_back("2");
	db->InsertInto("Animals2", record);

	record.clear();
	record.push_back("Sara");
	record.push_back("elephant");
	record.push_back("6");
	db->InsertInto("Animals2", record);

	record.clear();
	record.push_back("Sentra");
	record.push_back("Nissan");
	record.push_back("2012");
	db->InsertInto("Cars", record);

	record.clear();
	record.push_back("Mustang");
	record.push_back("Ford");
	record.push_back("2005");
	db->InsertInto("Cars", record);

	record.clear();
	record.push_back("Charger");
	record.push_back("Dodge");
	record.push_back("1976");
	db->InsertInto("Cars", record);

	record.clear();
	record.push_back("Heriberto");
	record.push_back("1");
	record.push_back("Marketing");
	db->InsertInto("Employees", record);

	record.clear();
	record.push_back("Christian");
	record.push_back("2");
	record.push_back("Finance");
	db->InsertInto("Employees", record);

	record.clear();
	record.push_back("Eliutt");
	record.push_back("3");
	record.push_back("Marketing");
	db->InsertInto("Employees", record);

	record.clear();
	record.push_back("Mr. Devlin");
	record.push_back("Marketing");
	db->InsertInto("Dept", record);

	record.clear();
	record.push_back("Mr. Happy");
	record.push_back("Finance");
	db->InsertInto("Dept", record);

	cout << endl << "FINISHED INSERTING INTO..." << endl << endl;

	db->Show("Animals");
	cout << endl;
	db->Show("Animals2");
	cout << endl;
	db->Show("Cars");
	cout << endl;

	vector<string> condition;
	condition.push_back("years");
	condition.push_back(">=");
	condition.push_back("5");
	db->Update("Animals", "7", condition);
	
	cout << endl << "FINISHED UPDATING..." << endl << endl;

	db->Show("Animals");

	condition.clear();
	condition.push_back("kind");
	condition.push_back("==");
	condition.push_back("dog");

	Table* dogs = db->Selection("Dogs", "Animals", condition);
	
	cout << endl << "FINISHED SELECTION..." << endl << endl;
	
	dogs->Show();

	vector<string> newattrs;
	newattrs.push_back("name");
	newattrs.push_back("kind");

	Table* project = db->Projection("Project", "Animals", newattrs); 

	cout << endl << "FINISHED PROJECTION..." << endl << endl;

	project->Show();
	
	Table* setunion = db->SetUnion("SetUnion", "Animals", "Animals2");

	cout << endl << "FINISHED SETUNION..." << endl << endl;

	setunion->Show();

	Table* difference = db->SetDifference("Difference", "Animals", "Animals2");

	cout << endl << "FINISHED DIFFERENCE..." << endl << endl;

	difference->Show();

	newattrs.clear();
	newattrs.push_back("NAME");
	newattrs.push_back("KIND");
	newattrs.push_back("YEARS");

	Table* rename = db->Rename("Rename", "Animals", newattrs); 

	cout << endl << "FINISHED RENAME..." << endl << endl;

	rename->Show();

	Table* crossproduct = db->CrossProduct("Animals*Cars", "Animals", "Cars");

	cout << endl << "FINISHED CROSSPRODUCT..." << endl << endl;

	crossproduct->Show();

	Table* join = db->Join("Animals(JOIN)Cars", "Animals", "Animals2");

	cout << endl << "FINISHED JOIN..." << endl << endl;

	join->Show();

	Table* join2 = db->Join("Employees (JOIN) Dept", "Employees", "Dept");

	cout << endl << "FINISHED JOIN..." << endl << endl;

	join2->Show();

	condition.clear();
	condition.push_back("years");
	condition.push_back("==");
	condition.push_back("3");
	db->DeleteFrom("Animals", condition);

	cout << endl << "FINISHED DELETING FROM..." << endl << endl;
	
	db->Show("Animals");

	return 0;
}
