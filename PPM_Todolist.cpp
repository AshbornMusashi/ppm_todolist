#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
using std::string;
using std::vector;

// thanks to chatgpt now I can cover both windows and linux users
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

// PPM image pixel struct
struct Pixel
{
    int r, g, b;
};

// Function prototypes
void parsePPMImage();
void runTodoList();

int main()
{
    int optionUserChose;
    std::cout << "--Menu--\n";
    std::cout << "1. Image Parser\n"
              << "2. To-Do List\n";
    std::cin >> optionUserChose;

    if (optionUserChose == 1)
    {
        parsePPMImage();
    }
    else if (optionUserChose == 2)
    {
        runTodoList();
    }
    else
    {
        std::cerr << "Invalid option selected.\n";
        return 1;
    }

    return 0;
}

// Function to parse a PPM (P3) image
void parsePPMImage()
{
    string filename;
    std::cout << "Enter the name of the PPM file (e.g., image.ppm): ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file.\n";
        return;
    }

    string format;
    int width, height, maxColor;
    file >> format;

    if (format != "P3")
    {
        std::cerr << "Error: Unsupported format (expected P3).\n";
        return;
    }

    file >> width >> height >> maxColor;

    vector<Pixel> pixels;
    for (int i = 0; i < width * height; ++i)
    {
        Pixel p;
        file >> p.r >> p.g >> p.b;
        pixels.push_back(p);
    }

    std::cout << "\nSuccessfully loaded PPM image!\n";
    std::cout << "Dimensions: " << width << " x " << height << "\n";
    std::cout << "Total Pixels: " << pixels.size() << "\n";
    std::cout << "Max Color Value: " << maxColor << "\n";
}

// Function to manage the To-Do List
void runTodoList()
{
    const int MAX_TASKS = 100;
    float version = 1.0;
    string tasks[MAX_TASKS];
    int taskCount = 0;
    int userChoice;

    std::cout << "--Welcome to my To-Do-List-- v" << std::fixed << std::setprecision(1)
              << version << "\n";
    do
    {
        std::cout << "\n1. Add Task\n"
                  << "2. View Tasks\n"
                  << "3. Mark Task as Done\n"
                  << "4. Exit\n";
        std::cout << "Enter option number: ";
        std::cin >> userChoice;
        std::cout << string(30, '*') << "\n";

        switch (userChoice)
        {
        case 1:
        {
            if (taskCount >= MAX_TASKS)
            {
                std::cout << "Task list is full.\n";
                break;
            }
            std::cin.ignore(); // clear buffer
            string taskName;
            std::cout << "Enter task name: ";
            std::getline(std::cin, taskName);
            tasks[taskCount++] = taskName;
            system("cls"); // or "clear" for non-Windows systems
            break;
        }
        case 2:
            if (taskCount == 0)
            {
                std::cout << "There are no items in the list.\n";
            }
            else
            {
                for (int i = 0; i < taskCount; ++i)
                {
                    std::cout << (i + 1) << ". " << tasks[i] << "\n";
                }
            }
            break;
        case 3:
            if (taskCount == 0)
            {
                std::cout << "There are no items to mark as done.\n";
            }
            else
            {
                for (int i = 0; i < taskCount; ++i)
                {
                    std::cout << (i + 1) << ". " << tasks[i] << "\n";
                }
                int taskIndex;
                std::cout << "Enter number for task to mark as done: ";
                std::cin >> taskIndex;
                if (taskIndex < 1 || taskIndex > taskCount)
                {
                    std::cout << "Invalid task number.\n";
                }
                else
                {
                    std::cout << "Task '" << tasks[taskIndex - 1] << "' marked as done.\n";
                    for (int i = taskIndex - 1; i < taskCount - 1; ++i)
                    {
                        tasks[i] = tasks[i + 1];
                    }
                    taskCount--;
                    system("cls"); // or "clear"
                }
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