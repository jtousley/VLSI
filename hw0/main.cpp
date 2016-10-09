#include "avl.h"

#define INFILE_NAME "input.txt"
#define OUTFILE_NAME "Tousley-A01908436.txt"


void print_menu();
void print_write_string(std::string, std::ofstream&);
int getInt(std::string line);

int main()
{
std::ifstream fin;
std::ofstream fout;
int insertion_value, deletion_value, search_value, traverse_value;
char input;
std::string line;
std::stringstream output_ss;
avlTree::avlTree<int> TREE;
std::shared_ptr<node::treeNode<int>> node = nullptr;

fout.open(OUTFILE_NAME);
if(!fout.is_open())
{
    std::cout << "Error opening file: " << OUTFILE_NAME << std::endl;
    exit(1);
}

print_menu();
std::getline(std::cin, line);
input = line[0];
while(input != 'q')
{
    input = input - '0';
    switch(input)
    {
        case 1:
        //delete existing tree
        TREE.delete_tree();

        //open file
        fin.open(INFILE_NAME);
        if(!fin.is_open())
        {
            output_ss << "Error opening file: " << INFILE_NAME << std::endl;
            print_write_string(output_ss.str(), fout);
            exit(1);
        }

        //create new tree
        output_ss << "Create Tree: ";
        while(std::getline(fin, line))
        {
            if(line == "") { break; }
            insertion_value = atoi(line.c_str());
            TREE.insert(insertion_value);
        }
        //close file
        fin.close();

        output_ss << TREE.traverse_pre_order() << std::endl;
        print_write_string(output_ss.str(), fout);
        output_ss.str(std::string());
        break;

        case 2:
        std::cout << "Insert (-1 is invalid): ";
        std::getline(std::cin, line);
        if(line == ""){ break; }
        insertion_value = getInt(line);
        if(insertion_value == -1){ break; }

        TREE.insert(insertion_value);
        output_ss << "Insert value: " << insertion_value << std::endl;
        output_ss << "Resulting state: ";
        output_ss << TREE.traverse_pre_order() << std::endl;
        print_write_string(output_ss.str(), fout);
        output_ss.str(std::string());
        break;

        case 3:
        std::cout << "Delete (-1 is invalid): ";
        std::getline(std::cin, line);
        if(line == ""){ std::cout << "Invalid value, please input a value\n"; break; }
        deletion_value = getInt(line);
        if(deletion_value == -1){ std::cout << "Invalid value, please use a number\n"; break; }

        if(TREE.is_empty())
        {
            output_ss << "Node cannot be deleted. Empty tree!\n";
        }
        else
        {
            if(TREE.remove(deletion_value))
            {
                output_ss << "Delete value: " << deletion_value << std::endl;
            }
            else
            {
                output_ss << "Node cannot be found. Deletion cannot be performed\n";
            }
        }
        output_ss << "Resulting state: ";
        output_ss << TREE.traverse_pre_order() << std::endl;
        print_write_string(output_ss.str(), fout);
        output_ss.str(std::string());
        break;

        case 4:
        std::cout << "Search (-1 is invalid): ";
        std::getline(std::cin, line);
        if(line == ""){ std::cout << "Invalid value, please input a value\n"; break; }
        search_value = getInt(line);
        if(search_value == -1){ break; }

        node = TREE.search(search_value);
        if(node == nullptr)
        {
            output_ss << "Search: Node cannot be found.\n";
        }
        else
        {
            output_ss << "Search: Found node at height: " << node::height(node) << std::endl;
        }
        print_write_string(output_ss.str(), fout);
        output_ss.str(std::string());
        break;

        case 5:
        std::cout 
            << "\ti. Pre_order\n"
            << "\tii. Post_order\n"
            << "\tiii. In_order\n"
            << "Choose: ";
        std::getline(std::cin, line);
        if(line == ""){ break; }
        traverse_value = getInt(line);
        if(traverse_value == -1){ break; }
        switch(traverse_value)
        {
            case 1:
            output_ss << "Pre order traversal: ";
            output_ss << TREE.traverse_pre_order() << std::endl;
            break;
            case 2:
            output_ss << "Post order traversal: ";
            output_ss << TREE.traverse_post_order() << std::endl;
            break;
            case 3:
            output_ss << "In order traversal: ";
            output_ss << TREE.traverse_in_order() << std::endl;
            break;
            default:
            output_ss << "Invalid value, please choose an option {1,3}\n";
            break;
        }
        print_write_string(output_ss.str(), fout);
        output_ss.str(std::string());
        break;

        case 6:
        TREE.delete_tree();
        output_ss << "Delete Tree: ";
        output_ss << "Tree deleted\n";
        print_write_string(output_ss.str(), fout);
        output_ss.str(std::string());
        break;

        case 7:
        line = TREE.check_balance();
        output_ss << "Check Balance: " << line << std::endl;
        print_write_string(output_ss.str(), fout);
        output_ss.str(std::string());
        break;

        default:
        std::cout << "Invalid\n";
        break;
    } //switch
print_menu();
std::getline(std::cin, line);
input = line[0];
} // while

output_ss << "Program terminated\n";
print_write_string(output_ss.str(), fout);
fout.close();
    
return 0;
}

void print_menu()
{
     std::cout 
          << "*** MENU ***\n"
          << "Choose an option to be performed:\n"
               << "\t1. Create_Tree\n"
               << "\t2. Insertion\n"
               << "\t3. Deletion\n"
               << "\t4. Search\n"
               << "\t5. Traversal\n"
               << "\t6. Delete_Tree\n"
               << "\t7. Check_Balance\n"
          << "Input: ";
}

void print_write_string(std::string s, std::ofstream& fout)
{
    std::cout << s;
    fout << s;
}

int getInt(std::string line)
{
    int toRet = -1;
    try
    {
        toRet = std::stoi(line);
    }
    catch(std::invalid_argument){}

    return toRet;
}
