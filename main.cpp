#include "maze.h"

int main()
{
    // Test-BFS ****************************************

    // std::cout << "Started...\n";
    // std::vector<int> root_state, goal_state;
    // root_state =  {-1, -1,  1, -1, -1,
    //                -1, -1,  0, -1, -1,
    //                -1,  0,  0,  0, -1,
    //                -1,  0,  0, -1, -1,
    //                -1,  0, -1, -1,  0};

    // goal_state =  {-1, -1,  0, -1, -1,
    //                -1, -1,  0, -1, -1,
    //                -1,  0,  0,  0, -1,
    //                -1,  0,  0, -1, -1,
    //                -1,  1, -1, -1,  0};

    // root_state = {-1, -1,  1, -1, -1, -1, -1,
    //               -1,  0,  0, -1,  0,  0, -1,
    //               -1,  0, -1, -1,  0, -1, -1,
    //               -1,  0,  0,  0,  0,  0, -1,
    //               -1, -1, -1, -1,  0, -1, -1,
    //               -1, -1, -1, -1,  0, -1, -1};

    // goal_state = {-1, -1,  0,  -1, -1,  -1,  -1,
    //               -1,  0,  0,  -1,  0,   0,  -1,
    //               -1,  0, -1,  -1,  0,  -1,  -1,
    //               -1,  0,  0,   0,  0,   0,  -1,
    //               -1, -1,  0,  -1,  0,  -1,  -1,
    //               -1, -1, -1,  -1,  0,  -1,  -1,
    //               -1, -1, -1,  -1,  1,  -1,  -1};

    // Maze::Node n(root_state);
    // std::cout << n.is_goal(goal_state) << std::endl;
    // Maze m(7);
    // m.set_goal(goal_state);
    // std::shared_ptr<Maze::Node> root_node = std::make_shared<Maze::Node>(root_state);
    // // root_node->set_state(root_state);
    // std::cout << "this\n";
    // auto solution = m.breadth_first_search(root_node, 100);
    // if (solution.size() > 0){
    //     // reversing
    //     solution = std::deque<std::shared_ptr<Maze::Node>>(solution.rbegin(), solution.rend());
    //     for (size_t i{}; i < solution.size(); i++){
    //         std::cout << "\033[1;32m"; // green bold text
    //         std::cout << "Move " << i << std::endl;
    //         solution[i]->show();
    //     }
    //     std::cout << "\033[0m\n"; // rest to default
    // }
    // else{
    //     std::cout << "\033[1;31m"; // red bold text
    //     std::cout << "No path to solution is found...\n";
    //     std::cout << "\033[0m\n"; // rest to default
    // }
    // *************************************************

    // Test-DFS ****************************************

    // std::vector<int> root_state, goal_state;
    // root_state = {-1, -1,  1, -1, -1, -1, -1,
    //               -1,  0,  0, -1,  0,  0, -1,
    //               -1,  0, -1, -1,  0, -1, -1,
    //               -1,  0,  0,  0,  0,  0, -1,
    //               -1, -1, -1, -1,  0, -1, -1,
    //               -1, -1, -1, -1,  0, -1, -1};

    // goal_state = {-1, -1,  0,  -1, -1,  -1,  -1,
    //               -1,  0,  0,  -1,  0,   0,  -1,
    //               -1,  0, -1,  -1,  0,  -1,  -1,
    //               -1,  0,  0,   0,  0,   0,  -1,
    //               -1, -1,  0,  -1,  0,  -1,  -1,
    //               -1, -1, -1,  -1,  0,  -1,  -1,
    //               -1, -1, -1,  -1,  1,  -1,  -1};

    // Maze m(7);
    // Maze::Node n(root_state);
    // m.depth_first_search(n, goal_state, 23);

    //**************************************************

    int dimension{};
    std::cout << RED << "Welcome to the maze royal :D" << WHITE << std::endl;
    std::cout << BOLDMAGENTA << "Please input the dimension of your maze : " << WHITE;
    std::cin >> dimension;
    std::cout << '\n';
    int input_key0{};
    std::cout << BOLDCYAN << "Well we have to ways to solve your maze !" << WHITE << '\n'
              << BOLDMAGENTA << "1)Use" << RED << " BFS" << BOLDMAGENTA << " algorithm to solve your maze" << WHITE << '\n'
              << BOLDMAGENTA << "2)Use" << RED << " DFS" << BOLDMAGENTA << " algorithm to solve your maze" << WHITE << '\n'
              << BOLDCYAN << "(Please input just " << RED << "1" << BOLDCYAN << " Or" << RED << " 2" << BOLDCYAN << " !)" << '\n'
              << BOLDCYAN << "Input number : " << WHITE;
    std::cin >> input_key0;
    if (input_key0 != 1 && input_key0 != 2)
    {
        while (true)
        {
            std::cerr << BOLDCYAN << "Eror ! No matching input ! Please input" << RED << " 1" << BOLDCYAN << " Or " << RED << "2 " << BOLDCYAN << "!" << WHITE << std::endl;
            std::cout << BOLDCYAN << "Input Again : " << WHITE;
            std::cin >> input_key0;
            std::cout << std::endl;
            if (input_key0 == 1 || input_key0 == 2)
                break;
        }
    }
    // Attemps to make random solvable maze!
    int attemps = 100;
    
    if (input_key0 == 1)
    {
        // ***************************************
        //Create Random Maze
        Maze m(dimension);
        auto root_node = std::make_shared<Maze::Node>(dimension);
        root_node = m.make_random_maze(attemps);
        auto goal_node = std::make_shared<Maze::Node>(dimension);
        goal_node->set_state(m.goal_state);
        std::cout << "Start:\n\n";
        root_node->show();
        std::cout << "End:\n\n";
        goal_node->show();
        std::cout << BOLDMAGENTA << "Press <any key + Enter> to start solution!\n";
        char any_key;
        std::cin >> any_key;
        auto solution = m.breadth_first_search(root_node, 100);
        if (solution.size() > 0)
        {
            // reversing
            solution = std::deque<std::shared_ptr<Maze::Node>>(solution.rbegin(), solution.rend());
            for (size_t i{}; i < solution.size() / 2; i++)
            {
                std::cout << "\033[1;32m"; // green bold text
                std::cout << "Move " << i << std::endl;
                solution[i]->show();
            }
            std::cout << "\033[0m\n"; // rest to default
        }
        else
        {
            std::cout << "\033[1;31m"; // red bold text
            std::cout << "No path to solution is found...\n";
            std::cout << "\033[0m\n"; // rest to default
        }

        // ***************************************
    }
    if (input_key0 == 2)
    {
        Maze m(dimension);
        Maze::Node root_node(dimension);
        root_node.set_state(m.make_random_maze(attemps)->state);
        auto goal_node = std::make_shared<Maze::Node>(dimension);
        goal_node->set_state(m.goal_state);
        std::cout << "Start:\n\n";
        root_node.show();
        std::cout << "End:\n\n";
        goal_node->show();
        std::cout << BOLDMAGENTA << "Press <any key + Enter> to start solution!\n";
        char any_key;
        std::cin >> any_key;
        m.depth_first_search(&root_node, m.goal_state, 23);
    }
    return 0;
}