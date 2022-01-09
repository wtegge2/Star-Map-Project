#include "star_list.h"

void Star_List::insertStar(Star star) {
    Star* s = new Star(star.getName(), star.getX(), star.getY(), star.getZ());
    s->color = star.color;
    stars_.insert(std::pair<std::string, Star*>(star.getName(), s));
}

void Star_List::insertNeighbor(std::string s1, std::string s2) {
    Star* star1 = stars_[s1];
    Star* star2 = stars_[s2];
    float distance = star1->dist(*star2);
    Neighbor* edge = new Neighbor(star1, star2, distance);
    
    neighbors_.push_back(edge);
    star1->neighbors.push_back(edge);
    star2->neighbors.push_back(edge);

}

 void Star_List::removeNeighbor(std::string s1, std::string s2) {
    Star* star1 = stars_[s1];
    Star* star2 = stars_[s2];

    Neighbor* n;
    for (auto it = star1->neighbors.begin(); it != star1->neighbors.end(); it++) {
        if (star1->getNeighbor(*it) == star2) {
            n = *it;
            star1->neighbors.remove(*it);
            break;
        }
    }
    for (auto it = star2->neighbors.begin(); it != star2->neighbors.end(); it++) {
        if (star2->getNeighbor(*it) == star1) {
            star2->neighbors.remove(*it);
            break;
        }
    }

 }
 
 std::list<Star*> Star_List::getNeighbors(std::string star) const {
    std::list<Star*> neighbor;
    Star* s = stars_.at(star);
    for (Neighbor* n: neighbors_) {
        neighbor.push_back(s->getNeighbor(n));
    }
    return neighbor;
 }

 bool Star_List::areNeighbors(std::string s1, std::string s2) const {

     Star* star1 = stars_.at(s1);
    for (Neighbor* n : star1->neighbors) {
        Star* star2 = star1->getNeighbor(n);
        if (star2->getName() == s2) {
            return true;
        }
    }
    return false;
 }

 Star* Star_List::getStar(std::string name) {
     return stars_[name];
 }

 Star_List::Star_List() {

 }

 Star_List::Star_List(const Star_List& other) {
     copy_(other);
 }

 Star_List& Star_List::operator=(Star_List& other) {
     if (this != &other) {
         destroy_();
         copy_(other);
     }
     return *this;
 }

 Star_List::~Star_List() {
     destroy_();
 }

 void Star_List::copy_(const Star_List& other) {

    for (const auto& s : other.stars_) {
        insertStar(*(s.second));
    }

    for (const auto& n : other.neighbors_) {
        insertNeighbor(n->one->getName(), n->two->getName());
    }

 }

 void Star_List::destroy_() {
    for (unsigned i = 0; i < neighbors_.size(); i++) {
        delete neighbors_[i];
    }

    for (auto& star : stars_) {
        delete star.second;
    }
 }
