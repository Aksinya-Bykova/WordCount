#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

/* проще посчитать сразу все характеристики каждого файла, в один проход */

struct params {
    int str;
    int word;
    int ch;
    int size;
};

params calculate(std::string filepath) {
    std::ifstream inp(filepath, std::ios::binary);

    params p;
    p.str = 0, p.word = 0, p.ch = 0, p.size = 0;

    char temp;
    bool new_word = true;
    bool new_str = true;

    while (inp.get(temp)) {
        if (std::isspace(temp)) {
            new_word = true;
        }
        if (temp == '\n') {
            new_str = true;
        }
        if (isprint(temp)) {
            p.ch++;
            if (new_str) {
                p.str++;
                new_str = 0;
            }
            if (new_word) {
                p.word++;
                new_word = 0;
            }
        }
    }
    p.size = std::filesystem::file_size(filepath);
    inp.close();

    return p;
}

int main(int argc, char** argv)
{
    std::vector <std::string> flags;
    std::vector <std::string> files;

    for (int i = 1; i < argc; i++) {
        std::string s = argv[i];
        if (s[0] == '-') {
            flags.push_back(s);
        }
        else {
            files.push_back(s);
        }
    }

    /* для каждого файла считаем все параметры одним проходом
       под каждый запрос мы не считаем все параметры заново
       если миллион раз попросили посчитать буквы, миллион раз
       выведем буквы, полученные из t один раз */

    for (int i = 0; i < files.size(); i++) {
        params t = calculate(files[i]);

        for (int j = 0; j < flags.size(); j++) {
            if (flags[j] == "-l") {
                std::cout << t.str << " ";
            }
            if (flags[j] == "-w") {
                std::cout << t.word << " ";
            }
            if (flags[j] == "-m") {
                std::cout << t.ch << " ";
            }
            if (flags[j] == "-c") {
                std::cout << t.size << " ";
            }
        }
    }

    return 0;
}