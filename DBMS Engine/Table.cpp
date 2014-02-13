#include "Table.h"

using namespace std;

//Copy Constructor

Table::Table(Table* _table)
{
	m_Name = _table->GetName();

	for(int i = 0; i < _table->GetNumAttrs(); i++)
	{
		m_Attrs.push_back(_table->GetAttr(i));
	}

	for(int i = 0; i < _table->GetNumKeys(); i++)
	{
		m_Key[_table->GetKeyFirst(i)] = _table->GetKeySecond(i);
	}

	for(int i = 0; i < _table->GetNumRecords(); i++)
	{
		m_Records.push_back(new Record(_table->GetRecord(i)));
	}
}

//Accessor

void
Table::Show() const
{
	cout << setw(5) << "";
	for(int i = 0; i < (int)m_Attrs.size(); i++)
	{
		cout << left << setw(20) << m_Attrs[i];
	}
	
	cout << endl;

	for(int i = 0; i < (int)m_Attrs.size(); i++)
	{
		cout << "--------------------";
	}

	cout << endl;

	for(int i = 0; i < (int)m_Records.size(); i++)
	{
		cout << (i+1) << ".   ";
		for(int k = 0; k < m_Records[i]->GetSize(); k++)
		{
			cout << left << setw(20) << m_Records[i]->GetAttr(k);
		}
		cout << endl;
	}
}

int
Table::GetKeyFirst(int _index) const
{
	typedef map<int, string>::const_iterator Iter;
	Iter iter = m_Key.begin(); 
	for(int i = 0; i < _index; i++)
	{
		iter++;
	}

	return iter->first;
}

string
Table::GetKeySecond(int _index) const
{
	typedef map<int, string>::const_iterator Iter;
	Iter iter = m_Key.begin(); 
	for(int i = 0; i < _index; i++)
	{
		iter++;
	}

	return iter->second;
}

//Mutator
void 
Table::InsertInto(vector<string> _record)
{
	bool duplicate = false;
	typedef map<int, string>::const_iterator Iter;
	for(int k = 0; k < (int)m_Records.size(); k++)
	{
		for(Iter i = m_Key.begin(); i != m_Key.end(); )
		{
			if(m_Records[k]->GetAttr(i->first).compare(_record[i->first]) != 0)
			{
				break;
			}

			else if(m_Records[k]->GetAttr(i->first).compare(_record[i->first]) == 0 && (++i == m_Key.end()))
			{
				duplicate = true;
			}
		}
	}
	
	if(!duplicate) m_Records.push_back(new Record(_record));
}

void
Table::InsertInto(Record* _record)
{
	bool duplicate = false;
	typedef map<int, string>::const_iterator Iter;
	for(int k = 0; k < (int)m_Records.size(); k++)
	{
		for(Iter i = m_Key.begin(); i != m_Key.end(); )
		{
			if(m_Records[k]->GetAttr(i->first).compare(_record->GetAttr(i->first)) != 0)
			{
				break;
			}

			else if(m_Records[k]->GetAttr(i->first).compare(_record->GetAttr(i->first)) == 0 && (++i == m_Key.end()))
			{
				duplicate = true;
			}
		}
	}
	
	if(!duplicate) m_Records.push_back(new Record(_record));
}

void 
Table::Update(const string _attr, vector<string> _condition)
{
	int index = -1;
	for(int i = 0; i < (int)m_Attrs.size(); i++)
	{
		if(_condition[0].compare(m_Attrs[i]) == 0)
		{
			index = i;
			break;
		}
	}
	
	if(index == -1)
	{
		cerr << "Error: Attribute not found" << endl;
		return;
	}
	
	bool noatoi = false;
	for(int i = 0; i < (int)_condition[2].size(); i++)
	{
		if(!isdigit(_condition[2][i]))
		{
			noatoi = true;
		}
	}
	
	int condition = 0;
	if(!noatoi) condition = atoi(_condition[2].c_str());
	
	for(int i = 0; i < (int)m_Records.size(); i++)
	{	
		//cases: == | != | < | > | <= | >=
	
		if(_condition[1].compare("==") == 0) {
			if(!noatoi)
			{
				int compare = atoi(m_Records[i]->GetAttr(index).c_str()); 
				if(compare == condition)
				{
					m_Records[i]->Update(index, _attr);
				}
			}
			
			else
			{
				if(m_Records[i]->GetAttr(index).compare(_condition[2]) == 0)
				{
					m_Records[i]->Update(index, _attr);  
				}
			}	
			
		} else if(_condition[1].compare("!=") == 0) {
			if(!noatoi)
			{
				int compare = atoi(m_Records[i]->GetAttr(index).c_str()); 
				if(compare != condition)
				{
					m_Records[i]->Update(index, _attr);
				}
			}
			
			else
			{
				if(m_Records[i]->GetAttr(index).compare(_condition[2]) != 0)
				{
					m_Records[i]->Update(index, _attr);
				}
			}	
			
		} else if(_condition[1].compare("<") == 0) {
			if(!noatoi)
			{
				int compare = atoi(m_Records[i]->GetAttr(index).c_str()); 
				if(compare < condition)
				{
					m_Records[i]->Update(index, _attr);
				}
			}
			
			else
			{
				if(m_Records[i]->GetAttr(index).compare(_condition[2]) < 0)
				{
					m_Records[i]->Update(index, _attr);
				}
			}	
			
		} else if(_condition[1].compare(">") == 0) {
			if(!noatoi)
			{
				int compare = atoi(m_Records[i]->GetAttr(index).c_str()); 
				if(compare > condition)
				{
					m_Records[i]->Update(index, _attr);
				}
			}
			
			else
			{
				if(m_Records[i]->GetAttr(index).compare(_condition[2]) > 0)
				{
					m_Records[i]->Update(index, _attr);
				}
			}
		
		} else if(_condition[1].compare("<=") == 0) {
			if(!noatoi)
			{
				int compare = atoi(m_Records[i]->GetAttr(index).c_str()); 
				if(compare <= condition)
				{
					m_Records[i]->Update(index, _attr);
				}
			}
			
			else
			{
				if(m_Records[i]->GetAttr(index).compare(_condition[2]) <= 0)
				{
					m_Records[i]->Update(index, _attr);
				}
			}	
			
		} else if(_condition[1].compare(">=") == 0) {
			if(!noatoi)
			{
				int compare = atoi(m_Records[i]->GetAttr(index).c_str()); 
				if(compare >= condition)
				{
					m_Records[i]->Update(index, _attr);
				}
			}
			
			else
			{
				if(m_Records[i]->GetAttr(index).compare(_condition[2]) >= 0)
				{
					m_Records[i]->Update(index, _attr);
				}
			}	
		}
	}
}

void 
Table::DeleteFrom(vector<string> _condition)
{
	int index = -1;
	for(int i = 0; i < (int)m_Attrs.size(); i++)
	{
		if(_condition[0].compare(m_Attrs[i]) == 0)
		{
			index = i;
			break;
		}
	}
	
	if(index == -1)
	{
		cerr << "Error: Attribute not found" << endl;
		return;
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
	
	for(int i = 0; i < (int)m_Records.size(); i++)
	{	
		//cases: == | != | < | > | <= | >=
	
		if(_condition[1].compare("==") == 0) {
			if(!noatoi)
			{
				int compare = atoi(m_Records[i]->GetAttr(index).c_str()); 
				if(compare == condition)
				{
					m_Records.erase(m_Records.begin() + i--);
				}
			}
			
			else
			{
				if(m_Records[i]->GetAttr(index).compare(_condition[2]) == 0)
				{
					m_Records.erase(m_Records.begin() + i--);  
				}
			}	
			
		} else if(_condition[1].compare("!=") == 0) {
			if(!noatoi)
			{
				int compare = atoi(m_Records[i]->GetAttr(index).c_str()); 
				if(compare != condition)
				{
					m_Records.erase(m_Records.begin() + i--);
				}
			}
			
			else
			{
				if(m_Records[i]->GetAttr(index).compare(_condition[2]) != 0)
				{
					m_Records.erase(m_Records.begin() + i--);
				}
			}	
			
		} else if(_condition[1].compare("<") == 0) {
			if(!noatoi)
			{
				int compare = atoi(m_Records[i]->GetAttr(index).c_str());
				if(compare < condition)
				{
					m_Records.erase(m_Records.begin() + i--);
				}
			}
			
			else
			{
				if(m_Records[i]->GetAttr(index).compare(_condition[2]) < 0)
				{
					m_Records.erase(m_Records.begin() + i--);
				}
			}	
			
		} else if(_condition[1].compare(">") == 0) {
			if(!noatoi)
			{
				int compare = atoi(m_Records[i]->GetAttr(index).c_str()); 
				if(compare > condition)
				{
					m_Records.erase(m_Records.begin() + i--);
				}
			}
			
			else
			{
				if(m_Records[i]->GetAttr(index).compare(_condition[2]) > 0)
				{
					m_Records.erase(m_Records.begin() + i--);
				}
			}
		
		} else if(_condition[1].compare("<=") == 0) {
			if(!noatoi)
			{
				int compare = atoi(m_Records[i]->GetAttr(index).c_str()); 
				if(compare <= condition)
				{
					m_Records.erase(m_Records.begin() + i--);
				}
			}
			
			else
			{
				if(m_Records[i]->GetAttr(index).compare(_condition[2]) <= 0)
				{
					m_Records.erase(m_Records.begin() + i--);
				}
			}	
			
		} else if(_condition[1].compare(">=") == 0) {
			if(!noatoi)
			{
				int compare = atoi(m_Records[i]->GetAttr(index).c_str()); 
				if(compare >= condition)
				{
					m_Records.erase(m_Records.begin() + i--);
				}
			}
			
			else
			{
				if(m_Records[i]->GetAttr(index).compare(_condition[2]) >= 0)
				{
					m_Records.erase(m_Records.begin() + i--);
				}
			}	
		}
	}
}

void
Table::DeleteColumn(int _index)
{
	m_Attrs.erase(m_Attrs.begin() + _index);

	for(int i = 0; i < (int)m_Records.size(); i++)
	{
		m_Records[i]->DeleteAttr(_index); 
	}
}