#include "stars.h"
#include <cmath>
#include <fstream>
#include <sstream>

float2::float2() {
    x = 0;
    y = 0;
}


float2::float2(float setX, float setY) {
    x = setX;
    y = setY;
}

float float2::mag() {
    return sqrt(x*x + y*y);
}

void float2::setMag(float f) {
    if (mag() == 0) {
        x = 0;
        y = 0;
    } else {
        *this = (f / mag()) * (*this);
    }
}

float2 float2::norm() {
    float m = mag();
    if (m != 0) {
        return float2(x / m, y / m);
    }
    return float2(0, 0);
}

float2 float2::operator+(const float2 &f) {
    float2 r(0, 0);
    r.x = x + f.x;
    r.y = y + f.y;
    return r;
}

float2 float2::operator-(const float2 &f) {
    float2 r(0, 0);
    r.x = x - f.x;
    r.y = y - f.y;
    return r;
}

float2& float2::operator+=(const float2 &f) {
    x += f.x;
    y += f.y;
    return *this;
}

float2 operator*(float c, const float2 &v) {
    float2 r(0, 0);
    r.x = c * v.x;
    r.y = c * v.y;
    return r;
}


Star::Star(std::string name, float x, float y, float z) {

    name_ = name;
    x_ = x;
    y_ = y;
    z_ = z;
    map_pos.x = x * 1;
    map_pos.y = y * 1;
    vel.x = 0, vel.y = 0;
    force.x = 0, force.y = 0;
    color = colorRGB(255, 255, 255);

}

bool Star::operator==(const Star& other) {
    return name_ == other.name_;
}


float Star::dist(const Star& other) const {

    return sqrt((x_ - other.x_)*(x_ - other.x_) + 
                (y_ - other.y_)*(y_ - other.y_) + 
                (z_ - other.z_)*(z_ - other.z_));

}

std::string Star::getName() const {
    return name_;
}

float Star::getX() const {
    return x_;
}

float Star::getY() const {
    return y_;
}

float Star::getZ() const {
    return z_;
}

Star* Star::getNeighbor(Neighbor* neighbor) {
    return neighbor->one->getName() != name_ ? neighbor->one : neighbor->two;
}

Neighbor::Neighbor(Star* first, Star* second, float distance) {
    one = first;
    two = second;
    dist = distance;
    color = colorRGB(0, 0, 0);
}

std::string colorRGB(int red, int green, int blue) {

    red = red < 0 ? 0 : red;
    red = red > 255 ? 255 : red;
    green = green < 0 ? 0 : green;
    green = green > 255 ? 255 : green;
    blue = blue < 0 ? 0 : blue;
    blue = blue > 255 ? 255 : blue;

    std::stringstream stream;
    stream << std::hex << red;
    std::string r = stream.str();
    r = r.size() == 1 ? '0' + r : r;
    stream.str("");
    stream << std::hex << green;
    std::string g = stream.str();
    g = g.size() == 1 ? '0' + g : g;
    stream.str("");
    stream << std::hex << blue;
    std::string b = stream.str();
    b = b.size() == 1 ? '0' + b : b;
    stream.str("");
    return r + g + b;

}

std::string trim(std::string str) {

   int start = 0, end = str.size() - 1;
   while (str[start++] == ' ');
   while (str[end--] == ' ');
   start--, end++;

   if (start > end) {
       return "";
   }

   return str.substr(start, end - start + 1); 

}

std::vector<std::string> loadFile(std::string filename) {

    std::vector<std::string> lines;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
    }

    return lines;

}

std::vector<Star> loadStars() {

    std::vector<Star> stars;
    auto lines = loadFile("star_data.txt");
    for (const auto& line : lines) {
        
        std::string name = trim(line.substr(0, 25));
        std::string proper_name = "";
        if (line.size() > 108) {
            proper_name = trim(line.substr(108, 15));
        }
        name = proper_name != "" ? proper_name : name;

        float ra_hours = std::stof(trim(line.substr(25, 3)));
        float ra_min = std::stof(trim(line.substr(28, 5)));
        float dec_deg = std::stof(trim(line.substr(33, 4)));
        float dec_min = std::stof(trim(line.substr(37, 3)));
        float dist = std::stof(trim(line.substr(92, 6)));

        float ra = ra_hours * 15 + ra_min / 4;
        float dec = (dec_deg >= 0) ? dec_deg + dec_min / 60 : 
        dec_deg - dec_min / 60;

        float x = cos(ra)*cos(dec)*dist;
        float y = sin(ra)*cos(dec)*dist;
        float z = sin(dec)*dist;

        Star star(name, x, y, z);
        stars.push_back(star);

    }

    return stars;

}
