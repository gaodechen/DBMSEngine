#ifndef TABLE_H_
#define TABLE_H_

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <cctype>
#include "Record.h"

using namespace std;

class Table {
public:

	//Constructors
	Table(string _name, vector<string> _attrs, map<int, string> _key):
	  m_Name(_name), m_Attrs(_attrs), m_Key(_key) {}
	
	Table(string _name, vector<string> _attrs):
	  m_Name(_name), m_Attrs(_attrs) {}
	
	Table(Table* _table);
	
	~Table() {}
	
	
	//Accessors
	bool	Empty() const { return m_Records.empty(); }
	string 	GetName() const { return m_Name; }
	Record* GetRecord(int _index) const { return m_Records[_index]; }
	string 	GetAttr(int _index) const { return m_Attrs[_index]; }
	int		GetNumRecords() const { return m_Records.size(); }
	int		GetNumAttrs() const { return m_Attrs.size(); }
	int		GetNumKeys() const { return m_Key.size(); }
	int		GetKeyFirst(int _index) const;
	string	GetKeySecond(int _index) const;
	void	Show() const;

	//Mutator
	void InsertInto(vector<string> _record);
	void InsertInto(Record* _record);
	void Update(const string _attr, vector<string> _condition);
	void DeleteFrom(vector<string> _condition);
	void Rename(vector<string> _attrs) { m_Attrs = _attrs; }
	void RemoveRecord(int _index) { m_Records.erase(m_Records.begin() + _index); }
	void DeleteColumn(int _index);

private:
	string m_Name;
	vector<Record*> m_Records;
	vector<string> m_Attrs; 
	map<int, string> m_Key;
};

#endif
