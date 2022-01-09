#include "star_list.h"
#include <algorithm>
#include <queue>

std::vector<std::string> dijikstra(Star_List& list, std::string start_star, std::string end_star) {    
    
    // Clearing results of previous dijktra function call
    for (auto s : list.stars_) {
        Star* star = s.second;
        star->prev_dist = +INFINITY;
        star->prev = NULL;
    }

    Forest forest;
    for (const auto& s : list.stars_) {
        forest.addElement(s.second);
    }
    for (const auto& n : list.neighbors_) {
        forest.setUnion(n->one, n->two);
    }
    if (!forest.compare(list.stars_[start_star], list.stars_[end_star])) {
        return std::vector<std::string>();
    }

    list.stars_[start_star]->prev_dist = 0;

    auto cmp = [](Star* a, Star* b) { return a->prev_dist > b->prev_dist; };
    std::priority_queue<Star*, std::vector<Star*>, decltype(cmp)> queue(cmp);

    for (auto s : list.stars_) {
        queue.push(s.second);
    }

    while (list.stars_[end_star]->prev == NULL) {
        Star* star = queue.top();
        queue.pop();
        for (Neighbor* n : star->neighbors) {
            Star* n_star = star->getNeighbor(n);
            if (n_star->prev == NULL && n->dist + star->prev_dist < n_star->prev_dist) {
                n_star->prev_dist = n->dist + star->prev_dist;
                n_star->prev = star;
                queue.push(n_star);
            }
        }
    }

    std::vector<std::string> journey;
    Star* star = list.stars_[end_star];
    while (star != NULL) {
        journey.push_back(star->getName());
        star = star->prev;
    }
    std::reverse(journey.begin(), journey.end());

    return journey;
    
}
