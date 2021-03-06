#include <map>
#include <vector>
#include <mutex>
#include <thread>
#include <string>
#include <netinet/in.h>

extern float Px, Py, Pz; // 현재 위치. 기본은 (0, (키), 0) 으로 고정되고 
extern int PLR, PUD; // 현재 시점의 각도

extern std::map <int, Screen_Info*> Screen_List;

// 스크린 정보
class Screen_Info{
    private:
        int ID = NULL; // 스크린 아이디
        sockaddr_in Client_Addr; // 스크린을 제어하는 클라이언트의 주소정보
        std::string NAME; // 스크린 이름
        float X, Y, Z; // 스크린이 위치하는 좌표 (좌표는 미터에 대응됩니다.)
        float LR, UD; // 좌우 / 상하 각도(0~6[360])
        int height, Width; // 높이 너비 (센치미터에 대응됩니다.)
    public:
        size_t components; // 생성된 컴포넌트 갯수 (삭제되어도 차감되지 않습니다.)
        std::map <int, Component_Info*> ComponentsList; // 컴포넌트 리스트
        std::map <int, std::string> EventList; // 이벤트 리스트 (창 크기 조절이나 컴포넌트에 포커스 되지 않은 상태에서 키보드 입력을 처리합니다.)
        Component_Info* focus; // 컴포넌트가 선택되어 있는 상태를 포커스라 합니다. 포커스 여부는 클릭 이벤트에 의해 지정되고, 이벤트로 포커스를 다른 대상으로 이동할것인지 처리함

        Screen_Info(std::string getname, float x, float y, float z,
         int lr, int ud, int h, int w, int* outputID);
        ~Screen_Info();
};

class Component_Info{
    private:
        int cID; // 컴포넌트 아이디 
        std::string NAME; // 컴포넌트 이름
        int X, Y; // 스크린 위에서의 컴포넌트 위치
        int Height, Width, Depth; // 컴포넌트 높이, 너비, 깊이(바깥쪽, 안쪽)
        Screen_Info* parants; // 스크린 정보
        char* RGBAList; // 색, 투명도 픽셀 정보 리스트
        std::map <int, std::string> EventList; // 이벤트 리스트 (클릭이나 타이머, 포커스된 상태에서 키보드 입력을 처리합니다.)
    public:
        Component_Info(std::string inName, int x, int y,
         int h, int w, int d, Screen_Info* p, int *compID);
        void Event_Create(); // 이벤트 생성
        ~Component_Info();
};

// 3D 모델을 위한 버텍스 정보 구조체
typedef struct vertex{
    float x; float y; float z; float a;
}VX;

// 모델 (3D 모델)
class Model3D{
    private:
        int ID; // 모델 아이디
        std::string NAME; // 모델 이름
        float X, Y, Z; // 모델이 존재하는 좌표
        float LR, UD, PR; // 회전되어 있는 정도 (Y축, X축, Z축 회전)
        std::vector <unsigned long, VX> Vertex; // 꼭짓점 좌표들
        std::map <int, std::string> EventList; // 이벤트 리스트 
};