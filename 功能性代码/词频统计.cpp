//
//文本查询程序
//1. 用户制定文本文件
//2. 用户输入需要查询得单词，程序返回：1）该单词的出现次数。2）该单词出现的行号

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <fcntl.h>
#include <map>
#include <utility>

// using namespace std;

class Word{
private:
    int count_;
    std::set<int> list_;
    
public:
    
    Word()
    :count_(0) {};
    
    void plus(int line_number){
        count_++;
        list_.insert(line_number);
    }
    
    const int & get_count() { return count_;}
    const std::set<int> & get_list() { return list_;}
    
};


class TextFinder{
private:
    std::map<std::string, Word> words_;
    std::vector<std::string> lines_;
    std::ifstream file_;
    
    void input_words_();
    void trim(std::string & word);
    
public:
    TextFinder(const std::string & filepath){
        lines_.push_back("");          //行数从1开始，把0填了先～～～～
        file_.open(filepath.c_str());
        input_words_();
    }
    
    void find_word(const std::string & word){
        Word temp(words_[word]);
        std::cout << "occurance:" << temp.get_count() << std::endl;
        
        for (int  linenumber : temp.get_list()){
            std::cout << lines_[linenumber] << std::endl;
        }
    }
    
};


inline void TextFinder::input_words_(){
    std::string temp_string, temp_word;
    Word word;
    int line_number = 1;
    
    while (getline(file_, temp_string)) {
        lines_.push_back(temp_string);
        std::istringstream single_line(temp_string);    //这里流变量怎么移到循环体外面去？
        
        while (single_line >> temp_word) {
            trim(temp_word);
            if (temp_word.length() == 0) continue;
            words_[temp_word].plus(line_number);        //这里利用了map下标访问的特性
        }
        
        line_number++;
    }
}


inline void TextFinder::trim(std::string & word){
    for (auto it = word.begin(); it != word.end(); ++it){
        if (isupper(*it))
            *it += 32;
        if (!isalpha(*it))
            it = word.erase(it) - 1;    //对于迭代器的实效一定要重视！
    }
    
}



int main(int argc, const char * argv[])
{
    std::string path(argv[1]);
    
    
    TextFinder test(path);
    
    std::string qqq;
    while (std::cin >> qqq){
        
        test.find_word(qqq);
        
    }
    
    
    return 0;
}

