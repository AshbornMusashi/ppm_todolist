#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>

//thanks to chatgpt now I can cover both windows and linux users
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

using std::string;
using std::vector;

// PPM image pixel struct
struct Pixel {
    int r, g, b;
};

// Function prototypes
void parsePPMImage();
void runTodoList();

int main() {
    int optionUserChose;
    std::cout << "--Menu--\n";
    std::cout << "1. Image Parser\n"
              << "2. To-Do List\n";
    std::cin >> optionUserChose;

    if (optionUserChose == 1) {
        parsePPMImage();
    } else if (optionUserChose == 2) {
        runTodoList();
    } else {
        std::cerr << "Invalid option selected.\n";
        return 1;
    }

    return 0;
}

// Function to parse a PPM (P3) image
void parsePPMImage() {
    string filename;
    std::cout << "Enter the name of the PPM file (e.g., image.ppm): ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file.\n";
        return;
    }

    string format;
    int width, height, maxColor;
    file >> format;

    if (format != "P3") {
        std::cerr << "Error: Unsupported format (expected P3).\n";
        return;
    }

    file >> width >> height >> maxColor;

    vector<Pixel> pixels;
    for (int i = 0; i < width * height; ++i) {
        Pixel p;
        file >> p.r >> p.g >> p.b;
        pixels.push_back(p);
    }

    std::cout << "\nSuccessfully loaded PPM image!\n";
    std::cout << "Dimensions: " << width << " x " << height << "\n";
    std::cout << "Total Pixels: " << pixels.size() << "\n";
    std::cout << "Max Color Value: " << maxColor << "\n";

    std::cout << "\nPreview of first 5 pixels:\n";
    for (int i = 0; i < 5 && i < pixels.size(); ++i) {
        std::cout << "(" << pixels[i].r << ", " << pixels[i].g << ", " << pixels[i].b << ")\n";
    }
}

// Function to manage the To-Do List
void runTodoList() {
    vector<string> tasks;
    int userChoice;
    float version = 1.0;

    std::cout << "--Welcome to my To-Do-List-- v" << std::fixed << std::setprecision(1)
              << version << "\n";

    do {
        std::cout << "\n1. Add Task\n"
                  << "2. View Tasks\n"
                  << "3. Mark Task as Done\n"
                  << "4. Exit\n";
        std::cout << "Enter option number: ";
        std::cin >> userChoice;
        std::cout << string(30, '*') << "\n";

        switch (userChoice) {
            case 1: {
                std::cin.ignore(); // clear buffer
                string taskName;
                std::cout << "Enter task name: ";
                std::getline(std::cin, taskName);
                tasks.push_back(taskName);
                system(CLEAR);
                break;
            }
            case 2:
                if (tasks.empty()) {
                    std::cout << "There are no items in the list.\n";
                } else {
                    for (size_t i = 0; i < tasks.size(); ++i) {
                        std::cout << (i + 1) << ". " << tasks[i] << "\n";
                    }
                }
                break;
            case 3:
                if (tasks.empty()) {
                    std::cout << "There are no items to mark as done.\n";
                } else {
                    for (size_t i = 0; i < tasks.size(); ++i) {
                        std::cout << (i + 1) << ". " << tasks[i] << "\n";
                    }
                    int taskIndex;
                    std::cout << "Enter number for task to mark as done: ";
                    std::cin >> taskIndex;
                    if (taskIndex < 1 || taskIndex > tasks.size()) {
                        std::cout << "Invalid task number.\n";
                    } else {
                        std::cout << "Task '" << tasks[taskIndex - 1] << "' marked as done.\n";
                        tasks.erase(tasks.begin() + taskIndex - 1);
                    }
                    system(CLEAR);
                }
                break;
            case 4:
                std::cout << "\nThank you for using the To-Do List!\n";
                break;
            default:
                std::cout << "\nInvalid input. Please enter a valid option.\n";
                break;
        }
    } while (userChoice != 4);
}