#include "Record.h"

using namespace std;

Record::Record(Record* _record)
{
	for(int i = 0; i < _record->GetSize(); i++)
	{
		m_Attrs.push_back(_record->GetAttr(i));
	}
}

bool Record::Equals(Record* _record)
{
	for(int i = 0; i < GetSize(); i++)
	{
		if(GetAttr(i).compare(_record->GetAttr(i)) != 0)
		{
			break;
		}

		else if(GetAttr(i).compare(_record->GetAttr(i)) == 0 && i == GetSize()-1)
		{
			return true;
		}
	}

	return false;
}
