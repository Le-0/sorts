#pragma once

#include <vector>
#include <string>
#include <exception>

class HtmlTable {
	std::vector<std::vector<std::string>> table;
	const unsigned int length;
public:
	HtmlTable(unsigned int length, unsigned int width = 0) : table{}, length{length}
	{
		table.reserve(width);
	}
	void add_column(std::vector<std::string>&& column)
	{
	    if(column.size() <= length)
		    table.emplace_back(column);
		else
		    throw std::invalid_argument{"column cannot have size more than length"};
	}
	void clear()
	{
		table.clear();
	}
	friend std::ostream& operator<<(std::ostream& out, const HtmlTable& table)
	{
		out << "\n<table>\n<tr>\n";
		for(const auto & column : table.table)
			out << "\t<th>" << column[0] << "</th>\n";
		out << "</tr>\n";
		for(auto i = 1; i < table.length; ++i) {
			out << "<tr>\n";
			for(const auto & column : table.table) {
			    try {
			        auto elem = column.at(i);
			        out << "\t<td>" << elem << "</td>\n";
			    }
			    catch(std::out_of_range&) {
			        out << "\t<td>-</td>\n";
			    }
			}
			out << "</tr>\n";
		}
		out << "</table>\n";
		return out;

	}
};
