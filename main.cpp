#include <iostream>
#include <filesystem>
#include <string>
#include <windows.h>
#include <commdlg.h>

namespace fs = std::filesystem;

std::string checking_if_kindle_is_connected();
std::string open_file_dialog();


int main()
{
    std::string kindle_path = checking_if_kindle_is_connected();
    if(kindle_path != "")
    {

        std::cout << "Welcome to Auto Ebook Kindle Uploader!\n1. Add a book \n2. Exit" << std::endl;
        while(true)
        {
            int choice {};
            std::cout << "Enter choice: ";
            std::cin >> choice;

            if(choice==1)
            {
                std::string book_path = open_file_dialog();
                if(book_path != "")
                {
                    std::string only_book_filename = fs::path(book_path).filename().string();
                    std::string full_path = kindle_path + "\\" + only_book_filename;
                    fs::copy_file(book_path, full_path, fs::copy_options::overwrite_existing);
                    std::cout << "Book added to Kindle." << std::endl;
                }
                else
                std::cout << "No book selected." << std::endl;
            }
            else if(choice==2) {
                std::cout << "Bye!"; 
                break;
            }
            else std::cout << "Invalid choice." << std::endl;
        }
    }
    else
    {
        std::cout << "Kindle is not connected, connect your kindle and try again!";
    }
    return 0;
}

std::string checking_if_kindle_is_connected()
{
    for(char i=65; i < 91; i++)
    {
        std::string full_path = std::string(1,i) + ":\\documents\\Downloads";
        if(fs::exists(full_path))
        {
            return full_path;
        }
    }
    return "";
}

std::string open_file_dialog()
{
    OPENFILENAMEA f = {0};
    f.lStructSize = sizeof(OPENFILENAMEA);

    f.lpstrFilter = "MOBI files\0*.mobi\0\0";
    f.lpstrTitle  = "Choose the book";

    char buff[MAX_PATH] = {0};
    f.nMaxFile = sizeof(buff);
    f.lpstrFile = buff;

    if(GetOpenFileNameA(&f)) return std::string(buff);
    return "";
}