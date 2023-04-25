#include <chrono>
#include <fstream>
#include <iostream>
#include <string>


#include "date/date.h"
#include "nlohmann/json.hpp"
#include <boost/date_time.hpp>

#include "internship.h"

using json = nlohmann::json;
using namespace date;
using namespace std::chrono;


namespace internship {
	struct info
	{
		std::string str1;
		std::string str2;
		int int1;
	};



	int calculateEOL(std::string releaseDate, std::string eolDate)
	{
		boost::gregorian::date release(boost::gregorian::from_simple_string(releaseDate));
		boost::gregorian::date eol(boost::gregorian::from_simple_string(eolDate));
		boost::gregorian::date_duration duration = eol - release;
		int days = duration.days();
		return days;
	}


	void function(const std::string& jsonFileName, int elementsCount) {
		std::ifstream f(jsonFileName);
		json data = json::parse(f);

		info* table = new info[elementsCount];
		info temp = { " ", " ", 0 };

		for (const auto& [id, product] : data.items()) {
			auto versions = product["versions"];

			if (product["os"]) {

				for (const auto& version : versions) {
					std::string releaseDate = version["releaseDate"].get<std::string>().substr(0, version["releaseDate"].get<std::string>().length());
					std::string eolDate = version["eol"].get<std::string>().substr(0, version["eol"].get<std::string>().length());

					temp = { product["name"],version["cycle"],calculateEOL(releaseDate,eolDate) };

					for (int i = 0; i < elementsCount; i++)
					{
						if (table[i].int1 < temp.int1)
						{
							table[i] = temp;
							break;
						}
						
					}
					
				}
			}
		}
		for(int i=0;i<elementsCount;i++)
		{
						std::cout << table[i].str1 << " " << table[i].str2 << " " << table[i].int1 << std::endl;
		}
		delete[] table;
	}

			// do not remove this function
	void solution(const std::string& jsonFileName, int elementsCount) {
		function(jsonFileName, elementsCount);
	}
			
}