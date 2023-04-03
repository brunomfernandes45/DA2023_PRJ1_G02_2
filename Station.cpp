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

void Station::setName(std::string name) {
    this -> name = std::move(name);
}

void Station::setDistrict(std::string district) {
    this -> district = std::move(district);
}

void Station::setMunicipality(std::string municipality) {
    this -> municipality = std::move(municipality);
}

void Station::setTownship(std::string township) {
    this -> township = std::move(township);
}

void Station::setLine(std::string line) {
    this -> line = std::move(line);
}
