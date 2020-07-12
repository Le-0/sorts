#pragma once

#include <string>
#include <list>
#include <vector>
#include <fstream>

using namespace std::literals;

static const std::list<std::string> templates = 
{
	"<!DOCTYPE html>\
<html>\
 <head>\
  <meta charset=\"utf-8\">\
  <title>Graphics</title>\
  <script src=\"https://www.google.com/jsapi\"></script>\
  <script>\
   google.load(\"visualization\", \"1\", {packages:[\"corechart\"]});\
   google.setOnLoadCallback(drawChart);\
   function drawChart() {\
    var data = google.visualization.arrayToDataTable([\
     ['type', "s,
	"],\
     ['random', "s, 
	"],\
     ['sorted', "s,
	"],\
     ['reversed', "s,
	"]\
    ]);\
    var options = {\
     title: 'Sorts comparasion(100)',\
     hAxis: {title: 'type'},\
     vAxis: {title: 'microseconds'}\
    };\
    var chart = new google.visualization.ColumnChart(document.getElementById('100'));\
    chart.draw(data, options);\
   }\
  </script>\
  <script>\
   google.load(\"visualization\", \"1\", {packages:[\"corechart\"]});\
   google.setOnLoadCallback(drawChart);\
   function drawChart() {\
    var data = google.visualization.arrayToDataTable([\
     ['type', "s,
	"],\
     ['random', "s,
	"],\
     ['sorted', "s,
	"],\
     ['reversed', "s,
	"]\
    ]);\
    var options = {\
     title: 'Sorts comparasion(1000)',\
     hAxis: {title: 'type'},\
     vAxis: {title: 'microseconds'}\
    };\
    var chart = new google.visualization.ColumnChart(document.getElementById('1000'));\
    chart.draw(data, options);\
   }\
  </script>\
  <script>\
   google.load(\"visualization\", \"1\", {packages:[\"corechart\"]});\
   google.setOnLoadCallback(drawChart);\
   function drawChart() {\
    var data = google.visualization.arrayToDataTable([\
     ['type', "s,
	"],\
     ['random', "s,
	"],\
     ['sorted', "s,
	"],\
     ['reversed', "s,
	"]\
    ]);\
    var options = {\
     title: 'Sorts comparasion(10000)',\
     hAxis: {title: 'type'},\
     vAxis: {title: 'microseconds'}\
    };\
    var chart = new google.visualization.ColumnChart(document.getElementById('10000'));\
    chart.draw(data, options);\
   }\
  </script>\
  <script>\
   google.load(\"visualization\", \"1\", {packages:[\"corechart\"]});\
   google.setOnLoadCallback(drawChart);\
   function drawChart() {\
    var data = google.visualization.arrayToDataTable([\
     ['type', "s,
	"],\
     ['random', "s,
	"],\
     ['sorted', "s,
	"],\
     ['reversed', "s,
	"]\
    ]);\
    var options = {\
     title: 'Sorts comparasion(100000)',\
     hAxis: {title: 'type'},\
     vAxis: {title: 'microseconds'}\
    };\
    var chart = new google.visualization.ColumnChart(document.getElementById('100000'));\
    chart.draw(data, options);\
   }\
  </script>\
 </head>\
 <body>\
  <div id=\"100\"></div>\
  <div id=\"1000\"></div>\
  <div id=\"10000\"></div>\
  <div id=\"100000\"></div>\
 </body>\
 </html>"s
};

void draw_graphic(std::array<std::vector<std::vector<std::string>>, 3>&& tables)
{
	auto temp = std::begin(templates);
	std::string graph = *temp++;
	
	for(auto & table : tables) {
		table.erase(std::begin(table));
	}
	for(auto i = 0; i < 4; ++i) {
		for(auto & column : tables[0])
			graph += "\""s + column[0] + "\", "s;
		graph += *temp++;
		for(auto & table : tables) {
			for(auto & column : table)
				graph += column[i + 1] + ", "s;
			graph += *temp++;
		}
	}

	std::ofstream out("graphic.html"s);
	out << graph;
}
