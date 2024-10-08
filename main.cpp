#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

// Cart structure to hold items and their quantity
struct CartItem
{
    int barCode;
    int quantity;
};

// Function prototypes
void displayMenu();
void displayEmployeeMenu();
void displaySales();
void displayStock();
void addToCart(std::vector<CartItem> &cart);
void viewCart(const std::vector<CartItem> &cart);
void checkout(std::vector<CartItem> &cart);
void returnItem();
void employeePanel();
bool authenticateEmployee();

// Add or remove items (employee panel actions)
void addItem();
void removeItem();

#include <algorithm>
#include <cctype>

// Function to trim whitespace from both ends of a string
std::string trim(const std::string &s)
{
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start))
    {
        start++;
    }

    auto end = s.end();
    do
    {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

// Function to execute Python command
std::string executePythonCommand(const std::string &command)
{
    char buffer[128];
    std::string result = "";

    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        std::cerr << "Failed to run Python script" << std::endl;
        return "";
    }

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        result += buffer;
    }

    pclose(pipe);
    return result;
}

int main()
{
    std::vector<CartItem> cart;
    int choice;

    do
    {
        displayMenu();
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            displayStock();
            break;
        case 2:
            addToCart(cart);
            break;
        case 3:
            viewCart(cart);
            break;
        case 4:
            checkout(cart);
            break;
        case 5:
            returnItem();
            break;
        case 6:
            displaySales();
            break;
        case 7:
            if (authenticateEmployee())
            {
                employeePanel();
            }
            else
            {
                std::cout << "Incorrect password. Access denied." << std::endl;
            }
            break;
        case 8:
            std::cout << "Exiting... Thank you!" << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    } while (choice != 8);

    return 0;
}

// Display main menu
void displayMenu()
{
    std::cout << "\n=== Main Menu ===" << std::endl;
    std::cout << "1. List items in stock" << std::endl;
    std::cout << "2. Add item to cart" << std::endl;
    std::cout << "3. View cart and checkout" << std::endl;
    std::cout << "4. Checkout" << std::endl;
    std::cout << "5. Return items" << std::endl;
    std::cout << "6. View sales (items with promotions)" << std::endl;
    std::cout << "7. Employee panel" << std::endl;
    std::cout << "8. Exit" << std::endl;
    std::cout << "Choose an option: ";
}

// Authenticate employee with a password (set to "1234" for now)
bool authenticateEmployee()
{
    std::string password;
    std::cout << "Enter employee password: ";
    std::cin >> password;

    return password == "1234";
}

// Employee panel menu
void employeePanel()
{
    int choice;
    do
    {
        displayEmployeeMenu();
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            addItem();
            break;
        case 2:
            removeItem();
            break;
        case 3:
            std::cout << "Exiting employee panel..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    } while (choice != 3);
}

// Display employee menu
void displayEmployeeMenu()
{
    std::cout << "\n=== Employee Panel ===" << std::endl;
    std::cout << "1. Add item to inventory" << std::endl;
    std::cout << "2. Remove item from inventory" << std::endl;
    std::cout << "3. Exit employee panel" << std::endl;
    std::cout << "Choose an option: ";
}

// Add item to inventory
void addItem()
{
    std::string itemName, promotions;
    double price;
    int stockCount;

    std::cout << "Enter item name: ";
    std::cin.ignore(); // Ignore newline character left by std::cin
    std::getline(std::cin, itemName);
    std::cout << "Enter item price: ";
    std::cin >> price;
    std::cout << "Enter promotions (or 'none'): ";
    std::cin.ignore();
    std::getline(std::cin, promotions);
    std::cout << "Enter stock count: ";
    std::cin >> stockCount;

    std::string command = "python3 DatabaseManager.py insert_item '" + itemName + "' " +
                          std::to_string(price) + " '" + promotions + "' " + std::to_string(stockCount);
    executePythonCommand(command);
    std::cout << "Item added successfully!" << std::endl;
}

// Remove item from inventory
void removeItem()
{
    int barCode;
    std::cout << "Enter BarCode of item to remove: ";
    std::cin >> barCode;

    // Corrected command: Remove 'inventory' from the arguments
    std::string command = "python3 /Users/jagrajgill/Desktop/CODE/CPP\\ Projects/Inventory\\ Management\\ System/DatabaseManager.py delete_item " + std::to_string(barCode);
    executePythonCommand(command);
    std::cout << "Item removed successfully!" << std::endl;
}

// Display all items in stock
void displayStock()
{
    std::cout << "\nItems in stock:" << std::endl;
    std::string command = "python3 /Users/jagrajgill/Desktop/CODE/CPP\\ Projects/Inventory\\ Management\\ System/DatabaseManager.py fetch_all inventory";
    std::string result = executePythonCommand(command);
    std::cout << result;
}

// Display all items on sale (with promotions)
void displaySales()
{
    std::cout << "\nItems on sale (with promotions):" << std::endl;
    std::string command = "python3 /Users/jagrajgill/Desktop/CODE/CPP\\ Projects/Inventory\\ Management\\ System/DatabaseManager.py fetch_promotional inventory";
    std::string result = executePythonCommand(command);
    std::cout << result;
}

// Add item to cart
void addToCart(std::vector<CartItem> &cart)
{
    int barCode, quantity;
    std::cout << "Enter the BarCode of the item to add: ";
    std::cin >> barCode;
    std::cout << "Enter quantity: ";
    std::cin >> quantity;

    // Construct the command without 'inventory'
    std::string command = "python3 DatabaseManager.py check_stock " + std::to_string(barCode) + " " + std::to_string(quantity);
    std::string result = executePythonCommand(command);

    // Debug: Print the result from Python
    std::cout << "DEBUG: check_stock returned: '" << result << "'" << std::endl;

    // Trim the result and convert to lowercase for comparison
    std::string trimmed_result = trim(result);
    std::transform(trimmed_result.begin(), trimmed_result.end(), trimmed_result.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });

    if (trimmed_result == "true")
    {
        CartItem item = {barCode, quantity};
        cart.push_back(item);
        std::cout << "Item added to cart!" << std::endl;
    }
    else
    {
        std::cout << "Not enough stock for this item." << std::endl;
    }
}

// View cart and perform checkout
void viewCart(const std::vector<CartItem> &cart)
{
    std::cout << "\nYour cart:" << std::endl;
    for (const auto &cartItem : cart)
    {
        std::string command = "python3 /Users/jagrajgill/Desktop/CODE/CPP\\ Projects/Inventory\\ Management\\ System/DatabaseManager.py fetch_item inventory " + std::to_string(cartItem.barCode);
        std::string result = executePythonCommand(command);
        std::cout << result;
        std::cout << "Quantity: " << cartItem.quantity << std::endl;
    }
}

// Checkout process
void checkout(std::vector<CartItem> &cart)
{
    for (const auto &cartItem : cart)
    {
        std::string command = "python3 /Users/jagrajgill/Desktop/CODE/CPP\\ Projects/Inventory\\ Management\\ System/DatabaseManager.py update_stock inventory " + std::to_string(cartItem.barCode) + " -" + std::to_string(cartItem.quantity);
        executePythonCommand(command);
    }
    cart.clear();
    std::cout << "Checkout complete! Thank you for your purchase." << std::endl;
}

// Return an item after purchase
void returnItem()
{
    int barCode, quantity;
    std::cout << "Enter the BarCode of the item to return: ";
    std::cin >> barCode;
    std::cout << "Enter quantity to return: ";
    std::cin >> quantity;

    std::string command = "python3 /Users/jagrajgill/Desktop/CODE/CPP\\ Projects/Inventory\\ Management\\ System/DatabaseManager.py update_stock inventory " + std::to_string(barCode) + " " + std::to_string(quantity);
    executePythonCommand(command);
    std::cout << "Return processed!" << std::endl;
}
