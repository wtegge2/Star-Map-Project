#include "star_list.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <list>



void bfs_graph(Star_List& list, std::string start){

    // Clearing previous traversal
    for (auto& s : list.stars_) {
        s.second->visited = false;
        s.second->jump_dist = -1;
    }

    std::queue<Star*> toVisit;

    Star* star1 = list.stars_[start];
    if (!star1->visited) {
        star1->visited = true;
        star1->jump_dist = 0;
        toVisit.push(star1);
    }

    while (!toVisit.empty()) {
        Star* curr = toVisit.front();
        toVisit.pop();

        for (Neighbor* n : curr->neighbors) {
            if (!curr->getNeighbor(n)->visited) {
                curr->getNeighbor(n)->visited = true;
                curr->getNeighbor(n)->jump_dist = curr->jump_dist + 1;
                toVisit.push(curr->getNeighbor(n));
            }
        }

    }

}