#ifndef DATABASE_H_
#define DATABASE_H_

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include "Table.h"

using namespace std;

class Database	{
public:

	//Constructors
	Database() {}
	~Database();

	//Accessors
	Table* GetTable(int index) const { return m_Tables[index]; }
	void Show(const string _name) const;

	//Mutators
	void CreateTable(const string _name, vector<string> _attrs, vector<string> _key);	//done
	void DeleteTable(const string _name);	//done

	void InsertInto(const string _name, vector<string> _rec);	//done
	void Update(const string _name, const string _attr, vector<string> _condition);
	void DeleteFrom(const string _name, vector<string> condition);

		//select the tuples in a relation that satisfy a particular condition
	Table* Selection(const string _newname, const string _oldname, vector<string> _condition);	//EDDIE	

		//select a subset of the attributes in a relation
	Table* Projection(const string _newname, const string _oldname, vector<string> _condition);

		//rename the attributes in a relation.
	Table* Rename(const string _newname, const string _oldname, vector<string> _attrs);

		//compute the union of two relations; the relations must be union-compatible.
	Table* SetUnion(const string _newname, const string _tbl1, const string _tbl2);

		//compute the set difference of two relations; the relations must be union-compatible.
	Table* SetDifference(const string _newname, const string _tbl1, const string _tbl2);

		//compute the Cartesian product of two relations.
	Table* CrossProduct(const string _newname, const string _tbl1, const string _tbl2);

		//compute the natural join of two relations
	Table* Join(const string _newname, const string _tbl1, const string _tbl2);

private:
	vector<Table*> m_Tables;
};

#endif
