#include <Geode/Geode.hpp>
#include "../headers/spline.hpp"

using namespace geode::prelude;

Spline::Spline(std::string idNew, std::vector<Point> newPoints) : id(idNew), points(newPoints) {}
Spline::Spline(std::string idNew) : id(idNew) {}

