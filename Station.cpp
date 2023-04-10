#include "Station.h"

#include <utility>

Station::Station(std::string name, std::string district, std::string municipality, std::string township, std::string line) {
    this -> name = std::move(name);
    this -> district = std::move(district);
    this -> municipality = std::move(municipality);
    this -> township = std::move(township);
    this -> line = std::move(line);
}

std::string Station::getName() {
    return name;
}

std::string Station::getDistrict() {
    return district;
}

std::string Station::getMunicipality() {
    return municipality;
}

std::string Station::getTownship() {
    return township;
}

std::string Station::getLine() {
    return line;
}
