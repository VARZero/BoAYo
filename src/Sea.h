#include <map>
#include <mutex>
#include <thread>
#include <string>

float Px, Py, Pz; // 현재 위치. 기본은 (0, (키), 0) 으로 고정되고 

// 스크린 정보
class Screen_Info{
    private:
        int ID; // 스크린 아이디
        std::string NAME; // 스크린 이름
        float X, Y, Z; // 스크린이 위치하는 좌표
        float LR, UD;
        float height, Width;
};