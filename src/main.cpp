#include <iostream>
#include "stars.h"
#include "star_list.h"

int main() {

    auto stars = loadStars();
    Star_List star_list;

    for (const auto& star : stars) {
        star_list.insertStar(star);
    }

    for (auto i = stars.begin(); i != stars.end(); i++) {
        for (auto j = i + 1; j != stars.end(); j++) {
            if (i->dist(*j) < 15) {
                star_list.insertNeighbor(i->getName(), j->getName());
            }
        }
    }

    Forest forest;
    for (const auto& s : star_list.stars_) {
        forest.addElement(s.second);
    }
    for (const auto& n : star_list.neighbors_) {
        forest.setUnion(n->one, n->two);
    }

    bfs_graph(star_list, "Sol");
    auto journey = dijikstra(star_list, "Sol", "Capella");
    for (auto n : journey) {
        std::cout << n << std::endl;
    }

    Star* sol = star_list.getStar("Sol");
    for (auto& s : star_list.stars_) {
        Star* star = s.second;
        int col = 255 - 16 * star->neighbors.size();
        star->color = colorRGB(col, col, 255);
        if (!forest.compare(star, sol)) {
            star->color = colorRGB(255, col - 75, col - 75);
        }
        if (star->jump_dist == 2) {
            star->color = colorRGB(255, 255, 0);
        }
        if (std::find(journey.begin(), journey.end(), star->getName()) != journey.end()) {
            star->color = colorRGB(50, 205, 50);
        }
    }

    for (auto& n : star_list.neighbors_) {
        n->color = colorRGB(15 * n->dist, 15 * n->dist, 15 * n->dist);
        if (std::find(journey.begin(), journey.end(), n->one->getName()) != journey.end()
            && std::find(journey.begin(), journey.end(), n->two->getName()) != journey.end()) {
                n->color = colorRGB(50, 205, 50);
            }
    }

    star_list.gen_map("");
    star_list.draw_map("map_out/15.svg");


}