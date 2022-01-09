#include "star_list.h"
#include <iostream>
#include <fstream>

void Star_List::gen_map(std::string filename) {

    int num = 750;
    for (int i = 0; i < num; i++) {

        // Apply a force centering nodes to origin (and zeroes force from previous iterations)
        for (auto it = stars_.begin(); it != stars_.end(); it++) {
            Star& star = *(it->second);
            star.force = -0.1 * star.map_pos;  
        }

        // Apply a force creating repulsion between nodes
        for (auto it = stars_.begin(); it != stars_.end(); it++) {
            for (auto jt = std::next(it); jt != stars_.end(); jt++) {
                Star& s1 = *(it->second);
                Star& s2 = *(jt->second);
                float2 dist = s1.map_pos - s2.map_pos;
                float2 force = (dist.mag() != 0) ? -50 * (1.0 / (dist.mag() * dist.mag())) * dist.norm() : float2(0, 0);
                s1.force += -1 * force;
                s2.force += force;
            }
        }

        // Spring between edges
        float error = 0.0;
        for (auto neighbor : neighbors_) {
            Star& s1 = *(neighbor->one);
            Star& s2 = *(neighbor->two);
            float2 dist = s1.map_pos - s2.map_pos;
            error += abs(neighbor->dist - dist.mag());
            float rest_force = -1 * (neighbor->dist - dist.mag());
            s1.force += -1 * rest_force * dist.norm();
            s2.force += rest_force * dist.norm();
        }

        // Update velocities and positions by euler approximation
        for (const auto& s : stars_) {
            Star& star = *(s.second);
            if (star.vel.mag() > 1) {
                star.force += -0.1 * (star.vel.mag() * star.vel.mag()) * star.vel.norm();
            }
            star.vel += 0.1 * star.force;
            if (star.vel.mag() > 100) {
                star.vel.setMag(100);
            }
            star.map_pos += 0.1 * star.vel;
        }

        // Draw Map every 1% through the iterations
        if (filename != "" && i % (num / 100) == 0) {
            std::cout << error / neighbors_.size() << std::endl;
            std::string fname = "map_out/map";
            fname += (i < num / 10) ? "0" + std::to_string(i / (num / 100)) : std::to_string(i / (num / 100));
            fname += ".svg";
            draw_map(fname);
        }
        
    }

    if (filename != "") {
        draw_map(filename);
    }


}

void Star_List::draw_map(std::string filename) {

    std::ofstream out(filename);

    // Boilerplate SVG header
    out << "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width=\"1200pt\" height=\"1200pt\" viewBox=\"0.00 0.00 1200.00 1200.00\">" << std::endl;

    out << "<g id=\"graph0\" class=\"graph\" transform=\"scale(1 1) rotate(0) translate(600 600)\">" << std::endl;

    out << "<title>Map</title>" << std::endl;

    // Drawing Neighbors
    for (const auto& n : neighbors_) {
        Star& star1 = *(n->one);
        Star& star2 = *(n->two);
        std::string name = star1.getName() + "-" + star2.getName();
        float2 from = 12 * star1.map_pos;
        float2 to = 12 * star2.map_pos;

        if (n->color == "none") continue;

        out << "<g id=\"" << name << "\" class=\"edge\">" << std::endl;
        out << "<title>" << name << "</title>" << std::endl;
        out << "<path fill=\"none\" stroke=\"#" << n->color << "\" d=\"M ";
        out << from.x << " " << from.y << " L " << to.x << " " << to.y << "\"/>" << std::endl;
        out << "</g>" << std::endl;
    }

    // Drawing Stars
    for (const auto& star : stars_) {

        std::string name = star.second->getName();
        float2 map = 12 * star.second->map_pos;
        float rx = 24.0 / 1.2, ry = 10.0 / 1.2, font = 8.0 / 1.2;

        out << "<g id=\"" << name  << "\" class=\"node\">" << std::endl;
        out << "<title>" << name << "</title>" << std::endl;

        out << "<ellipse fill=\"#" << star.second->color << "\" stroke=\"#000000\"";
        out << " cx=\"" << map.x << "\" cy=\"" << map.y <<  "\" rx=\"" << rx << "\" ry=\"" << ry << "\"/>" << std::endl;

        out << "<text text-anchor=\"middle\"";
        out << " x=\"" << map.x << "\" y=\"" << map.y + 2.5;
        out << "\" font-family=\"Times,serif\" font-size=\"" << font << "\" fill=\"#000000\">" << name << "</text>" << std::endl;

        out << "</g>" << std::endl;

        
    }

    out << "</g>" << std::endl;
    out << "</svg>" << std::endl;

    out.close();

}