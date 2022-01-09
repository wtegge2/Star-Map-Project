#pragma once
#include <string>
#include <list>
#include <vector>

struct Neighbor;

struct float2 {
    float x;
    float y;

    float2();
    float2(float setX, float setY);
    float mag();
    void setMag(float f);
    float2 norm();
    float2 operator+(const float2 &f);
    float2 operator-(const float2 &f);
    float2& operator+=(const float2 &f);

};

float2 operator*(float c, const float2 &v);

class Star {

    public:

        //Constructor that sets name and position of Star
        Star(std::string name, float x, float y, float z);
        
        //Returns distance between two stars
        float dist(const Star& other) const;

        //Getters for Star
        std::string getName() const;
        float getX() const;
        float getY() const;
        float getZ() const;
        Star* getNeighbor(Neighbor* neighbor);

        bool operator==(const Star& other);

        //List of Neighbors
        std::list<Neighbor*> neighbors;
        float2 map_pos;
        float2 vel, force;
        std::string color;

        // BFS helper variables
        bool visited;
        int jump_dist;
        
        // Dijkstra helper variables
        Star* prev;
        float prev_dist;


    private:
        std::string name_;
        float x_, y_, z_;
        

};

struct Neighbor {
    Star* one;
    Star* two;
    float dist;
    std::string color;

    Neighbor(Star* first, Star* second, float distance);

    bool operator== (const Neighbor &n) {
        return (*one == *(n.one) && *two == *(n.two));
    }

    std::string getOneName() {
        return one->getName();
    }

    std::string getTwoName() {
        return two->getName();
    }
   
};



//Helper Functions
std::vector<Star> loadStars();
std::string colorRGB(int red, int green, int blue);
