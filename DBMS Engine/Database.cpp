#include "Database.h"

using namespace std;

//Destructor

Database::~Database() 
{
	for(int i = 0; i < (int)m_Tables.size(); i++)
	{
		delete m_Tables[i];
	}
	
}

//Mutators

void 
Database::CreateTable(const string _name, vector<string> _attrs, vector<string> _key)
{
	map<int, string> mapkey;
	for(int i = 0; i < (int)_attrs.size(); i++)	//maps the index of the _attrs to its string in a map
	{
		for(int k = 0; k < (int)_key.size(); k++)
		{
			if(_attrs[i].compare(_key[k]) == 0)
			{
				mapkey[i] = _attrs[i];
			}
		}
	}
	
	if(_key.size() != mapkey.size())
	{
		cerr << "Error: Primary key not defined properly" << endl;
		return;
	}

	for(int i = 0; i < (int)m_Tables.size(); i++)
	{
		if(_name.compare(m_Tables[i]->GetName()) == 0)
		{
			cerr << "Error: Name already taken" << endl;
			return;
		}
	}
	 m_Tables.push_back(new Table(_name, _attrs, mapkey));
}


void 
Database::DeleteTable(const string _name)
{
	for(int i = 0; i < (int)m_Tables.size(); i++)
	{
		if(_name.compare(m_Tables[i]->GetName()) == 0)
		{
			m_Tables.erase(m_Tables.begin() + i);
			break;
		}
	}
}

void
Database::Show(const string _name) const
{
	for(int i = 0; i < (int)m_Tables.size(); i++)
	{
		if(_name.compare(m_Tables[i]->GetName()) == 0)
		{
			m_Tables[i]->Show();
			break;
		}
	}
}

void
Database::InsertInto(const string _name, vector<string> _record)
{	
	for(int i = 0; i < (int)m_Tables.size(); i++)
	{
		if(_name.compare(m_Tables[i]->GetName()) == 0)
		{
			m_Tables[i]->InsertInto(_record);
			break;
		}
	}
}

void
Database::Update(const string _name, const string _attr, vector<string> _condition)
{
	for(int i = 0; i < (int)m_Tables.size(); i++)
	{
		if(_name.compare(m_Tables[i]->GetName()) == 0)
		{
			m_Tables[i]->Update(_attr, _condition);
			break;
		}
	}
}

void
Database::DeleteFrom(const string _name, vector<string> _condition)
{
	for(int i = 0; i < (int)m_Tables.size(); i++)
	{
		if(_name.compare(m_Tables[i]->GetName()) == 0)
		{
			m_Tables[i]->DeleteFrom(_condition);
			break;
		}
	}
}

// Relational operations

Table* 
Database::Selection(const string _newname, const string _oldname, vector<string> _condition)
{
	Table* table = NULL;
	for(int i = 0; i < (int)m_Tables.size(); i++)
	{
		if(_oldname == m_Tables[i]->GetName())
		{
			table = m_Tables[i];
			break;
		}
	}

	if(table == NULL)
	{
		cerr << "Error: Table not found" << endl;
		return NULL;
	}

	Table* newtable = new Table(table);

	while(!newtable->Empty())
	{
		newtable->RemoveRecord(0);
	}

	vector<Record*> newrecords;
	int indexOfAttr = -1;
	for(int i = 0; i < newtable->GetNumAttrs(); i++)
	{
		if(_condition[0].compare(newtable->GetAttr(i)) == 0)
		{
			indexOfAttr = i;
			break;
		}
	}
	
	if(indexOfAttr == -1)
	{
		cerr << "Error: Attribute not found" << endl;
		return NULL;
	}
	
	bool noatoi = false;
	for(int i = 0; i < (int)_condition[2].size(); i++)
	{
		if(!isdigit(_condition[2][i]))
		{
			noatoi = true;
		}
	}
	
	int condition;
	if(!noatoi) condition = atoi(_condition[2].c_str());
	
	for(int i = 0; i < (int)table->GetNumRecords(); i++)
	{	
		//cases: == | != | < | > | <= | >=
	
		if(_condition[1].compare("==") == 0) {
			if(!noatoi)
			{
				int compare = atoi(table->GetRecord(i)->GetAttr(indexOfAttr).c_str()); 
				if(compare == condition)
				{
					newtable->InsertInto(table->GetRecord(i));
				}
			}
			
			else
			{
				if(table->GetRecord(i)->GetAttr(indexOfAttr).compare(_condition[2]) == 0)
				{
					newtable->InsertInto(table->GetRecord(i));  
				}
			}	
			
		} else if(_condition[1].compare("!=") == 0) {
			if(!noatoi)
			{
				int compare = atoi(table->GetRecord(i)->GetAttr(indexOfAttr).c_str()); 
				if(compare != condition)
				{
					newtable->InsertInto(table->GetRecord(i));
				}
			}
			
			else
			{
				if(table->GetRecord(i)->GetAttr(indexOfAttr).compare(_condition[2]) != 0)
				{
					newtable->InsertInto(table->GetRecord(i));
				}
			}	
			
		} else if(_condition[1].compare("<") == 0) {
			if(!noatoi)
			{
				int compare = atoi(table->GetRecord(i)->GetAttr(indexOfAttr).c_str());
				if(compare < condition)
				{
					newtable->InsertInto(table->GetRecord(i));
				}
			}
			
			else
			{
				if(table->GetRecord(i)->GetAttr(indexOfAttr).compare(_condition[2]) < 0)
				{
					newtable->InsertInto(table->GetRecord(i));
				}
			}	
			
		} else if(_condition[1].compare(">") == 0) {
			if(!noatoi)
			{
				int compare = atoi(table->GetRecord(i)->GetAttr(indexOfAttr).c_str()); 
				if(compare > condition)
				{
					newtable->InsertInto(table->GetRecord(i));
				}
			}
			
			else
			{
				if(table->GetRecord(i)->GetAttr(indexOfAttr).compare(_condition[2]) > 0)
				{
					newtable->InsertInto(table->GetRecord(i));
				}
			}
		
		} else if(_condition[1].compare("<=") == 0) {
			if(!noatoi)
			{
				int compare = atoi(table->GetRecord(i)->GetAttr(indexOfAttr).c_str()); 
				if(compare <= condition)
				{
					newtable->InsertInto(table->GetRecord(i));
				}
			}
			
			else
			{
				if(table->GetRecord(i)->GetAttr(indexOfAttr).compare(_condition[2]) <= 0)
				{
					newtable->InsertInto(table->GetRecord(i));
				}
			}	
			
		} else if(_condition[1].compare(">=") == 0) {
			if(!noatoi)
			{
				int compare = atoi(table->GetRecord(i)->GetAttr(indexOfAttr).c_str()); 
				if(compare >= condition)
				{
					newtable->InsertInto(table->GetRecord(i));
				}
			}
			
			else
			{
				if(table->GetRecord(i)->GetAttr(indexOfAttr).compare(_condition[2]) >= 0)
				{
					newtable->InsertInto(table->GetRecord(i));
				}
			}	
		}
	}
	return newtable;
}

Table*
Database::Projection(const string _newname, const string _oldname, vector<string> _attrs)
{
	Table* table = NULL;
	vector<int> AttrIndicies;

	for(int i=0; i<(int)m_Tables.size(); i++)
	{
		if(_oldname == m_Tables[i]->GetName())
		{
			table = m_Tables[i];
			break;
		}
	}

	if(table == NULL)
	{
		cerr << "Error: Table not found" << endl;
		return NULL;
	}

	for(int k=0; k < (int)_attrs.size(); k++)
	{
		for(int m=0; m < (int)table->GetNumAttrs(); m++)
		{
			if(_attrs[k].compare(table->GetAttr(m)) == 0)
			{
				AttrIndicies.push_back(m);
				break;
			}
		}
	}

	Table* newtable = new Table(_newname, _attrs);
	for(int i = 0; i < table->GetNumRecords(); i++)
	{
		vector<string> newrecord;
		for(int k = 0; k < (int)AttrIndicies.size(); k++)
		{
			newrecord.push_back(table->GetRecord(i)->GetAttr(AttrIndicies[k]));
		}
		newtable->InsertInto(new Record(newrecord));
	}
	return newtable;
}

Table*
Database::Rename(const string _newname, const string _oldname, vector<string> _attrs)
{
	Table* newtable = NULL;
	for(int i = 0; i < (int)m_Tables.size(); i++)
	{
		if(_oldname.compare(m_Tables[i]->GetName()) == 0)
		{
			newtable = new Table(m_Tables[i]);
		}
	}

	if(newtable == NULL)
	{
		cerr << "Error: Table not found" << endl;
		return NULL;
	}

	if(_attrs.size() != newtable->GetNumAttrs())
	{
		cerr << "Error: Attributes not defined correctly" << endl;
		return NULL;
	}
	
	newtable->Rename(_attrs);
	return newtable;
}

Table*
Database::SetUnion(const string _newname, const string _tbl1, const string _tbl2)
{
	Table* tbl1 = NULL;
	Table* tbl2 = NULL;
	for(int i =0; i<(int) m_Tables.size(); ++i)
	{
		if(_tbl1.compare(m_Tables[i]->GetName()) == 0)
			tbl1 = m_Tables[i];
		if(_tbl2.compare(m_Tables[i]->GetName()) == 0)
			tbl2 = m_Tables[i];
	}

	if(tbl1 == NULL || tbl2 == NULL)
	{
		cerr << "Error: Table(s) not found" << endl;
		return NULL;
	}

	//Union compatibility check
	if(tbl1->GetNumAttrs() != tbl2->GetNumAttrs())
	{
		cerr << "Tables are not Union Compatible" << endl;
		return NULL;
	}

	for(int i = 0; i < (int)tbl1->GetNumAttrs(); i++)
	{
		if(tbl1->GetAttr(i).compare(tbl2->GetAttr(i)) != 0)
		{
			cerr << "Tables are not Union Compatible" << endl;
			return NULL;
		}
	}

	vector<string> newattrs;
	for(int i=0; i<(int)tbl1->GetNumAttrs(); i++)
	{
		newattrs.push_back(tbl1->GetAttr(i));
	}

	Table* newtable = new Table(_newname, newattrs);

	for(int i = 0; i<(int)tbl1->GetNumRecords(); i++)
	{
		newtable->InsertInto(tbl1->GetRecord(i));
	}
	
	for(int i = 0; i<(int)tbl2->GetNumRecords(); i++)
	{
		for(int k = 0; k<(int)newtable->GetNumRecords(); k++)
		{
			if(tbl2->GetRecord(i)->Equals(newtable->GetRecord(k)))
			{
				break;
			}
			
			else if(!tbl2->GetRecord(i)->Equals(newtable->GetRecord(k)) && k == (int)newtable->GetNumRecords() - 1)
			{
				newtable->InsertInto(tbl2->GetRecord(i));
				break;
			}
		}
	}

	return newtable;
}

Table*  
Database::SetDifference(const string _newname, const string _tbl1, const string _tbl2)
{
	Table* tbl1 = NULL;
	Table* tbl2 = NULL;
	for(int i =0; i<(int) m_Tables.size(); ++i)
	{
		if(_tbl1.compare(m_Tables[i]->GetName()) == 0)
			tbl1 = m_Tables[i];
		if(_tbl2.compare(m_Tables[i]->GetName()) == 0)
			tbl2 = m_Tables[i];
	}

	if(tbl1 == NULL || tbl2 == NULL)
	{
		cerr << "Error: Table(s) not found" << endl;
		return NULL;
	}

	//Union compatibility check
	if(tbl1->GetNumAttrs() != tbl2->GetNumAttrs())
	{
		cerr << "Tables are not Union Compatible" << endl;
		return NULL;
	}

	for(int i = 0; i < (int)tbl1->GetNumAttrs(); i++)
	{
		if(tbl1->GetAttr(i).compare(tbl2->GetAttr(i)) != 0)
		{
			cerr << "Tables are not Union Compatible" << endl;
			return NULL;
		}
	}

	vector<string> newattrs;
	for(int i=0; i<(int)tbl1->GetNumAttrs(); i++)
	{
		newattrs.push_back(tbl1->GetAttr(i));
	}

	Table* newtable = new Table(_newname, newattrs);

	for(int i = 0; i<(int)tbl1->GetNumRecords(); i++)
	{
		newtable->InsertInto(tbl1->GetRecord(i));
	}
	
	for(int i = 0; i<(int)tbl2->GetNumRecords(); i++)
	{
		for(int k = 0; k<(int)newtable->GetNumRecords(); k++)
		{
			if(newtable->GetRecord(k)->Equals(tbl2->GetRecord(i)))
			{
				newtable->RemoveRecord(k--);
				break;
			}

			else if(!newtable->GetRecord(k)->Equals(tbl2->GetRecord(i)) && k == (int)newtable->GetNumRecords() - 1)
			{
				newtable->InsertInto(tbl2->GetRecord(i));
				break;
			}
		}
	}
	return newtable;
}

Table*
Database::CrossProduct(const string _newname, const string _tbl1, const string _tbl2)
{
	Table* tb1 = NULL;
	Table* tb2 = NULL;
	for(int i = 0; i < (int)m_Tables.size(); i++)
	{
		if(_tbl1.compare(m_Tables[i]->GetName()) == 0)
		{
			tb1 = m_Tables[i];
		}

		else if(_tbl2.compare(m_Tables[i]->GetName()) == 0)
		{
			tb2 = m_Tables[i];
		}
	}

	if(tb1 == NULL || tb2 == NULL)
	{
		cerr << "Error: Table(s) not found" << endl;
		return NULL;
	}

	vector<string> newattrs;
	for(int i = 0; i < tb1->GetNumAttrs(); i++)
	{
		newattrs.push_back(tb1->GetAttr(i));
	}

	for(int i = 0; i < tb2->GetNumAttrs(); i++)
	{
		newattrs.push_back(tb2->GetAttr(i));
	}

	Table* newtable = new Table(_newname, newattrs);
	
	vector<string> newrecord;
	for(int i = 0; i < tb1->GetNumRecords(); i++)
	{
		for(int k = 0; k < tb2->GetNumRecords(); k++)
		{
			for(int m = 0; m < tb1->GetRecord(i)->GetSize(); m++)
			{
				newrecord.push_back(tb1->GetRecord(i)->GetAttr(m));
			}

			for(int m = 0; m < tb2->GetRecord(k)->GetSize(); m++)
			{
				newrecord.push_back(tb2->GetRecord(k)->GetAttr(m));
			}

			newtable->InsertInto(newrecord);
			newrecord.clear();
		}
	}

	return newtable;
}

//helper function

bool 
sort_pair_second(const pair<int,int> &left, const pair<int,int> &right) 
{
	return left.second < right.second;
}

Table* 
Database::Join(const string _newname, const string _tbl1, const string _tbl2)
{
	Table* tb1 = NULL;
	Table* tb2 = NULL;
	for(int i = 0; i < (int)m_Tables.size(); i++)
	{
		if(_tbl1.compare(m_Tables[i]->GetName()) == 0)
		{
			tb1 = m_Tables[i];
		}

		else if(_tbl2.compare(m_Tables[i]->GetName()) == 0)
		{
			tb2 = m_Tables[i];
		}
	}

	if(tb1 == NULL || tb2 == NULL)
	{
		cerr << "Error: Table(s) not found" << endl;
		return NULL;
	}

	vector<string> newattrs;
	vector< pair<int, int> > SharedAttrsIndicies;
	for(int i = 0; i < tb1->GetNumAttrs(); i++)
	{
		newattrs.push_back(tb1->GetAttr(i));
	}

	for(int i = 0; i < tb2->GetNumAttrs(); i++)
	{
		for(int k = 0; k < (int)newattrs.size(); k++)
		{
			if(newattrs[k].compare(tb2->GetAttr(i)) != 0 && k == (int)newattrs.size() - 1)
			{
				newattrs.push_back(tb2->GetAttr(i));
				break;
			}

			else if(newattrs[k].compare(tb2->GetAttr(i)) == 0)
			{
				SharedAttrsIndicies.push_back(make_pair(k,i+tb1->GetNumAttrs()));
			}
		}
	}

	Table* newtable = CrossProduct(_newname, _tbl1, _tbl2);
	for(int i = 0; i < (int)SharedAttrsIndicies.size(); i++)
	{
		for(int k = 0; k < (int)newtable->GetNumRecords(); k++)
		{
			string compare1 = newtable->GetRecord(k)->GetAttr(SharedAttrsIndicies[i].first);
			string compare2 = newtable->GetRecord(k)->GetAttr(SharedAttrsIndicies[i].second);
			if(compare1.compare(compare2) != 0)
			{
				newtable->RemoveRecord(k--);
			}
		}
	}
	
	sort(SharedAttrsIndicies.begin(), SharedAttrsIndicies.end(), sort_pair_second);

	for(int i = (int)SharedAttrsIndicies.size()-1; i >= 0 ; i--)
	{
		newtable->DeleteColumn(SharedAttrsIndicies[i].second);
	}

	return newtable;
}
