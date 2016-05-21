#ifndef LAZY_STRING_H
#define LAZY_STRING_H

#include <string>
#include <iostream>
#include <memory>

class lazy_string {

private:

	size_t shift, ls_size;
	std::shared_ptr<std::string> data;
	lazy_string(size_t shift, size_t ls_size, std::shared_ptr<std::string> data);

	struct char_str {

	public:
		friend class lazy_string;
		operator char() const;
		char_str &operator=(char);

	private:
		char_str(lazy_string *, size_t);
		const size_t index;
		lazy_string *const lazy_str;
	};

public:
	//Constructors:
	lazy_string();

	lazy_string(const std::string &str);
	


	//Returns length of lazy string:
	size_t size() const;

	size_t length() const;



	//Returns reference to a character at given position  index: 
	char_str operator[](size_t index);

	char operator[](size_t index) const;



	//Returns reference to a character at given position  index. Safe about bounds:
	char_str at(size_t index);

	char at(size_t index) const;



	//Makes std:string copy from current lazy_string:
	operator std::string();



	//Returns substring of lazy_string , starting from start_pos , ending on start_pos + length. Safe about bounds:
	lazy_string substr(size_t start_pos = 0, size_t length = std::string::npos);


	
	//Takes string from input std::istream and replaces ls:
	friend std::istream &operator >> (std::istream &is, lazy_string &ls);



	//Outputs lazy_string:
	friend std::ostream &operator << (std::ostream &os, lazy_string &ls);
};

#endif