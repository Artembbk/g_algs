#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

template <class Container>
void PrintContainer(const Container& x) {
    for (auto i = x.begin(); i != x.end(); ++i) {
        std::cout << *i << ' ';
    }
    std::cout << std::endl;
}

struct Tower {
    size_t x, y;
    size_t color;
};

void dfs(std::vector<Tower>& towers, size_t color, double radius, Tower now) {
    for (Tower& other : towers) {
        if (other.x == now.x && other.y == now.y) {
            other.color = color;
        }
        else if ((other.x - now.x) * (other.x - now.x) + (other.y - now.y) * (other.y - now.y) <= (2 * radius) * (2 * radius)) {
            if (other.color == 0) dfs(towers, 3 - color, radius, other);
            else if (other.color == color) other.color = 3;
        }
    }
}

int main() {
    size_t n;
    std::cin >> n;
    std::vector<Tower> towers;
    size_t x, y;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> x >> y;
        towers.push_back({ x,y });
    }
    double left = 0;
    double right = 10000;
    size_t i = 0;
    bool is_paintable = true;
    std::vector<size_t> coloring;
    while (i < 100) {
        ++i;
        for (Tower& tower : towers) {
            tower.color = 0;
        }
        double radius = (left + right) / 2;
        dfs(towers, 1, radius, towers[0]);
        is_paintable = true;
        for (Tower& tower : towers) {
            if (tower.color == 3) {
                is_paintable = false;
                break;
            }
        }
        if (is_paintable) {
            coloring.clear();
            for (Tower& tower : towers) coloring.push_back(tower.color);
            left = radius;
        } else {
            right = radius;
        }
    }
    std::cout << std::fixed << std::setprecision(9) << left << '\n';
    for (auto color : coloring) {
        std::cout << color << ' ';
    }
    return 0;
}
