#include "maze.h"

Maze::Maze(int n) : n(n) {}

Maze::Node::Node(int n) : n(n) {}

Maze::Node::Node(Node *node)
{
    n = node->n;
    set_state(node->state);
    parent = node->parent;
    children = node->children;
}

Maze::Node::Node(std::vector<int> s)
{
    state = s;
}

void Maze::Node::set_state(std::vector<int> &s)
{
    state = s;
}

void Maze::Node::show() const
{
    // int one_andis{find_one()};
    // if (one_andis < n){
    //     for (int i{-1}; i < n + 1; i++){
    //         if (i == one_andis){
    //             std::cout << BOLDGREEN << std::setw(3) << " ";
    //         }
    //         else{
    //             std::cout << BOLDGREEN << std::setw(3) << "|||";
    //         }
    //     }
    // }
    // else{
        for (int i{-1}; i < n + 1; i++){
            std::cout << BOLDGREEN << std::setw(3) << "|||";
        }
    // }
    std::cout << std::endl;
    for (size_t i{}; i < n; i++)
    {
        std::cout << BOLDGREEN << std::setw(3) << "|||";
        for (size_t j{}; j < n; j++)
        {
            switch (state[n * i + j])
            {
            case -1:
                std::cout << BOLDCYAN << std::setw(3) << "|||";
                break;

            case 0:
                std::cout << std::setw(3) << " ";
                break;

            default:
                std::cout << BOLDRED << std::setw(3) << " @ ";
                break;
            }
        }
        std::cout << BOLDGREEN << std::setw(3) << "|||";
        std::cout << std::endl;
    }
    // if (one_andis > n * (n - 1)){
    //     for (int i{-1}; i < n + 1; i++){
    //         if (i == one_andis % n){
    //             std::cout << BOLDGREEN << std::setw(3) << " ";
    //         }
    //         else{
    //             std::cout << BOLDGREEN << std::setw(3) << "|||";
    //         }
    //     }
    // }
    // else{
        for (int i{-1}; i < n + 1; i++){
            std::cout << BOLDGREEN << std::setw(3) << "|||";
        }
    // }
    std::cout << WHITE << std::endl;
    std::cout << std::endl;
}

int Maze::Node::find_one() const
{
    for (size_t i{}; i < n; i++)
    {
        for (size_t j{}; j < n; j++)
        {
            if (state[n * i + j] == 1)
            {
                return n * i + j;
            }
        }
    }
    return -1;
}

bool Maze::Node::move_right(int one_index)
{
    if (one_index % n < n - 1)
    {
        if (state[one_index + 1] == 0)
        {
            std::shared_ptr<Node> temp = std::make_shared<Node>(this);
            temp->state[one_index] = 0;
            temp->state[one_index + 1] = 1;
            children.push_back(temp);
            temp->parent = std::make_shared<Node>(this);
            return true;
        }
    }
    return false;
}

bool Maze::Node::move_left(int one_index)
{
    if (one_index % n > 0)
    {
        if (state[one_index - 1] == 0)
        {
            std::shared_ptr<Node> temp = std::make_shared<Node>(this);
            temp->state[one_index] = 0;
            temp->state[one_index - 1] = 1;
            children.push_back(temp);
            temp->parent = std::make_shared<Node>(this);
            return true;
        }
    }
    return false;
}

bool Maze::Node::move_down(int one_index)
{
    if (one_index < n * (n - 1))
    {
        if (state[one_index + n] == 0)
        {
            std::shared_ptr<Node> temp = std::make_shared<Node>(this);
            temp->state[one_index] = 0;
            temp->state[one_index + n] = 1;
            children.push_back(temp);
            temp->parent = std::make_shared<Node>(this);
            return true;
        }
    }
    return false;
}

bool Maze::Node::move_up(int one_index)
{
    if (one_index > n - 1)
    {
        if (state[one_index - n] == 0)
        {
            std::shared_ptr<Node> temp = std::make_shared<Node>(this);
            temp->state[one_index] = 0;
            temp->state[one_index - n] = 1;
            children.push_back(temp);
            temp->parent = std::make_shared<Node>(this);
            return true;
        }
    }
    return false;
}

void Maze::Node::expand_node()
{
    int x = find_one();
    move_right(x);
    move_left(x);
    move_down(x);
    move_up(x);
}

bool Maze::Node::is_goal(std::vector<int> s) const
{
    bool is_goal{1};
    for (int i{}; i < n * n; i++)
    {
        is_goal = is_goal && ((state[i] == s[i]) ? 1 : 0);
    }
    return is_goal;
}

void Maze::set_goal(std::vector<int> gs)
{
    goal_state = gs;
}

std::deque<std::shared_ptr<Maze::Node>> Maze::breadth_first_search(std::shared_ptr<Node> root, int max_depth, bool console_out)
{
    auto start = std::chrono::high_resolution_clock::now();
    if (root->is_goal(goal_state))
    {
        return std::deque<std::shared_ptr<Node>>{root};
    }

    int depth{};
    std::deque<std::shared_ptr<Node>> path_to_solution{};
    std::deque<std::shared_ptr<Node>> open_list{};
    std::deque<std::shared_ptr<Node>> closed_list{};

    open_list.push_back(root);
    bool goal_reached{false};

    int count{1};
    while (open_list.size() > 0 && !goal_reached && depth < max_depth)
    {
        auto between = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed{between - start};
        if (elapsed.count() >= count)
        {
            if (console_out){
                std::cout << "\033[1;32m";    // green bold text
                std::cout << "\033[A\033[2K"; // remove last line
                std::cout << std::setw(4) << count << "s >> solving... please wait!\n";
            }
            count++;
        }
        std::shared_ptr<Node> current_node = open_list.front();
        closed_list.push_back(current_node);
        open_list.pop_front();

        current_node->expand_node();

        for (size_t i{}; i < current_node->children.size(); i++)
        {
            std::shared_ptr<Node> current_child = current_node->children[i];

            if (current_child->is_goal(goal_state))
            {
                if (console_out){
                    std::cout << "\033[A\033[2K"; // remove last line
                    std::cout << "\033[1;35m";    // magneta bold text
                    std::cout << "\n*************\n";
                    std::cout << "Goal reached!\n";
                    std::cout << "*************\n";
                    std::cout << "\033[0m\n"; // rest to default
                }
                goal_reached = true;
                // Tracing path
                path_trace(path_to_solution, current_child);
            }

            if (!contains(open_list, current_child) && !contains(closed_list, current_child))
            {
                open_list.push_back(current_child);
            }
        }

        // depth calculating
        std::shared_ptr<Node> temp_node = current_node;
        depth = 0;
        while (temp_node->parent != nullptr)
        {
            temp_node = temp_node->parent;
            depth++;
        }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed{finish - start};
    if (console_out){
        std::cout << "\033[1;32m"; // green bold text
        std::cout << "\n>> Elapsed time: " << elapsed.count() * 1000 << " ms\n\n";
        std::cout << "\033[0m\n"; // rest to default
    }
    return path_to_solution;
}

bool Maze::contains(std::deque<std::shared_ptr<Node>> list, std::shared_ptr<Node> c)
{
    bool contains = false;
    for (size_t i{}; i < list.size(); i++)
    {
        if (list[i]->is_goal(c->state))
        {
            contains = true;
        }
    }
    return contains;
}

void Maze::path_trace(std::deque<std::shared_ptr<Node>> &path, std::shared_ptr<Node> node)
{
    std::cout << "Tracing path...\n";
    std::shared_ptr<Maze::Node> current = node;
    path.push_back(current);

    while (current->parent != nullptr)
    {
        current = current->parent;
        path.push_back(current);
    }
}

bool Maze::contains_DFS(std::stack<std::shared_ptr<Node>> q, std::shared_ptr<Node> n)
{
    bool exist = false;
    while (!q.empty())
    {
        if (q.top()->state == n->state)
            exist = true;
        q.pop();
    }
    return exist;
}

void Maze::depth_first_search(Node init, std::vector<int> goalState, int max_depth)
{
    std::stack<std::shared_ptr<Node>> openList;
    std::stack<std::shared_ptr<Node>> closedList;
    openList.push(std::shared_ptr<Node>(&init));
    bool goalFound = false;
    int count0{0};
    std::vector<std::shared_ptr<Node>> solution;
    std::vector<std::shared_ptr<Node>> vecForCheck;
    std::cout << "Searching for Depth First Search algorithm ..." << std::endl;
    while (!openList.empty() && !goalFound)
    {
        std::shared_ptr<Node> currentNode = openList.top();
        closedList.push(currentNode);
        openList.pop();
        currentNode->expand_node();
        for (auto i : currentNode->children)
        {
            std::shared_ptr<Node> currentChild = i;
            if (currentChild->is_goal(goalState))
            {
                std::cout << "\033[A\033[2K"; // remove last line
                std::cout << "\033[1;35m";    // magneta bold text
                std::cout << "\n*************\n";
                std::cout << "Goal reached!\n";
                std::cout << "*************\n";
                std::cout << "\033[0m\n"; // rest to default
                std::shared_ptr<Node> curr = currentChild;
                int count{0};
                solution.push_back(currentChild);
                while (curr->parent != NULL)
                {
                    count++;
                    curr = curr->parent;
                    solution.push_back(curr);
                }
                std::reverse(solution.begin(), solution.end());
                for (size_t i{}; i < solution.size(); i++)
                {
                    std::cout << "\033[1;32m"; // green bold text
                    std::cout << "Move " << i << std::endl;
                    solution[i]->show();
                }
                std::cout << "\033[0m\n"; // rest to default
                std::cout << "\033[38;5;12mNo. of depths : " << count << WHITE << std::endl;
                goalFound = true;
            }
            if (!currentChild->is_goal(goalState))
            {
                int count1{0};
                std::shared_ptr<Node> curr = currentChild;
                while (curr->parent != NULL)
                {
                    count1++;
                    curr = curr->parent;
                }
                if (count1 > max_depth)
                {
                    currentNode = openList.top();
                    openList.pop();
                    if (openList.empty())
                    {
                        std::cout << "\033[1m\033[31mFound no answer until depth you have entered :(\033[37m" << std::endl;
                        std::cout << '\n';
                        goalFound = true;
                        break;
                    }
                }
            }
            if (!contains_DFS(openList, currentChild) && !contains_DFS(closedList, currentChild))
            {
                openList.push(currentChild);
            }
        }
        count0++;
    }
    std::cout << "\033[38;5;4mNo. of nodes in closed list: " << count0 << WHITE << std::endl;
    std::cout << '\n';
}

std::shared_ptr<Maze::Node> Maze::make_random_maze()
{
    std::vector<int> state;
    for (int i{}; i < n * n; i++)
    {
        state.push_back(0);
    }
    Node node(n);
    node.set_state(state);
    srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    for (int i{}; i < n * n; i++)
    {
        if (state[i] != 1 && state[i] != 2)
        {
            state[i] = -(rand() % 2);
        }
    }
    // Set ending element
    int cnt{};
    for (int i{}; i < n; i++)
    {
        if (state[i + n * (n - 1)] == 0)
        {
            cnt++;
        }
    }
    if (cnt == 0)
    {
        state[rand() % n + n * (n - 1)] = 1;
    }
    else
    {
        cnt = rand() % cnt;
        for (int i{}; i < n; i++)
        {
            if (state[i + n * (n - 1)] == 0)
            {
                if (cnt == 0)
                {
                    state[i + n * (n - 1)] = 1;
                    break;
                }
                cnt--;
            }
        }
    }
    // Set goal_state
    set_goal(state);
    node.set_state(state);
    state[node.find_one()] = 0;
    // Set starting element
    cnt = 0;
    for (int i{}; i < n; i++)
    {
        if (state[i] == 0)
        {
            cnt++;
        }
    }
    if (cnt == 0)
    {
        state[rand() % n] = 1;
    }
    else
    {
        cnt = rand() % cnt;
        for (int i{}; i < n; i++)
        {
            if (state[i] == 0)
            {
                if (cnt == 0)
                {
                    state[i] = 1;
                    break;
                }
                cnt--;
            }
        }
    }
    node.set_state(state);
    return std::make_shared<Maze::Node>(node);
}

std::shared_ptr<Maze::Node> Maze::make_random_maze(int attemps){
    auto root_node = std::make_shared<Maze::Node>(n);
    std::deque<std::shared_ptr<Maze::Node>> sol;
    root_node = make_random_maze();
    sol = breadth_first_search(root_node, 100, false);
    for (int i{}; i < attemps; i++){
        std::cout << "Attemp >> " << i << std::endl;
        if (sol.size() > 0){
            std::cout << BOLDMAGENTA << ">> A solvable maze found! <<\n";
            break;
        }
        else{
            std::cout << BOLDRED << "Not solvable!\n";
            root_node->show();
            root_node = make_random_maze();
            sol = breadth_first_search(root_node, 100, false);
        }
    }
    return root_node;
}