#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <array>
#include <functional>
#include <cmath>

#include "HtmlTable.hpp"

using testing_signature = std::function<void(std::vector<int>::iterator, std::vector<int>::iterator)>;
using namespace std::literals;

const std::string head{"<!DOCTYPE html>\
<html>\
<head>\
	<style>\
		body {\
			text-align: center;\
		}\
		table {\
			width:100%;\
			border-collapse: collapse;\
		}\
		td, th {\
			border: 1px solid #dddddd;\
		}\
	</style>\
</head>\
<body>\
	<h1>Sorts comparasion</h1>"};
const std::string bottom{"</body>\
</html>"};

auto write_table(const std::array<std::tuple<testing_signature, std::string>, 11>& sorts)
{
	std::ofstream out{"table.html"};
	out << head << std::endl;

	HtmlTable table(5, sorts.size() + 1);
	std::array<std::vector<std::vector<std::string>>, static_cast<size_t>(sequence_type::reversed) + 1> tables;
	for(int type = static_cast<int>(sequence_type::random); type <= static_cast<int>(sequence_type::reversed); ++type) {
		out << "<h2>" << seqttos(static_cast<sequence_type>(type)) << "</h2>";
		table.add_column(std::vector<std::string>{"name"s, "100"s, "1000"s, "10000"s, "100000"s});
		for(const auto & it : sorts) {
			std::vector<std::string> column(5);
			column[0] = std::get<1>(it);
			for(auto i = 1, size = 100; size <= 100000; ++i, size *= 10) {
				std::ifstream in{"./results/"s + std::get<1>(it) + "_"s + std::to_string(size) + "_"s + seqttos(static_cast<sequence_type>(type))};
				std::string str;
				if(!in.eof())
					std::getline(in, str);
				if(str.empty())
					str = "-"s;
				column[i] = std::to_string(std::lround(std::stod(str)));	
			}
			table.add_column(std::move(column));
		}
		out << table;
		tables[type] = table.data();
		table.clear();
	}

	out << bottom << std::endl;
	return tables;
}
