#pragma once
#include "InputInfo.h"
#include <unordered_map>

/*
	入力管理に使う情報を持つための基底クラス
	綾部
*/

template <class T>
class InputBase
{
public:
	InputBase() : ctrlNo(0) { infos.clear(); }
	virtual ~InputBase() { infos.clear(); }
	void SetControllerNo(const int& _no) { ctrlNo = _no; }
	virtual void Update() {}

	T GetInfo(const std::string& _name) { return infos[_name]; }

protected:
	void AddInfo(const std::string& _name)
	{
		infos.insert({ _name, T() });
	}
	void AddInfo(const std::string& _name, const int& _type)
	{
		infos.insert({ _name, T()});
		infos[_name].type = _type;
	}

	std::unordered_map<std::string, T> infos;
	int ctrlNo; // パッド情報
};