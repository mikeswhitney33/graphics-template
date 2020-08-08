#ifndef MATHS_HPP
#define MATHS_HPP

#include "glm/glm.hpp"
#include "glm/gtc/random.hpp"

#include <map>
#include <vector>

typedef enum {FLUID, AIR, SOLID} CellType;

struct Cell {
    float h;
    float p;
    glm::vec3 u;
    int x, y, z;
    int layer;
    CellType type;
    Cell(const glm::vec3 & particle) {
        h = 1;p = 0;u = glm::vec3(0, 0, 0);
        x = particle.x;y = particle.y;z = particle.z;
    }
    Cell():Cell(glm::vec3()) {

    }
};

int hash(const glm::vec3 & particle)
{
    return 541 * particle.x + 79 * particle.y + 31 * particle.z;
}

int hash(int x, int y, int z) {
    return hash(glm::vec3(x, y, z));
}

std::vector<glm::vec3> getNeighborLocs(const glm::vec3 & p)
{
    std::vector<glm::vec3> neighbors = {
        glm::vec3(p.x + 1, p.y, p.z),
        glm::vec3(p.x - 1, p.y, p.z),
        glm::vec3(p.x, p.y + 1, p.z),
        glm::vec3(p.x, p.y - 1, p.z),
        glm::vec3(p.x, p.y, p.z + 1),
        glm::vec3(p.x, p.y, p.z - 1)
    };
    return neighbors;
}

std::vector<glm::vec3> getNeighborLocs(int x, int y, int z) {
    return getNeighborLocs(glm::vec3(x, y, z));
}

std::vector<int> getNeighborHashes(const std::vector<glm::vec3> & particles) {
    std::vector<int> neighbors;
    for(auto it = particles.begin(); it != particles.end();++it)
    {
        neighbors.push_back(hash(*it));
    }
    return neighbors;
}

class FluidSolver {
public:
    void run()
    {
        for(int i = 0;i < 100;i++)
        {
            particles.push_back(glm::linearRand(glm::vec3(-100, -100, -100), glm::vec3(100, 100, 100)));
        }
        update_grid();
    }

private:
    std::vector<glm::vec3> particles;
    std::map<int, Cell> cells;

    bool inBounds(const glm::vec3 & p)
    {
        return true;
    }
    void update_grid() {
        for(auto it = cells.begin();it != cells.end();++it)
        {
            cells[it->first].layer = -1;
        }
        // update cells that currently have fluid in them
        for(auto it = particles.begin();it != particles.end();++it)
        {
            int key = hash(*it);
            if(cells.find(key) == cells.end())
            {
                Cell c(*it);
                c.type = FLUID;
                c.layer = 0;
            }
            else
            {
                cells[key].type = FLUID;
                cells[key].layer = 0;
            }
        }

        // create a buffer zone around the fluid
        for(int i = 1;i < 2;i++)
        {
            for(auto it = cells.begin();it != cells.end();++it) {
                Cell C = it->second;
                if((C.type != FLUID && C.type != AIR) || C.layer != i-1)
                {
                    continue;
                }
                std::vector<glm::vec3> nlocs = getNeighborLocs(C.x, C.y, C.z);

                for(auto Nit = nlocs.begin();Nit != nlocs.end();++Nit)
                {
                    int nkey = hash(*Nit);
                    std::map<int, Cell>::iterator N = cells.find(nkey);
                    if(N != cells.end())
                    {
                        if(N->second.layer == -1 && N->second.type != SOLID)
                        {
                            N->second.layer = i;
                            N->second.type = AIR;
                        }
                        else
                        {
                            Cell n(*Nit);
                            n.layer = i;
                            if(inBounds(*Nit))
                            {
                                n.type = AIR;
                            }
                            else
                            {
                                n.type = SOLID;
                            }
                            cells[nkey] = n;
                        }
                    }
                }
            }
        }

        // delete any cells with layer == -1
        for(std::map<int, Cell>::iterator it = cells.begin();it != cells.end();)
        {
            if(it->second.layer == -1)
            {
                cells.erase(it++);
            }
            else
            {
                ++it;
            }
        }
    }
};

#endif // MATHS_HPP