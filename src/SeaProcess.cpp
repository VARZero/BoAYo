#include "Sea.h"
#include <random>

std::map <int, Screen_Info*> Screen_List;

// 스크린 부분
Screen_Info::Screen_Info(std::string getname, float x, float y, float z,
 int lr, int ud, int h, int w, int* outputID){
    NAME = getname;
    X = x; Y = y; Z = z; LR = (float) lr/6; UD = (float) ud/6;
    height = h; Width = w;
    std::random_device rdidm;
    std::mt19937 gen(rdidm());
    do{
        std::uniform_int_distribution<int> rdidv(1000000,9999999);
        ID = rdidv(rdidm);
    }while(Screen_List.end() != Screen_List.find(ID));
    Screen_List.insert({ID,this});
    *outputID = ID;
}

Screen_Info::~Screen_Info(){
    Screen_List.erase(ID);
}

// 컴포넌트 부분
Component_Info::Component_Info(std::string inName, int x, int y,
 int h, int w, int d, Screen_Info* p){
    NAME = inName;
    X = x; Y = y; Height = h; Width = w; Depth = d;
    parants = p;
    cID = parants->components++;
    parants->ComponentsList.insert({cID,this});
}

Component_Info::~Component_Info(){
    parants->ComponentsList.erase(cID);
}