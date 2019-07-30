#include <sstream>
#include <iostream>

//为啥会Segmentation fault？在vs调试没啥问题？

std::istringstream& get_istringstream(){
    static thread_local std::istringstream stream;
    stream.clear();//记得clear..
    // stream.str("");
    return stream;
}

template <typename T>
inline T from_string(const std::string s){
    auto& iss = get_istringstream();
    iss.str(s);
    T result;
    iss >> result;
    return result;
}

int main(){
    //其实可以用stoi的...方便快捷 👍
    std::string xi = "1211";
    int val = from_string<int>(xi);
    std::cout<<val<<' ';

    float fval = from_string<float>("12.11");
    std::cout<<fval<<' ';
    
    return 0;
}