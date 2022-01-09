#include "star_list.h"
#include <queue>

void Forest::addElement(Star* star) {

    keys_[star] = elements_.size();
    elements_.push_back(-1);

}

int Forest::find_(int elem) {

    if (elements_[elem] < 0) {
        return elem;
    }

    int root = find_(elements_[elem]);
    elements_[elem] = root;

    return root;

}

bool Forest::compare(Star* a, Star* b) {
    int elemA = keys_[a];
    int elemB = keys_[b];
    int ra = find_(elemA);
    int rb = find_(elemB);
    return ra == rb;
}


void Forest::setUnion(Star* a, Star* b) {

    int elemA = keys_[a];
    int elemB = keys_[b];
    int ra = find_(elemA);
    int rb = find_(elemB);
    if (ra == rb) {
        return;
    }
    if (elements_[ra] <= elements_[rb]) {
        elements_[ra] = elements_[ra] + elements_[rb];
        elements_[rb] = ra;
    } else {
        elements_[rb] = elements_[ra] + elements_[rb];
        elements_[ra] = rb;
    }

}

Star_List* kruskal(const Star_List& star_list) {

    Star_List* min_tree = new Star_List();
    Forest forest;
    for (const auto& s : star_list.stars_) {
        forest.addElement(s.second);
        min_tree->insertStar(*(s.second));
    }

    auto cmp = [](Neighbor a, Neighbor b) { return a.dist > b.dist; };
    std::priority_queue<Neighbor, std::vector<Neighbor>, decltype(cmp)> queue(cmp);

    for (const auto& n : star_list.neighbors_) {
        queue.push(*n);
    }

    while (min_tree->neighbors_.size() < star_list.stars_.size() - 1 && !queue.empty()) {
        Neighbor n = queue.top();
        queue.pop();
        if (!forest.compare(n.one, n.two)) {
            min_tree->insertNeighbor(n.one->getName(), n.two->getName());
            forest.setUnion(n.one, n.two);
        }
    }

    return min_tree;

}
