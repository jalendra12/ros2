#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <thread>
#include <chrono>

class ControlledDFS {
public:
    ControlledDFS() : pause_flag(false), stop_flag(false) {}

    void dfs(int node, const std::unordered_map<int, std::vector<int>>& graph, std::unordered_set<int>& visited) {
        // Check if we need to stop the DFS
        if (stop_flag) {
            std::cout << "DFS stopped." << std::endl;
            return;
        }

        // Check if we need to pause the DFS
        if (pause_flag) {
            std::cout << "DFS paused. Waiting to resume..." << std::endl;
            while (pause_flag) {
                std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate pause with a sleep
            }
            std::cout << "DFS resumed." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Continue with DFS if not stopped or paused
        if (visited.find(node) == visited.end()) {
            std::cout << "Visiting node " << node << std::endl;
            visited.insert(node);

            for (int neighbor : graph.at(node)) {
                dfs(neighbor, graph, visited);
            }
        }
    }

    void pause() {
        pause_flag = true;
    }

    void resume() {
        pause_flag = false;
    }

    void stop() {
        stop_flag = true;
    }

private:
    bool pause_flag;
    bool stop_flag;
};

int main() {
    // Example graph represented as an adjacency list
    std::unordered_map<int, std::vector<int>> graph = {
        {0, {1, 2}},
        {1, {0, 3, 4}},
        {2, {0, 5}},
        {3, {1}},
        {4, {1}},
        {5, {2,6}},
        {6, {5,7}},
        {7, {6}}
    };

    ControlledDFS dfsController;
    std::unordered_set<int> visited;

    // Start DFS in a separate thread to simulate control
    std::thread dfsThread([&]() {
        std::cout << "Starting DFS" << std::endl;
        dfsController.dfs(0, graph, visited);
    });
    std::this_thread::sleep_for(std::chrono::seconds(2));
    dfsController.pause();
    while(1){
        int a;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout<<"Input Command :";
        std::cin>>a;
        if(a==1)dfsController.resume();
        else if(a==2)dfsController.stop();
        else dfsController.pause();
    }
    // Wait for the DFS thread to finish
    dfsThread.join();

    return 0;
}
