#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <deque>
#include <iostream>
#include <iomanip>
#include <memory>
#include <chrono>
#include <stack>
#include <cstdlib>
#include <algorithm>
#include <random>
#define BOLDBLACK "\033[38;5;0m"      /* Bold Black */
#define BLUE "\033[34m"               /* Blue */
#define BOLDGREEN "\033[1;32m"        /* Bold Green */
#define WHITE "\033[37m"              /* White */
#define RED "\033[31m"                /* Red */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */

class Maze
{
public:
    class Node
    {
    public:
        Node() = default;
        Node(int n);
        Node(Node *node);
        Node(std::vector<int> s);
        ~Node() = default;
        int n{5};
        std::shared_ptr<Node> parent;
        std::vector<std::shared_ptr<Node>> children;
        std::vector<int> state;
        void set_state(std::vector<int> &s);
        void show() const;
        int find_one() const;
        bool move_right(int one_index);
        bool move_left(int one_index);
        bool move_down(int one_index);
        bool move_up(int one_index);
        void expand_node();
        bool is_goal(std::vector<int> s) const;
    };
    int n{5};
    std::vector<int> goal_state;
    Maze() = default;
    ~Maze() = default;
    Maze(int n);
    void set_goal(std::vector<int> gs);
    std::deque<std::shared_ptr<Node>> breadth_first_search(std::shared_ptr<Node> root, int max_depth = 100, bool console_out = true);
    bool contains(std::deque<std::shared_ptr<Node>> list, std::shared_ptr<Node> c);
    void path_trace(std::deque<std::shared_ptr<Node>> &path, std::shared_ptr<Node> node);
    bool contains_DFS(std::stack<std::shared_ptr<Node>> q, std::shared_ptr<Node> n);
    void depth_first_search(Node init, std::vector<int> goalState, int max_depth);
    std::shared_ptr<Node> make_random_maze();
    std::shared_ptr<Node> make_random_maze(int attemps);
};

#endif