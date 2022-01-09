#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "stars.h"
#include "star_list.h"

Star_List load_star_list() {

    //Helper function that loads stars from dataset, and loads them in graph data structure
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

    return star_list;
}

TEST_CASE("Loads Star Dataset Correctly") {

    auto stars = loadStars();

    // Testing whether all stars were loaded properly
    REQUIRE(stars.size() == 133);
    REQUIRE(stars[0].getName() == "Sol");
 
 }

TEST_CASE("Testing Star_List class") {

    auto star_list = load_star_list();

    // Testing whether star_list is inserts stars correctly
    REQUIRE(star_list.stars_.size() == 133);
    REQUIRE(star_list.getStar("Sol")->neighbors.size() == 7);
    REQUIRE(star_list.getStar("Arcturus")->neighbors.size() == 3);

}

TEST_CASE("Testing Forest class") {

    auto star_list = load_star_list();

    Forest forest;
    for (const auto& s : star_list.stars_) {
        forest.addElement(s.second);
    }
    for (const auto& n : star_list.neighbors_) {
        forest.setUnion(n->one, n->two);
    }

    // Testing whether Disjoint Sets will differentiate seperate connected components
    REQUIRE(forest.compare(star_list.getStar("Sol"), star_list.getStar("Sirius")) == true);
    REQUIRE(forest.compare(star_list.getStar("Sol"), star_list.getStar("Vega")) == true);
    REQUIRE(forest.compare(star_list.getStar("Sol"), star_list.getStar("Chara")) == true);

    REQUIRE(forest.compare(star_list.getStar("Sol"), star_list.getStar("Muphrid")) == false);
    REQUIRE(forest.compare(star_list.getStar("Sol"), star_list.getStar("Alderamin")) == false);
    REQUIRE(forest.compare(star_list.getStar("Sol"), star_list.getStar("HR8")) == false);

}

TEST_CASE("Testing Kruskal's Algorithm") {

    auto star_list = load_star_list();

    Star_List* min_tree = kruskal(star_list);

    // Testing whether kruskals creates minimum spanning tree of given star_list
    REQUIRE(min_tree->stars_.size() == 133);
    REQUIRE(min_tree->getStar("Sirius")->neighbors.size() == 3);
    REQUIRE(min_tree->getStar("Epsilon Eridani")->neighbors.size() == 1);

    delete min_tree;

}

TEST_CASE("Testing BFS Traversals") {

    auto star_list = load_star_list();

    // Testing Breadth First Traversal works
    bfs_graph(star_list, "Sol");

    REQUIRE(star_list.getStar("Alpha Centauri")->jump_dist == 1);
    REQUIRE(star_list.getStar("Achird")->jump_dist == 2);
    REQUIRE(star_list.getStar("Keid")->jump_dist == 2);
    REQUIRE(star_list.getStar("Rana")->jump_dist == 3);

    // Testing whether Breadth First Traversal works multiple times
    bfs_graph(star_list, "Sirius");
    REQUIRE(star_list.getStar("Alpha Centauri")->jump_dist == 1);
    REQUIRE(star_list.getStar("Procyon")->jump_dist == 2);
    REQUIRE(star_list.getStar("Vega")->jump_dist == 2);
    REQUIRE(star_list.getStar("p Eridani")->jump_dist == 3);

}

TEST_CASE("Testing Dijkstra's Algorithm") {

    auto star_list = load_star_list();

    auto journey = dijikstra(star_list, "Sol", "Capella");

    // Testing whether Dijkstra's algorithm finds the correct path
    REQUIRE(journey[0] == "Sol");
    REQUIRE(journey[1] == "Sirius");
    REQUIRE(journey[2] == "HR7703");
    REQUIRE(journey[3] == "107 Piscium");
    REQUIRE(journey[4] == "Zavijava");
    REQUIRE(journey[5] == "Al Haud");
    REQUIRE(journey[6] == "HR7162");
    REQUIRE(journey[7] == "I Hydrae");
    REQUIRE(journey[8] == "Capella");

}
