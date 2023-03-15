//
// Created by Bruno Fernandes on 15/03/2023.
//

#ifndef DA2023_PRJ1_G02_2_STATION_H
#define DA2023_PRJ1_G02_2_STATION_H

#include <string>

class Station {
public:
    Station(std::string name, std::string district, std::string municipality, std::string township, std::string line);

    std::string getName();
    std::string getDistrict();
    std::string getMunicipality();
    std::string getTownship();
    std::string getLine();

    void setName(std::string name);
    void setDistrict(std::string district);
    void setMunicipality(std::string municipality);
    void setTownship(std::string township);
    void setLine(std::string line);

private:
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::string line;

};


#endif //DA2023_PRJ1_G02_2_STATION_H
