#ifndef RECORD_H_
#define RECORD_H_

#include <vector>

using namespace std;

class Record {
public:

	//Constructors
	Record(vector<string> _attrs) :
		m_Attrs(_attrs) {}
	Record(Record* _record);
	~Record() {}

	//Accessors
	string GetAttr(int index) { return m_Attrs[index]; }
	int GetSize() { return m_Attrs.size(); }
	bool Equals(Record* _record);

	//Mutators
	void Update(int _index, string _attr) { m_Attrs[_index] = _attr; }
	void DeleteAttr(int _index) { m_Attrs.erase(m_Attrs.begin() + _index); }

private:
	vector<string>  m_Attrs;
};

#endif
