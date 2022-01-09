#pragma once
#include "stars.h"
#include <unordered_map>

class Star_List {

    public:
        //Stars are accessed by a string containing their name
        void insertStar(Star star);
        void insertNeighbor(std::string s1, std::string s2);
        void removeNeighbor(std::string s1, std::string s2);
        std::list<Star*> getNeighbors(std::string star) const;
        bool areNeighbors(std::string s1, std::string s2) const;
        Star* getStar(std::string name);

        // Generates the positions of the stars on the map
        void gen_map(std::string filename);
        // Draws Map as an SVG file
        void draw_map(std::string filename);

        Star_List();
        Star_List(const Star_List& other);
        Star_List& operator=(Star_List& other);
        ~Star_List();

        std::unordered_map<std::string, Star*> stars_;
        std::vector<Neighbor*> neighbors_;

    private:

        void copy_(const Star_List& other);
        void destroy_();

};

Star_List* kruskal(const Star_List& star_list);
void bfs_graph(Star_List& list, std::string star);
std::vector<std::string> dijikstra(Star_List& list, std::string start_star, std::string end_star);
class Forest {
    public:
        void addElement(Star* star);
        void setUnion(Star* a, Star* b);
        bool compare(Star* a, Star* b);
    private:
        int find_(int elem);
        std::unordered_map<Star*, int> keys_;
        std::vector<int> elements_;
};

